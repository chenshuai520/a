#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import numpy as np
import torch
import torchvision
import torchvision.transforms as transforms
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.utils.tensorboard import SummaryWriter
import matplotlib.pyplot as plt

# REF [site] >> https://pytorch.org/tutorials/intermediate/tensorboard_tutorial.html
def tensorboard_tutorial():
	# Transforms.
	transform = transforms.Compose([transforms.ToTensor(), transforms.Normalize((0.5,), (0.5,))])

	# Datasets.
	trainset = torchvision.datasets.FashionMNIST('./data', download=True, train=True, transform=transform)
	testset = torchvision.datasets.FashionMNIST('./data', download=True, train=False, transform=transform)

	# Dataloaders.
	trainloader = torch.utils.data.DataLoader(trainset, batch_size=4, shuffle=True, num_workers=2)
	testloader = torch.utils.data.DataLoader(testset, batch_size=4, shuffle=False, num_workers=2)

	# Constant for classes.
	classes = ('T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat', 'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle Boot')

	# Helper function to show an image (used in the 'plot_classes_preds' function below)
	def matplotlib_imshow(img, one_channel=False):
		if one_channel:
			img = img.mean(dim=0)
		img = img / 2 + 0.5  # Unnormalize.
		npimg = img.numpy()
		if one_channel:
			plt.imshow(npimg, cmap='Greys')
		else:
			plt.imshow(np.transpose(npimg, (1, 2, 0)))

	#--------------------
	class Net(nn.Module):
		def __init__(self):
			super(Net, self).__init__()
			self.conv1 = nn.Conv2d(1, 6, 5)
			self.pool = nn.MaxPool2d(2, 2)
			self.conv2 = nn.Conv2d(6, 16, 5)
			self.fc1 = nn.Linear(16 * 4 * 4, 120)
			self.fc2 = nn.Linear(120, 84)
			self.fc3 = nn.Linear(84, 10)

		def forward(self, x):
			x = self.pool(F.relu(self.conv1(x)))
			x = self.pool(F.relu(self.conv2(x)))
			x = x.view(-1, 16 * 4 * 4)
			x = F.relu(self.fc1(x))
			x = F.relu(self.fc2(x))
			x = self.fc3(x)
			return x

	net = Net()

	criterion = nn.CrossEntropyLoss()
	optimizer = optim.SGD(net.parameters(), lr=0.001, momentum=0.9)

	#--------------------
	# Setup TensorBoard.

	# Default 'log_dir' is 'runs' - we'll be more specific here.
	writer = SummaryWriter('runs/fashion_mnist_experiment_1')

	#--------------------
	# Write to TensorBoard.

	# Get some random training images.
	dataiter = iter(trainloader)
	images, labels = dataiter.next()

	# Create grid of images.
	img_grid = torchvision.utils.make_grid(images)

	# Show images.
	matplotlib_imshow(img_grid, one_channel=True)

	# Write to tensorboard.
	writer.add_image('four_fashion_mnist_images', img_grid)

	#--------------------
	# Inspect the model using TensorBoard.

	writer.add_graph(net, images)
	writer.close()

	#--------------------
	# Add a 'Projector' to TensorBoard.

	# Helper function.
	def select_n_random(data, labels, n=100):
		'''
		Selects n random datapoints and their corresponding labels from a dataset
		'''
		assert len(data) == len(labels)

		perm = torch.randperm(len(data))
		return data[perm][:n], labels[perm][:n]

	# Select random images and their target indices.
	images, labels = select_n_random(trainset.data, trainset.targets)

	# Get the class labels for each image.
	class_labels = [classes[lab] for lab in labels]

	# Log embeddings.
	features = images.view(-1, 28 * 28)
	writer.add_embedding(features, metadata=class_labels, label_img=images.unsqueeze(1))
	writer.close()

	#--------------------
	# Track model training with TensorBoard.

	# Helper functions.
	def images_to_probs(net, images):
		'''
		Generates predictions and corresponding probabilities from a trained
		network and a list of images
		'''
		output = net(images)
		# Convert output probabilities to predicted class.
		_, preds_tensor = torch.max(output, 1)
		preds = np.squeeze(preds_tensor.numpy())
		return preds, [F.softmax(el, dim=0)[i].item() for i, el in zip(preds, output)]

	def plot_classes_preds(net, images, labels):
		'''
		Generates matplotlib Figure using a trained network, along with images
		and labels from a batch, that shows the network's top prediction along
		with its probability, alongside the actual label, coloring this
		information based on whether the prediction was correct or not.
		Uses the "images_to_probs" function.
		'''
		preds, probs = images_to_probs(net, images)
		# Plot the images in the batch, along with predicted and true labels.
		fig = plt.figure(figsize=(12, 48))
		for idx in np.arange(4):
			ax = fig.add_subplot(1, 4, idx+1, xticks=[], yticks=[])
			matplotlib_imshow(images[idx], one_channel=True)
			ax.set_title('{0}, {1:.1f}%\n(label: {2})'.format(classes[preds[idx]], probs[idx] * 100.0, classes[labels[idx]]),
				color=('green' if preds[idx] == labels[idx].item() else 'red'))
		return fig

	running_loss = 0.0
	for epoch in range(1):  # Loop over the dataset multiple times.
		for i, data in enumerate(trainloader, 0):
			# Get the inputs; data is a list of [inputs, labels].
			inputs, labels = data

			# Zero the parameter gradients.
			optimizer.zero_grad()

			# Forward + backward + optimize.
			outputs = net(inputs)
			loss = criterion(outputs, labels)
			loss.backward()
			optimizer.step()

			running_loss += loss.item()
			if i % 1000 == 999:  # Every 1000 mini-batches...
				# Log the running loss.
				writer.add_scalar('training loss', running_loss / 1000, epoch * len(trainloader) + i)

				# Log a Matplotlib Figure showing the model's predictions on a random mini-batch.
				writer.add_figure('predictions vs. actuals', plot_classes_preds(net, inputs, labels), global_step=epoch * len(trainloader) + i)
				running_loss = 0.0
	print('Finished Training')

	#--------------------
	# Assess trained models with TensorBoard.

	# 1. gets the probability predictions in a test_size x num_classes Tensor.
	# 2. gets the preds in a test_size Tensor takes ~10 seconds to run.
	class_probs = []
	class_preds = []
	with torch.no_grad():
		for data in testloader:
			images, labels = data
			output = net(images)
			class_probs_batch = [F.softmax(el, dim=0) for el in output]
			_, class_preds_batch = torch.max(output, 1)

			class_probs.append(class_probs_batch)
			class_preds.append(class_preds_batch)

	test_probs = torch.cat([torch.stack(batch) for batch in class_probs])
	test_preds = torch.cat(class_preds)

	# Helper function.
	def add_pr_curve_tensorboard(class_index, test_probs, test_preds, global_step=0):
		'''
		Takes in a "class_index" from 0 to 9 and plots the corresponding
		precision-recall curve
		'''
		tensorboard_preds = test_preds == class_index
		tensorboard_probs = test_probs[:, class_index]

		writer.add_pr_curve(classes[class_index], tensorboard_preds, tensorboard_probs, global_step=global_step)
		writer.close()

	# Plot all the pr curves.
	for i in range(len(classes)):
		add_pr_curve_tensorboard(i, test_probs, test_preds)

def main():
	tensorboard_tutorial()

#--------------------------------------------------------------------

if '__main__' == __name__:
	main()

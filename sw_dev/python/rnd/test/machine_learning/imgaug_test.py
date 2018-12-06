#!/usr/bin/env python

# REF [site] >> https://github.com/aleju/imgaug

import os, sys
if 'posix' == os.name:
	swl_python_home_dir_path = '/home/sangwook/work/SWL_github/python'
else:
	swl_python_home_dir_path = 'D:/work/SWL_github/python'
sys.path.append(swl_python_home_dir_path + '/src')

#%%------------------------------------------------------------------
# Prepare dataset.

import numpy as np
from skimage import data
import imgaug as ia
from imgaug import augmenters as iaa
from swl.image_processing.util import load_images_by_pil, load_labels_by_pil
from swl.machine_learning.data_preprocessing import standardize_samplewise, standardize_featurewise

if 'posix' == os.name:
	#dataset_home_dir_path = '/home/sangwook/my_dataset'
	dataset_home_dir_path = '/home/HDD1/sangwook/my_dataset'
else:
	dataset_home_dir_path = 'D:/dataset'

def prepare_dataset(image_dir_path, label_dir_path):
	image_suffix = '_rgb'
	image_extension = 'png'
	label_suffix = '_fg'
	label_extension = 'png'

	image_width, image_height = None, None
	#image_width, image_height = 500, 530
	#image_width, image_height = 224, 224

	# REF [file] >> ${SWL_PYTHON_HOME}/test/image_processing/util_test.py
	images = load_images_by_pil(image_dir_path, image_suffix, image_extension, width=image_width, height=image_height)
	labels = load_labels_by_pil(label_dir_path, label_suffix, label_extension, width=image_width, height=image_height)

	# RGBA -> RGB.
	images = images[:,:,:,:-1]

	return images, labels

#%%------------------------------------------------------------------

from swl.image_processing.util import to_rgb, stack_images_horzontally
from PIL import Image

def export_images(images, labels, filepath_prefix, filepath_suffix):
	for idx in range(images.shape[0]):
		img = Image.fromarray(images[idx])
		#lbl = Image.fromarray(to_rgb(np.uint8(np.argmax(labels[idx], axis=-1) * 255 / np.max(labels[idx]))))
		lbl = Image.fromarray(to_rgb(np.uint8(labels[idx] * 255 / np.max(labels[idx]))))
		stacked_img = stack_images_horzontally([img, lbl])
		stacked_img.save(filepath_prefix + str(idx) + filepath_suffix + '.jpg')

#%%------------------------------------------------------------------

if 'posix' == os.name:
	lib_home_dir_path = '/home/sangwook/lib_repo/python'
else:
	lib_home_dir_path = 'D:/lib_repo/python'
	#lib_home_dir_path = 'D:/lib_repo/python/rnd'
sys.path.append(lib_home_dir_path + '/imgaug_github')

def simple_imgaug_example():
	image_dir_path = dataset_home_dir_path + '/phenotyping/cvppp2017_lsc_lcc_challenge/package/CVPPP2017_LSC_training/training/A1'
	label_dir_path = dataset_home_dir_path + '/phenotyping/cvppp2017_lsc_lcc_challenge/package/CVPPP2017_LSC_training/training/A1'
	images, labels = prepare_dataset(image_dir_path, label_dir_path)

	image_width, image_height = 200, 200

	# FIXME [decide] >> Before or after random transformation?
	# Preprocessing (normalization, standardization, etc).
	images_pp = images.astype(np.float)
	#images_pp /= 255.0
	images_pp = standardize_samplewise(images_pp)
	#images_pp = standardize_featurewise(images_pp)

	seq = iaa.Sequential([
		iaa.SomeOf(1, [
			#iaa.Sometimes(0.5, iaa.Crop(px=(0, 100))),  # Crop images from each side by 0 to 16px (randomly chosen).
			iaa.Sometimes(0.5, iaa.Crop(percent=(0, 0.1))), # Crop images by 0-10% of their height/width.
			iaa.Fliplr(0.5),  # Horizontally flip 50% of the images.
			iaa.Flipud(0.5),  # Vertically flip 50% of the images.
			iaa.Sometimes(0.5, iaa.Affine(
				scale={'x': (0.8, 1.2), 'y': (0.8, 1.2)},  # Scale images to 80-120% of their size, individually per axis.
				translate_percent={'x': (-0.2, 0.2), 'y': (-0.2, 0.2)},  # Translate by -20 to +20 percent (per axis).
				rotate=(-45, 45),  # Rotate by -45 to +45 degrees.
				shear=(-16, 16),  # Shear by -16 to +16 degrees.
				#order=[0, 1],  # Use nearest neighbour or bilinear interpolation (fast).
				order=0,  # Use nearest neighbour or bilinear interpolation (fast).
				#cval=(0, 255),  # If mode is constant, use a cval between 0 and 255.
				#mode=ia.ALL  # Use any of scikit-image's warping modes (see 2nd image from the top for examples).
				#mode='edge'  # Use any of scikit-image's warping modes (see 2nd image from the top for examples).
			))
			#iaa.Sometimes(0.5, iaa.GaussianBlur(sigma=(0, 3.0)))  # Blur images with a sigma of 0 to 3.0.
		]),
		iaa.Scale(size={'height': image_height, 'width': image_width})  # Resize.
	])

	for idx in range(images.shape[0]):
		images_pp[idx] = (images_pp[idx] - np.min(images_pp[idx])) / (np.max(images_pp[idx]) - np.min(images_pp[idx])) * 255
	images_pp = images_pp.astype(np.uint8)

	# Test 1 (good).
	seq_det = seq.to_deterministic()  # Call this for each batch again, NOT only once at the start.
	#images_aug1 = seq_det.augment_images(images)
	images_aug1 = seq_det.augment_images(images_pp)
	labels_aug1 = seq_det.augment_images(labels)
	seq_det = seq.to_deterministic()  # Call this for each batch again, NOT only once at the start.
	#images_aug2 = seq_det.augment_images(images)
	images_aug2 = seq_det.augment_images(images_pp)
	labels_aug2 = seq_det.augment_images(labels)

	#export_images(images, labels, './augmented1/img', '')
	export_images(images_pp, labels, './augmented1/img', '')
	export_images(images_aug1, labels_aug1, './augmented1/img', '_aug1')
	export_images(images_aug2, labels_aug2, './augmented1/img', '_aug2')

	# Test 2 (bad).
	seq_det = seq.to_deterministic()  # Call this for each batch again, NOT only once at the start.
	#images_aug1 = seq_det.augment_images(images)
	images_aug1 = seq_det.augment_images(images_pp)
	labels_aug1 = seq_det.augment_images(labels)
	#images_aug2 = seq_det.augment_images(images)
	images_aug2 = seq_det.augment_images(images_pp)
	labels_aug2 = seq_det.augment_images(labels)

	#export_images(images, labels, './augmented2/img', '')
	export_images(images_pp, labels, './augmented2/img', '')
	export_images(images_aug1, labels_aug1, './augmented2/img', '_aug1')
	export_images(images_aug2, labels_aug2, './augmented2/img', '_aug2')

	print('*********************************', images_pp.dtype)

	# FIXME [decide] >> Before or after random transformation?
	# Preprocessing (normalization, standardization, etc).
	#images_pp = images.astype(np.float)
	##images_pp /= 255.0
	#images_pp = standardize_samplewise(images_pp)
	##images_pp = standardize_featurewise(images_pp)

	# One-hot encoding.
	#num_classes = np.unique(labels).shape[0]
	#labels = np.uint8(keras.utils.to_categorical(labels, num_classes).reshape(labels.shape + (-1,)))
	#labels_aug = np.uint8(keras.utils.to_categorical(labels_aug, num_classes).reshape(labels_aug.shape + (-1,)))

# NOTICE [info] >> Keras does not support keras.utils.data_utils.Sequence.
"""
from keras.utils.data_utils import Sequence

def keras_example():
	class CvpppSequence(Sequence):
		def __init__(self, images, labels, batch_size, shuffle=False):
			self.X, self.y = images, labels
			self.batch_size = batch_size
			self.shuffle = shuffle

		def __len__(self):
			return len(self.X) // self.batch_size

		def __getitem__(self, idx):
			batch_x = self.X[idx*self.batch_size:(idx+1)*self.batch_size]
			batch_y = self.y[idx*self.batch_size:(idx+1)*self.batch_size]

			return np.array(batch_x), np.array(batch_y)

	image_dir_path = dataset_home_dir_path + '/phenotyping/cvppp2017_lsc_lcc_challenge/package/CVPPP2017_LSC_training/training/A1'
	label_dir_path = dataset_home_dir_path + '/phenotyping/cvppp2017_lsc_lcc_challenge/package/CVPPP2017_LSC_training/training/A1'
	images, labels = prepare_dataset(image_dir_path, label_dir_path)

	ii = 0
	for batch_images, batch_labels in CvpppSequence(images, labels, 5):
		print('**************', batch_images.shape, batch_labels.shape)
		ii += 1
"""

from swl.machine_learning.data_generator import create_dataset_generator_from_array, create_dataset_generator_using_imgaug

def data_generator_example():
	image_dir_path = dataset_home_dir_path + '/phenotyping/cvppp2017_lsc_lcc_challenge/package/CVPPP2017_LSC_training/training/A1'
	label_dir_path = dataset_home_dir_path + '/phenotyping/cvppp2017_lsc_lcc_challenge/package/CVPPP2017_LSC_training/training/A1'
	images, labels = prepare_dataset(image_dir_path, label_dir_path)

	image_width, image_height = 200, 200

	seq = iaa.Sequential([
		iaa.SomeOf(1, [
			#iaa.Sometimes(0.5, iaa.Crop(px=(0, 100))),  # Crop images from each side by 0 to 16px (randomly chosen).
			iaa.Sometimes(0.5, iaa.Crop(percent=(0, 0.1))), # Crop images by 0-10% of their height/width.
			iaa.Fliplr(0.5),  # Horizontally flip 50% of the images.
			iaa.Flipud(0.5),  # Vertically flip 50% of the images.
			iaa.Sometimes(0.5, iaa.Affine(
				scale={'x': (0.8, 1.2), 'y': (0.8, 1.2)},  # Scale images to 80-120% of their size, individually per axis.
				translate_percent={'x': (-0.2, 0.2), 'y': (-0.2, 0.2)},  # Translate by -20 to +20 percent (per axis).
				rotate=(-45, 45),  # Rotate by -45 to +45 degrees.
				shear=(-16, 16),  # Shear by -16 to +16 degrees.
				#order=[0, 1],  # Use nearest neighbour or bilinear interpolation (fast).
				order=0,  # Use nearest neighbour or bilinear interpolation (fast).
				#cval=(0, 255),  # If mode is constant, use a cval between 0 and 255.
				#mode=ia.ALL  # Use any of scikit-image's warping modes (see 2nd image from the top for examples).
				#mode='edge'  # Use any of scikit-image's warping modes (see 2nd image from the top for examples).
			))
			#iaa.Sometimes(0.5, iaa.GaussianBlur(sigma=(0, 3.0)))  # Blur images with a sigma of 0 to 3.0.
		]),
		iaa.Scale(size={'height': image_height, 'width': image_width})  # Resize.
	])

	batch_size = 5

	#batch_idx = 0
	#for batch_images, batch_labels in create_dataset_generator_from_array(images_aug, labels_aug, batch_size):
	#	export_images(batch_images, batch_labels, './generated/img', '')
	#	#print(batch_idx, type(batch_images), type(batch_labels))
	#	print(batch_idx, ':', batch_images.shape, ',', batch_labels.shape)
	#	batch_idx += 1

	batch_idx = 0
	for batch_images, batch_labels in create_dataset_generator_using_imgaug(seq, images, labels, batch_size):
		export_images(batch_images, np.argmax(batch_labels, axis=-1), './augmented/img', '')
		#print(batch_idx, type(batch_images), type(batch_labels))
		print(batch_idx, ':', batch_images.shape, ',', batch_labels.shape)
		batch_idx += 1

# A generator that loads batches from the hard drive.
def load_batches():
	# Here, load 10 batches of size 4 each.
	# You can also load an infinite amount of batches, if you don't train in epochs.
	batch_size = 4
	nb_batches = 10 #1000000000

	# Here, for simplicity we just always use the same image.
	astronaut = data.astronaut()
	astronaut = ia.imresize_single_image(astronaut, (64, 64))

	for i in range(nb_batches):
		# A list containing all images of the batch.
		batch_images = []
		# A list containing IDs of images in the batch. This is not necessary
		# for the background augmentation and here just used to showcase that
		# you can transfer additional information.
		batch_data = []

		# Add some images to the batch.
		for b in range(batch_size):
			batch_images.append(astronaut)
			batch_data.append((i, b))

		# Create the batch object to send to the background processes.
		batch = ia.Batch(
			images=np.array(batch_images, dtype=np.uint8),
			data=batch_data
		)

		yield batch

# A generator that loads batches from a numpy array.
def load_batches_from_numpy():
	batch_size = 10
	shuffle = True
	is_time_major = False

	astronaut = data.astronaut()
	astronaut = ia.imresize_single_image(astronaut, (64, 64))
	images = list()
	for _ in range(100):
		images.append(astronaut)
	images = np.array(images)

	#--------------------
	batch_dim = 1 if is_time_major else 0

	num_examples, steps_per_epoch = 0, 0
	if images is not None:
		num_examples = images.shape[batch_dim]
		steps_per_epoch = ((num_examples - 1) // batch_size + 1) if num_examples > 0 else 0
	#if images is None:
	if num_examples <= 0:
		return None

	indices = np.arange(num_examples)
	if shuffle:
		np.random.shuffle(indices)

	for step in range(steps_per_epoch):
		start = step * batch_size
		end = start + batch_size
		batch_indices = indices[start:end]
		if batch_indices.size > 0:  # If batch_indices is non-empty.
			batch_images = images[batch_indices]
			if batch_images.size > 0:  # If batch_images is non-empty.
				#batch_data = []
				#for idx in batch_indices:
				#	batch_data.append((step, idx))

				# Create the batch object to send to the background processes.
				batch = ia.Batch(
					images=batch_images,
					#data=batch_data
					data=batch_indices
				)

				yield batch

def background_process_augmentation_example_1():
	# Example augmentation sequence to run in the background.
	augseq = iaa.Sequential([
		iaa.Fliplr(0.5),
		iaa.CoarseDropout(p=0.1, size_percent=0.1)
	])

	print('Started epoch.')

	# Background augmentation consists of two components:
	#  (1) BatchLoader, which runs in a Thread and calls repeatedly a user-defined
	#      function (here: load_batches) to load batches (optionally with keypoints
	#      and additional information) and sends them to a queue of batches.
	#  (2) BackgroundAugmenter, which runs several background processes (on other
	#      CPU cores). Each process takes batches from the queue defined by (1),
	#      augments images/keypoints and sends them to another queue.
	# The main process can then read augmented batches from the queue defined by (2).
	batch_loader = ia.BatchLoader(load_batches)
	bg_augmenter = ia.BackgroundAugmenter(batch_loader, augseq)

	# Run until load_batches() returns nothing anymore. This also allows infinite training.
	while True:
		print('Next batch...')
		batch = bg_augmenter.get_batch()
		if batch is None:
			print('Finished epoch.')
			break
		#images = batch.images
		images_aug = batch.images_aug
		#keypoints = batch.keypoints
		#keypoints_aug = batch.keypoints_aug

		print('Image IDs:', batch.data)

		#ia.imshow(np.hstack(list(images_aug)))

	batch_loader.terminate()
	bg_augmenter.terminate()

def background_process_augmentation_example_2():
	augseq = iaa.Sequential([
		iaa.Fliplr(0.5),
		iaa.CoarseDropout(p=0.1, size_percent=0.1)
	])

	num_epoches = 2
	for epoch in range(num_epoches):
		print('Started epoch {}.'.format(epoch))

		batch_loader = ia.BatchLoader(load_batches_from_numpy)
		bg_augmenter = ia.BackgroundAugmenter(batch_loader, augseq)

		while True:
			print('Next batch...')
			batch = bg_augmenter.get_batch()
			if batch is None:
				print('Finished epoch.')
				break
			#images = batch.images
			images_aug = batch.images_aug
			#keypoints = batch.keypoints
			#keypoints_aug = batch.keypoints_aug

			print('Image IDs:', batch.data)

			#ia.imshow(np.hstack(list(images_aug)))

		batch_loader.terminate()
		bg_augmenter.terminate()

def main():
	#simple_imgaug_example()
	#keras_example()  # Not working.

	#data_generator_example()

	#background_process_augmentation_example_1()
	background_process_augmentation_example_2()

#%%------------------------------------------------------------------

if '__main__' == __name__:
	main()


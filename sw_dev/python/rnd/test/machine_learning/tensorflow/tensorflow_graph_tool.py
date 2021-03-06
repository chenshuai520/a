#!/usr/bin/env python

import numpy as np
import tensorflow as tf
from tensorflow.python.tools import freeze_graph, optimize_for_inference_lib
from tensorflow.core.protobuf import saver_pb2
import os

# NOTE [info] >>
#	Use TensorBoard or the summarize_graph tool to get a graph's shape.
#	If there are still unsupported layers, check out graph_transform tools.

def display_graph_def(graph_def, node_names, display_all_nodes=False):
	for node in node_names:
		print('------------------------------------------------ Nodes with "{}".'.format(node))
		#print([n for n in graph_def.node if n.name.find(node) != -1])
		print(*[n for n in graph_def.node if n.name.find(node) != -1], sep='\n')
	#print('------------------------------------------------ Node operations.')
	##print([n.op for n in graph_def.node])
	#print(*[n.op for n in graph_def.node], sep='\n')
	if display_all_nodes:
		print('------------------------------------------------ All nodes.')
		#print(graph_def.node)  # Too much output in a frozen graph.
		print(*graph_def.node, sep='----------\n')  # Too much output in a frozen graph.
	print('----------------------------------------------------------------------')

def display_graph(graph):
	print('------------------------------------------------ All operations.')
	#print([op.name for op in graph.get_operations()])
	print(*[op.name for op in graph.get_operations()], sep='\n')
	print('----------------------------------------------------------------------')

def display_graph_info():
	# NOTE [info] >> checkpoint_to_graph() in tensorflow_saving_and_loading.py
	graph_filepath = './mnist_cnn_graph.pb'
	#graph_filepath = './mnist_cnn_frozen_graph.pb'
	#graph_filepath = './mnist_cnn_optimized_frozen_graph.pb'
	is_graph_file_text = False

	graph_def = tf.GraphDef()
	with tf.gfile.GFile(graph_filepath, 'r' if is_graph_file_text else 'rb') as fd:
		graph_def.ParseFromString(fd.read())

	if True:
		display_graph_def(graph_def, node_names=['input', 'Softmax'], display_all_nodes=False)

	if False:
		with tf.Session() as sess:
			g = tf.import_graph_def(graph_def)
			if sess.graph is not None:
				# NOTE [info] >> Use a graph loaded from checkpoint. Use node names, instead of tensor names, for a graph loaded from graph file.
				# REF [function] >> load_model_from_checkpoint() in tensorflow_saving_and_loading.py
				input_tensor = sess.graph.get_tensor_by_name('input_tensor_ph:0')  # NOTE [error] >> The name 'input_tensor_ph:0' refers to a Tensor which does not exist. The operation, 'input_tensor_ph', does not exist in the graph.
				output_tensor = sess.graph.get_tensor_by_name('mnist_cnn_using_tf/fc2/dense/Softmax:0')  # NOTE [error] >> The name 'mnist_cnn_using_tf/fc2/dense/Softmax:0' refers to a Tensor which does not exist. The operation, 'mnist_cnn_using_tf/fc2/dense/Softmax', does not exist in the graph.
				#input_tensor = sess.graph.get_operation_by_name('input_tensor_ph')  # NOTE [error] >> The name 'input_tensor_ph' refers to an Operation not in the graph.
				#output_tensor = sess.graph.get_operation_by_name('mnist_cnn_using_tf/fc2/dense/Softmax')  # NOTE [error] >> The name 'mnist_cnn_using_tf/fc2/dense/Softmax' refers to an Operation not in the graph.
				print('input_tensor =', input_tensor.get_shape())
				print('output_tensor =', output_tensor.get_shape())
			else:
				print('Graph not found:', sess.graph)

	if False:
		with tf.Session() as sess:
			g = tf.import_graph_def(graph_def)
			if sess.graph is not None:
				display_graph(sess.graph)
			else:
				print('Graph not found:', sess.graph)

def graph_to_tensorboard_log():
	checkpoint_dir_path = './mnist_cnn_checkpoint'
	checkpoint_meta_graph_filename = 'tf_ckpt-7740.meta'
	log_dir_path = './tensorboard_log'

	graph = tf.Graph()
	with graph.as_default():
		# Method 1.
		#	Create a model.

		# Method 2.
		#	Load a graph.
		tf.train.import_meta_graph(os.path.join(checkpoint_dir_path, checkpoint_meta_graph_filename))

	#display_graph_def(graph.as_graph_def(), node_names=['input', 'output'], display_all_nodes=True)
	#display_graph(graph)

	#config = tf.ConfigProto()
	#with tf.Session(graph=graph, config=config) as sess:
	with tf.Session(graph=graph) as sess:
		#display_graph_def(sess.graph_def, node_names=['input', 'output'], display_all_nodes=True)

		# Write log.
		file_writer = tf.summary.FileWriter(logdir=log_dir_path, graph=graph) 
		#file_writer.flush()
		#file_writer.close()

# Frozen graph:
#	REF [site] >>
#		https://www.tensorflow.org/extend/tool_developers/#freezing
#		https://blog.metaflow.fr/tensorflow-how-to-freeze-a-model-and-serve-it-with-a-python-api-d4f3596b3adc
#	The freeze_graph tool takes a graph definition and a set of checkpoints and freezes them together into a single file.
#	freeze_graph:
#		cd ${TENSORFLOW_HOME}
#		bazel build tensorflow/python/tools:freeze_graph
#		bazel-bin/tensorflow/python/tools/freeze_graph --help
#	python freeze_graph.py:
#		${TENSORFLOW_HOME}/tensorflow/python/tools/freeze_graph.py
#	e.g.) freeze_graph --input_graph=/path/to/graph.pbtxt --input_binary=false --input_checkpoint=/path/to/checkpoint/tf_ckpt-1234 --output_graph=/path/to/frozen_graph.pb --output_node_names=output_nodes
#		${TENSORFLOW_HOME}/bazel-bin/tensorflow/python/tools/freeze_graph --input_graph=/home/sangwook/work/mnist_cnn_graph.pbtxt --input_binary=false --input_checkpoint=/home/sangwook/work/mnist_cnn_checkpoint/tf_ckpt-7740 --output_graph=/home/sangwook/work/mnist_cnn_frozen_graph.pb --output_node_names=mnist_cnn_using_tf/fc2/dense/Softmax
#	e.g.) python -m tensorflow.python.tools.freeze_graph --input_graph=/path/to/graph.pbtxt --input_binary=false --input_checkpoint=/path/to/checkpoint/tf_ckpt-1234 --output_graph=/path/to/frozen_graph.pb --output_node_names=output_nodes
#	=> Recommend using TensorBoard to get 'output_node_names' which I think is operations' names in a TensorFlow graph.
def freeze_graph_tool():
	# REF [function] >> checkpoint_to_graph() in tensorflow_saving_and_loading.py.
	model_graph_filepath = './mnist_cnn_graph.pb'
	checkpoint_dir_path = './mnist_cnn_checkpoint'
	checkpoint_filename = 'tf_ckpt-7740'

	output_frozen_graph_filepath = './mnist_cnn_frozen_graph.pb'
	output_node_names = 'mnist_cnn_using_tf/fc2/dense/Softmax'  # The name(s) of the output nodes, comma separated.

	input_binary = True
	clear_devices = True

	freeze_graph.freeze_graph(
		input_graph=model_graph_filepath,
		input_saver='',  # TensorFlow saver file to load.
		input_binary=input_binary,
		input_checkpoint=os.path.join(checkpoint_dir_path, checkpoint_filename),
		output_node_names=output_node_names,
		restore_op_name=None,  # Unused.
		filename_tensor_name=None,  # Unused.
		output_graph=output_frozen_graph_filepath,
		clear_devices=clear_devices,
		initializer_nodes='',  # Comma separated list of initializer nodes to run before freezing.
		variable_names_whitelist='',
		variable_names_blacklist='',
		#input_meta_graph_def=None,
		#input_saved_model_dir=None,
		#saved_model_tags=None,
		##saved_model_tags=tf.saved_model.tag_constants.SERVING,
		checkpoint_version=saver_pb2.SaverDef.V2
	)

	# Check the frozen graph.
	graph_def = tf.GraphDef()
	with tf.gfile.GFile(output_frozen_graph_filepath, 'rb') as fd:
		graph_def.ParseFromString(fd.read())
	display_graph_def(graph_def, node_names=['input', 'output'], display_all_nodes=False)

# Optimized graph:
#	The optimize_for_inference tool takes in the input and output names and does another pass to strip out unnecessary layers.
#	optimize_for_inference:
#		cd ${TENSORFLOW_HOME}
#		bazel build tensorflow/python/tools:optimize_for_inference
#		bazel-bin/tensorflow/python/tools/optimize_for_inference --help
#	python optimize_for_inference.py:
#		${TENSORFLOW_HOME}/tensorflow/python/tools/optimize_for_inference.py
#	e.g.) optimize_for_inference --input=/path/to/frozen_graph.pb --output=/path/to/optimized_frozen_graph.pb --frozen_graph=true --input_names=input_nodes --output_names=output_nodes
#		${TENSORFLOW_HOME}/bazel-bin/tensorflow/python/tools/optimize_for_inference --input=/home/sangwook/work/mnist_cnn_frozen_graph.pb --output=/home/sangwook/work/mnist_cnn_optimized_frozen_graph.pb --frozen_graph=true --input_names=input_tensor_ph --output_names=mnist_cnn_using_tf/fc2/dense/Softmax
def optimize_for_inference_tool():
	input_frozen_graph_filepath = './mnist_cnn_frozen_graph.pb'
	output_optimized_graph_filepath = './mnist_cnn_optimized_frozen_graph.pb'

	input_node_names_list = ['input_tensor_ph']  # A list of names of the nodes that are fed inputs during inference.
	output_node_names_list = ['mnist_cnn_using_tf/fc2/dense/Softmax']  # A list of names of the nodes that produce the final results.

	input_graph_def = tf.GraphDef()
	with tf.gfile.GFile(input_frozen_graph_filepath, 'rb') as fd:
		input_graph_def.ParseFromString(fd.read())

	output_graph_def = optimize_for_inference_lib.optimize_for_inference(
		input_graph_def=input_graph_def,
		input_node_names=input_node_names_list,
		output_node_names=output_node_names_list,
		placeholder_type_enum=tf.float32.as_datatype_enum,
		toco_compatible=False
	)

	# Save the optimized graph.
	with tf.gfile.FastGFile(output_optimized_graph_filepath, 'wb') as fd:
		fd.write(output_graph_def.SerializeToString())
	#tf.train.write_graph(output_graph_def, './', output_optimized_graph_name)

def load_graph(frozen_graph_filepath):
	# Load the protobuf file from the disk and parse it to retrieve the unserialized graph_def.
	with tf.gfile.GFile(frozen_graph_filepath, 'rb') as f:
		graph_def = tf.GraphDef()
		graph_def.ParseFromString(f.read())

	# Import the graph_def into a new Graph.
	with tf.Graph().as_default() as graph:
		# The 'name' argument will prefix every op/nodes in your graph.
		tf.import_graph_def(graph_def, name='prefix')
		#tf.import_graph_def(graph_def, name='')
		#tf.import_graph_def(graph_def)

	return graph
	
def infer_by_frozen_graph():
	"""
	frozen_model_filepath = './mnist_cnn_frozen_graph.pb'

	# Load a graph.
	graph = load_graph(frozen_model_filepath)

	# List operations in the graph.
	for op in graph.get_operations():
		print(op.name)
		
	# Access the input and output nodes.
	inputs = graph.get_tensor_by_name('prefix/input_tensor_ph:0')
	outputs = graph.get_tensor_by_name('prefix/mnist_cnn_using_tf/fc2/fc/Softmax:0')
		
	with tf.Session(graph=graph) as sess:
		# NOTE [infor] >> Don't need to initialize/restore anything.
		x_in = np.random.rand(1, 28, 28, 1)
		y_out = sess.run(outputs, feed_dict={inputs: x_in})
		print('Inference =', np.argmax(y_out))
	"""
	frozen_model_filepath = './mobis_yonsei_5way_frozen_graph.pb'

	# Load a graph.
	graph = load_graph(frozen_model_filepath)

	# List operations in the graph.
	for op in graph.get_operations():
		print(op.name)
		
	# Access the input and output nodes.
	inputs = graph.get_tensor_by_name('prefix/input_6:0')
	outputs = graph.get_tensor_by_name('prefix/dense_18/Softmax:0')
		
	with tf.Session(graph=graph) as sess:
		# NOTE [infor] >> Don't need to initialize/restore anything.
		x_in = np.random.rand(1, 75, 128)
		y_out = sess.run(outputs, feed_dict={inputs: x_in})
		print('Inference =', np.argmax(y_out))

# REF [site] >> https://github.com/tensorflow/tensorflow/tree/master/tensorflow/tools/graph_transforms/
#	transform_graph:
#		cd ${TENSORFLOW_HOME}
#		bazel build tensorflow/tools/graph_transforms:transform_graph
#		bazel-bin/tensorflow/tools/graph_transforms/transform_graph --help
#	e.g.) transform_graph --in_graph=input_graph.pb --out_graph=output_graph.pb --inputs='Mul:0' --outputs='softmax:0' --output_as_text=false \
#			--transforms= \
#			'strip_unused_nodes(type=float, shape="1,299,299,3")
#			remove_nodes(op=Identity, op=CheckNumerics)
#			fold_old_batch_norms'
def graph_transform_tool():
	raise NotImplementedError('Use the graph_transform tool')

# REF [site] >> https://github.com/tensorflow/tensorflow/tree/master/tensorflow/tools/graph_transforms/
#	summarize_graph:
#		cd ${TENSORFLOW_HOME}
#		bazel build tensorflow/tools/graph_transforms:summarize_graph
#		bazel-bin/tensorflow/tools/graph_transforms/summarize_graph --help
#	e.g.) summarize_graph --in_graph=graph.pb --print_structure=false
def summarize_graph_tool():
	raise NotImplementedError('Use the summarize_graph tool')

def main():
	display_graph_info()
	#graph_to_tensorboard_log()

	#freeze_graph_tool()
	#optimize_for_inference_tool()

	#infer_by_frozen_graph()

	#graph_transform_tool()  # Not implemented.
	#summarize_graph_tool()  # Not implemented.

#--------------------------------------------------------------------

if '__main__' == __name__:
	main()

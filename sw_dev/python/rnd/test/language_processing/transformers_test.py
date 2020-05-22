#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# REF [site] >>
#	https://github.com/huggingface/transformers
#	https://huggingface.co/transformers/
#	https://medium.com/analytics-vidhya/a-comprehensive-guide-to-build-your-own-language-model-in-python-5141b3917d6d

import time
import torch
from transformers import GPT2Tokenizer, GPT2LMHeadModel
from transformers import BertTokenizer, BertModel, BertForMaskedLM
from transformers.modeling_bert import BertPreTrainedModel
from transformers import BertConfig
from transformers import *

# REF [site] >> https://github.com/huggingface/transformers
def quick_tour():
	# Transformers has a unified API for 10 transformer architectures and 30 pretrained weights.
	#          Model          | Tokenizer          | Pretrained weights shortcut
	MODELS = [(BertModel,       BertTokenizer,       'bert-base-uncased'),
			  (OpenAIGPTModel,  OpenAIGPTTokenizer,  'openai-gpt'),
			  (GPT2Model,       GPT2Tokenizer,       'gpt2'),
			  (CTRLModel,       CTRLTokenizer,       'ctrl'),
			  (TransfoXLModel,  TransfoXLTokenizer,  'transfo-xl-wt103'),
			  (XLNetModel,      XLNetTokenizer,      'xlnet-base-cased'),
			  (XLMModel,        XLMTokenizer,        'xlm-mlm-enfr-1024'),
			  (DistilBertModel, DistilBertTokenizer, 'distilbert-base-cased'),
			  (RobertaModel,    RobertaTokenizer,    'roberta-base'),
			  (XLMRobertaModel, XLMRobertaTokenizer, 'xlm-roberta-base'),
			 ]

	# To use TensorFlow 2.0 versions of the models, simply prefix the class names with 'TF', e.g. `TFRobertaModel` is the TF 2.0 counterpart of the PyTorch model `RobertaModel`.

	# Let's encode some text in a sequence of hidden-states using each model.
	for model_class, tokenizer_class, pretrained_weights in MODELS:
		# Load pretrained model/tokenizer.
		tokenizer = tokenizer_class.from_pretrained(pretrained_weights)
		model = model_class.from_pretrained(pretrained_weights)

		# Encode text.
		input_ids = torch.tensor([tokenizer.encode('Here is some text to encode', add_special_tokens=True)])  # Add special tokens takes care of adding [CLS], [SEP], <s>... tokens in the right way for each model.
		with torch.no_grad():
			last_hidden_states = model(input_ids)[0]  # Models outputs are now tuples.

	#--------------------
	# Each architecture is provided with several class for fine-tuning on down-stream tasks, e.g.
	BERT_MODEL_CLASSES = [BertModel, BertForPreTraining, BertForMaskedLM, BertForNextSentencePrediction,
						  BertForSequenceClassification, BertForTokenClassification, BertForQuestionAnswering]

	output_dir_path = './directory/to/save'
	import os
	os.makedirs(output_dir_path, exist_ok=True)

	# All the classes for an architecture can be initiated from pretrained weights for this architecture.
	# Note that additional weights added for fine-tuning are only initialized and need to be trained on the down-stream task.
	pretrained_weights = 'bert-base-uncased'
	tokenizer = BertTokenizer.from_pretrained(pretrained_weights)
	for model_class in BERT_MODEL_CLASSES:
		# Load pretrained model/tokenizer.
		model = model_class.from_pretrained(pretrained_weights)

		# Models can return full list of hidden-states & attentions weights at each layer.
		model = model_class.from_pretrained(pretrained_weights, output_hidden_states=True, output_attentions=True)
		input_ids = torch.tensor([tokenizer.encode("Let's see all hidden-states and attentions on this text")])
		all_hidden_states, all_attentions = model(input_ids)[-2:]

		# Models are compatible with Torchscript.
		model = model_class.from_pretrained(pretrained_weights, torchscript=True)
		traced_model = torch.jit.trace(model, (input_ids,))

		# Simple serialization for models and tokenizers.
		model.save_pretrained(output_dir_path)  # Save.
		model = model_class.from_pretrained(output_dir_path)  # Re-load.
		tokenizer.save_pretrained(output_dir_path)  # Save.
		tokenizer = BertTokenizer.from_pretrained(output_dir_path)  # Re-load.

		# SOTA examples for GLUE, SQUAD, text generation...

		print('{} processed.'.format(model_class.__name__))

def gpt2_example():
	# NOTE [info] >> Refer to example codes in the comment of forward() of each BERT class in https://github.com/huggingface/transformers/blob/master/src/transformers/modeling_gpt2.py

	pretrained_model_name = 'gpt2'
	tokenizer = GPT2Tokenizer.from_pretrained(pretrained_model_name)

	input_ids = torch.tensor(tokenizer.encode('Hello, my dog is cute', add_special_tokens=True)).unsqueeze(0)  # Batch size 1.

	if True:
		print('Start loading a model...')
		start_time = time.time()
		# The bare GPT2 Model transformer outputting raw hidden-states without any specific head on top.
		model = GPT2Model.from_pretrained(pretrained_model_name)
		print('End loading a model: {} secs.'.format(time.time() - start_time))

		print('Start inferring...')
		start_time = time.time()
		model.eval()
		with torch.no_grad():
			outputs = model(input_ids)
		print('End inferring: {} secs.'.format(time.time() - start_time))

		last_hidden_states = outputs[0]  # The last hidden-state is the first element of the output tuple.
		print('{} processed.'.format(GPT2Model.__name__))

	if True:
		print('Start loading a model...')
		start_time = time.time()
		# The GPT2 Model transformer with a language modeling head on top (linear layer with weights tied to the input embeddings).
		model = GPT2LMHeadModel.from_pretrained(pretrained_model_name)
		print('End loading a model: {} secs.'.format(time.time() - start_time))

		print('Start inferring...')
		start_time = time.time()
		model.eval()
		with torch.no_grad():
			outputs = model(input_ids, labels=input_ids)
		print('End inferring: {} secs.'.format(time.time() - start_time))

		loss, logits = outputs[:2]
		print('{} processed.'.format(GPT2LMHeadModel.__name__))

	if True:
		print('Start loading a model...')
		start_time = time.time()
		# The GPT2 Model transformer with a language modeling and a multiple-choice classification head on top e.g. for RocStories/SWAG tasks.
		model = GPT2DoubleHeadsModel.from_pretrained(pretrained_model_name)
		print('End loading a model: {} secs.'.format(time.time() - start_time))

		# Add a [CLS] to the vocabulary (we should train it also!).
		tokenizer.add_special_tokens({'cls_token': '[CLS]'})
		model.resize_token_embeddings(len(tokenizer))  # Update the model embeddings with the new vocabulary size.
		print(tokenizer.cls_token_id, len(tokenizer))  # The newly token the last token of the vocabulary.

		choices = ['Hello, my dog is cute [CLS]', 'Hello, my cat is cute [CLS]']
		encoded_choices = [tokenizer.encode(s) for s in choices]
		cls_token_location = [tokens.index(tokenizer.cls_token_id) for tokens in encoded_choices]
		input_ids0 = torch.tensor(encoded_choices).unsqueeze(0)  # Batch size: 1, number of choices: 2.
		mc_token_ids = torch.tensor([cls_token_location])  # Batch size: 1.

		print('Start inferring...')
		start_time = time.time()
		model.eval()
		with torch.no_grad():
			outputs = model(input_ids0, mc_token_ids=mc_token_ids)
		print('End inferring: {} secs.'.format(time.time() - start_time))

		lm_prediction_scores, mc_prediction_scores = outputs[:2]
		print('{} processed.'.format(GPT2DoubleHeadsModel.__name__))

# REF [site] >> https://medium.com/analytics-vidhya/a-comprehensive-guide-to-build-your-own-language-model-in-python-5141b3917d6d
def sentence_completion_model_using_gpt2_example():
	# Load pre-trained model tokenizer (vocabulary).
	tokenizer = GPT2Tokenizer.from_pretrained('gpt2')

	# Encode a text inputs.
	text = 'What is the fastest car in the'
	indexed_tokens = tokenizer.encode(text)

	# Convert indexed tokens in a PyTorch tensor.
	tokens_tensor = torch.tensor([indexed_tokens])

	# Load pre-trained model (weights).
	model = GPT2LMHeadModel.from_pretrained('gpt2')

	# Set the model in evaluation mode to deactivate the DropOut modules.
	model.eval()

	# If you have a GPU, put everything on cuda.
	tokens_tensor = tokens_tensor.to('cuda')
	model.to('cuda')

	# Predict all tokens.
	with torch.no_grad():
		outputs = model(tokens_tensor)
		predictions = outputs[0]

	# Get the predicted next sub-word.
	predicted_index = torch.argmax(predictions[0, -1, :]).item()
	predicted_text = tokenizer.decode(indexed_tokens + [predicted_index])

	# Print the predicted word.
	print('Predicted text =', predicted_text)

# REF [site] >>
#	https://github.com/huggingface/transformers/blob/master/examples/run_generation.py
#		python pytorch-transformers/examples/run_generation.py --model_type=gpt2 --length=100 --model_name_or_path=gpt2
#	https://medium.com/analytics-vidhya/a-comprehensive-guide-to-build-your-own-language-model-in-python-5141b3917d6d
def conditional_text_generation_using_gpt2_example():
	raise NotImplementedError

def bert_example():
	# NOTE [info] >> Refer to example codes in the comment of forward() of each BERT class in https://github.com/huggingface/transformers/blob/master/src/transformers/modeling_bert.py

	pretrained_model_name = 'bert-base-uncased'
	tokenizer = BertTokenizer.from_pretrained(pretrained_model_name)

	input_ids = torch.tensor(tokenizer.encode('Hello, my dog is cute', add_special_tokens=True)).unsqueeze(0)  # Batch size 1.

	if True:
		print('Start loading a model...')
		start_time = time.time()
		# The bare Bert Model transformer outputting raw hidden-states without any specific head on top.
		model = BertModel.from_pretrained(pretrained_model_name)
		print('End loading a model: {} secs.'.format(time.time() - start_time))

		print('Start inferring...')
		start_time = time.time()
		model.eval()
		with torch.no_grad():
			outputs = model(input_ids)
		print('End inferring: {} secs.'.format(time.time() - start_time))

		last_hidden_states = outputs[0]  # The last hidden-state is the first element of the output tuple.
		print('{} processed.'.format(BertModel.__name__))

	if True:
		print('Start loading a model...')
		start_time = time.time()
		# Bert Model with two heads on top as done during the pre-training: a 'masked language modeling' head and a 'next sentence prediction (classification)' head.
		model = BertForPreTraining.from_pretrained(pretrained_model_name)
		print('End loading a model: {} secs.'.format(time.time() - start_time))

		print('Start inferring...')
		start_time = time.time()
		model.eval()
		with torch.no_grad():
			outputs = model(input_ids)
		print('End inferring: {} secs.'.format(time.time() - start_time))

		prediction_scores, seq_relationship_scores = outputs[:2]
		print('{} processed.'.format(BertForPreTraining.__name__))

	if True:
		print('Start loading a model...')
		start_time = time.time()
		# Bert Model with a 'language modeling' head on top.
		model = BertForMaskedLM.from_pretrained(pretrained_model_name)
		print('End loading a model: {} secs.'.format(time.time() - start_time))

		print('Start inferring...')
		start_time = time.time()
		model.eval()
		with torch.no_grad():
			outputs = model(input_ids, masked_lm_labels=input_ids)
		print('End inferring: {} secs.'.format(time.time() - start_time))

		loss, prediction_scores = outputs[:2]
		print('{} processed.'.format(BertForMaskedLM.__name__))

	if True:
		print('Start loading a model...')
		start_time = time.time()
		# Bert Model with a 'next sentence prediction (classification)' head on top.
		model = BertForNextSentencePrediction.from_pretrained(pretrained_model_name)
		print('End loading a model: {} secs.'.format(time.time() - start_time))

		print('Start inferring...')
		start_time = time.time()
		model.eval()
		with torch.no_grad():
			outputs = model(input_ids)
		print('End inferring: {} secs.'.format(time.time() - start_time))

		seq_relationship_scores = outputs[0]
		print('{} processed.'.format(BertForNextSentencePrediction.__name__))

	if True:
		print('Start loading a model...')
		start_time = time.time()
		# Bert Model transformer with a sequence classification/regression head on top (a linear layer on top of the pooled output) e.g. for GLUE tasks.
		model = BertForSequenceClassification.from_pretrained(pretrained_model_name)
		print('End loading a model: {} secs.'.format(time.time() - start_time))

		labels = torch.tensor([1]).unsqueeze(0)  # Batch size 1.

		print('Start inferring...')
		start_time = time.time()
		model.eval()
		with torch.no_grad():
			outputs = model(input_ids, labels=labels)
		print('End inferring: {} secs.'.format(time.time() - start_time))

		loss, logits = outputs[:2]
		print('{} processed.'.format(BertForSequenceClassification.__name__))

	if True:
		print('Start loading a model...')
		start_time = time.time()
		# Bert Model with a multiple choice classification head on top (a linear layer on top of the pooled output and a softmax) e.g. for RocStories/SWAG tasks.
		model = BertForMultipleChoice.from_pretrained(pretrained_model_name)
		print('End loading a model: {} secs.'.format(time.time() - start_time))

		choices = ['Hello, my dog is cute', 'Hello, my cat is amazing']
		input_ids0 = torch.tensor([tokenizer.encode(s, add_special_tokens=True) for s in choices]).unsqueeze(0)  # Batch size 1, 2 choices.
		labels = torch.tensor(1).unsqueeze(0)  # Batch size 1.

		print('Start inferring...')
		start_time = time.time()
		model.eval()
		with torch.no_grad():
			outputs = model(input_ids0, labels=labels)
		print('End inferring: {} secs.'.format(time.time() - start_time))

		loss, classification_scores = outputs[:2]
		print('{} processed.'.format(BertForMultipleChoice.__name__))

	if True:
		print('Start loading a model...')
		start_time = time.time()
		# Bert Model with a token classification head on top (a linear layer on top of the hidden-states output) e.g. for Named-Entity-Recognition (NER) tasks.
		model = BertForTokenClassification.from_pretrained(pretrained_model_name)
		print('End loading a model: {} secs.'.format(time.time() - start_time))

		labels = torch.tensor([1] * input_ids.size(1)).unsqueeze(0)  # Batch size 1.

		print('Start inferring...')
		start_time = time.time()
		model.eval()
		with torch.no_grad():
			outputs = model(input_ids, labels=labels)
		print('End inferring: {} secs.'.format(time.time() - start_time))

		loss, scores = outputs[:2]
		print('{} processed.'.format(BertForTokenClassification.__name__))

	if True:
		print('Start loading a model...')
		start_time = time.time()
		# Bert Model with a span classification head on top for extractive question-answering tasks like SQuAD (a linear layers on top of the hidden-states output to compute 'span start logits' and 'span end logits').
		model = BertForQuestionAnswering.from_pretrained('bert-large-uncased-whole-word-masking-finetuned-squad')
		print('End loading a model: {} secs.'.format(time.time() - start_time))

		question, text = 'Who was Jim Henson?', 'Jim Henson was a nice puppet'
		encoding = tokenizer.encode_plus(question, text)
		input_ids0, token_type_ids = encoding['input_ids'], encoding['token_type_ids']

		print('Start inferring...')
		start_time = time.time()
		model.eval()
		with torch.no_grad():
			start_scores, end_scores = model(torch.tensor([input_ids0]), token_type_ids=torch.tensor([token_type_ids]))
		print('End inferring: {} secs.'.format(time.time() - start_time))

		all_tokens = tokenizer.convert_ids_to_tokens(input_ids0)
		answer = ' '.join(all_tokens[torch.argmax(start_scores) : torch.argmax(end_scores)+1])

		assert answer == 'a nice puppet'
		print('{} processed.'.format(BertForQuestionAnswering.__name__))

# REF [site] >> https://www.analyticsvidhya.com/blog/2019/07/pytorch-transformers-nlp-python/?utm_source=blog&utm_medium=openai-gpt2-text-generator-python
def masked_language_modeling_for_bert_example():
	# Load pre-trained model tokenizer (vocabulary).
	tokenizer = BertTokenizer.from_pretrained('bert-base-uncased')

	# Tokenize input.
	text = '[CLS] Who was Jim Henson ? [SEP] Jim Henson was a puppeteer [SEP]'
	tokenized_text = tokenizer.tokenize(text)

	# Mask a token that we will try to predict back with 'BertForMaskedLM'.
	masked_index = 8
	tokenized_text[masked_index] = '[MASK]'
	assert tokenized_text == ['[CLS]', 'who', 'was', 'jim', 'henson', '?', '[SEP]', 'jim', '[MASK]', 'was', 'a', 'puppet', '##eer', '[SEP]']

	# Convert token to vocabulary indices.
	indexed_tokens = tokenizer.convert_tokens_to_ids(tokenized_text)
	# Define sentence A and B indices associated to 1st and 2nd sentences (see paper).
	segments_ids = [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1]

	# Convert inputs to PyTorch tensors.
	tokens_tensor = torch.tensor([indexed_tokens])
	segments_tensors = torch.tensor([segments_ids])

	# Load pre-trained model (weights).
	model = BertForMaskedLM.from_pretrained('bert-base-uncased')
	model.eval()

	# If you have a GPU, put everything on cuda.
	tokens_tensor = tokens_tensor.to('cuda')
	segments_tensors = segments_tensors.to('cuda')
	model.to('cuda')

	# Predict all tokens.
	with torch.no_grad():
		outputs = model(tokens_tensor, token_type_ids=segments_tensors)
		predictions = outputs[0]

	# Confirm we were able to predict 'henson'.
	predicted_index = torch.argmax(predictions[0, masked_index]).item()
	predicted_token = tokenizer.convert_ids_to_tokens([predicted_index])[0]
	assert predicted_token == 'henson'
	print('Predicted token is:', predicted_token)

class MyBertForSequenceClassification(BertPreTrainedModel):
	def __init__(self, config, pretrained_model_name):
		super(MyBertForSequenceClassification, self).__init__(config)

		#self.bert = BertModel(config)       
		self.bert = BertModel.from_pretrained(pretrained_model_name, config=config)
		self.dropout = torch.nn.Dropout(config.hidden_dropout_prob)
		self.classifier = torch.nn.Linear(config.hidden_size, config.num_labels)

		# TODO [check] >> Are weights initialized?
		#self.init_weights()

	def forward(self, input_ids, attention_mask=None, token_type_ids=None, position_ids=None, head_mask=None, inputs_embeds=None, encoder_hidden_states=None, encoder_attention_mask=None):
		_, pooled_output = self.bert(input_ids, token_type_ids, attention_mask)
		pooled_output = self.dropout(pooled_output)
		logits = self.classifier(pooled_output)
		return logits

def sequence_classification_using_bert():
	# REF [site] >> https://huggingface.co/transformers/model_doc/bert.html

	pretrained_model_name = 'bert-base-multilingual-cased'

	tokenizer = BertTokenizer.from_pretrained(pretrained_model_name)
	print('tokenizer.vocab_size = {}.'.format(tokenizer.vocab_size))
	#print('tokenizer.get_vocab():\n{}.'.format(tokenizer.get_vocab()))

	if False:
		model = MyBertForSequenceClassification.from_pretrained(pretrained_model_name, pretrained_model_name=pretrained_model_name)  # Not good.
	else:
		#config = BertConfig(num_labels=10, output_attentions=False, output_hidden_states=False)
		#config = BertConfig.from_pretrained(pretrained_model_name, num_labels=10, output_attentions=False, output_hidden_states=False)
		config = BertConfig.from_pretrained(pretrained_model_name, output_attentions=False, output_hidden_states=False)

		#model = MyBertForSequenceClassification.from_pretrained(pretrained_model_name, config=config, pretrained_model_name=pretrained_model_name)  # Not good.
		model = MyBertForSequenceClassification(config, pretrained_model_name=pretrained_model_name)

	#--------------------
	# Train a model.

	#--------------------
	# Test a model.
	input_ids = [
		tokenizer.encode('Hello, my dog is so cute.', add_special_tokens=True),
		tokenizer.encode('Hi, my cat is cute', add_special_tokens=True),
		tokenizer.encode('Hi, my pig is so small...', add_special_tokens=True),
	]
	max_input_len = len(max(input_ids, key=len))
	print('Max. input len = {}.'.format(max_input_len))
	def convert(x):
		y = [x[-1]] * max_input_len  # TODO [check] >> x[-1] is correct?
		y[:len(x)] = x
		return y
	input_ids = list(map(convert, input_ids))
	input_ids = torch.tensor(input_ids)

	model.eval()
	with torch.no_grad():
		model_outputs = model(input_ids)  # Batch size x #labels.

	print('Model outputs =\n{}.'.format(model_outputs))

def main():
	#quick_tour()

	#--------------------
	#gpt2_example()
	#sentence_completion_model_using_gpt2_example()
	#conditional_text_generation_using_gpt2_example()

	#--------------------
	bert_example()
	#masked_language_modeling_for_bert_example()

	#sequence_classification_using_bert()

#--------------------------------------------------------------------

if '__main__' == __name__:
	main()

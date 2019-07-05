import os
import time
import glob
import json
import jieba
import pickle
import gensim.models
import numpy as np
from scipy.linalg import norm


model_file = '/home/zht/桌面/Models/word_model.mod'
model = gensim.models.KeyedVectors.load(model_file)


with open('/home/zht/桌面/Models/paraData.pk', 'rb') as f:
	paradatas = pickle.load(f)
	paradatas = [data for data in paradatas if len(data['fanyi']) > 2 or len(data['shangxi']) > 2]

def sentence_vector(s):
	words = jieba.lcut(s)
	v = np.zeros(100)
	if not words:
		return v
	for word in words:
		if word not in model:
			continue
		v += model[word]
	return v / norm(v) if norm(v) else v

def creatKd(data):
    texts = data['fanyi'] + data['shangxi']
    vecs = [sentence_vector(s) for s in texts.split()]
    n = len(vecs)
    return KDTree(np.array(vecs).reshape((n,100)))
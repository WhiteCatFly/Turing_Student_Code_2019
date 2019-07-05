import os
import time
import glob
import json
import jieba
import pickle
import gensim.models
import numpy as np
from scipy.linalg import norm
from sklearn.svm import SVC

model_file = '/home/zht/桌面/Models/word_model.mod'
model = gensim.models.KeyedVectors.load(model_file)

singleword_file = '/home/zht/桌面/poemsearch/poemsearch/singleword.model'
singleword_model = gensim.models.KeyedVectors.load(singleword_file)

paradatas = []
nonparadatas = []

paradatas_vecs = []
nonparadatas_vecs = []

#Load data from cache
with open('/home/zht/桌面/poemsearch/finalKdtree.pk', 'rb') as f:
	paradatas = pickle.load(f)

with open('/home/zht/桌面/poemsearch/poemsearch/paradatas_vecs.pk','rb') as f:
	paradatas_vecs = pickle.load(f)

with open('/home/zht/桌面/Models/nonparaData.pk','rb') as f:
	nonparadatas = pickle.load(f)

with open('/home/zht/桌面/poemsearch/poemsearch/nonparadatas_vecs.pk','rb') as f:
	nonparadatas_vecs = pickle.load(f)


def sentence_vector(s):
	words = jieba.lcut(s)
	v = np.zeros(100)
	for word in words:
		if word not in model:
			continue
		v += model[word]
	return v / norm(v) if norm(v) else v



def search(target = '夏天的荷花'):
	'''返回在平行语料库中各首诗歌的得分，序号 （递增）'''
	def getscore(target, kdtree, n = 3):
		'''返回KDTree中前N近的距离之和'''
		scores, indexs = kdtree.query(target, n)
		return sum(scores)
	target_vec = sentence_vector(target)
	poemScores = [getscore(target_vec, data['kd']) for data in paradatas]
	return sorted(enumerate(poemScores), key = lambda x: x[1])


def show(n, indexs):
	res = []
	n = n if n < 10 else 10
	for index, sco in indexs[:n]:
		res.append((paradatas[index]['name'], paradatas[index]['content']))
	return res

def svmSearch(n,indexs):
	res = []
	ps = indexs
	tags = [1]*3+[0]*20
	toTrain = [paradatas_vecs[index] for index, val in ps[:3]]
	toTrain += [paradatas_vecs[index] for index, val in ps[-20:]]
	clf = SVC(gamma='auto', probability=True)
	clf.fit(toTrain, tags)
	pres = clf.predict_proba(nonparadatas_vecs)
	pres = [(i,p[0])for i,p in enumerate(pres)]
	pres = sorted(pres, key = lambda x:x[1])
	n = n if 0 <= n and n < 10 else 10
	for index, p in pres[:n]:
		res.append((nonparadatas[index]['name'],nonparadatas[index]['content']))
	return res

def findFirstMoreVal(array, key):
	'''
	返回一个单调递增的数组中第一个大于key的值的索引,[lo, hi)
	'''
	lo, hi = 0, len(array)
	while hi > lo:
		mid = (lo+hi) // 2
		if array[mid] > key:
			hi = mid - 1
		else:
			lo = mid + 1
	return hi

def m3sigma(ps):
	scores = [data[1] for data in ps[:-100]]
	m = np.mean(scores)
	sigma = np.std(scores)
	return m-3*sigma





def Sentence2VectorBySinglewordModel(sentence):
	'''
	parameters: sentence 
	return: a 100 dimension vector that present that string (using singleword_model)
	'''
	new_s = ''.join(sentence.split())
	v = np.zeros(100)
	for word in new_s:
		if word not in singleword_model:
			continue
		v += singleword_model[word]
	return v / norm(v) if norm(v) else v



def updateKDTree(item, vectors):
	'''update KDTree of item'''
	from scipy.spatial import KDTree
	kddata = item['kd'].data
	for vec in vectors:
		kddata = np.vstack((kddata,vec))
	item['kd'] = KDTree(kddata)

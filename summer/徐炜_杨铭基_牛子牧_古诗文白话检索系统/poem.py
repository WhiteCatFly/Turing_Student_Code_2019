#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import gensim
import jieba
import sys
import time
import os
import numpy as np

def gen_result(id_list) :
	f = open("../data/poem.txt", "r", encoding = "utf8")
	ret = ""
	poems = []
	p_id = f.readline().strip()
	while (p_id != "") :
		p_info = f.readline().strip()
		num_of_lines = f.readline().strip()
		lines = []
		for i in range(int(num_of_lines)) :
			lines.append(f.readline().strip())
		if (p_id in id_list) :
			poems.append([p_id, p_info, "<br>".join(lines)])
		p_id = f.readline().strip()
	for id in id_list :
		for poem in poems :
			if (id == poem[0]) :
				ret += str(id) + "&" + poem[1] + "&" + poem[2] + "#"
				break
	f.close()
	return ret

import io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding="utf-8")
sys.stdin = io.TextIOWrapper(sys.stdin.buffer, encoding="utf-8")

model = gensim.models.Word2Vec.load("../my_w2v.model")
text = sys.argv[1]
sentence = jieba.lcut(text)
myvec = np.zeros(100)
for word in sentence :
	try :
		myvec += np.array(model[word])
	except KeyError:
		pass
myvec /= len(sentence)
command = "./../search"
for dim in myvec :
	command += " " + str(dim)
time_pre = time.clock()
a = os.popen(command)
top10 = a.read().split(" ")
print(gen_result(top10))

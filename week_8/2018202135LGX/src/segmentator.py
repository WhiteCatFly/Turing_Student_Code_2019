# -*- coding: utf-8 -*-
import os
LTP_DATA_DIR = '/home/lgx/Desktop/pyltp/ltp_data_v3.4.0'  # ltp模型目录的路径
cws_model_path = os.path.join(LTP_DATA_DIR, 'cws.model')  # 分词模型路径，模型名称为`cws.model`
pos_model_path = os.path.join(LTP_DATA_DIR, 'pos.model')

from pyltp import Segmentor
from pyltp import Postagger 

str_1 = open('default').read()
segmentor = Segmentor()  # 初始化实例
postagger = Postagger()
segmentor.load(cws_model_path)  # 加载模型
postagger.load(pos_model_path)
words = segmentor.segment(str_1)  # 分词
postags = postagger.postag(words)


f = open('result_1', "w")
for i in range(0, len(words)):
    # print words[i]
    # print postags[i]
    # print '|'
    print >> f, '%s' % words[i]
segmentor.release()  # 释放模型
postagger.release()
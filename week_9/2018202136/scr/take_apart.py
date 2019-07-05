#encoding=utf-8
import jieba
import jieba.posseg as pseg
filename = "input.txt"
database = "cache.txt"
f = open(filename,"r")
fn = open(database,"w+")    
line = f.read()
words = pseg.cut(line)
for word in words:
    print >>fn,str(word)
f.close()
fn.close()
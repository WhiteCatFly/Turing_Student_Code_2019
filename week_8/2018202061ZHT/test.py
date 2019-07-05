# encoding=utf-8
import jieba
import jieba.posseg as psg

def copy_file (inputFile, outputFile, encoding):
    fin = open(inputFile, 'r', encoding=encoding) #以读的方式打开文件
    fout = open(outputFile, 'w', encoding=encoding) #以写得方式打开文件
    for eachLiine in fin.readlines(): #读取文件的每一行
        line = eachLiine.strip() #去除每行的首位空格
        seg_list = jieba.cut(line);
        fout.write("/".join(seg_list) + '\n')
        #for x in psg.cut(line):
        #	fout.write(x.word)
        #	fout.write(' (' + x.flag + ') ')
    fin.close()
    fout.close()
    return
    
if __name__ == '__main__':
	copy_file('crawl.txt', 'splite.txt','UTF-8')
"""
seg_list = jieba.cut("我来到北京清华大学", cut_all=True)
print("Full Mode: " + "/ ".join(seg_list))  # 全模式

seg_list = jieba.cut("我来到北京清华大学", cut_all=False)
print("Default Mode: " + "/ ".join(seg_list))  # 精确模式

seg_list = jieba.cut("他来到了网易杭研大厦")  # 默认是精确模式
print(", ".join(seg_list))

seg_list = jieba.cut_for_search("小明硕士毕业于中国科学院计算所，后在日本京都大学深造")  # 搜索引擎模式
print(", ".join(seg_list))
"""

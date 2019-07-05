import requests
import lxml
import sys
from bs4 import BeautifulSoup
import time, threading
import multiprocessing


def show_html(url) :
	html_file = open("debug.html", "w")
	page = requests.get(url)
	soup = BeautifulSoup(page.text, 'lxml')
	print(soup, file = html_file)
	html_file.close()

def write_file(str_list) :
	if (len(str_list) != 7) :
		return
	for str in str_list :
		print(str, file = out_file)

def get_text(tag) :
	if (tag == None) :
		return "None"
	if (isinstance(tag, str)) :
		return tag.strip()
	return tag.text.strip()

def parse(index, url) :
	page = requests.models.Response()
	for i in range(3) :
		try:
			page = requests.get(url, timeout = 0.5)
			break
		except :
			if (i == 3) :
				return
	soup = BeautifulSoup(page.text, 'lxml')
	output = []

	view_box = soup.find("div", class_ = "article")

	if (view_box == None) :
		return
	output.append(str(index))
	## 诗名
	name_box = view_box.find("h1")
	output.append(get_text(name_box))
	#output.append(view_box.find("h1").string)
	#print(view_box.find("h1").string, file = out_file)
	
	#作者 朝代
	info_box = view_box.find("div", class_ = "f-l")
	if (info_box == None) :
		output.append("None")
		output.append("None")
	else :
		info_box = info_box.find_all("a")
		cnt = 0
		for tag in info_box :
			output.append(get_text(tag))
			cnt += 1
			if (cnt >= 2) :
				break
		while (cnt < 2) :
			output.append("None")
			cnt += 1
		#print(tag.string, file = out_file)

	##标签
	tag_box = view_box.find("div", class_ = "f-l ziliao12")
	if (tag_box != None) :
		tag_string = get_text(tag_box)
		tags = [tag for tag in tag_string.split("\n，") if tag]
		tag_string = ''
		tag_string += str(len(tags)) + ' '
		#print(len(tags), end = ' ', file = out_file)
		for tag in tags :
			tag_string += tag + ' '
			#print(tag, end = ' ', file = out_file)
		output.append(tag_string)
		#print(file = out_file)
	else :
		output.append('0')
		#print(0, file = out_file)

	##内容
	content_box = view_box.find("dd", class_ = "conview conview_main show")
	if (content_box == None) :
		return
	content_str = ''
	for string in content_box.stripped_strings:
		content_str += string
	output.append(content_str)
	#print(content_str, file = out_file)

	##译文
	trans_str = ''
	trans_box_list = view_box.find("div", class_ = "nr_info")
	if (trans_box_list != None) :
		trans_box_list = trans_box_list.find("div", class_ = "nr")
		for trans_box in trans_box_list :
			if (isinstance(trans_box, str)) : 
				trans_str += trans_box.strip()
			elif (trans_box.name != 'a') :
				trans_str += trans_box.text.strip()
		trans_str = trans_str.replace('\n', "").replace('\r', "")
		output.append(trans_str)
		#print(trans_str, file = out_file)
	else :
		output.append("None")
		#print("None", file = out_file)
	lock.acquire()
	try :
		write_file(output)
	finally :
		lock.release()

def crawl(index) :
	parse(index, "https://www.gswen.cn/poetry/" + str(index) + ".html")

def work(l, r) :
	for index in range(l, r + 1) :
		print(index)
		crawl(index)

out_file = open("data.txt", "w")
start = 0
lock = threading.Lock()
threads = []
for i in range(20) :
	t = threading.Thread(target=work, args=(start + i * 3250 + 1, start + (i + 1) * 3250,))
	threads.append(t)
for i in range(20) :
	threads[i].start()
for i in range(20) :
	threads[i].join()

out_file.close()
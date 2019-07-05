import jieba
import re
def extract_pretty(line) :
	if line == "None" :
		return "None"
	result = pretty_pattern.findall(line)
	return "".join(result)
def extract_chinese(line) :
	if line == "None" :
		return "None"
	result = chinese_pattern.findall(line)
	return "".join(result)
def cut_sentence(line) :
	ret = []
	while True :
		searchObj = re.search(r"[，。！？,.!?]", line)
		if searchObj :
			s = line[:(searchObj.start()) + 1].strip()
			if (len(s)) :
				ret.append(s)
			line = line[(searchObj.start() + 1):]
		else :
			if (len(line.strip())) :
				ret.append(line.strip())
			return ret
	return ret
def cut_lines() :
	f = open("data.txt", "r")
	outf = open("sentence.txt", "w")
	lines = f.readlines()
	lines = [line.strip() for line in lines]
	for i in range(55760) :
		print(lines[i * 7], file = outf)
		print(lines[i * 7 + 1], file = outf)
		print(lines[i * 7 + 2], file = outf)
		print(lines[i * 7 + 3], file = outf)
		tags = lines[i * 7 + 4].split(" ")
		print(len(tags) - 1, file = outf)
		if (len(tags) != 1) :
			print("\n".join(tags[1:]), file = outf)
		print(lines[i * 7 + 5], file = outf)
		line = extract_pretty(lines[i * 7 + 5])
		sentences = cut_sentence(line)
		print(len(sentences), file = outf)
		print("\n".join(sentences), file = outf)
		line = extract_pretty(lines[i * 7 + 6])
		sentences = cut_sentence(line)
		print(len(sentences), file = outf)
		print("\n".join(sentences), file = outf)
	f.close()
	outf.close()
def cut_word() :
	f = open("sentence.txt", "r")
	outf = open("cut.txt", "w")
	p_id = f.readline().strip()
	while (p_id != "") :
		p_name = f.readline().strip()
		p_author = f.readline().strip()
		p_dynasty = f.readline().strip()
		num_of_tags = f.readline().strip()
		print(p_id, file = outf)
		print(p_name, file = outf)
		print(p_author, file = outf)
		print(p_dynasty, file = outf)
		print(num_of_tags, file = outf)
		for i in range(int(num_of_tags)) :
			tag = f.readline().strip()
			print(tag, file = outf)
		content = f.readline().strip()
		print(content, file = outf)
		num_of_lines = f.readline().strip()
		print(num_of_lines, file = outf)
		for i in range(int(num_of_lines)) :
			line = f.readline().strip()
			print(line, file = outf)
		num_of_lines = f.readline().strip()
		print(num_of_lines, file = outf)
		for i in range(int(num_of_lines)) :
			line = f.readline().strip()
			if (line == "None") :
				print("None", file = outf)
			else :
				seg_list = jieba.cut(extract_chinese(line))
				print(" ".join(seg_list), file = outf)
		p_id = f.readline().strip()
	f.close()
	outf.close()

pretty_pattern = re.compile(r'[\u4e00-\u9fa5，0-9。！？：；‘’“”、,.!?:;\'\"]+')
chinese_pattern = re.compile(r'[\u4e00-\u9fa5]+')
cut_lines()
cut_word()

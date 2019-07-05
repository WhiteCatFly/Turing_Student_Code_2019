import gensim

def train() :
	f = open("cut.txt", "r")
	sentences = []
	p_id = f.readline().strip()
	while (p_id != "") :
		f.readline()
		f.readline()
		f.readline()
		tag_num = f.readline().strip()
		for i in range(int(tag_num)) :
			tag = f.readline().strip()
			sentences.append([tag])
		f.readline()
		line_num = f.readline().strip()
		for i in range(int(line_num)) :
			f.readline()
		line_num = f.readline().strip()
		for i in range(int(line_num)) :
			line = f.readline().strip()
			sentence = line.split(" ")[:-1]
			if (len(sentence)) :
				sentences.append(sentence)
		p_id = f.readline().strip()
	model = gensim.models.Word2Vec(sentences, size = 100, min_count = 1, iter = 100)
	model.save("my_w2v.model")
	f.close()

def calc_vec() :
	f = open("cut.txt", "r")
	outf = open("vec.txt", "w")
	model = gensim.models.Word2Vec.load("my_w2v.model")
	p_id = f.readline().strip()
	while (p_id != "") :
		sentences = []
		f.readline()
		f.readline()
		f.readline()
		tag_num = f.readline().strip()
		for i in range(int(tag_num)) :
			tag = f.readline().strip()
			sentences.append([tag])
		f.readline()
		line_num = f.readline().strip()
		for i in range(int(line_num)) :
			f.readline()
		line_num = f.readline().strip()
		for i in range(int(line_num)) :
			line = f.readline().strip()
			sentence = line.split(" ")[:-1]
			if (len(sentence)) :
				sentences.append(sentence)
		print(p_id, file = outf)
		print(len(sentences), file = outf)
		for sentence in sentences :
			vec = 0
			for word in sentence :
				vec += model[word]
			vec /= len(sentence)
			for dim in vec :
				print(dim, end = " ", file = outf)
			print("", file = outf)
		p_id = f.readline().strip()
	f.close()
	outf.close()

train()
calc_vec()

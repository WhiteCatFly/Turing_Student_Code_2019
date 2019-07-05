f = open("cut.txt", "r")
outf = open("poem.txt", "w")
p_id = f.readline().strip()
while (p_id != "") :
	p_name = f.readline().strip()
	p_author = f.readline().strip()
	p_dynasty = f.readline().strip()
	num_of_tags = f.readline().strip()
	for i in range(int(num_of_tags)) :
		f.readline()
	f.readline()
	num_of_lines = f.readline().strip()
	lines = []
	for i in range(int(num_of_lines)) :
		lines.append(f.readline().strip())
	num_of_lines = f.readline().strip()
	for i in range(int(num_of_lines)) :
		f.readline()
	print(p_id, file = outf)
	ret_title = p_name
	if (p_author != "None") :
		ret_title += " " + p_author
	if (p_dynasty != "None") :
		ret_title += " " + p_dynasty
	print(ret_title, file = outf)
	#至少4行，每行至多30
	lenth = len("".join(lines))
	lenth_per_line = min(30, lenth / 4)
	new_lines = [""]
	cur_lenth = 0
	num_of_lines = 0
	for line in lines :
		cur_lenth += len(line)
		new_lines[-1] = new_lines[-1] + line
		if (cur_lenth >= lenth_per_line) :
			cur_lenth = 0
			num_of_lines += 1
			if (num_of_lines > 5) :
				new_lines.append("......")
				break
			new_lines.append("")
	if (new_lines[-1] == "") :
		new_lines.pop(-1)
	print(len(new_lines), file = outf)
	print("\n".join(new_lines), file = outf)
	p_id = f.readline().strip()
f.close()
outf.close()
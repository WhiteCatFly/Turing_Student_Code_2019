command-line argument:
	choose one from two commands:
	--parse WEBSITE NUM NAME
		parse WEBSITE and save the result to file NAME
		NUM = 1 : title
			  2 : text
			  3 : link
			  4 : custom(input a regex)
	--crawl WEBSITE
		crawl WEBSITE and save it
		if a web name is http://info.ruc.edu.cn/en/index.php, it will be saved as a file named website/http:__info_ruc_edu_cn_en_index_php
		
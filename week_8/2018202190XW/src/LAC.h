#ifndef LAC_H_INCLUDED
#define LAC_H_INCLUDED

typedef std::vector<std::pair<std::string, std::string> > THULAC_result;

class LAC {
	THULAC my_lac;
	public:
	LAC() {
		my_lac.init(NULL, NULL, 0, 0, 0, '_');
	}
	THULAC_result cut(std::string str) {
		THULAC_result ret;
		my_lac.cut(str, ret);
		return ret;
	}
};

#endif
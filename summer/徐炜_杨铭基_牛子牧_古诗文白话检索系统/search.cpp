#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include "KD_Tree.h"
using namespace std;

struct myvector {
	float a[100];
};
vector<pair<int, float>> a;
inline float calc_dis(struct myvector x, struct myvector y) {
	float ret = 0;
	for (int i = 0; i < 100; i++) ret += (x.a[i] - y.a[i]) * (x.a[i] - y.a[i]);
	return sqrt(ret);
}
float min(float x, float y) {
	if (x < y) return x;
	return y;
}
bool cmp(pair<int, float> a, pair<int, float> b) {
	return a.second < b.second;
}
int id, cnt;
float min_dis;
clock_t startTime;
double useTime;
struct myvector tmp, myvec;
int main(int argv, char **argc) {
	FILE *fp = fopen("../data/vec.bin", "rb");
	for (int i = 0; i < 100; i++) {
		myvec.a[i] = atof(argc[i + 1]);
	}
	while (fread(&id, 1, sizeof(int), fp) == sizeof(int)) {
		min_dis = 10000;
		fread(&cnt, 1, sizeof(int), fp);
		for (int j = 0; j < cnt; j++) {
			for (int i = 0; i < 100; i++) {
				fread(&tmp.a[i], 1, sizeof(float), fp);
			}
			min_dis = min(min_dis, calc_dis(myvec, tmp));
		}
		a.push_back(make_pair(id, min_dis));
	}
	sort(a.begin(), a.end(), cmp);
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i].first);
	}
	fclose(fp);
	return 0;
}
#include <stdio.h>
int id, cnt;
float x;
int main() {
    FILE *fpin, *fpout;
    fpin = fopen("vec.txt", "r");
    fpout = fopen("vec.bin", "wb");
    while (fscanf(fpin, "%d", &id) == 1) {
        fwrite(&id, 1, sizeof(int), fpout);
        fscanf(fpin, "%d", &cnt);
        fwrite(&cnt, 1, sizeof(int), fpout);
        for (int i = 0; i < cnt; i++) {
            for (int j = 0; j < 100; j++) {
                fscanf(fpin, "%f", &x);
                fwrite(&x, 1, sizeof(float), fpout);
            }
        }
    }
	fclose(fpin);
	fclose(fpout);
    return 0;
}
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace(char *des, char *src, char *tar, int *aMode, int *iMode, int *c);

int main(int argc, char **argv) {
		//if(argc < 3) exit(0);
		int iMode = 1, aMode = 0;
		int i, j;
		char *src_pat, *tar_pat;
		src_pat = *(argv + argc - 3);
		tar_pat = *(argv + argc - 2);
		FILE *fptr = fopen("data.txt", "r");

		char *buf = malloc(10000 * sizeof(char));
		int c = 0;
		while(fgets(buf, 2000, fptr) != 0) {
				printf("%s", replace(buf, src_pat, tar_pat, &aMode, &iMode, &c));
				c++;
		}
		free(buf);
		return 0;
}

char *replace(char *des, char *src, char *tar, int *aMode, int *iMode, int *c) {
		char *head, *tail;
		tail = alloca(10000 * sizeof(char));
		if(*c > 0 && *aMode == 0) return des;
		if((head = *iMode ? strcasestr(des, src)  :  strstr(des, src)) != 0) {
				strcpy(tail ,head + strlen(src));
				*head = '\0';
				strcat(des, tar);
				if(*aMode == 0) {
						return strcat(des, tail);
				}
				strcat(des, replace(tail, src, tar, aMode, iMode, c));
		}
		return des;
}


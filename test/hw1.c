#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace(char *des, char *src, char *tar, int *aMode, int *iMode, int *c);

int main(int argc, char **argv) {
		if(argc < 2) exit(0);
		int iMode = 0, aMode = 0;
		int i, j;
		char *src_pat, *tar_pat;
		src_pat = *(argv + argc - 2);
		tar_pat = *(argv + argc - 1);
		for(i = 1; i < argc - 2; i++) {
				char *tmp = *(argv + i);
				if(tmp[0] == '-') {
						for(j = 1; j < (int)strlen(tmp); j++) {
								switch(tmp[j]) {
										case 'a':
												aMode = 1;
												break;
										case 'i':
												iMode = 1;
												break;
								}
						}
				}
		}

		char *buf = malloc(10000 * sizeof(char));
		int c = 0;
		while(fgets(buf, 2000, stdin) != 0) {
				printf("%s", replace(buf, src_pat, tar_pat, &aMode, &iMode, &c));
				c++;
		}
		free(buf);
		return 0;
}

char *replace(char *des, char *src, char *tar, int *aMode, int *iMode, int *c) {
		char *head, *tail;
		tail = alloca(10000 * sizeof(char));
		if(*c && !*aMode) return des;
		if((head = *iMode ? strcasestr(des, src)  :  strstr(des, src)) != 0) {
				strcpy(tail ,head + strlen(src));
				*head = '\0';
				strcat(des, tar);
				if(!*aMode) {
						return strcat(des, tail);
				}
				strcat(des, replace(tail, src, tar, aMode, iMode, c));
		}
		return des;
}


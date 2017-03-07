#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
	int iMode = 0, cMode = 0, nMode = 0, vMode = 0;
	int i, j, imHereC = 0, line = 0;
	FILE *fPtr = fopen(*(argv + argc - 1), "r");
	if(fPtr == 0) {
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	if(argc < 3) {
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	char *pattern = *(argv + argc - 2);
	char *buf = malloc(20000 * sizeof(char));
	for(i = 1; i < argc - 2; i++) {
		char *tmp = *(argv + i);
		for(j = 0; j < (int)strlen(tmp); j++) {
			switch(tmp[j]) {
				case 'i': 
					iMode = 1;
					break;
				case 'c': 
					cMode = 1;
					break;
				case 'n': 
					nMode = 1;
					break;
				case 'v': 
					vMode = 1;
					break;
				default:
					break;
			}
		}
	}
	if((cMode == 1 && nMode == 1)) {
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	while(fgets(buf, 20000, fPtr) != 0) {
		int imHere = 0;
		j = 0;
		if(strstr(buf, pattern) != 0 && imHere == 0 && iMode == 0) {
			imHere = 1;
		}       
		if(strcasestr(buf, pattern) != 0 && imHere == 0 && iMode == 1) {
			imHere = 1;
		}       
		if(imHere == 1) {
			imHereC++;
			if(cMode == 0 && vMode == 0) {
				if(nMode == 1) {
					printf("%d:", line + 1);
				}
				printf("%s", buf);
			}
		}
		else if(cMode == 0 && vMode == 1) {
			if(nMode == 1) {
				printf("%d:", line + 1);
			}
			printf("%s", buf);
		}
		line++;
	}
	fclose(fPtr);
	free(buf);
	if(cMode == 1) {
		printf("%d\n", vMode == 1 ? line - imHereC : imHereC);
	}
	/*if(vMode == 0 && imHereC == 0) {
		printf("\n");
	}
	if(vMode == 1 && line - imHereC == 0) {
		printf("\n");
	}*/
	return 0;
}


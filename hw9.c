#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LineNum(char *a);
char **toLine(FILE *input, int *index);

int main(int argc, char **argv) {
		FILE *fPtr;
		char *para, mode = 0;
		if(argc == 2) {
				fPtr = fopen(argv[1], "r");
		}
		if(argc == 3) {
				para = *(argv + 1);
				mode = *(para + 1);
				fPtr = fopen(argv[2], "r");
		}
		int i, j, *index = malloc(sizeof(int));
		char **result = toLine(fPtr, index);
		fclose(fPtr);
		for(i = 0; i < *index; i++) {
				for(j = 1; j < *index; j++) {
						char *up = *(result + j - 1);
						char *down = *(result + j);
						if(mode == 0) {
								if(strcmp(up, down) >= 1) {
										char *tmp;
										tmp = *(result + j - 1);
										*(result + j - 1) = *(result + j);
										*(result + j) = tmp;
								}
						}
						if(mode == 'r') {
								if(strcmp(up, down) <= -1) {
										char *tmp;
										tmp = *(result + j - 1);
										*(result + j - 1) = *(result + j);
										*(result + j) = tmp;
								}
						}
						if(mode == 'n') {
								if(LineNum(up) > LineNum(down)) {
										char *tmp;
										tmp = *(result + j - 1);
										*(result + j - 1) = *(result + j);
										*(result + j) = tmp;
								}
						}
				}
		}
		for(i = 0; i < *index; i++) {
				printf("%s", *(result + i));
		}
		free(result);
		return 0;
}
int LineNum(char *a) {
		int i;
		for(i = 0; i < (int)strlen(a); i++) {
				if(*(a + i) >= '0' && *(a + i) <= '9') {
						return atoi((a + i));
				}
		}
		return 0;
}
char **toLine(FILE *input, int *index) {
		int lineSize = 1000;
		char *buf= malloc(2000 * sizeof(char));
		int i, j;
		char **output = malloc(lineSize * sizeof(char*));
		i = j = 0;
		while(fgets(buf, 2000, input) != 0) {
				if(i >= lineSize) {
						lineSize *= 2;
						*output = realloc(output, lineSize * sizeof(char*));
				}
				*(output + i) = buf;
				buf = 0;
				buf = malloc(2000 * sizeof(char));
				i++;
		}
		free(buf);
		*index = i;
		return output;
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define IN 1
#define OUT 0

void result(char *a, int length);
int isUp(int a);
int isLow(int a);
int isNum(int a);
int main() {
		int c;
		int count = 0, size = 100;
		char *file = malloc(size * sizeof(char));
		while((c = getchar()) != EOF) {
				if(count >= size) {
						size *= 2;
						file = realloc(file, size * sizeof(char));
				}
				*(file + count) = c;
				count++;
		}
		result(file, count);
		free(file);

		return 0;
}

void result(char *a, int length) {
		int c = 0, buf;
		int wordC = 0, wordsC = 0, line = 0, convertC = 0, firstABC = 0, state = OUT;
		char *tolow = malloc(length * sizeof(char));
		while(c < length) {
				buf = *(a + c);
				*(tolow + c) = tolower(buf);
				c++;
				if(buf == '\n') {
						line++;
				}
				if(buf != ' ' && buf != '\n' && buf != '\t') {
						if(state == OUT && (isUp(buf) || isLow(buf))) {
								firstABC = 1;
						}
						state = IN;
				}
				else if(state == IN && (buf == ' ' || buf == '\n' || buf == '\t')) {
						if(firstABC == 1) {
								wordsC++;
						}
						firstABC = 0;
						wordC = 0;
						state = OUT;
				}
				if(state == IN && firstABC == 1) {
						wordC++;
				}
				if(isUp(buf) == 1) {
						convertC++;
				}
		}
		printf("Total character:%d\nWord count:%d\nLine:%d\n--original--\n", length, wordsC, line);
		printf("%s", a);
		printf("--lower case--\n");
		printf("%s", tolow);
		printf("--count--\nupper case to lower case:%d\n", convertC);
		free(tolow);
}
int isUp(int a) {
		return a >= 'A' && a <= 'Z';
}
int isLow(int a) {
		return a >= 'a' && a <= 'z';
}
int isNum(int a) {
		return a >= '0' && a <= '9';
}

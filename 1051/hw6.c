#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX 2000
#define IN 1
#define OUT 0

int isUppercase(int a);
int isLowercase(int a);
int isNum(int a);
int isNext(int a);
void reverse(char arr[]);

int main() {
		int c = 0, i = 0, j = 0, maxWordC = 0;
		int wordC = 0, firstNum = FALSE, state = OUT, maxhead = i, charCount[3] = {};
		char data[MAX] = {};
		while((c = getchar()) != EOF) {
				data[i++] = c;
				if(isUppercase(c) || isLowercase(c) || isNum(c)) {
						if(wordC == 0 && isNum(c)) {
								firstNum = TRUE;
						}
						state = IN;
				}
				if(isNext(c)) {
						if(wordC > maxWordC) {
								maxWordC = wordC;
								maxhead = i - maxWordC - 1;
						}
						firstNum = FALSE;
						wordC = 0;
						state = OUT;
				}
				if(state == IN && firstNum == FALSE) {
						wordC++;
				}
				if(isUppercase(c)) {
						charCount[0]++;
				}
				if(isLowercase(c)) {
						charCount[1]++;
				}
				if(isNum(c)) {
						charCount[2]++;
				}
		}
		if(c == EOF) {
				if(wordC > maxWordC) {
						maxWordC = wordC;
						maxhead = i - maxWordC - 1;
				}
		}
		printf("maxWordC = %d\n", maxWordC);
		data[MAX - 1] = '\0';
		char maxWord[maxWordC + 1];
		for(i = 0; i < maxWordC; i++) {
				maxWord[i] = data[maxhead + i];
		}
		maxWord[maxWordC] = '\0';
		if(charCount[1] > 0) {
				printf("Uppercase / Lowercase¡G%.3f\n", (float)charCount[0] / charCount[1]);
		}
		else {
				printf("Uppercase / Lowercase¡G0 (There has no lowercase)\n");
		}
		if((charCount[0] + charCount[1]) > 0) {
				printf("Digit / Alphabet¡G%.3f\n", (float)charCount[2] / (charCount[0] + charCount[1]));
		}
		else {
				printf("Digit / Alphabet¡G0 (There has no alphabet)\n");
		}
		printf("--- Reverse ---\n");
		reverse(data);
		printf("The longest word is: %s (%d)\n", maxWord, maxWordC);
		printf("%d\n", maxWordC);

		return 0;
}

int isUppercase(int a) {
		return a >= 'A' && a <= 'Z';
}
int isLowercase(int a) {
		return a >= 'a' && a <= 'z';
}
int isNum(int a) {
		return a >= '0' && a <= '9';
}
int isNext(int a) {
		return a == ' ' || a == ',' || a == '&' || a == '(' || a == ')' || a == '\n' || a == '\t';
}
void reverse(char arr[]){
		int i;
		for(i = (strlen(arr) - 1); i >=0 ; i--) {
				printf("%c", arr[i]);
		}
		printf("\n");
}


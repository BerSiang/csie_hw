#include <stdio.h>

#define IN 1
#define OUT 0

int main(void) {
		int c, i = 0;
		int wCount = 0, wLongCount = 0, abcTotal = 0, lineTotal = 0;
		int maxWordLine = 0, maxWordC = 0;
		int state = OUT, firstValid = 0;	//state �O�_�b��r��(IN, OUT), firstNum ����O�_���Ʀr(0���_, 1���O) 
		int abcCount[26] = {};	//abc����
		float abcFre[26] = {};	//abc[1][] �W�v
		char word[100000] = {};

		/*	WordCount	*/
		while((c = getchar()) != EOF) {
				if(isUpperCase(c) || isLowerCase(c) || isOther(c)) {	//�P�_�O�_���r(�j�p�g�B�Ʀr)
						state = IN;
						if(wLongCount == 0 && (isOther(c) || c == '&')) {	//����O�_���Ʀr
								firstValid = 1;
						}

				}
				if(isNext(c)) {
						state = OUT;
						if(wLongCount != 0) {	//�]��o�AwLongCount����0�ɡA�N��@�ӳ�r����
								lineTotal++;
								word[i++] = '\n';
								if(wLongCount > maxWordC) {	//�����̪���r�渹
										maxWordC = wLongCount;
										maxWordLine = lineTotal;
								}
								wLongCount = 0;	//���m
								wCount++;
						}
						firstValid = 0;	//���m
				}
				if(state == IN && firstValid == 0) {	//���r
						if(isUpperCase(c) || isLowerCase(c) || isNum(c) || isOther(c)) {
								wLongCount++;
						}
						word[i++] = c;
				}
				if(isUpperCase(c)) {	//��r���`��(�j�g)
						abcCount[c - 'A']++;
						abcTotal++;
				}
				if(isLowerCase(c)) {	//��r���`��(�p�g)
						abcCount[c - 'a']++;
						abcTotal++;
				}
		}

		/* Frequency, MaxFre & minFre Count	*/
		int j = 0, maxIndex = 0, minIndex = 0;
		for(j = 0; j < 26; j++) {
				if(abcTotal != 0) {
						abcFre[j] = (float)abcCount[j] / abcTotal;
				}
				else {
						abcFre[j] = 0;
				}
				if(abcFre[maxIndex] < abcFre[j]) {
						maxIndex = j;
				}
				if(abcFre[minIndex] > abcFre[j]) {
						minIndex = j;
				}
		}

		/*	Max Word	*/
		char maxWord[maxWordC];
		int x = 0, y = 1, z = 0;
		while(y < maxWordLine) {
				if(word[x++] == '\n') {
						y++;
						while(y == maxWordLine && word[x] != '\n') {
								maxWord[z++] = word[x++];
						}
				}
		}
		maxWord[maxWordC] = '\0';


		/*	Output	*/
		printf("Word count: %d\n%s\n", wCount, word);
		printf("Total: %d\n--Alphabet--\n", abcTotal);
		for(j = 0; j < 26; j++) {
				printf("%c:%3d, %1.3f\n", j + 'a', abcCount[j], abcFre[j]);
		}
		printf("\nAvg = %.3f\n", (float)1/26);
		printf("Max: %c:%3d, %1.3f\n", maxIndex + 'a', abcCount[maxIndex], abcFre[maxIndex]);
		printf("Min: %c:%3d, %1.3f\n", minIndex + 'a', abcCount[minIndex], abcFre[minIndex]);
		printf("\nThe longest word: %s(%d)\n", maxWord, maxWordC);
		//printf("%s\n%d", maxWord, maxWordC);
		/*	End of Output	*/
}
/*	Word Distinguish	*/
int isUpperCase(int a) {
		return a >= 'A' && a <= 'Z';
}
int isLowerCase(int a) {
		return a >= 'a' && a <= 'z';
}
int isNum(int a) {
		return a >= '0' && a <= '9';
}
int isNext(int a) {
		return a == '&' || a == ' ' || a == '\t' || a == '\n' || a == ',';
}
int isOther(int a) {
		if((a > 32 && a < 126) && isUpperCase(a) == 0 && isLowerCase(a) == 0 && isNext(a) == 0) {
				return 1;
		}
		else {
				return 0;
		}
}

#include <stdio.h>

#define IN 1
#define OUT 0

int main(void) {
		int c, i = 0;
		int wCount = 0, wLongCount = 0, abcTotal = 0, lineTotal = 0;
		int maxWordLine = 0, maxWordC = 0;
		int state = OUT, firstValid = 0;	//state 是否在單字內(IN, OUT), firstNum 首位是否為數字(0為否, 1為是) 
		int abcCount[26] = {};	//abc次數
		float abcFre[26] = {};	//abc[1][] 頻率
		char word[100000] = {};

		/*	WordCount	*/
		while((c = getchar()) != EOF) {
				if(isUpperCase(c) || isLowerCase(c) || isOther(c)) {	//判斷是否為字(大小寫、數字)
						state = IN;
						if(wLongCount == 0 && (isOther(c) || c == '&')) {	//首位是否為數字
								firstValid = 1;
						}

				}
				if(isNext(c)) {
						state = OUT;
						if(wLongCount != 0) {	//跑到這，wLongCount不為0時，代表一個單字結束
								lineTotal++;
								word[i++] = '\n';
								if(wLongCount > maxWordC) {	//紀錄最長單字行號
										maxWordC = wLongCount;
										maxWordLine = lineTotal;
								}
								wLongCount = 0;	//重置
								wCount++;
						}
						firstValid = 0;	//重置
				}
				if(state == IN && firstValid == 0) {	//算單字
						if(isUpperCase(c) || isLowerCase(c) || isNum(c) || isOther(c)) {
								wLongCount++;
						}
						word[i++] = c;
				}
				if(isUpperCase(c)) {	//算字母總數(大寫)
						abcCount[c - 'A']++;
						abcTotal++;
				}
				if(isLowerCase(c)) {	//算字母總數(小寫)
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

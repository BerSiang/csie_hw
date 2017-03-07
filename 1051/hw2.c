#include<stdio.h>

int main() {
		int c;
		int lineCount = 0, vowelCount = 0, numCount = 0, total = 0;
		while((c = getchar()) != EOF){
				if(c == '\n'){
						lineCount++;
				}
				if(c == 'a' | c == 'e' | c == 'i' | c == 'o' | c == 'u'){
						vowelCount++;
				}
				if(c >= 48 && c <= 57){
						numCount++;
				}
				total++;
		}
		printf("Line:%d\nVowel:%d\nNumber:%d\nTotal:%d\n", lineCount, vowelCount, numCount, total);
		return 0;
}

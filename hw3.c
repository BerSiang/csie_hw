#include <stdio.h>
#include <ctype.h>

int main() {
		int c = 0;
		int total = 0, numCount = 0, abcCount = 0; 
		int Count[256] = {};
		while((c = getchar()) != EOF) {
				Count[c]++;
				total++;
				if(c >= 48 && c <= 57) {
						numCount += 1;
				}
				if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
						abcCount += 1;
				}
		}
		unsigned char num, abc;

		printf("Total characters:%3d\n", total);
		printf("Other characters:%3d\n", total - numCount - abcCount);

		printf("-----------number----------\n");
		if(numCount != 0) {
				for(num = 48; num <= 52; num++) { 	// number ascii 48~57
						printf("%c: %2d, %2.3f", num, Count[num], (float)Count[num] / total);
						printf("%5c: %2d, %2.3f\n", num + 5, Count[num + 5], (float)Count[num + 5] / total);
				}
		}
		else {
				printf("This file hasn't any number.\n");
		}

		printf("----------alphabet---------\n");
		if(abcCount != 0) {
				for(abc = 97; abc <= 109; abc++) {	// alphabet ascii 97~122
						int tmpA = Count[abc] + Count[abc - 32];	// A~Z 65~90, a~z 97~122 
						int tmpB = Count[abc + 13] + Count[abc + 13 - 32];
						printf("%c: %2d, %2.3f", abc, tmpA, (float)tmpA / total);
						printf("%5c: %2d, %2.3f\n", abc + 13, tmpB, (float)tmpB / total);
				}
		}
		else {
				printf("This file hasn't any alphabet.\n");
		}

		printf("------------end------------\n");

		return 0;
}

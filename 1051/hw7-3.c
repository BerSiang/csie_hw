#include <stdio.h>

void star(int a);
int main() {
		int input;
		while(scanf("%d", &input) != EOF) {
				printf("----------n = %d----------\n", input);
				star(input);
		}
		return 0;
}

void star(int a) {
		if(a < 3) {
				printf("n can't small than 3.");
				return;
		}
		if(a % 2 == 0) {
				printf("n is not an odd number.\n");
				return;
		}
		int i = (a - 1) / 2, j = 1, r = 0, c;
		for(c = 0; c < a; c++) {
				int x;
				for(x = 0; x < i; x++) {
						printf(" ");
				}
				for(x = 0; x < j; x++) {
						printf("*");
				}
				printf("\n");
				if(j >= a) {
						r = 1;
				}
				if(r == 0) {
						i--;
						j += 2;
				}
				if(r == 1) {
						i++;
						j -= 2;
				}
		}
		return;
}

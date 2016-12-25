#include <stdio.h>
#include <math.h>

int isPrime(int);
void sort(int[], int);
int main(){
		int c, i = 0, input[1000];
		while(scanf("%d", &c) != EOF) {
				input[i++] = c;
		}
		for(c = 0; c < i; c++) {
				printf("%d: %s\n", input[c], isPrime(input[c]) ? "yes" : "no");
		}
		printf("\n-----------------Sort-----------------\n");
		sort(input, i);
		for(c = 0; c < i; c++) {
				printf("%d\n", input[c]);
		}
}

int isPrime(int a) {
		int i, k = 1;
		if(a <= 1) {
				return 0;
		}
		for(i = 2; i < sqrt(a); i++) {
				if(a % i == 0) {
						k = 0;
				}
				if(a < 0) {
						k = 0;
				}
		}
		return k;
}
void sort(int data[], int n) {
		int i, j;
		for(i = 0; i < n; i++) {
				for(j = 0; j < n - 1; j++) {
						if(data[j] > data[j + 1]) {
								int tmp;
								tmp = data[j];
								data[j] = data[j + 1];
								data[j + 1] = tmp;
						}
				}
		}
		return;
}

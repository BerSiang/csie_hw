#include <stdio.h>
#include <string.h>

int gcd(int, int);
int lcm(int, int);
int main() {
		int c, input[2][1000] = {0}, i = 0, j = 0;
		char buf[1000];
		while(fgets(buf, 1000, stdin) != NULL) {
				sscanf(buf, "%d%*[^0-9]%d", &i, &j);
				printf("-------%d, %d-------\n", i, j);
				printf("gcd = %d\n", gcd(i, j));
				printf("lcm = %d\n", lcm(i, j));
		}
		/*while((c = getchar()) != EOF) {
				if(c >= '0' && c <= '9') {
						input[j % 2][i] *= 10;
						input[j % 2][i] += c - '0';
				}
				if(c == ' ') {
						j++;
				}
				if(c == '\n') {
						i++;
				}
		}
		for(j = 0; j < i; j++) {
				printf("-------%d, %d-------\n", input[0][j], input[1][j]);
				printf("gcd = %d\n", gcd(input[0][j], input[1][j]));
				printf("lcm = %d\n", lcm(input[0][j], input[1][j]));
		}*/
}
int gcd(int a, int b) {
		int x, max = a, min = b;
		if(max < 0 || min < 0) {
				return -1;
		}
		if(max < min) {
				max = b, min = a;
		}
		if(max == 0) {
				return min;
		}
		if(min == 0) {
				return max;
		}
		for(x = min; x > 0; x--) {
				if((max % x == 0) && (min % x == 0)) {
						return x;
				}
		}
		return -1;
}
int lcm(int a, int b) {
		int x, max = a, min = b;
		if(max < min) {
				max = b, min = a;
		}
		if(max == 0 || min == 0) {
				return -1;
		}
		for(x = 1;x <= min; x++) {
				if((x * max) % min == 0) {
						return x * max;
				}
		}
		return -1;
}

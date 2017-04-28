#include <stdio.h>
#include <stdlib.h>

int main() {
		int a, b;
		while(1) {
				printf("a:");
				scanf("%d", &a);
				printf("\nb:");
				scanf("%d", &b);
				printf("%d\n", a | b);
				printf("%d\n", a & b);
		}
}

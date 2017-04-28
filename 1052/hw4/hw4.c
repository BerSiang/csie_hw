#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(X, Y, T) (T)=(X),(X)=(Y),(Y)=(T)

typedef struct word {
		char value[200];
		int count;
}word;

int main() {
		word data[2000];
		int dataCount = 0, i;
		char *buf = malloc(1024 * sizeof(char));
		while(fgets(buf, 1024, stdin) != NULL) {
				if(buf[strlen(buf) - 1] == '\n') {
						buf[strlen(buf) - 1] = '\0';
				}
				if(buf[0] == '\0') continue;
				int find = 0;
				for(i = 0; i < dataCount; i++) {
						if(strcmp(data[i].value, buf) == 0) {
								data[i].count++;
								find = 1;
						}
				}
				if(find == 1) continue;
				strcpy(data[dataCount].value, buf);
				data[dataCount].count++;
				dataCount++;
		}
		int n = dataCount;
		for(i = 0; i < n; i++) {
				int j;
				for(j = 0; j < n - 1; j++) {
						if(data[j].count < data[j + 1].count) {
								word t;
								SWAP(data[j], data[j + 1], t);
						}
						if(strcmp(data[j].value, data[j + 1].value) > 0 && data[j].count == data[j + 1].count) {
								word t;
								SWAP(data[j], data[j + 1], t);
						}		
				}
		}
		for(i = 0; i < dataCount; i++) {
				printf("%d %s\n", data[i].count, data[i].value);
		}
		return 0;
}

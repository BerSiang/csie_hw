#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
		int iMode = 0, cMode = 0, nMode = 0, vMode = 0;
		int i, j;
		FILE *fPtr = fopen(*(argv + argc - 1), "r");
		char *pattern = *(argv + argc - 2);
		char *buf = malloc(20000 * sizeof(char));
		for(i = 1; i < argc - 2; i++) {
				char *tmp = *(argv + i);
				for(j = 0; j < strlen(tmp); j++) {
						switch(tmp[j]) {
								case 'i': 
										iMode = 1;
										break;
								case 'c': 
										cMode = 1;
										break;
								case 'n': 
										nMode = 1;
										break;
								case 'v': 
										vMode = 1;
										break;
								default:
										break;
						}
				}
		}
		if((cMode && nMode) || (cMode && vMode)) {
				printf("error");
				exit(EXIT_FAILURE);
		}
		while(fgets(buf, 20000, fPtr) != 0) {
				int imHere = 0, line = 0, imHereC = 0;// head = 0;
				for(i = 0; i < strlen(buf); i++) {
						if(buf[i] == pattern[0] && imHere == 0) {
								imHere = 1;
								j = 0; 
						}       
						if(tolower(buf[i]) == tolower(pattern[0]) && imHere == 0 && iMode == 1) {
								imHere = 1;
								j = 0; 
						}       
						if(imHere == 1) {
								if(buf[i] != pattern[j++]) {
										imHere = 0;
								}       
						}       
						if(imHere == 1 && iMode == 1) {
								if(tolower(buf[i]) != tolower(pattern[j++])) {
										imHere = 0;
								}
						}
				}
				line++;
				if(imHere == 1) {
						imHereC++;
						if(nMode == 1) {
								printf("%d:", line);
						}
				}
		}
		return 0;
}


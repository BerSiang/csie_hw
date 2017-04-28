#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*compfn)(const void*, const void*);
typedef struct wordStat {
		struct wordStat *previous;
		char word[200];
		int count;
		struct wordStat *next;
}wordStat;

wordStat *createNode(char*, int);
void insertNode(wordStat*, wordStat*);
void removeNode(wordStat*);
void freeList(wordStat*);
wordStat *findList(wordStat*, char*);
void printList(wordStat*);
wordStat* sort(wordStat* list, int len); 
int comp(const void *p, const void *q);
int test(wordStat *p, wordStat *q);
int compStr(const void *p, const void *q);

int main(int argc, char** argv) {
		if(argc < 2) exit(EXIT_FAILURE);
		char* buf = (char*)malloc(1024 * sizeof(char));
		wordStat* head = (wordStat*)malloc(sizeof(wordStat));
		FILE *fptr = fopen(argv[1], "r");
		int len = 0;
		
		while(fgets(buf, 1024, fptr) != NULL) {
				if(buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = '\0';
				wordStat *tmp;
				if(buf[0] == '-') {
						if((tmp = findList(head, (buf + 1))) != NULL) {
								if(tmp->count != 1) {
										printf("--\n");
										tmp->count--;
										printf("%d\n", tmp->count);
								}
								else {
										removeNode(tmp);
										len--;
								}
						}
				}
				else {
						if((tmp = findList(head, buf)) == NULL) {
								insertNode(head, createNode(buf, 1));
								len++;
						}
						else {
								tmp->count++;
						}
				}

		}
		head = head->next;
		head = sort(head, len);
		printList(head);
		return 0;

}

wordStat *createNode(char* word, int count) {
		wordStat *out = (wordStat*)malloc(sizeof(wordStat));
		//out->word = malloc(200 * sizeof(char));
		strcpy(out->word, word);
		out->count = count;
		out->previous = NULL;
		out->next = NULL;
		return out;
}
void insertNode(wordStat* list, wordStat* tar) {
		wordStat* current = list;
		while(current->next != NULL) {
				current = current->next;
		}
		current->next = tar;
		tar->previous = current;
}
void removeNode(wordStat* tar) {
		tar->previous->next = tar->next;
}
wordStat *findList(wordStat* list, char* tar) {
		wordStat* current = list;
		while(current != NULL) {
				if(strcmp(current->word, tar) == 0) {
						return current;
				}
				current = current->next;
		}
		return 0;
}
void printList(wordStat* list) {
		wordStat* current = list;
		while(current != NULL) {
				printf("%s:\t%d\n", current->word, current->count);
				current = current->next;
		}
}
wordStat* sort(wordStat* list, int len) {
		wordStat* listAddr[len];
		wordStat* current = list;
		int i = 0;
		while(current != NULL) {
				listAddr[i++] = current;
				current = current->next;
		}
		qsort(listAddr, len, sizeof(listAddr[0]), comp);
		for(i = 0; i < len; i++) {
				//printf("%s: %d\n", listAddr[i]->word, listAddr[i]->count);
				if(i != 0) {
						listAddr[i]->previous = listAddr[i - 1]; 
				}   
				else {
						listAddr[i]->previous = NULL;
				}   
				if(i != len - 1) {
						listAddr[i]->next = listAddr[i + 1]; 
				}   
				else {
						listAddr[i]->next = NULL;
				}   
		}
		return listAddr[0];
}
int comp(const void *p, const void *q) {
		wordStat* tmpA = *(struct wordStat* const*)p;
		wordStat* tmpB = *(struct wordStat* const*)q;
		//printf("Count\tA(%s):%d(%p) B(%s):%d(%p)\n", tmpA->word, tmpA->count, tmpA, tmpB->word, tmpB->count, tmpB);
		if(tmpA->count == tmpB->count) {
				return strcmp(tmpA->word, tmpB->word);
		}
		return -(tmpA->count - tmpB->count);
}

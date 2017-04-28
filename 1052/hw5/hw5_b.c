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
int comp(const void *p, const void *q);
int test(wordStat *p, wordStat *q);
int compStr(const void *p, const void *q);

int main(int argc, char** argv) {
		char* buf = (char*)malloc(1024 * sizeof(char));
		wordStat* head = (wordStat*)malloc(sizeof(wordStat));
		FILE *fptr = fopen("./hw5_test/terms_3.txt", "r");
		//wordStat* tt = (wordStat*)malloc(sizeof(wordStat));
		//wordStat* yy = (wordStat*)malloc(sizeof(wordStat));
		//tt->count = 100;
		//yy->count = -200;
		//test(tt, yy);
		int i;
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
								}
						}
				}
				else {
						if((tmp = findList(head, buf)) == NULL) {
								insertNode(head, createNode(buf, 1));
						}
						else {
								tmp->count++;
						}
				}

		}
		strcpy(head->word, "123");
		head = head->next;
		printList(head);
		wordStat **listAddr, *current = head;
		listAddr = malloc(1000 * sizeof(wordStat*));
		int len = 0;
		while(current != NULL) {
				listAddr[len] = current;
				current = current->next;
				len++;
		}
		printf("Test\n");
		for(i = 0; i < len; i++) {
				printf("%s: %d\n", listAddr[i]->word, listAddr[i]->count);
		}
		printf("End Test\n");
		qsort(listAddr, len, sizeof(wordStat**), compStr);
		qsort(listAddr, len, sizeof(wordStat**), comp);
		printf("Test\n");
		for(i = 0; i < len; i++) {
				printf("%s: %d\n", listAddr[i]->word, listAddr[i]->count);
		}
		printf("End Test\n");
		for(i = 0; i < len; i++) {
				if(i != 0) {
						listAddr[i]->previous = listAddr[i - 1];
				}
				else {
						listAddr[i]->previous = NULL;
				}
				if(i != len) {
						listAddr[i]->next = listAddr[i + 1];
				}
				else {
						listAddr[i]->next = NULL;
				}
		}
		head = listAddr[0];
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
int comp(const void *p, const void *q) {
		wordStat* tmpA = (wordStat *)p;
		wordStat* tmpB = (wordStat *)q;
		/*if(tmpA->count > tmpB->count) {
		  return -1;
		  }
		  else if(tmpA->count < tmpB->count) {
		  return 1;
		  }
		  else {  //count: big -> small word: small -> big
		  return strcmp(tmpA->word, tmpB->word);
		  }*/
		//return 0;
		printf("Count\tA(%s):%d(%p) B(%s):%d(%p)\n", tmpA->word, tmpA->count, tmpA, tmpB->word, tmpB->count, tmpB);
		return tmpA->count - tmpB->count;
}
/*int test(const void *p, const void *q) {
  wordStat* tmpA = (wordStat *)p;
  wordStat* tmpB = (wordStat *)q;
  printf("Count\tA:%d B:%d\n", tmpA->count, tmpB->count);
  return 0;
  }*/
int test(wordStat *tmpA, wordStat *tmpB) {
		printf("Count\tA(%s):%d(%p) B(%s):%d(%p)\n", tmpA->word, tmpA->count, tmpA, tmpB->word, tmpB->count, tmpB);
		if (tmpA->count < tmpB->count)
				return -1;
		else if (tmpA->count > tmpB->count)
				return 1;
		else
				return 0;
}
int compStr(const void *p, const void *q) {
		wordStat *tmpA, *tmpB;
		tmpA = (wordStat*)p;
		tmpB = (wordStat*)q;
		//printf("Str:%d\n", strcmp(tmpA->word, tmpB->word));
		printf("Str\tA(%s):%d B(%s):%d\n", tmpA->word, tmpA->count, tmpB->word, tmpB->count);
		return strcmp(tmpA->word, tmpB->word);
}

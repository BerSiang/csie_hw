#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SWAP(X, Y, T) T=X,X=Y,Y=T

int *bub_sort(int *in, int *out, int len);
int *ins_sort(int *in, int *out, int len);
int *sele_sort(int *in, int *out, int len);
double bored(int *table, char fun, int len, int times);
int comp(const void * ,const void *); 

int main() {
		srand((unsigned) time(NULL) + getpid());
		int *rand_table = malloc(1000000 * sizeof(int));
		int i;
		for(i = 0; i < 1000000; i++) {
				rand_table[i] = (int)(1000000 * (double)rand() / (RAND_MAX + 1));
		}
		double exec_time[20] = {};
		i = 0;
		exec_time[i++] = bored(rand_table, 'i', 1000, 100);
		exec_time[i++] = bored(rand_table, 's', 1000, 100);
		exec_time[i++] = bored(rand_table, 'b', 1000, 100);
		exec_time[i++] = bored(rand_table, 'm', 1000, 100);
		exec_time[i++] = bored(rand_table, 'q', 1000, 100);

		exec_time[i++] = bored(rand_table, 'i', 10000, 10);
		exec_time[i++] = bored(rand_table, 's', 10000, 10);
		exec_time[i++] = bored(rand_table, 'b', 10000, 10);
		exec_time[i++] = bored(rand_table, 'm', 10000, 10);
		exec_time[i++] = bored(rand_table, 'q', 10000, 10);
		
		exec_time[i++] = bored(rand_table, 'i', 100000, 1);
		exec_time[i++] = bored(rand_table, 's', 100000, 1);
		exec_time[i++] = bored(rand_table, 'b', 100000, 1);
		exec_time[i++] = bored(rand_table, 'm', 100000, 1);
		exec_time[i++] = bored(rand_table, 'q', 100000, 1);

		i++;//bored(rand_table, 'i', 1000000, 1);
		i++;//bored(rand_table, 's', 1000000, 1);
		i++;//bored(rand_table, 'b', 1000000, 1);
		exec_time[i++] = bored(rand_table, 'm', 1000000, 1);
		exec_time[i++] = bored(rand_table, 'q', 1000000, 1);
		printf("---------- Execute Time ----------\n");
		printf("\t\t|\t%-8d\t|\t%-8d\t|\t%-8d\t|\t%-8d\n", 1000, 10000, 100000, 1000000);
		printf("Insertion Sort\t|\t%lf\t|\t%lf\t|\t%lf\t|\tX\t\n", exec_time[0], exec_time[5], exec_time[10]);
		printf("Selection Sort\t|\t%lf\t|\t%lf\t|\t%lf\t|\tX\t\n", exec_time[1], exec_time[6], exec_time[11]);
		printf("Bubble Sort\t|\t%lf\t|\t%lf\t|\t%lf\t|\tX\t\n", exec_time[2], exec_time[7], exec_time[12]);
		printf("Merge Sort\t|\t%lf\t|\t%lf\t|\t%lf\t|\t%lf\t\n", exec_time[3], exec_time[8], exec_time[13], exec_time[18]);
		printf("Quick Sort\t|\t%lf\t|\t%lf\t|\t%lf\t|\t%lf\t\n", exec_time[4], exec_time[9], exec_time[14], exec_time[19]);

		free(rand_table);
		return 0;
}

int *bub_sort(int *in, int *out, int len) {
		int i, j;
		memcpy(out, in, len * sizeof(int));
		for(i = 0; i < len; i++, len--) {
				for(j = 1; j < len; j++) {
						if(out[j - 1] > out[j]) {
								int t;
								SWAP(out[j -1], out[j], t);
						}
				}
		}
		return out;
}
int *ins_sort(int *in, int *out, int len) {
		int pValue, i, j;
		memcpy(out, in, len * sizeof(int));
		for(i = 0; i < len; i++) {
				pValue = out[i];
				for(j = i - 1; j >= 0; j--) {
						if(pValue < out[j]) {
								out[j + 1] = out[j];
								out[j] = pValue;
						}
				}
		}
		return out;
}
int *sele_sort(int *in, int *out, int len) {
		int i, j;
		memcpy(out, in, len * sizeof(int));
		for(i = 0; i < len; i++) {
				int min = i, t;
				for(j = i; j < len; j++) {
						if(out[j] < out[min]) {
								min = j;
						}
				}
				SWAP(out[i], out[min], t);
		}
		return out;
}
double bored(int *table, char fun, int len, int times) {
		int *compare_tmp = alloca(len * sizeof(int));
		int *out = alloca(len * sizeof(int));
		clock_t start_time, end_time, diff = 0;
		int i = 0;
		switch(fun) {
				case 'i':
						memcpy(compare_tmp, table, len * sizeof(int));
						start_time = clock();
						while(i++ < times) {
								ins_sort(compare_tmp, out, len);
						}
						end_time = clock();
						memcpy(compare_tmp, out, len * sizeof(int));
						printf("----- Insertion Sort, n = %d -----\n", len);
						break;
				case 's':
						memcpy(compare_tmp, table, len * sizeof(int));
						start_time = clock();
						while(i++ < times) {
								sele_sort(compare_tmp, out, len);
						}
						end_time = clock();
						memcpy(compare_tmp, out, len * sizeof(int));
						printf("----- Selection Sort, n = %d -----\n", len);
						break;
				case 'b':
						memcpy(compare_tmp, table, len * sizeof(int));
						start_time = clock();
						while(i++ < times) {
								bub_sort(compare_tmp, out, len);
						}
						end_time = clock();
						memcpy(compare_tmp, out, len * sizeof(int));
						printf("----- Bubble Sort, n = %d -----\n", len);
						break;
				case 'm':
						while(i++ < times) {
								memcpy(compare_tmp, table, len * sizeof(int));
								start_time = clock();
								mergesort(compare_tmp, len, sizeof(int), comp);
								end_time = clock();
								diff += end_time - start_time;
						}
						printf("----- Merge Sort, n = %d -----\n", len);
						break;
				case 'q':
						while(i++ < times) {
								memcpy(compare_tmp, table, len * sizeof(int));
								start_time = clock();
								qsort(compare_tmp, len, sizeof(int), comp);
								end_time = clock();
								diff += end_time - start_time;
						}
						printf("----- Quick Sort, n = %d -----\n", len);
						break;
		}
		printf("Before\t\t\tAfter\n");
		for(i = 0; i < 100; i++) {
				printf("%d\t\t\t%d\n", table[i], compare_tmp[i]);
		}
		if(!(fun == 'm' || fun == 'q')) {
				diff = end_time - start_time;
		}
		double diff_time = (double)diff / CLOCKS_PER_SEC / times;
		printf("%lf\n", diff_time);
		return diff_time;
}
int comp(const void *p, const void *q) { 
		return (*(int*)p - *(int*)q) ; 
}

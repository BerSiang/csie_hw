#include <stdio.h> 
#include <stdlib.h> 

int comp( const void * , const void * ) ; 

int main( int argc, char * argv[ ] ) 
{ 
		int i; 
		int array[] = {6, 8, 2, 9, 1, 0}; 

		qsort (array, 6, sizeof(int), comp); 

		for(i = 0; i < 6; i++) { 
				printf("%d\t", array[i]); 
		}
		printf("/n"); 

		return 0; 
} 

int comp(const void *p, const void *q) 
{ 
		return (*(int*)p - *(int*)q) ; 
}

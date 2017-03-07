#include<stdio.h>
	main(){
			float input, output;
			while(1){
				printf("input:");
				scanf("%f", &input);
				if(input == 0) break;
				output = input * 30.48;
				printf("\nResult:%.2f\n", output);
			}
}

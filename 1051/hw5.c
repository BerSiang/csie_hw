#include <stdio.h>
#include <stdlib.h>

#define MAX 2000
#define IN 1
#define OUT 0

double sqrt1(double);
double adjustScore(double);

int main() {
		int ID[MAX]= {}, c, Order[MAX] = {}; 
		char tmp[100];
		float score[MAX][3] = {}, avg[MAX] = {}, max[3], min[3], objAvg[3];
		int state = OUT, i = 0, j = 0, k = 0, stuC = 0, count = 0, pointC = 0;
		while((c = getchar()) != EOF) {
				if((c >= '0' && c <= '9') || (count > 0 && pointC == 0 && c == '.')) {
						if( c == '.') {
								pointC++;
						}
						state = IN;
						/*if(i >= 10) {
								printf("The score can't be over 100.\n"); 
								exit(EXIT_FAILURE);
						}*/
						tmp[i++] = c;
						count++;
				}
				else if(state == IN){
						tmp[i] = '\0';
						if(atof(tmp) < 0 || atof(tmp) > 100) {
								printf("The score can't be over 100.\n"); 
								exit(EXIT_FAILURE);
						}
						state = OUT;
						i = 0;
						ID[stuC] = stuC;
						score[ID[stuC]][k++%3] = adjustScore(atof(tmp));
						if(c == '\n') {
								avg[ID[stuC]]= (score[stuC][0] + score[stuC][1] + score[stuC][2]) / 3;
								stuC++;
						}
						count = 0;
						pointC = 0;
				}
		}
		k = stuC;

		for(i = 0; i < k - 1; i++) {
				for(j = 0; j < k - i - 1; j++) {
						if(avg[j] < avg[j + 1]) {
								float tmp = avg[j + 1];
								avg[j + 1] = avg[j];
								avg[j] = tmp;
								tmp = ID[j + 1];
								ID[j + 1] = ID[j];
								ID[j] = tmp;
						}
				}
		}

		max[0] = min[0] = score[0][0];
		max[1] = min[1] = score[0][1];
		max[2] = min[2] = score[0][2];
		for(i = 1; i < stuC; i++) {
				if(score[i][0] > max[0]) {
						max[0] = score[i][0];
				}
				if(score[i][0] < min[0]){
						min[0] = score[i][0];
				}
				if(score[i][1] > max[1]) {
						max[1] = score[i][1];
				}
				if(score[i][1] < min[1]){
						min[1] = score[i][1];
				}
				if(score[i][2] > max[2]) {
						max[2] = score[i][2];
				}
				if(score[i][2] < min[2]){
						min[2] = score[i][2];
				}
				objAvg[0] += score[i][0];
				objAvg[1] += score[i][1];
				objAvg[2] += score[i][2];
		}
		if(stuC != 0) {
				objAvg[0] /= stuC;
				objAvg[1] /= stuC;
				objAvg[2] /= stuC;
		}
		else {
				objAvg[0] = 0;
				objAvg[1] = 0;
				objAvg[2] = 0;
		}
		printf("ID | Calculus | Programming | Linear Algebra | Average\n");
		printf("-------------------------------------------------------\n");
		for(i = 0; i < stuC; i++) {
				printf("%3d| %-8.1f | %-11.1f | %-14.1f | %-7.1f\n", ID[i], score[ID[i]][0], score[ID[i]][1], score[ID[i]][2], avg[i]);
		}
		printf("-------------------------------------------------------\n");
		printf("Max| %-8.1f | %-11.1f | %-14.1f\n", max[0], max[1], max[2]);
		printf("Min| %-8.1f | %-11.1f | %-14.1f\n", min[0], min[1], min[2]);
		printf("Avg| %-8.1f | %-11.1f | %-14.1f\n", objAvg[0], objAvg[1], objAvg[2]);

		return 1;
}

double sqrt1(double a) {
		double inaccuracy = 0.0001;
		double high = 0, low = 0;
		if(a >=  0 && a <= 1) {
				low = 0;
				high = 1;
		}
		else {
				low = 1;
				high = a;
		}

		while(high - low > inaccuracy) {
				float tmp = (high + low)/2;
				if(tmp * tmp >  a) {
						high = tmp;
				}
				else {
						low = tmp;
				}
		}
		return low;
}
double adjustScore(double Score) {
		return sqrt1(Score) * 10;
}

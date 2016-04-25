#include <stdio.h>
#include <math.h>
#include <stdlib.h>
float a[500];
float b[500];
int c[500];
int count = 0;
void scanFile(float a[],float b[],int c[]){
	FILE *f;
	f = fopen("result.txt","rt");
	while(fgetc(f)!=EOF){
		fscanf(f,"%f %f %d",&a[count],&b[count],&c[count]);
		count++;
	}
	fclose(f);
}

void ghiFile(float sum1, float sum2, int number){
	FILE *f;
	f = fopen("ketqua.txt", "at");
	if (f == NULL){
		printf("Khong mo duoc file\n");
		exit(1);
	}
	fprintf(f,"%f %f %d\n",sum1, sum2, number);
	fclose(f);
}

int main(){
	scanFile(a, b, c);
	
	for (int i = 0; i < count; i+=5)
	{
		float sum1 = 0, sum2 = 0;
		for(int j = i; j < i+5; j++){
//			printf("%f ", a[j]);
			sum1 += a[j];
			sum2 += b[j];
		}
		sum1 = sum1/5;
		sum2 = sum2/5;
		ghiFile(sum1, sum2, c[i]);
	}
	// printf("Tong lon nhat la: %d", maxSum);
	return 0;
}
	

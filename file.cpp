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

int main(){
	scanFile(a, b, c);
	int m = 116, n= 121;
	float sum1 = 0, sum2 = 0;
	for (int i = m; i < n; ++i)
	{
		printf("%f ", a[i]);
		sum1 += a[i];
		sum2 += b[i];
	}
	printf("\nSo ban ghi: %d\n", n);
	printf("Gia tri %f, %f", sum1/(n-m), sum2/(n-m));
	// printf("Tong lon nhat la: %d", maxSum);
	return 0;
}
	

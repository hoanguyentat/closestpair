#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int a[500];
int b[500];
int c[500];
int n = 0;

void docfile(int a[], b[], c[]){
	FILE *f;
	f = fopen("result.txt","rt");
	while(fgetc(f)!=EOF){
		fscanf(f,"%3d",&a[n]);
		fscanf(f,"%3d",&b[n]);
		fscanf(f,"%3d",&c[n]);
		n++;
	}
	fclose(f);
}

int main(){
	// int a[100];
	// docfile(a);
	// printf("%d \n",k);
	// int maxSum = 0;
	// for(int i=0; i<k;i++){
	// 	int sum = 0;
	// 	for(int j=i;j<k;j++){
	// 		sum+=a[j];
	// 		if(maxSum<sum) maxSum = sum;
	// 	}
	// }
	printf("Nhap vao so phan tu: ");
	scanf("%d", &n);
	ghiFile();
	// printf("Tong lon nhat la: %d", maxSum);
	return 0;
}
	

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int k = 0;
int n;
void ghiFile(){
	FILE *f;
	f = fopen("point.txt","w");
	if (f == NULL)
	{
		printf("Khong mo duoc file\n");
		exit(1);
	}
	fprintf(f, "%d\n", n);
	for (int i = 0; i < n; ++i)
	{
		fprintf(f, "%d %d\n",rand() % 100000, rand()%100000);
	}
	fclose(f);
}
void docfile(int a[]){
	FILE *f;
	f = fopen("docfile.txt","rt");
	while(fgetc(f)!=EOF){
		fscanf(f,"%3d",&a[k]);
		k++;
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
	

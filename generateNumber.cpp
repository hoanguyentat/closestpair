#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <windows.h>
#include <math.h>
#include "Timer.cpp"

struct Point{
	int x, y;
};

void merge(Point* p, int L, int M, int R, int flag){
	int i =L; int j = M+1;
	Point* tmp = (Point*) malloc((R + 1) * sizeof(Point));
	for(int k = L; k <= R; k++){
		if(i > M){
			tmp[k] = p[j];
			j++;	
		} 
		else if(j>R){
			tmp[k] = p[i];
			i++;
		}
		else {
			int s1;
			int s2;
			if (flag == 0){
				s1 = p[i].x;
				s2 = p[j].x;
			}
			else{
				s1 = p[i].y;
				s2 = p[j].y;
			}
			if (s1 < s2){
				tmp[k] = p[i];
				i++;
			}
			else {
				tmp[k] = p[j];
				j++;
			}
		}
	}
	for(int k = L; k <=R; k++){
		p[k] = tmp[k];
	}
	free(tmp);
}

void mergeSort(Point* p, int L, int R, int flag){
	if(L < R){
		int M = (L+R)/2;
		mergeSort(p, L, M, flag);
		mergeSort(p, M+1, R, flag);
		merge(p,L, M, R, flag);
	}
}



bool checkPoint(Point *a, int count, int x, int y){
	if (count == 0) return 0;
	for(int i = 0; i< count; i++){
		if (a[i].x == x && a[i].y == y) return 1;
	}
	return 0;
}

void generatePoint(Point a[], int n){	
	FILE *f;
	f = fopen("point.txt","w");
	if (f == NULL)
	{
		printf("Khong mo duoc file\n");
		exit(1);
	}
	fprintf(f, "%d\n", n);
	int count = 0;
	int x; int y;
	x = rand() %10000;
	y = rand() %10000;	
	for(int i = 0; i < n; i++){
		while(checkPoint(a,i,x,y)){
			x = rand() %10000;
			y = rand() %10000;
		}
		a[i].x = x;
		a[i].y = y;
		fprintf(f, "%d %d\n",x, y);
	}
	fclose(f);
}


int main(){
	for(int k = 0; k < 5; k++){
		Point *a;
		int n = 20;
		a = (Point*) malloc(n*sizeof(Point));
		srand(time(NULL));
		generatePoint(a, n);
		mergeSort(a,0,n-1, 1);
		printf("Danh sach cac diem:\n");
		for(int i = 0; i< n; i++){
			printf("P%d(%d,%d) ",i+1, a[i].x, a[i].y);
			if (i%20 == 19){
				printf("\n");
			}
		}
		printf("\n");
		Sleep(2000);
	}
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int count = 0;
struct Point{
	int x, y;
};

Point* p;

void readFile(){
	FILE* f = fopen("point.txt","rt");
	if(f==NULL) {
		printf("Khong mo duoc file");
		exit(0);
	}
	fscanf(f, "%d", &count);
	p = (Point*) malloc(count * sizeof(Point));
	int x, y;
	for(int i = 0; i < count; i++){
		fscanf(f,"%d",&x);
		fscanf(f,"%d",&y);
		p[i].x = x;
		p[i].y = y;
	}
	fclose(f);
}

void insertionSort(Point* p, int n){
	for (int k = 1; k < n; ++k)
	{
		Point last = p[k];
		int j = k;
		while(j > 0 && p[j-1].x > last.x){
			p[j] = p[j-1];
			j--;
		}
		p[j] = last;
	}
}

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

int main(int argc, char *argv[])
{
	readFile();
	
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <timer.h>

int count = 0;
struct Point{
	int x, y;
};

Point* p;
Point a, b;
int dmin = 10000;
void readFile();								// Doc va khoi tao diem ban dau
void swap(Point&, Point&);						// Hoan vi 2 diem
void printPoint(Point*);								// in danh sach cac diem
int dist(Point, Point);							// khoang cach giua hai diem o, q
void mergeSort(Point*, int, int, int);
void merge(Point*, int, int ,int, int); 		// sap xep tron theo x voi flag = 0, theo y voi flag = 1
int bruteForce(Point*, int, int);				// Thuat toan vet can
void setPoint(Point*, Point*);

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

void swap(Point &p, Point &q){
	Point tmp;
	tmp =p;
	p =q;
	q =tmp;
}

void setPoint(Point* p, Point* q){
	for(int i = 0; i < count; i++){
		q[i] = p[i];
	}
}

void printPoint(Point* p){
	printf("Danh sach cac diem:\n");
	for(int i = 0; i< count; i++){
		printf("P%d(%d,%d) ",i+1, p[i].x, p[i].y);
		if (i%5 == 4){
			printf("\n");
		}		
	}
}

int dist(Point p, Point q){
	return sqrt(pow(p.x-q.x,2) + pow(p.y-q.y,2));
}

int bruteForce(Point *p, int L, int R){
	for(int i = L; i <= R; i++){
		for(int j = i+1; j <= R; j++){
			int d = dist(p[i], p[j]);
			if (d < dmin){
				dmin = d;
				a.x = p[i].x; b.x = p[j].x;
				a.y = p[i].y; b.y = p[j].y;
			}
		}
	}
	return dmin;
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

void ClosestPair(Point* p, int L, int R){
	if(R - L <= 3) return bruteForce(p,L,R);
	
}

int main(int argc, char const *argv[]){
	readFile();
	printPoint(p);
	Point* pX = (Point*) malloc(count * sizeof(Point));
	mergeSort(p,0,count-1, 0);
	setPoint(p, pX);
	Point* pY = (Point*) malloc(count * sizeof(Point));
	mergeSort(p,0,count-1, 1);
	setPoint(p, pY);
	printPoint(pX);
	printPoint(pY);
	bruteForce(p, 0, count-1);
	printf("Hai diem gan nhau nhat la:\nA(%d, %d), B(%d, %d)\n",a.x,a.y,b.x,b.y);
	return 0;
}

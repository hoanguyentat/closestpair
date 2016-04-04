#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <windows.h>
#include <math.h>
#include "Timer.cpp"
//#define number 20

int count = 0;
struct Point{
	int x, y;
};

Point* p;
Point a, b;
float dmin = FLT_MAX;						//dmin la gia tri nho nhat trong suot chuong trinh
void readFile();
void printPoint(Point*);
void setPoint(Point*, Point*);
void generatePoint(int);
void mergeSort(Point*, int, int, int);
void merge(Point*, int, int ,int, int); 			// sap xep tron theo x voi flag = 0, theo y voi flag = 1
void result(double, double);
float min(float, float);
float stripClosest(Point*, int, float);
float dist(Point, Point);								// khoang cach giua hai diem o, q
float bruteForce(Point*, int);						// Thuat toan vet can

//Doc gia tri dau vao
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
// Sinh ngau nhien diem tren mat phang
void generatePoint(int n){
	srand(time(NULL));
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

//Ghi lai ket qua
void result(double y1, double y2){
	FILE* f1 = fopen("result.txt","a+");
	if(f1 == NULL){
		printf("Khong mo duoc file");
		exit(1);
	}
	fprintf(f1,"%f %f %d\n",y1,y2,count);
	fclose(f1);
}

void setPoint(Point* p, Point* q){
	for(int i = 0; i < count; i++){
		q[i] = p[i];
	}
}

//In ra man hinh toa do cac diem
void printPoint(Point* p){
	printf("Danh sach cac diem:\n");
	for(int i = 0; i< count; i++){
		printf("P%d(%d,%d) ",i+1, p[i].x, p[i].y);
		if (i%5 == 4){
			printf("\n");
		}		
	}
}

//Tinh khoang cach giua hai diem
float dist(Point p, Point q){
	return sqrt(pow(abs(p.x-q.x),2) + pow(abs(p.y-q.y),2));
}

//Tra ve gia tri nho nhat
float min(float x, float y){
	if (x > y) return  y;
	else return x;
}

//Thuat toan vet can
float bruteForce(Point *p, int n){
	float min = FLT_MAX;
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			float d = dist(p[i], p[j]);
			if (d < min){
				min = d;
				//dmin luon luon la gia tri nho nhat trong suot chuong trinh
				if (min < dmin){
					dmin = min;
					a.x = p[i].x; b.x = p[j].x;
					a.y = p[i].y; b.y = p[j].y;
				}
			}
		}
	}
	return min;
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

//Tim khoang cach nho nhat o khoang giua
float stripClosest(Point* pLR, int k, float d){
	float min = d;

//	mergeSort(pLR,0,k-1, 1);
	for (int i = 0; i < k; ++i){
		// Gioi han so diem can xet
		for (int j = i+1; j < k && pLR[j].y -  pLR[i].y < min; ++j){
			if (dist(pLR[i],pLR[j]) < min){
				min = dist(pLR[i],pLR[j]);
				if (min < dmin){
					dmin = min;
					a.x = pLR[i].x; b.x = pLR[j].x;
					a.y = pLR[i].y; b.y = pLR[j].y;
				}
			}
		}
	}
	free(pLR);
	return min;
}

float ClosestPair(Point* pX, int n){
	if(n <= 5) return bruteForce(pX, n);
	
	//Chia mang thanh hai phan bang nhau
	int mid = n/2;
	Point midPoint = pX[mid];

	//De qui tim hai diem co khoang cach nho nhat
	float dL = ClosestPair(pX, mid);
	float dR = ClosestPair(pX + mid,n-mid);
	
	float d = min(dL, dR);   //Khoang cach nho nhat giua hai mang

	//Tim tap cac diem co khang cach toi diem chinh giua nho hon d
	Point* pLR = (Point*) malloc (n * sizeof(Point));
	if (pLR == NULL)
	{
		printf("Khong du bo nho\n");
		exit(1);
	}
	int k = 0;
	for (int i = 0; i < n; ++i){
		if (abs(pX[i].x - midPoint.x) <= d){
			pLR[k] = pX[i];
			k++;
		}
	}

	return min(stripClosest(pLR, k, d), d);;
}
int main(int argc, char *argv[]){
//	for(int i = 0; i < 10; i++){
//		generatePoint(number);
		readFile();
		//Sap xep cac diem theo toa do y
		mergeSort(p,0,count-1, 1);
		
		//	printf("Co %d diem tren mat phang.\n", count);
		//	printPoint(p);
		int choose;
		double y1, y2;
		printf("Xin moi lua chon:\n");
		printf("1. Thuat toan Vet can\n");
		printf("2. Thuat toan Chia de tri\n");
		printf("Nhap vao vi tri: ");
		scanf("%d", &choose);
		switch(choose){
			case 1:{
				//Do thoi gian chay cua cac giai thuat
				Timer ti;
				float minbf = bruteForce(p, count);
				y1 = ti.getElapsedTime();
				printf("Khoang cach gan nhat la: %3.2f\n", minbf);
				printf("Hai diem gan nhau nhat la:\nA(%d, %d), B(%d, %d)\n",a.x,a.y,b.x,b.y);
				printf("Thoi gian chay: %f\n",y1);
				break;
			}
			case 2:{
				Timer timer;
				float min1 = ClosestPair(p, count);
				y2 = timer.getElapsedTime();
				printf("Khoang cach gan nhat la: %3.2f\n", min1);
				printf("Hai diem gan nhau nhat la:\nA(%d, %d), B(%d, %d)\n",a.x,a.y,b.x,b.y);
				printf("Thoi gian chay: %f\n",y2);
				printf("\n");
				break;
			}
			default: {
				printf("Ban khong lua chon thuat toan\n");
				break;
			}
		}
		result(y1,y2);
		free(p);
		Sleep(1000);
//	}
	return 0;
}

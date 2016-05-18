#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <float.h>
// #include <windows.h>
#include <string.h>
#include <math.h>
#include "Timer.cpp"
#include <set>
// #define number 100000

using namespace std;
int count = 0;
char fileName[50]="input";

struct Point{
	int x, y;
};

Point* p;
Point a, b;
float dmin = FLT_MAX;						//dmin la gia tri nho nhat trong suot chuong trinh
void readFile(char*);
void savePoint(Point*, int, char*);
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
int compareY(const void*, const void*);
//Doc gia tri dau vao
void readFile(char fileName[]){
	char fileread[50];
	strcpy(fileread,fileName);
	strcat(fileread, ".in");		//Gan phan mo rong cho file
	FILE* f = fopen(fileread,"rt");
	if(f==NULL) {
		printf("Khong mo duoc file\n");
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

//Luu cac diem dau vao nhap tu ban phim
void savePoint(Point *p, int count, char fileName[]){
	FILE *f;
	char fileread[50];
	strcpy(fileread,fileName);
	strcat(fileread,".in");
	f = fopen(fileread,"w");
	if (f == NULL)
	{
		printf("Khong mo duoc file\n");
		exit(1);
	}
	fprintf(f, "%d\n", count);
	for (int i = 0; i < count; ++i)
	{
		fprintf(f, "%d %d\n",p[i].x, p[i].y);
	}
	fclose(f);
}

// Sinh ngau nhien diem tren mat phang
bool checkPoint(Point *a, int count, int x, int y){
	if (count == 0) return 0;
	for(int i = 0; i< count; i++){
		if (a[i].x == x && a[i].y == y) return 1;
	}
	return 0;
}

//Sinh diem ngau nhien 
void generatePoint(Point a[], int n, char fileName[]){
	FILE *f;
	char generateFile[30];
	strcpy(generateFile,fileName);
	strcat(generateFile,".in");
	f = fopen(generateFile,"w");
	if (f == NULL)
	{
		printf("Khong mo duoc file\n");
		exit(1);
	}
	fprintf(f, "%d\n", n);
	int x; int y;
	x = rand() %100000;
	y = rand() %100000;
	for(int i = 0; i < n; i++){
		while(checkPoint(a,i,x,y)){
			x = rand() %100000;
			y = rand() %100000;
		}
		a[i].x = x;
		a[i].y = y;
		fprintf(f, "%d %d\n",x, y);
	}
	fclose(f);
}


//Luu lai ket qua
void result(Point A, Point B, double y, char fileName[]){
	char fileResult[50];
	strcpy(fileResult,fileName);
	strcat(fileResult, ".out");
	FILE* f1 = fopen(fileResult,"a+");
	if(f1 == NULL){
		printf("Khong mo duoc file");
		exit(1);
	}
	fprintf(f1,"%d\n%d %d\n%d %d\n%f\n\n",count,A.x, A.y, B.x, B.y, y);
	fclose(f1);
}

//Gan gia tri cua p cho q
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

//Sap xep so sanh theo chieu tang toa do Y su dung qsort() san co trong thu vien stdlib;
int compareY(const void* a, const void* b){
	Point *p1 = (Point*) a;
	Point *p2 = (Point*) b;
	return (p1->y - p2->y);
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

float ClosestPair(Point* p, int n){
	if(n <= 3) return bruteForce(p, n);
	//Chia mang thanh hai phan bang nhau
	int mid = n/2;
	Point midPoint = p[mid];
	//De qui tim hai diem co khoang cach nho nhat
	float dL = ClosestPair(p, mid);
	float dR = ClosestPair(p + mid,n-mid);

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
		if (abs(p[i].x - midPoint.x) <= d){
			pLR[k] = p[i];
			k++;
		}
	}

	return min(stripClosest(pLR, k, d), d);
}
int main(int argc, char *argv[]){
	srand(time(NULL));
	bool checkRead = false;			// Bien kiem tra su ton tai cua du lieu
		
	int choose;			//Bien kiem tra lua chon dau vao lan 1
	do{
		
		// double y1, y2;
		// system("clear");
		system("cls");
		printf("1. Doc du lieu dau vao\n");
		printf("2. Giai quyet bai toan\n");
		printf("3. Danh sach cac diem\n");
		printf("4. Thoat\n");
		do{
			printf("Nhap vao lua chon cua ban: ");
			scanf("%d", &choose);
		}while(choose != 1 && choose !=2 && choose != 3 && choose != 4);

		switch(choose){
	     	case 1:{
	     	 	// system("clear");
	     	 	system("cls");
	     	 	int chooseIn;
				//Doc du lieu dau vao trong chuong trinh
				printf("1. Doc du lieu tu file\n");
				printf("2. Nhap du lieu tu ban phim\n");
				printf("3. Sinh diem ngau nhien\n");
				do{
					printf("Xin moi lua chon: ");
					scanf("%d", &chooseIn);
				}
				while(chooseIn != 1 && chooseIn != 2 && chooseIn != 3);
				switch(chooseIn){
					case 1:{
						fflush(stdin);
						printf("Nhap ten file du lieu dau vao: ");
						scanf("%s",fileName);
						readFile(fileName);
						checkRead = true;
						printf("Nhap thanh cong...");
						getch();
						break;
					}
					// Doc du lieu tu ban phim
					case 2:{
						printf("Nhap vao so diem: ");
						scanf("%d", &count);
						p = (Point*) malloc (count * sizeof(Point));
						for (int i = 0; i < count; ++i)
						{
							printf("x[%d]: ",i+1);
							scanf("%d", &p[i].x);
							printf("y[%d]: ",i+1);
							scanf("%d", &p[i].y);
						}
						fflush(stdin);
						printf("Nhap ten file de luu: ");
						scanf("%s",fileName);
						savePoint(p, count, fileName);
						checkRead = true;	//Bien kiem tra trang thai dau vao
						printf("Nhap thanh cong...");
						getch();
						break;
					}
					case 3:{
						printf("Nhap vap so diem: ");
						scanf("%d", &count);
						printf("Nhap ten file de luu: ");
						scanf("%s",fileName);
						p = (Point*) malloc (count * sizeof(Point));
						srand(time(NULL));
						generatePoint(p, count, fileName);
						checkRead = true;
						printf("Nhap thanh cong...");
						getch();
						break;
					}
					default: {
						break;
					}
				}
				 break;
			 }
			case 2:{
				// system("clear");
				system("cls");
				if (checkRead == false)
				{
					printf("Chua doc du lieu dau vao...\n");
					getch();
					break;
				}
				int chooseAlgorithm;
				printf("1. Brute Force\n");
				printf("2. Divide and Conquer\n");
				do{
					printf("Xin moi lua chon thuat toan so: ");
					scanf("%d", &chooseAlgorithm);
				}while (chooseAlgorithm != 1 && chooseAlgorithm != 2);
//				mergeSort(p,0,count-1, 1);	
				qsort(p, count, sizeof(Point), compareY);
				bool checkSolution = false;	
				Timer ti;	
				double y;	
				switch(chooseAlgorithm){
					case 1:{
					
						bruteForce(p, count);
						y = ti.getElapsedTime();
						printf("Khoang cach gan nhat la: %3.2f\n", dmin);
						printf("Hai diem gan nhau nhat la:\nA(%d, %d), B(%d, %d)\n",a.x,a.y,b.x,b.y);
						printf("Thoi gian chay: %f",y);
						checkSolution = true;
						break;
					}
					case 2:{
						ClosestPair(p, count);
						y = ti.getElapsedTime();
						printf("Khoang cach gan nhat la: %3.2f\n", dmin);
						printf("Hai diem gan nhau nhat la:\nA(%d, %d), B(%d, %d)\n",a.x,a.y,b.x,b.y);
						printf("Thoi gian chay: %f",y);
						printf("\n");
						checkSolution = true;	
						break;
					}
					default: {
						printf("Ban khong lua chon thuat toan\n");
						getch();
						break;
					}
				}	
				if(checkSolution == true){
					char saveResult[10] = "";
					printf("\nBan co muon luu lai ket qua khong? c/k? ");
					scanf("%s", saveResult);
					if(strcmp(saveResult,"c") == 0 || strcmp(saveResult,"C") == 0 || strcmp(saveResult,"co") == 0){
						char fileOut[30];
						printf("Nhap ten file de luu ket qua: ");
						scanf("%s", fileOut);
						result(a, b, y, fileOut);
						printf("Da luu ket qua vao file %s.out...", fileOut);
					} 
				}
				getch();
				break;	
			}
			case 3:{
				// system("clear");
				system("cls");
				if (checkRead == false)
				{
					printf("Chua co danh sach! Hay tao du lieu dau vao...\n");
					getch();
					break;
				}
				printf("Co %d diem tren mat phang\n", count);
				printPoint(p);
				getch();
				break;
			}
		}
	}while(choose != 4);
	free(p);
	return 0;
}

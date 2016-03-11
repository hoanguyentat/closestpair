#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct point{
	int x;
	int y;
};
point a, b;

float dista(point p, point q){
	return sqrt(pow(p.x-q.x,2) + pow(p.y-q.y,2));
}
int main(int argc, char *argv[])
{
	printf("nhap a: ");
	scanf("%d %d", &a.x, &a.y);
	printf("nhap b: ");
	scanf("%d %d", &b.x, &b.y);
	printf("Khoang cach: %3.2f\n", dista(a, b));
	return 0;
}
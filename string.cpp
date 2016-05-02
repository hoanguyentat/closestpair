#include <stdlib.h>
#include <stdio.h>
// #include <conio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char input[30] = "Hola";
	printf("Ten cua ban la: %s\n",input);
	printf("Nhap ten cua ban: ");
	fflush(stdin);
	gets(input);
	printf("Ten cua ban la: %s\n",input);
	strcat(input,".in");
	printf("Ten cua ban la: %s\n",input);
	return 0;
}
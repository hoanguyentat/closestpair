#include <conio.h> 
#include <stdlib.h> 
#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

int timx(int a[],int n,int x)// co gia tri x trong mang a do dai n hay ko 
{ 
    int i; 
    if(n==0)return 0; 
    for(i=0;i<n;++i) 
        if(a[i]==x)return 1; 
    return 0; 
} 


void gen_random(int a[],int n)// tao n gia tri ngau nhien luu vao mang a 
{ 
    int i,x; 
    x= rand() % 100;
    for(i=0;i<n;++i) 
    { 
        while(timx(a,i,x)) 
            x=rand() % 100; // tao ngau nhien tu 0->99 
        a[i]=x; 
    } 
} 

int main() 
{ 
	for(int k = 0; k < 10; k++){
	    srand(time(NULL));// cai nay de moi lan chay ko trung lap 
	    int a[10],i; 
	
	    gen_random(a,10); 
	
	    for(i=0;i<10;++i) 
	        cout <<' '<<a[i]; 
	        cout << '\n';
	    getch(); 
	}
}  

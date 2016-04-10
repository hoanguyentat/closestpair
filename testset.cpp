#include <iostream>
#include <stdlib.h>
#include <set>

int main ()
{
  int *myints;
  myints = (int*) malloc (5*sizeof(int));
  for(int i =0; i<5;i++){
  	*(myints +i )= i;
  }
  std::set<int> myset (myints,myints+5);

  std::cout << "myset contains:";
  for (std::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
}

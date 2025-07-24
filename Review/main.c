#include <stdio.h>
#include <stdlib.h>
 void swap (int*  , int*  );
 void number (int , int);



int main()
{ int x;  int y;
  int *prt1=x;   int *prt2=y;
  prt1=&x; prt2= &y;
  printf("the values of x and y:\n");
  scanf("%d%d", &x , &y);
  swap(&x , &y);
  printf("x:%d y:%d", x , y);
  printf("%d", number);
    return 0;
}
void swap (int *a , int *b){
  int temp;
  temp=*a;
  *a=*b;
   *b=temp;
}

void number(int max , int min){
    int z; int f;
   if (z>f)
    return max;
   else
     return min;


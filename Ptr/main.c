#include <stdio.h>
#include <stdlib.h>


int main(){

    int *ptr;
    int x=12;
    ptr=&x;
    printf(" value x:%d\n", x);
    printf(" value x:%d\n", *ptr);
    printf(" address x:%d\n", &x);
    printf(" address x:%p", ptr);





}














//void swap(int * , int *);
//
//int main()
//{
//   int x , y;
//   int *ptr1 , *ptr2;
//   ptr1= &x , ptr2=&y;
//
//   printf("please enter values or x and y :\n");
//   scanf("%d\n%d", ptr1 , ptr2);
//   swap(&x , &y);
//   printf("the value of x:%d\n", x);
//   printf("the value of y:%d\n", *ptr2);
//   return 0 ;
//
//}
//void swap(int *a, int *b){
//  int tmep=0;
//   tmep = *a;
//   *a= *b;
//   *b=tmep;
//           }
//

#include <stdio.h>
#include <stdlib.h>
int findSum(int size);
double findeAverage(double size);

int main()
{
    printf("the sum of v :%d\n", findSum(5));
    printf("the av :%0.2f\n", findeAverage(4));
}
int findSum(int size){
  int i=0 ,sum =0;
  do{
    sum+=i;
    i++;
  }
  while(i<size);
  return sum;

  }

  double findeAverage(double size){
  int i=0 , sum=0; double avg=0;
  while(i<size){
    i++;
    sum+=findSum(i);
  }
    return sum/size;
  }




//    printf("plz enter values of a and b:\n");
//    scanf("%lf%lf", &a , &b);
//    x=pow(a, b);
//    printf("the power %.1lf of %.1lf = %.1lf" , a, b, x);
//  double a , b , x;
//  printf("enter values of a and b:\n");
//  scanf("%lf%lf", &a , &b);
//  x=a*a+2*b*a+b*b;
//  printf("the value of x =%.2lf", x);



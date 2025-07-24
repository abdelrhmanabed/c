#include <stdio.h>
#include <stdlib.h>
//abdelrhman abed
//id:1193191
//sec lab:1

 double PowerOfNumber(double , int);
 double factorialOfNumber(int);
 double computer_Ex(double);

int main()
{
    double x;
   printf("enter value of x :\n");
    scanf("%lf",&x);
    double ex = computer_Ex(x);
    printf("e to the power %.2lf is : %.2lf",x , ex);

    return 0;
}
double PowerOfNumber(double x , int y){
     double power =1;
     int i=0;
     while(i<y){
        power=power*x;
        i++;

     }
     return power;
}

double factorialOfNumber(int x){
    if(x==0)
        return 1;
     double factorial=1;
     for(int i =1; i<=x; i++){
            factorial= factorial*i;

     }
     return factorial;

     }
double computer_Ex(double x){
    double ex=0;
    double term;
    int y=0;

     do{
        term =   PowerOfNumber(x,y)/factorialOfNumber(y);
        ex=ex+term;
        y++;
        if(ex< 0)
           term = term*-1;
        }
     while (term >= 0.0001);
     return ex;
     }

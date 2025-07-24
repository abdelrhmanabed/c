#include <stdio.h>
#include <stdlib.h>
    int calculateCharges(float );
  int main()

{
   float n;
     printf("enter the nis:");
     scanf("%f", &n);
   float charge;
    charge = calculateCharges( n);
    printf("charge/month is :%.2f\n", charge);
    FILE *myfile;
    myfile=fopen("usage.txt","r");
    fscanf(myfile,"%f", &n);
    fclose(myfile);
    printf("the charges is:%f\n",n);
   return 0;
}



int calculateCharges(float n)
{

   if(n> 0.0 && n <= 1.0)
     return 250;


    else if(n > 1.0 && n <= 2.0)
     return 500;


    else if(n >2.0 && n <= 5.0)
     return 1000;


    else if(n >5.0 && n <= 10.0)
     return 1500;


     else if (n>10.0)
     return 2000;
}



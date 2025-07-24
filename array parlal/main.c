#include <stdio.h>
#include <stdlib.h>

int main()
{
   int size;
   printf("please enter the number of student:\n");
   scanf("%d",&size);
   int stdid[size];
   int stdmid[size];
   int stdfinal[size];
   float stdavg[size];
   for(int i=0;i<size;i++){
    printf("enter the student ID:\n ");
    scanf("%d",&stdid[i]);
    printf("Enter the mid mark:\n");
    scanf("%d",&stdmid[i]);
    printf("Enter final mark:\n");
    scanf("%d",&stdfinal[i]);
   }
   for(int i=0;i<size;i++){
        stdavg[i]=(stdmid[i]+stdfinal[i])/2.0;
   }
   printf("ID student    student marks avg\n ");
   for(int i=0;i<size;i++){
    printf("%d,          %0.2f\n", stdid[i], stdavg[i]);
   }




    return 0;

}

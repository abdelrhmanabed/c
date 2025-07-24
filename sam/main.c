#include <stdio.h>
#include <stdlib.h>

void Push(int x[],int y[], int n) {
     int i=0, j=n-1;
      while (i<=j){
      y[i]=x[j]+2;
      j--;
      i++;
      }
}
    int  main(){

          int A[8]={0}, i;
           for (i=0;i<4;i++)
                A[i]=A[i-1]+2;

            int B[4]={0};
            Push(A, B,4);
             for (i=0;i<4;i++)
                printf("%d %d\n", A[i], B[i]);
    }

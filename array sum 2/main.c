#include <stdio.h>
#include <stdlib.h>
void arraysum(int  a[], int b[], int sum[]);

int main()
{
    int array1[5]={1,2,3,4,5};
    int array2[5]={1,2,3,4,5};
    int sum[5];
    arraysum(array1,array2,sum);
    for(int i=0; i<5; i++){
        printf("%d",sum[i]);
    }

}
void arraysum(int  a[], int b[], int sum[]){
    for(int i=0; i<5;i++)
            sum[i]=a[i]+b[i];

    }

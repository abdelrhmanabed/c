#include <stdio.h>
#include <stdlib.h>
void printarry (int [], int);
void fillarry (int[], int);
void sortarry (int [], int);
void revesearry(int [],int);
void primenumbers(int [], int);
int prime(int);
void inof();
int main()
{
    int arr2[5];
    fillarry (arr2, 5);
    printarry(arr2, 5);
    int choise=1;
    while(choise){
        inof();
        scanf("%d", &choise);

        switch(choise){
        case 1:
            sortarry ( arr2, 5);
            printarry(arr2, 5);
            break;
        case 2:
            revesearry(arr2,5);
            printf("the revers\n");
            printarry(arr2, 5);
            break;
        case 3:
            printf("the prime number is:\n");
            primenumbers( arr2, 5);
            break;
        case 0:
            printf("thank you\n");
            break;
        default:
            printf("please enter number between 0-3");

            }
    }

    return 0;
}

void inof(){
    printf("please enter one of the following:\n");
    printf("1-to sort the array:\n");
    printf("2-to reverse the array:\n ");
    printf("3-to find the prime numbers in the array:\n");
    printf("0-to exit the program :\n ");
}
 void printarry(int x[], int size){
         printf("[");
   for(int i=0; i<size;i++){
    printf("%d ,",x[i]);
   }
   printf("]");
   printf("\n ");
  }
   void fillarry (int f[], int size){
         for(int i=0; i<size; i++){
            printf("please enter array elements:\n" );
           scanf("%d", &f [i]);
     }
     }
   void sortarry (int x [], int size){
       for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            if(x[j]<x[i]){
                int temp;
                temp=x[i];
                x[i]=x[j];
                x[j]=temp;
            }


        }
       }

    }
     void revesearry(int x[],int size){
        for(int i=0 , j=size-1; i<size/2;i++, j--){
            int temp;
            temp=x[i];
            x[i]=x[j];
            x[j]=temp;       }
    }
    void primenumbers(int x[], int size){
        for(int i=0; i<size; i++){
            if(prime(x[i])==1){
                printf("%d,", x[i]);
           }
        }

    }
    int prime(int z){
        for(int i=2; i<z; i++){
            if(z%i==0){
                return 0;
            }
        }
        return 1;
}

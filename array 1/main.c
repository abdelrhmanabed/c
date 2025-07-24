#include <stdio.h>
#include <stdlib.h>
void printarry (int [], int);
void fillarry (int[], int);
void avg( int [], int);
int findelement(int[],int ,int a);
void sortarry (int [], int);
void revesearry(int [],int);
void primenumbers(int [], int);
int prime(int);
int main(){


   int arr2[5];
   int a;
   fillarry (arr2, 5);
   printarry(arr2, 5);
   printf("the avarge of arry is:");
   avg( arr2, 5);

    printf("please enter element  to find\n" );
    scanf("%d", &a);
   if( findelement(arr2,5 ,a )){
    printf("the element %d the exist\n", a);
   }else{
   printf("the element %d the not exist\n", a);}

   sortarry ( arr2, 5);
   printf("the sorting");
   printarry(arr2, 5);

   revesearry(arr2,5);
    printf("the revers\n");
   printarry(arr2, 5);

   printf("the prime number is:\n");
   primenumbers( arr2, 5);


    return 0;
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

     void avg( int l[], int size){
         int avarge =0;
       for(int i=0; i<size; i++){
         avarge= avarge+l[i];
       }
       printf("%d", avarge/size);
        printf("\n ");
     }
      int findelement(int s[], int size , int a ){

    for(int i=0; i<size; i++){
        if(a==s[i]){
        return 1;

    }


    }
    return 0;
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
//-------------------------------------------------------------------------------------------------------------------------------

//    for(int i=0; i<5; i++){
//            printf("Enter value %d\n", i);
//            scanf("%d\n", &arr2[i]);
//    }
//    for(int i=0; i<5; i++){
//        printf("%d", arr2[i]};
//    }





     //
// int y[5]={1,2,3,4,5};
//   printf("%d\n",y[2]);
//
//   int a[]={1, 2 , 3, 4,5};
//   printf("%d\n", a[2]);
//
//   int m [5]={};
//   printf("%d\n", m[2]);//رح يطبع الكل اصفار
//
//   int arr[4]={2,3,4,6};
//   for(int i=0;i<4;i++){
//    printf(" %d\n", arr[i]);
//    }






     //{ int x[5];
//    x[0]=0;
//    x[1]=2;
//    x[2]=4;
//    x[3]=8;
//    x[4]=16;
//    printf("%d\n", x[4]);


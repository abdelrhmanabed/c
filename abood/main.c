#include <stdio.h>
#include <stdlib.h>
int row=4,  clm=3;
void printarray(int [][clm]);
void filearray(int [][clm]);
int main()
{
    printf("please enter the number of rows:\n");
    scanf("%d",&row);
    printf("please enter the number of clm:\n");
    scanf("%d",&clm);
    int array[row][clm];
   filearray(array);
   printarray(array);

    return 0;
}
void printarray(int array[][clm]){
    for(int i=0; i<row;i++){
    for(int j=0;j<clm;j++){
    printf("%d",array[i][j]);
        }
        printf("\n");
    }
}

void filearray(int array[][clm]){
    for(int i=0; i<row;i++){
         printf("please enter the element of row:%d\n",i);
        for(int j=0;j<clm;j++){
            scanf("%d",&array[i][j]);
        }
        printf("\n");
        }
}

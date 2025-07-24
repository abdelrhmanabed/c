#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{ int size=4;
    char name [size][20];
    for(int i=0;i<size;i++){
        printf("please enter the name number:%d\n",i);
        gets(name[i]);
    }
    printf("printing...\n");
    for(int i=0;i<size;i++){
        puts(name[i]);
    }
    for(int i=0;i<size;i++){
        if(strcmp(name[i],"ahmad")==0){
        puts(name[i]);
    }
    }
    char temp[20];
    for(int i=0; i<size; i++){
       for(int j=i+1; j<size; j++){
            if(strcmp(name[i],name[j])>0){
              strcpy(temp,name[i]);
              strcpy(name[i],name[j]);
              strcpy(name[j],temp);
           }
       }
    }
    printf("after soriting\n");
    for(int i=0;i<size;i++){
        puts(name[i]);
    }

    return 0;
}

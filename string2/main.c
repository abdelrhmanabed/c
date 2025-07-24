#include <stdio.h>
#include <stdlib.h>

int main()
{ char name[]="Ramallah, Alirseal street, 20#30";//هاي بتفصل حسب بدك ياه
    char *part;
//    part=strtok(name ,"  ");
//    printf("%s\n",part);
//    while(part!='\0'){
//    part=strtok('\0' ,"  #");
//    printf("%s\n",part);
//    }
    int i=0;
    while(part!='/0'){
          if(i==0){
        part=strtok(name ,"  ");
        printf("%s\n",part);
          }
        else{
        part=strtok('\0' ,",");
        printf("%s\n",part);
        }
        i++;
}
    return 0;
}

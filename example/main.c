#include <stdio.h>
#include <stdlib.h>

int main()
{int num;
  printf("enter a number:\n");
  scanf("%d", &num);
  int sum=0;
  int count=0;
  int max=0;
  while(num!=0){
    int lastdigit=num%10;
    if(max<lastdigit){
        max=lastdigit;
    }
    num/=10;
    sum+=lastdigit;
    count++;
     }
    printf("the sum all digit is:%d\n", sum);
    printf("the number of digit is:%d\n", count);
    printf("the max digit is:%d\n",max);

    return 0;
}

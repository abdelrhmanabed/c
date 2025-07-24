#include <stdio.h>
#include <stdlib.h>

int main()
{
   int a;
   int b;
   int x;
   printf("the value of a and b");
   scanf("%d%d",&a,&b);

   x=2* a + b*b*b + 5 * a * b;
   printf("the value of x :%d",x);
}

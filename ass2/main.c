#include <stdio.h>
#include <stdlib.h>

//Abedelrhman Abed
//ID:1193191

int find_GCD(int,int);
int find_odd_sum(int);
int main()
{

   int num1,num2,choice,gcd,odd_sum;
   printf("Enter first number: ");
   scanf("%d",&num1);
   printf("Enter second number: ");
   scanf("%d",&num2);
   if(!((num1>999 && num1<10000)&&(num2>999 && num2<10000)))
       {
           printf("Numbers are not four digits");
           return 0;
       }
   else
   printf(" 1-Print GCD of the two numbers:\n");
   printf(" 2-Print sum of odd digits of each number:\n");
   printf(" 3-Print relation of odd sum of digits larger/smaller/equal:\n");
   printf("Enter your choice(1-3):\n ");
   scanf("%d",&choice);

   switch(choice)
   {
       case 1:
           {
               gcd=find_GCD(num1,num2);
               printf("GCD of %d and %d is %d",num1,num2,gcd);
           }
           break;

       case 2:
           {
               odd_sum=find_odd_sum(num1);
               printf("Sum of odd digits of %d is %d:\n",num1,odd_sum);
               odd_sum=find_odd_sum(num2);
               printf("Sum of odd digits of %d is %d:\n",num2,odd_sum);
           }
           break;

       case 3:
           {
               if(find_odd_sum(num1)>find_odd_sum(num2))
                   printf("Sum of odd digits of %d is larger than the sum of %d\n",num1,num2);
               else if(find_odd_sum(num1)<find_odd_sum(num2))
                   printf("Sum of odd digits of %d is smaller than the sum of %d\n",num1,num2);
               else
                   printf("Sum of odd digits of %d and %d is equal\n",num1,num2);
           }
           break;
       default:
           printf(" error");
   }
}

int find_GCD(int num1,int num2)
{
   int i,gcd;
   for(i=1;i<=num1&&i<=num2;i++)
   {
       if(num1%i==0 && num2%i==0)
           gcd=i;
   }
   return gcd;
}
int find_odd_sum(int num)
{
   int n,rem,sum=0;
   n=num;
   while(n)
   {
       rem=n%10;
       n=n/10;
       if(rem%2==1)
           sum=sum+rem;
   }
   return sum;
}

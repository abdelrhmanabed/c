#include <stdio.h>
#include <stdlib.h>
int main()

{   int num;
    printf("please enter the number:\n");
    scanf("%d",&num);
    int sum=0;
    int sumodd=0;
    int max=num%10;
    int countdigit =0;
    while(num!=0){
        int lastdigit=num%10;
        num/=10;



        countdigit++;

       if (max<countdigit){
          countdigit=max;
       }
       if(lastdigit%2==0)
        sum+= lastdigit;
        if(lastdigit%2!=0)
            sumodd+=lastdigit;



    }

    printf("the last digit is:%d\n",countdigit);
    printf("the sum digit:%d\n",sum);
    printf("the max digit is:%d\n", max);
    printf("the sumodd is:%d\n", sumodd);


for(int x=7; x>=1 ;x--){   //دلطباعه مثلث قاآم الزاويه
        for( int j=0; j<x; j++)
    printf("%d",x);
    printf("\n");}

return 0;
}



//int temp;
//int max=-999;
//for(int i=0; i<4; i++){
//    printf("enter value\n");
//    scanf("%d", &temp);
//    if(temp>max){
//        max=temp;
//    }
//
//}
//
//printf("the max value is:%d", max);
//




//for(int x=7; x>=1 ;x--){   لطباعه مثلث قاآم الزاويه
//        for( int j=0; j<x; j++)
//    printf("%d",x);
//    printf("\n");


//  int h;
//printf("enter value h:\n");
//scanf("%d",&h);
// int w;
//printf("enter value w:\n");
//scanf("%d",&w);
//
//    for(int x=0; x<h; x++){
//    for(int x=0; x<w; x++){
//
//        printf("* ");
//
//    }
//    printf("\n");





//for(int x=10; x>=0; x--){ للعد العكسي
//        printf("%d",x);
//    }






//{
//    for(int x=0; x<=10; x++){
//            printf("%d\n", x);
//
//    }


//int x=0;
//    do{
//
//       printf("%d\n",x);
//         x++;
//
//    }while( x>0 && x<5);
//
//    return 0;












//    int x;
//    do{
//        printf("please enter number:\n");
//        scanf("%d",&x);
//        printf("your number is :%d\n",x);
//
//    }while(x!=0);
//
//








//int i=0;
//while (i<10){
//        i++;
//    if(i==7)
//
//        continue;
//
//    printf("%d\n",i);
//
//}


//int counter=0;
//while(counter<=10){
//    if(counter==10){
//            break;
//
//    }
//    printf("%d\n", counter);
//    counter++;
//
//}
//



//int i=1;
//while (i<=10){
//    printf("%d\n",i);
//    i++;
//    }

//int x;
//printf("enter grade\n");
//scanf("%d",&x);
//
//while(x!=-1){
//
//      x>=60 && x<100 ? printf("up\n") : printf("down\n");
//
//printf("enter grade to co and -1 to exit\n");
//scanf("%d",&x);
//
//
//}



  //  int num1, num2;
//  char oper;
//  printf("please enter opertner:\n");
//  scanf("%c",&oper);
//  printf("please enter number 1 and number 2:\n");
//  scanf("%d%d", &num1, &num2);
//  switch(oper){
//  case '+':
//     printf("the sum :%d\n", num1 + num2);
//     break;
//  case '-':
//     printf("the sub :%d\n", num1 - num2);
//     break;
//  case '*':
//     printf("the muilt :%d\n", num1 * num2);
//     break;
//  case '/':
//      printf("the divi :%d\n", num1 / num2);
//      break;







//{int x;
//    printf("enter your number\n");
//    scanf("%d",&x);
//    switch (x)        {
//       case 1:
//       printf("sun");
//       break;
//       case 2:
//       printf("mon");
//       break;
//       case 3:
//       printf("th");
//       break;
//       default:
//        printf("should between 1-3")
//    }

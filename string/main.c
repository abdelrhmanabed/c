#include <stdio.h>
#include <stdlib.h>

int main()
{
    char name[6]={'a','h','m','a','d'};
    printf("name:%s\n",name);
    char lastname[20]="hosam";
    printf("last name:%s\n", lastname);
//    strcpy(name,lastname);//تغير مكان
//    puts(name);
//    strncpy(name,lastname,3);غير اول 3 احرف من ahmad حط بدالهم اول 3 احرف من hosam
//    puts(name);
    printf("cmp all:%d\n",strcmp(name,lastname));//للمقارنه جميع الاسم بتعطيك يا 1او-1او0
    printf("%d\n",strncmp(name, lastname, 3));
    printf("lenght :%d\n",strlen(name));
    //printf("cat:%s\n",strcat(name,lastname));هاي بتشبك كلمتين مع بعض
     printf("cat not all:%s",strncat(name,lastname,3));//هاي شبكت name مع اول 3 احرف للlastnaem
  //scanf("%s",lastname);// هسا هاي ممنوع يكون  في سباس فبنستخدم gets(lastname)
   // printf("%s",lastname);// برضو ممنوع يكون في سباس puts(lastname)
//   gets(lastname);
//   puts(lastname);

    return 0;
}

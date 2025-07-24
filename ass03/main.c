#include <stdio.h>
#include <stdlib.h>
//abdelrhman abed
//1193191
int len=0;
struct sum_pos
{
    int number;
    int pos;
}sum_pos_var;
int sum_of_divs(int num1)
{
    int sum=num1+1;
    for(int i=2;i<=num1/2;i++)
    {

        if(num1%i==0)
        {
            sum+=i;
        }
    }
    return sum;
}

void max_sum_and_pos(int a[100])
{
    int large=0,pos,num;
    for(int i=0;i<len;i++)
    {
        num=sum_of_divs(a[i]);
        if(num>large)
        {
        large=num;
        pos=i;
        }
    }
    sum_pos_var.number=a[pos];
    sum_pos_var.pos=pos;

}

int main() {
    FILE *infile;
    int number1, number2, sum,num[100],i=0;

    infile = fopen("nums.txt", "r");
    if (infile == NULL)
    {
        printf("Can't open file for reading.\n");
    }
    else
    {
        while( fscanf(infile, "%d", &number1)!=EOF)
        {
        num[i++]=number1;
        len++;
        }
        max_sum_and_pos(num);
        printf("The number with max sum of divisors is %d at position %i in the array",sum_pos_var.number,sum_pos_var.pos);
    }
    fclose(infile);
}


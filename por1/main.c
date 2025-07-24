
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void uploaddatafile(char **title,int *bin,double *price,int *records)   //pass by refrence titel,bin number, records
{

  FILE *fptr;
  printf("\nUploading data file\n");
  if ((fptr = fopen("data.txt", "r")) == NULL) {  // Program exits if file pointer returns NULL.
        printf("Error! opening file");

        exit(1);
    }
  printf("Data File uploaded\n");
  fclose(fptr);
}
void updateDatafile(char **title,int *bin,double *price,int *records){  //pass by refrence titel,bin number, records
    int i;
    FILE *fptr1;
    printf("\nUpdating data file ...");
    printf("\nThank you for using my Bookstore Management System. Goodbye\n");
    fptr1 = fopen("data.txt", "w");    // open file for write.
    for(i=0;i==(*records);i++){
      fprintf(fptr1, "%s,", title[i]);    //write in file book titel
      fprintf(fptr1, "%d,", bin[i]);      //write in file book bin number
      fprintf(fptr1, "%lf", price[i]);    // write in file price
      fprintf(fptr1, "\n");
    }
    fclose(fptr1);




}
void addbook(char **title,int *bin,double *price,int *records){ //pass by refrence titel,bin number, records
  //add the book
  printf("\nEnter the Book titel: ");
  scanf("%s",title[*records]);
  printf("\nEnter the book bin number: ");
  scanf("%d",&bin[*records]);
  printf("\nEnter the book price: ");
  scanf("%lf",&price[*records]);
  *records = (*records)+1;
}
void removebook(char **title,int *bin,double *price,int *records){  //pass by refrence titel,bin number, records
    int temp;
    printf("\nEnter bin number for remove book:-");
    scanf("%d",&temp);
    //remove the book detail
    for(int i=0;i<25;i++)
    {
      if(bin[i]==temp)
      {
        title[i]=title[i+1];
        bin[i]=bin[i+1];
        price[i]=price[i+1];
        *records = (*records)-1;
        return;
      }
    }
    printf("\nRecord Not found\n");
}

void searchbook(char **title,int *bin,double *price){
    int temp;
    printf("\nEnter bin number for search book:-");
    scanf("%d",&temp);
    //search the book detail
    for(int i=0;i<25;i++)
    {
      if(bin[i]==temp)
      {
        printf("\nTitle:%s",title[i]);
        printf("\nBin number:%d",bin[i]);
        printf("\nPrice:%.2lf",price[i]);
        printf("\n");
        return;
      }
    }
    printf("\nRecord Not found\n");
}

void displayMainMenu(int *choice)
{
  printf("\nPlease selece an Operation <1-4>:\n1- Add a Book:\n2-Remove a Book:\n3- Search for a Book:\n4- Exit System:\n\n");
  scanf("%d",choice);     //get choice of menu
}
int main(void) {
  char *title[25];
  int bin[25];
  double price[25];
  int records=0;
  int choice;



uploaddatafile(title,bin,price,&records);  //call function uploaddatafile


while(choice!=4)            //menu
{
  displayMainMenu(&choice);
  switch(choice)
  {
    case 1:addbook(title,bin,price,&records);
          break;
    case 2:removebook(title,bin,price,&records);
          break;
    case 3:searchbook(title,bin,price);
          break;
    case 4:updateDatafile(title,bin,price,&records);
            break;
    default:
            printf("\nNo such Operation! Please try again\n");
  }
}


  return 0;
}

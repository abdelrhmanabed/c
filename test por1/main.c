#include <stdio.h>
#include <stdlib.h>
void displayMainMenu();
void addBook();
void removeBook();
void searchForBook();
void uploadDataFile();
void updateDataFile();

int main()
{
    uploaddatafile();
    int choice;
    while(choice!=4){
  displayMainMenu();
    scanf("%d",&choice);
  switch(choice)
  {
    case 1:addBook();
          break;
    case 2:removeBook();
          break;
    case 3:searchForBook();
          break;
    case 4:updateDatafile();
          break;
    default:
            printf("\nNo such Operation! Please try again\n");
  }
}
}
void uploaddatafile(){
  FILE *book;
  printf("\nUploading data file...\n");
  if ((book = fopen("data.txt", "r"))==NULL){
        printf("Error! opening file");
        exit(1);
  }
 printf("Data File uploaded\n");
  fclose(book);
}

void updateDatafile(){

    FILE *book;
    printf("\nUpdating data file ...");
    printf("\nDate file updated");
    printf("\nThank you for using my Bookstore Management System. Goodbye\n");
    book= fopen("data.txt", "w");

    fclose(book);
}
void displayMainMenu(){
printf("\n Please select an Operation <1-4>:\n");
printf(" 1-add book:\n 2-remove a book:\n 3-search for a book:\n 4-Exit System:\n\n");

}
void addBook(){
    printf("Book info has been add\n");
}
void removeBook(){
    printf("Book info has been removed\n");
}
void searchForBook(){
    printf("Book has been search for\n");
}

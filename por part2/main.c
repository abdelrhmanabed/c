#include <stdio.h>
#include <stdlib.h>
//abdelrhman abed
//1193191
//sec 1
void displayMainMenu();
void addBook();
void removeBook();
void searchForBook();
void uploadDataFile();
void updateDatafile();

int main()
{
    printf("Welcome to my Bookstore Management System:\n");
    uploadDataFile();
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
            printf("\nNo such Operation! Please try again.\n");
      }
   }
}
void uploadDataFile(){
    printf("\nUploading data file...\n");
    printf("Data File uploaded\n");

}

void updateDatafile(){
    printf("\nUpdating data file ...");
    printf("\nDate file updated");
    printf("\nThank you for using my Bookstore Management System. Goodbye.\n");
}
void displayMainMenu(){
    printf("\n Please select an Operation <1-4>:\n");
    printf(" 1-Add a Book:\n 2-Remove a Book:\n 3-Search for a Book:\n 4-Exit System:\n\n");

}
void addBook(){
    printf("Book info has been added\n");
}
void removeBook(){
    printf("Book info has been removed\n");
}
void searchForBook(){
    printf("Book has been searched for\n");
}

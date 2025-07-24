#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 100
int m_size = 0;


void uploadDataFile(int *bins, double *prices, int *status);
void displayMainMenu();
void printBooks(const int bins[], const double prices[], const int* status);
void addBook(int bins[], double prices[], int status[]);
const bool isBookExists(const int bins[], const int bin, int *bookIndex);
void searchForBook(int bins[], double prices[], int status[]);
void removeBook(int bins[], double prices[], int status[]);
void updateDataFile(int bins[], double prices[], int status[]);

int main()
{
int bins[MAXSIZE] = {0};
double prices[MAXSIZE] = {0.0};
int status[MAXSIZE] = {0};

printf("Welcome to My BookStore Management System:\n\n");
uploadDataFile(bins, prices, status);

int userInput = 0;
do
{
displayMainMenu();
scanf("%d", &userInput);
switch(userInput)
{
case 0:
break;
case 1:
addBook(bins, prices, status);
break;
case 2:
removeBook(bins, prices, status);
break;
case 3:
searchForBook(bins, prices, status);
break;
case 4:
printBooks(bins, prices, status);
break;
case 5:
updateDataFile(bins, prices, status);
break;
}
}while(userInput != 5);
return 0;
}

void displayMainMenu()
{
printf("Please select an operation (1-4):\n");
printf("1- Add a Book:\n");
printf("2- Remove a Book:\n");
printf("3- Search for a Book:\n");
printf("4- Print Book List:\n");
printf("5- Exit System:\n");
}

void uploadDataFile(int *bins, double *prices, int *status)
{
char line[100] = {'\0'}, c;
printf("Uploading data file...\n");
FILE *fp = fopen("books.txt", "r");
do
{
line[0] = '\0';
fscanf(fp, "%s", line);
if(strlen(line) > 0)
{
bins[m_size] = atoi(line);
}
line[0] = '\0';
fscanf(fp, "%s", line);
if(strlen(line) > 0)
{
prices[m_size] = atof(line);
status[m_size] = 1;
m_size++;
}
}while(strlen(line) > 0);
fclose(fp);
printf("Data File uploaded\n\n");
}

void printBooks(const int bins[], const double prices[], const int* status)
{
for(int i = 0; i < m_size; i++)
{
if(1 == status[i])
{
printf(" bin# = %d\tprice = %f\n", bins[i], prices[i]);
}
}
printf("\n");
}

void addBook(int bins[], double prices[], int status[])
{
if(m_size < MAXSIZE)
{
int bookIndex = -1;
int newBin = 0;
double newPrice = 0.0;
printf("Enter bin number for book\n");
scanf("%d", &newBin);
printf("Enter price of book\n");
scanf("%lf", &newPrice);

if(!isBookExists(bins, newBin, &bookIndex))
{
bins[m_size] = newBin;
prices[m_size] = newPrice;
status[m_size] = 1;
m_size++;
printf("Book with bin %d has been added\n", newBin);
}
else
{
if(0 == status[bookIndex])
{
status[bookIndex] = 1;
}
    printf("Book already exists\n");
}
}
}

   const bool isBookExists(const int bins[], const int bin, int *bookIndex)
{
for(int i = 0; i < m_size; i++)
{
     if(bin == bins[i])
{
*bookIndex = i;
return true;
}
}
return false;
}

void searchForBook(int bins[], double prices[], int status[])
{
  if(0 < m_size)
{
int bookIndex = -1;
  int remBin = 0;
  printf("Enter the bin number for the book to search\n");
   scanf("%d", &remBin);
if(isBookExists(bins, remBin, &bookIndex))
{
printf(" bin# = %d\tprice = %f\n", bins[bookIndex], prices[bookIndex]);


}
}
printf("\n");
}



void removeBook(int bins[], double prices[], int status[])
{
   if(0 < m_size)
{
  int bookIndex = -1;
   int remBin = 0;
     printf("Enter bin number for book to remove\n");

scanf("%d", &remBin);

if(isBookExists(bins, remBin, &bookIndex))

     status[bookIndex] = 0;

    printf("Book with bin %d has been removed\n", remBin);
}
else
{
     printf("Book with bin %d does not exist\n", remBin);
}
}
}

void updateDataFile(int bins[], double prices[], int status[])
{
    printf("Updating data file...\n");
    char data[100] = {'\0'};
    FILE *fp = fopen("books.txt", "w");
for(int i = 0; i < MAXSIZE; i++)
{
   if(1 == status[i])
{
char buf[20] = {'\0'};
   data[0] = '\0';
  snprintf(buf, sizeof(buf), "%d", bins[i]);
   strcpy(data, buf);
  strcat(data, " ");
   memset(buf, '\0', sizeof(buf));
    snprintf(buf, sizeof(buf), "%f", prices[i]);
     strcat(data, buf);
       fprintf(fp, "%s\n", data);
}
}
   fclose(fp);
   printf("Data File update\n");
}

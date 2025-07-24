//Abdelrhman abed
//1193191
//3


#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include <string.h>

void Load_bus_information();
void Load_pass_information();
int Assign_passengers_print_buss_information();
int Print_specific_bus_info();
int Print_unmatched_passengers();
int Add_new_passenger();
void Delete_passenger();
int Delete_bus_number();

char  source_all[150][150];
char  destination_all[150][150];
int id_all [150];
char time_all[250][250];
int date_all [150];
///////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int bus_number[150];
int bus_date[150];
char bus_time[155][150];
char  sourceBus_all[150][150];
char  destinationBus_all[150][150];
int capacity[150];
int price[150];
///////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

struct passenger
{
    int id_p ;
    int date_p   ;
    char time_p[150] ;
    char sour_p[150];
    char des_p[150];
    struct passenger* Next;
};


struct bus
{
    int num ;
    int date_b;
    char time_b ;
    char des_b;
    char sour_p;
    struct bus* Next;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void insert(int id2,int date2,char time2[], char sou2[],  char dest2[], struct passenger* L );
struct passenger* FindPrevious(int X, struct passenger* L);
struct passenger*  IsLast(struct passenger* P, struct passenger* L);
int isEmpty(struct passenger* L);
void Delete(int X, struct passenger* L);
struct passenger *start=NULL;
struct passenger* L;
void PrintList( struct passenger *L);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int main()
{


    int task=0;
    do
    {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. Load the bus information file. \n");
        printf("2. Load the passenger information file. \n");
        printf("3. Assign passengers and print assignment information of all busses.\n");
        printf("4. Print a specific bus information along with its passengers information (names and IDs).\n");
        printf("5. Print unmatched passengers. \n");
        printf("6. Add new passenger.\n");
        printf("7. Delete passenger.\n");
        printf("8. Delete bus number.\n");
        printf("9. Exit.\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        scanf("%d",&task);
        switch(task)
        {
        case 1:
            Load_bus_information();
            break;
        case 2:
            Load_pass_information();
            break;
        case 3:
            Assign_passengers_print_buss_information();
            break;
        case 4:
            Print_specific_bus_info();
            break;
        case 5:
            Print_unmatched_passengers();
            break;
        case 6:
            Add_new_passenger();
            break;
        case 7:
            Delete_passenger();
            break;
        case 8:
            Delete_bus_number();
            break;
        default:
            exit(-1);
            //}
        }
    }
    while (task!=9);
    return 0;
}
//********************************


void insert(int id2,int date2,char time2[], char sou2[],  char dest2[], struct passenger* L  )
{
    struct passenger *temp2 = NULL, *current = NULL, *head = NULL;
    // L =  head ;
    temp2 = (struct passenger*)malloc(sizeof(struct passenger));
//   head = NULL;    head = (struct passenger*)malloc(sizeof(struct passenger));
    temp2->Next=NULL;
    temp2->id_p = id2;
    temp2->date_p= date2;
    strcpy(temp2->time_p, time2);
    strcpy(temp2->sour_p, sou2);
    strcpy(temp2->des_p, dest2);
    temp2->Next = NULL;
    // temp2->Next = head->Next;
    //head->Next= temp2;

    if(head ==NULL)
    {
        head = temp2;
        current = temp2;
    }
    else
    {
        current->Next = temp2 ;
        current = current->Next ;
    }
    printf(" %-10d %-10d %-10s %-10s %-10s \n",temp2->id_p, temp2->date_p,  temp2->time_p,temp2->sour_p,temp2->des_p);
    head = L ;
}

/*
void insert(int id2,int date2,char time2[], char sou2[],  char dest2[] , struct passenger **head)
{
    //create a new node
    struct passenger *temp2 = malloc(sizeof(struct passenger));
    temp2->id_p = id2;
    temp2->date_p= date2;
    strcpy(temp2->time_p, time2);
    strcpy(temp2->sour_p, sou2);
    strcpy(temp2->des_p, dest2);
    temp2->Next= NULL;

    if(*head == NULL)
         *head = temp2;
        printf(" %d %d %s %s %s \n",temp2->id_p, temp2->date_p,  temp2->time_p,temp2->sour_p,temp2->des_p);
    //if head is NULL, it is an empty list


}*/


struct passenger* FindPrevious(int X, struct passenger* L)
{

    struct passenger* P;
    struct passenger* S = L -> Next;

    P = L;

    while(P->Next != NULL && P->Next->id_p != X)
        P = P->Next;
    S = S->Next;

    return P;

}


struct passenger*  IsLast(struct passenger* P, struct passenger* L)
{

    return P->Next == NULL ;
}

int isEmpty(struct passenger* L)
{
    return L->Next ==NULL;
}


void Delete(int X, struct passenger* L)
{
    if(!isEmpty(L))
    {
        struct passenger* P;
        struct passenger* temp;

        P = FindPrevious(X, L);

        if(P!= NULL)
        {
            temp = P->Next;
            P->Next = temp->Next; //bypass delete cell
            free(temp);
        }

    }

}

struct passenger* MakeEmpty(struct passenger* L)
{

    L = ( struct passenger *)malloc(sizeof(struct passenger));

    if(L == NULL)
        printf ("Out of memory!\n");

    else
        L->Next = NULL;
    return L;
}



void Load_bus_information()
{
    FILE* file;
    char chB;
    char Bname[20];


    // Opening file in reading mode
    file = fopen("busses.txt", "r");

    if (NULL == file)
    {

        ("file can't be opened \n");
    }


    char Bbuf[100] ;
    char Btemp[150];
    char timeB[145] ;
    char Bdestination[150] ;
    char Bsource[150] ;
    int bus_num, dateB, cap, pr ;
    int counter =0;

    while (fgets(Bbuf,100,file))
    {
        bus_num = atoi( strcpy(Btemp,strtok(Bbuf,"#")));
        dateB= atoi( strcpy(Btemp,strtok(NULL,"#")));
        strcpy(timeB,strtok(NULL,"#"));
        strcpy(Bsource,strtok(NULL,"#"));
        strcpy(Bdestination,strtok(NULL,"#"));
        pr= atoi( strcpy(Btemp,strtok(NULL,"#")));
        cap= atoi( strcpy(Btemp,strtok(NULL,"#")));

        for(int s=0; s<5; s++)
        {
            price[s]= pr;
        }
        for(int s=0; s<5; s++)
        {
            capacity[s]= cap;
        }

        for(int s=0; s<5; s++)
        {
            bus_number[s]= bus_num;
        }
        for(int s=0; s<150; s++)
        {
            bus_date[s]= dateB;
        }

        for(int s=0; s<150; s++)
        {
            bus_time[counter][s]= timeB[s];
        }

        for(int s=0; s<150; s++)
        {
            sourceBus_all[counter][s]= Bsource[s];
        }

        for(int s=0; s<150; s++)
        {
            destinationBus_all[counter][s]= Bdestination[s];
        }

        counter++;

        printf("%-10d %-10d %-10s %-15s %-15s %-15d %-15d \n",bus_num, dateB, timeB, Bsource, Bdestination, pr, cap );



    }
}

void Load_pass_information()
{

    FILE* fout;
    char ch;
    char fname[20];
    // Opening file in reading mode
    fout = fopen("passengers.txt", "r");

    if (NULL == fout)
    {
        printf("file can't be opened \n");
    }


    // Printing what is written in file
    char buf[100] ;
    char temp[150];
    char source[150] ;
    char destination[150] ;
    char time[150] ;
    int date ;
    int id ;
    int count =0;

    // cutting each line in the file and store them in variables
    while (fgets(buf,100,fout))
    {
        id = atoi( strcpy(temp,strtok(buf,"#")));
        date= atoi( strcpy(temp,strtok(NULL,"#")));
        strcpy(time,strtok(NULL,"#"));
        strcpy(source,strtok(NULL,"#"));
        strcpy(destination,strtok(NULL,"#"));
        //****************
        struct passenger * head;
         insert(id, date, time, source, destination, L );

    }

    count++;
    fclose(fout);


}


int Assign_passengers_print_buss_information()
{
    //passenger * buss_array[100];

}

int Print_specific_bus_info()
{

}

int Print_unmatched_passengers()
{

}


int Add_new_passenger()
{
    int add_id, add_date;
    char add_time[100],add_source [100], add_destination [100];
    printf("please enter the id of the passenger:_");
    scanf("%d", &add_id);
    printf("please enter the date :_");
    scanf("%d", &add_date);
    printf("please enter the time:_");
    // for (int i = 0;i < 4;i++)
    scanf("%s", add_time);

    printf("please enter the place to be collected :_");
    scanf("%s", add_source);
    printf("please enter the destination:_");
    scanf("%s", add_destination);

    printf("\n");
    Load_pass_information();
    insert(add_id, add_date, add_time, add_source, add_destination, L );
    //Load_pass_information();
    printf("\n");
}

void Delete_passenger( )
{
    int X;
    printf("enter id of the passenger that will be deleted ");
    scanf("%d", &X);
    Delete( X,L);
    Load_pass_information();
}

int Delete_bus_number()
{
    struct passenger*L;
    PrintList(L);
}


void PrintList( struct passenger *L)
{

    struct passenger* P = L;
    if( isEmpty(L))

        printf("Empty list\n");

    else

        do
        {

            P=P->Next;
            printf(" %-10d %-10d %-10s %-10s %-10s \n",P->id_p, P->date_p,  P->time_p,P->sour_p,P->des_p);

        }
        while( !IsLast(P, L) );
    printf("\n");

}
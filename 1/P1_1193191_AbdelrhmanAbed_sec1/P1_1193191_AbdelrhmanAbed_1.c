//Abdelrhman Abed 1193191 Sec#1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define string_length 30                // length for the string it fix 30 characters it is size for the words

typedef struct node {                 //   defining the doubly node it have the next and prev pointers to link them together

   char data [string_length + 1 ];  //     name of the array data that have a size of 31 chars

   struct node* next;             //       the name of pointer is next and it is of type pointer
                                 //        it is commonly used in linked list to point to next node the sequence
   struct node* prev;           //         it is similar to next and name is prev , it is used to point to the previous node in a link list
} node;


typedef struct {                     //    the doubly link list

      node* head                   //      type for pointer it implies that this structure is meant to represent
                                  //       a linked list , and head is a pointer to the first node in the list
} doubly_link_list;


void load_text(doubly_link_list* list , const char* data) {   //
     node* newnode = (node*)malloc(sizeof(node));            // allocates memory for new node and ensures that the allocated memory is enough to hold a node structure
     if(newnode == NULL) {                                  //  check if the allocation was successful
        fprintf(stderr, "reading file failed.\n");         //   the exit mean from the if statement that has 1 as a condition
        exit(1);
     }

     strncpy(newnode->data , data , string_length);  //copies the data from the provided string data into the data array the new node using strncpy
     newnode->data[string_length] = NULL;
     newnode->next = NULL;                         //  assigning the pointer to a null value

     if (list->head == NULL){                     //   check if the doubly link list is empty
        newnode->prev = NULL;                    //    the list is empty , sets the prev pointer of the new node
        list->head = newnode;                   //     to NULL and makes the new node the head of the list
     }
     else {                                   //       if the list is no empty , it traverses the list to find the last node
        node* current = list->head;          //        adds the new node to the end of the list by updating the next pointer of the last node
        while (current->next != NULL){      //         setting the new pointer of the new node to the last node
                current = current->next;
        }

        current->next = newnode;
        newnode->prev = current;
     }
}


void print(const doubly_link_list* list){
    node* current = list->head;             // this pointer is used to traverse the list
    while(current != NULL){                //  it enters a loop that continues as long as the current node is not NULL
        printf("%s\n" , current->data);   //   inside the loop , it prints the data of the current node
        current = current->next;         //    move to the next node
    }
}


void radixsort (doubly_link_list* list){
  int max_string_length =0;                     // specifies the length string
  node* current = list->head;                  //  the list to find the maximum length of the strings

  while (current != NULL) {
    int current_length = strlen(current->data);  // to determine the length of each string
    if (current_length > max_string_length){    //  performs radix sort on each character position in the strings
        max_string_length = current_length;
    }
    current = current->next;

  }
  for (int i = max_string_length - 1 ; i >=0; i --) {  //              this loop runs through each character position in the strings
      doubly_link_list buckets [128];                              //  starting from the rightmost character
      for (int i = 0 ; i < 128; i++){                             //   the buckets same the buffer and characters number is 128 mean (a , b, c....)
          buckets[i].head = NULL;                                //    initialize buckets
                                                                //     and the number in the asci is 128

      }

   current = list->head;                                  //this loop iterates through the list and distributes
   while(current != NULL){                               //nodes in to buckets based on the character at the current position

    int charindex;
    if( i < strlen(current->data)){
            charindex = current->data[i];
    }else{
     charindex =0;
    }                                                   //calculates the index of the bucket based on the character at the current position
    load_text(&buckets[charindex], current->data);
             current = current->next;                 // adds the current node to next bucket

  }
  list->head=NULL;                                 //  initializes the main list as empty
  for(int i = 0; i < 128; i++){                   //   this loop iterates through each bucket
    node* bucketcurrent = buckets[i].head;
    while(bucketcurrent != NULL){               //     loop iterates through each node in the current bucket
        node* temp = bucketcurrent;
        bucketcurrent = bucketcurrent->next;  //       remove a node from the bucket , resets its pointers
        temp->next = NULL;                   //        adds it back to the main list
        temp->prev = NULL;
        load_text(list, temp->data);       //          and then free memory
        free(temp);
       }
    }
  }
}

int is_valid_string(const char *str) {
    while (*str) {
        if (!isalpha(*str))
            return 0;
        str++;
    }
    return 1;
}

void load_strings(const char* filename, doubly_link_list* list) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "error opening file: %s\n", filename);
        exit(1);
    }

    char buffer[string_length + 1];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        if (is_valid_string(buffer)) {  // Check if the string contains only characters
            load_text(list, buffer);  // Load valid string into the list
        }
    }
    fclose(file);
    printf("\nfile have been read successfully\n");
}

void load_to_output(const char* filename, const doubly_link_list*list){  // the function appends the data from a doubly linked list to a file
     FILE* file = fopen (filename, "w");                                //  opens the specified file (filename) in append mode ("a")
     if (file == NULL) {                                               //   if the file opening fails , it prints an error message and exits the program
        fprintf(stderr , "error opening file : %s\n" , filename);
        exit(1);
     }
     node* current = list->head;                                   //       initializes a pointer to the head of the doubly linked list
     while (current != NULL) {
        fprintf(file, "%s\n" , current->data);                   //         return through the list and appends each node data to the file using fprintf
        current = current->next;
     }
     fclose(file);                                                        //closes the file using (fclose) to release the associated resources
     printf("\nthe date have been added\n");                             // prints a success message indicating that the data has been added to the file
     printf("\n***please enter (2) to view the modified list*****\n");

}



int main () {

doubly_link_list linkedlist; // initializes an empty linked list name (linkedlist)
linkedlist.head = NULL;

while (1){  // the while is true
    //this information from the project requirements
    printf("\n menu:\n");
    printf("1. load the strings form 'input.txt'\n");
    printf("2. print\n");
    printf("3. sort the strings\n");
    printf("4. add a new word to the list of sorted strings (and sort it)\n");
    printf("5. delete a word from the sorted strings \n");
    printf("6. save to 'output.txt'  \n");
    printf("7. exit \n");
    printf("NOTE:enter (2) to print \n");
    printf("enter your choice (1-7): ");

    int choice;
    scanf("%d",&choice); // read and save the data from the user entering
    printf("\n");       // create new line

    switch (choice) {
      case 1: {
        load_strings("input.txt", &linkedlist); //calls the (load_strings) functions to load strings form (input.txt) into linked list
        break;
      }

      case 2:
        print(&linkedlist);                     // calls the (print) function to print the current state of the linked list
        break;

      case 3:
        printf("the list has been sorted\n");      //     calls the (radixsort) function to sort the strings in the linked list using radix sort
        radixsort(&linkedlist);            //      the method was described by video send in ritaj
        break;

      case 4:  {  // add new word
          printf("enter the new word: ");     //   prompts the user to enter a new word
          char new_word[string_length + 1 ];  //   array name is new_word and size is 30+1

          scanf("%s", new_word);
          load_text(&linkedlist, new_word);  //    calls the (load_text) function to add new word to the linked list
          radixsort(&linkedlist);           //     calls the (radixsort)  to sort the updated list
          printf("\nnew word added '%s' and the list is sorted\n " , new_word);
          printf("\n***please enter (2) to view the modified list*****\n");
          break;
      }
      case 5: {
        char delete_the_word[string_length + 1];    // prompts the user to enter the word to delete
        printf("enter the word to delete: ");
        scanf("%s", delete_the_word);
                                                   // return through the linked list to find the node containing the specified word
                                                  //  if the node to be deleted is not the head . it updates the (prev->next) pointer
        node* current = linkedlist.head;         //   the head , it updates (linklist.head)
        node* prev    = NULL;                   //    calls (radix sort(&linked list) to ensure that the list remains sorted after deletion

        while (current !=NULL && strcmp (current->data, delete_the_word) != 0){
            prev = current;                    //
            current = current->next;
        }
    if(current != NULL ){
        if(prev != NULL) {
        prev->next = current->next;
        }

       else {
            linkedlist.head = current->next;
        }
      free(current); //the free used the statically allocated memory (exp:local variables) pr memory allocated on the stack
      printf("word'%s' deleted from the list.\n", delete_the_word);
      printf("\n***please enter (2) to view the modified list*****\n");
      radixsort(&linkedlist);
      }
      else{

        printf("\nword '%s' not found in the list.\n", delete_the_word);
      }
      break;

    }

       case 6: {
         load_to_output("output.txt",&linkedlist); // this is the function that appends the data to the output file
         break;

       }

       case 7:
           printf("thank you to used my program , bye .\n");   //display message point that the program is exiting
           exit(0);                                           // calls (exit(0)) to terminate the program with a status code of 0

       default:
        printf("\n incorrect choice --> -_- enter a number between 1 and 7.\n"); // this message show when the users entering letters and number other than (1-7)
       }
}

return 0;

}

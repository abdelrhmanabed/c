//Abdelrhman abed 1193191 sec 1
// DR.Ahmad Abusnaina
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 251
int quadratic_collisions=0;        //global variable to count the collision in quadratic hash
int double_hashing_collisions =0; //global variable to count the collision in double hash


struct Word {
       char word [80];           // array name word size of 80
       char meanings [3][100];  //  two dimensional array 3 rows and 100 columns
};

int hash (char* key , int table_size){    // function hash takes a string key and table size char* key a pointer to the beginning string
     int hashValue = 0;                  //  initializes the hash value to zero.
    while(*key !='\0'){                 // '\0' null terminator
        hashValue = hashValue + *key++;           // the loop, it adds the ASCII value of the current character and the pointer to move to next character in string

    }
    return (hashValue % table_size); // processing all characters in the string
}

int hash2 (char* key , int table_size){  // char* key  pointer to the first character of the string and table_size the size of the hash table
    long long hashValue = 0;             //  initializes the hash value to zero and long long used to handle larger number
    while (*key != '\0'){
        hashValue = ((hashValue * 32 )+ *key++) %table_size;
    }
    return hashValue;
}

void insert_quadratic(struct Word table[], struct Word new_word) {  //function is used to add a new word into a table
    int index = hash(new_word.word, TABLE_SIZE);  //this line calculates a starting position 'index'
    int i = 0; //attempt
    while (table[index].word[0] != '\0' && i < TABLE_SIZE) {  // this loop to keep turn must be two conditions ture
        quadratic_collisions++;
        i++;                           // adds one to counter
        index = (index + i * i) % TABLE_SIZE; // calculating a new position to try and put the word in
    }                                         // % TABLE_SIZE makes sure that the new position you calculate is still within the bounds of your table
    if (i==TABLE_SIZE) {
        printf("table is full or needs rehashing\n");
        return;
    }
    table[index] = new_word; // If you have found an empty spot in the table, this line puts the new word in that spot
}

void insert_double_hashing(struct Word table[], struct Word new_word) {
    int index = hash(new_word.word, TABLE_SIZE);
    int i = 0; //attempt
    while (table[index].word[0] != '\0' && i < TABLE_SIZE) {
        double_hashing_collisions++;
        i++;
        index = ((index) + i * hash2(new_word.word, TABLE_SIZE)) % TABLE_SIZE; //calculates a new index using the double hashing method
    }
    if (i >= TABLE_SIZE) {
        printf("table is full or needs rehashing\n");
        return;
    }
    table[index] = new_word;  // If you have found an empty spot in the table, this line puts the new word in that spot
}

void print_table(struct Word table[]) {  // this function to print table and takes array of struct word this array table
     for (int i = 0; i < TABLE_SIZE;  i++){  // this loop to slot hash in table to check every slot in table
        if (table[i].word[0] !='\0') {// if table.word have value print the value if not print empty
            printf("%d]: %s - ", i, table[i].word);
            if (table[i].meanings[0][0] != '\0') {
                printf("%s", table[i].meanings[0]);
            }
            if (table[i].meanings[1][0] != '\0') {
                printf(",%s", table[i].meanings[1]);
            }
            if (table[i].meanings[2][0] != '\0') {
                printf(",%s", table[i].meanings[2]);
                printf("\n");

            }
            }

        else{
            printf("%d]: empty\n", i);
        }
     }
}

void load_factors(struct Word quadratic_table[], struct Word double_hashing_table[], int table_size) {
    float load_factor(struct Word table[], int size) { // this function used to calculate load factors in double table and quadratic table
        int count = 0;
        for (int i = 0; i < size; i++) {    // loop that will iterate over each slot in the hash table
            if (table[i].word[0] != '\0') {  // statement checks if the current slot at index i in the hash table is occupied
                count++;
            }
        }
        return (float)count / size; //  the load factor is calculated by dividing  count by size
    }

    printf("table Size: %d\n", table_size);
    float load_factor_quadratic = load_factor(quadratic_table, table_size); //calls function load_factor_quadratic and stores the result in load_factor_quadratic
    float load_factor_double_hashing = load_factor(double_hashing_table, table_size); //calls function load_factor_double_hashing and stores the result in load_factor_double_hashing.
    printf("load factor for quadratic: %.2f\n", load_factor_quadratic);
    printf("load factor for double hashing: %.2f\n", load_factor_double_hashing);
}

void add_hash(struct Word new_word, struct Word quadratic_table[], struct Word double_hashing_table[]) {
    int i; // attempt
    int index;  //this function to add new word to double table and quadratic table
    int table_choice;
    scanf("%d", &table_choice); // case statement
    switch(table_choice) {
        case 1:
            insert_quadratic(quadratic_table, new_word);  // call function insert quadratic
            printf("word '%s' inserted in quadratic table\n", new_word.word);
            break;

        case 2:
            insert_double_hashing(double_hashing_table, new_word);  // call function insert double
            printf("word '%s' inserted in double hashing table\n", new_word.word);
            break;

        case 3:
            insert_quadratic(quadratic_table, new_word);  // insert new word to both table calls  function insert double&function insert quadratic
            insert_double_hashing(double_hashing_table, new_word);
            printf("word '%s' inserted in both tables\n", new_word.word);
            break;

        default:
            printf("incorrect choice. Please enter a number between [1-3]\n");
    }
}

void search_word (struct Word table[] , char* word , int use_quadratic){
     int index = hash (word , TABLE_SIZE); //hash index for the given word and using hash function to get initial position in hash
     int i = 0; // attempt
     int j = 0; // step

     while(table[index].word[0] !='\0' && strcmp(table[index].word , word) !=0){ // this loop slot at the current index
        if(use_quadratic){ // if use_quadratic is 1, the step size j is set to the square of the attempt number i (quadratic)
            j= i *i; // step = attempt * attempt
        }
        else{  //if use_quadratic is 0, j is calculated using a hash2 (double hashing)
            j = i * hash2(word , TABLE_SIZE);
        }
        index = (index + j) % TABLE_SIZE; // update the index for next probe using the calculated step size j.
        i++;
        if(i > TABLE_SIZE){   //it means the function has checked the entire table without finding the word
            printf("word not found\n");
            return;
        }
     }
     if (table[index].word[0] == '\0'){  //checks if the current slot is empty. If it is, it means the word was not found in the table.
        printf("word not found \n");
     }
     else{
        printf("word: %s\n" , table[index].word); //if the word is found, it prints the word and its meanings stored at the current index.
        printf("meanings: %s, %s, %s\n", table[index].meanings[0], table[index].meanings[1], table[index].meanings[2]);
     }
  }

void delete_word(struct Word table[], char* word, int use_double_hashing) {
    int index = hash(word, TABLE_SIZE);
    int i = 1; // attempt
    while (strcmp(table[index].word, word) != 0) {
        if (table[index].word[0] == '\0') { // the word is not present in table
            printf("word not found\n");
            return;
        }
        if (use_double_hashing) {
            index = (index + i * hash2(word, TABLE_SIZE)) % TABLE_SIZE;
        } else {
            index = (index + i * i) % TABLE_SIZE;
        }
        i++; // increments the attempt counter
        if (strcmp(table[index].word, "") == 0) {
            printf("word not found.\n");
            return;
        }
    }
    strcpy(table[index].word, "");
}

void load_from_file1(struct Word quadratic_table[]) { // this function using to load quadratic  form file
     FILE *file = fopen("words.txt", "r");      //  read the word and meanings form input file
     if(!file) {
        printf("error opening file\n");
        return;
     }
     struct Word new_word;
     char line[200];  // character array to hold each line read from the file

     while (fgets(line , sizeof(line) , file)) { //this loop reads the file line by line until the end of the file is reached. Each line is stored in the line array.
        memset(&new_word , 0 , sizeof(new_word)); // it used to initialize new word to zero it is cleaning  before storing new data
        int count = sscanf(line , "%[^:]:%[^#]#%[^#]#%[^#\n]", new_word.word , new_word.meanings[0] ,new_word.meanings[1] , new_word.meanings[2]);
        if (count >=1 ) {
            insert_quadratic(quadratic_table, new_word);
        }
     }
     fclose(file);
     }

void load_from_file2( struct Word double_hashing_table[]) { // this function using to load double hashing  form file
     FILE *file = fopen("words.txt", "r");
     if(!file) {
        printf("error opening file\n");
        return;
     }
     struct Word new_word;
     char line[200];

     while (fgets(line , sizeof(line) , file)) {
        memset(&new_word , 0 , sizeof(new_word));
        int count = sscanf(line , "%[^:]:%[^#]#%[^#]#%[^#\n]", new_word.word , new_word.meanings[0] ,new_word.meanings[1] , new_word.meanings[2]);
        if (count >=1 ) {
            insert_double_hashing(double_hashing_table, new_word);
        }
     }
     fclose(file);
     }

void save_to_file(struct Word table[]) {     // save double hashing to output file
     FILE *file = fopen("saved_words.txt", "w"); //rewrite in same input file and saving in it
     if (file == NULL) {
        printf("error opening file\n");
        exit(1);
     }
     for (int i = 0; i < TABLE_SIZE; i++){
        if(table[i].word[0] != '\0') {
            fprintf(file , "%s:" , table[i].word);
             if(table[i].meanings[0][0] != '\0'){
                fprintf(file , "%s" , table[i].meanings[0]);
             }
             if(table[i].meanings[1][0] != '\0'){
                fprintf(file , "#%s" , table[i].meanings[1]);

             }
             if(table[i].meanings[2][0] != '\0'){
                fprintf(file , "#%s\n" , table[i].meanings[2]);

             }
        }
     }
     fclose(file);
     printf("double hashing table saved to 'saved_words.txt'");
     }

int main() {
    struct Word quadratic_table[TABLE_SIZE] = {0};    // array  of struct Word with the size / {0} this mean initializes all elements of these array =0
    struct Word double_hashing_table[TABLE_SIZE] = {0};
    load_from_file1(quadratic_table); // call function load from file 1  "quadratic table to load"
    load_from_file2( double_hashing_table);// call function load from file 2 "double hashing to load"

    while(1){        // while loop
        printf("\nMenu:\n");
        printf("1. Print hashed tables\n");
        printf("2. Print table size and load factor\n");
        printf("3. Print hash functions\n");
        printf("4. Insert a new word\n");
        printf("5. Search for a word\n");
        printf("6. Delete a word\n");
        printf("7. Compare collision count\n");
        printf("8. Save double hashing table to file\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d" , &choice);
        char word[80];
        struct Word new_word;

        switch(choice){
        case 1: // display contents of both tables
            printf("\nopening quadratic table:\n");
            print_table(quadratic_table);
            printf("\nopening double hashing table:\n");
            print_table(double_hashing_table);
            break;

        case 2:  // print table size and load factor
              load_factors(quadratic_table, double_hashing_table, TABLE_SIZE);
              break;

        case 3:  // print hash functions

            printf("primary hash function: hash(key) % table_size\n");
            printf("this function sums the ASCII values of the characters in the key. ");
            printf("the sum is then modulo'ed by the table size to ensure it fits within the table bounds.\n");
            printf("it is a simple and fast hash function, suitable for small datasets.\n\n");

            printf("secondary Hash Function for Double Hashing: hash2(key)\n");
            printf("this function uses a more complex method, multiplying the current hash value by 32 ");
            printf("and adding the next character's ASCII value. The result is again modulo'ed by the table size.\n");
            printf("this approach reduces clustering and provides better distribution, especially beneficial ");
            printf("for larger datasets or datasets with high collision potential.\n\n");

            printf("good hash functions aim to distribute keys uniformly across the table to minimize collisions. ");
            printf("this is crucial for maintaining the efficiency of hash table operations.\n");
        break;

        case 4:   // insert new word
            printf("enter word: ");
            scanf("%s" , new_word.word);
            printf("\nenter meaning 1: ");
            scanf("%s" , new_word.meanings[0]);
            printf("\nenter meaning 2: ");
            scanf("%s" , new_word.meanings[1]);
            printf("\nenter meaning 3: ");
            scanf("%s" , new_word.meanings[2]);

            printf("\n1. quadratic table\n");
            printf("2. double hashing table\n");
            printf("3. both\n");
            printf("please enter choice [1 or 2 or 3]\n");
            add_hash(new_word, quadratic_table, double_hashing_table);

            break;
         case 5:   // search for word
                printf("enter word to search: ");
                scanf("%s", word);
                printf("select a table to search:\n");
                printf("1. quadratic table\n");
                printf("2. double hashing Table\n");
                printf("enter your choice [1 or 2]: ");
                int table_choice;
                scanf("%d", &table_choice);

                 switch (table_choice) {  // case statement
                 case 1:
                        printf("searching the word '%s' in quadratic table:\n",&word);
                        search_word(quadratic_table, word , 1);
                        break;
                 case 2:
                        printf("searching the word '%s'in double hashing table:\n",&word);
                        search_word(double_hashing_table, word , 0);
                        break;
                 default:
                         printf("incorrect choice please enter number between [1-2].\n");
                 }
                 break;
                 break;

            case 6:  // delete word form table
                printf("enter word to delete: ");
                scanf("%s", word);
                printf("select a table to delete from:\n");
                printf("1. quadratic table\n");
                printf("2. double hashing table\n");
                printf("3. both\n");
                printf("enter your choice [1 or 2 or 3] : ");
                scanf("%d", &table_choice);

                switch (table_choice) { // case statement
                case 1:
                        printf("the word '%s' deleting from quadratic table:\n", &word);
                        delete_word(quadratic_table, word, 0);
                        break;
                case 2:
                        printf("the word '%s' deleting from double hashing table:\n", &word);
                        delete_word(double_hashing_table, word, 1);
                        break;
                case 3:
                         printf("the word '%s' deleting from both table:\n", &word);
                         delete_word(quadratic_table, word, 0);
                         delete_word(double_hashing_table, word, 1);
                         break;

                default:
                        printf("incorrect choice please enter number between [1-2].\n");
                        break;
                        }
                break;
            case 7:  // compare collision count
                printf("collisions in quadratic: %d\n", quadratic_collisions);
                printf("collisions in Double hashing: %d\n", double_hashing_collisions);
                if (quadratic_collisions > double_hashing_collisions){
                        printf("the quadratic collisions more than double collisions by %d\n",quadratic_collisions-double_hashing_collisions );
                        }
                else if(double_hashing_collisions > quadratic_collisions){
                    printf("the double collisions more than quadratic collisions by %d\n",double_hashing_collisions-quadratic_collisions );
                    }
                else{
                      printf("the quadratic collisions and the quadratic collisions they are equal\n");
                      }
                break;

                case 8:  // save to output file
                   save_to_file(double_hashing_table);
                break;

                case 9:
                    printf("thank you for using my program bye -_-.\n");
                    return 0;
                default:
                    printf("incorrect choice please enter number between [1-9]\n");
            break;
              }
        }
    }



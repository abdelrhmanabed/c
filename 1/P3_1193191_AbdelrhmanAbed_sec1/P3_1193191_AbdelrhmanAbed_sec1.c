#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 50
struct Word {
    char word[50];
    char meanings[3][50];
};

 int hash(char* key, int table_size) {
     int hashValue = 0;
    while (*key != '\0') {
        hashValue += *key++;
    }
    return (hashValue % table_size);
}

 int hash2(char* key, int table_size) {
     long long hashValue = 0;
    while (*key != '\0') {
        hashValue = ((hashValue * 32 )+ *key++) %table_size;
    }
    return hashValue;
 }

void insert_quadratic(struct Word table[], struct Word new_word) {
    int index = hash(new_word.word, TABLE_SIZE);
    int i = 0;
    int collisions = 0;
    while (table[index].word[0] != '\0') {
        i++;
        index = (index + i * i) % TABLE_SIZE;
}
    table[index] = new_word;
    return collisions;

}


void insert_double_hashing(struct Word table[], struct Word new_word) {
     int index = hash(new_word.word, TABLE_SIZE);
    int i = 1;
    int collisions =0;
    while (table[index].word[0] != '\0') {
        index = (index + i * hash2(new_word.word, TABLE_SIZE)) % TABLE_SIZE;
        i++;
    }
    table[index] = new_word;
    return collisions;

}

void search_word(struct Word table[], char* word, int use_quadratic_probing) {
    int index = hash(word, TABLE_SIZE);
    int i = 0;
    int step = 0;

    while (table[index].word[0] != '\0' && strcmp(table[index].word, word) != 0) {
        if (use_quadratic_probing) {
            step = i * i;
        } else {
            step = i * hash2(word, TABLE_SIZE);
        }
        index = (index + step) % TABLE_SIZE;
        i++;

        if (i > TABLE_SIZE) {
            printf("Word not found.\n");
            return;
        }
    }

    if (table[index].word[0] == '\0') {
        printf("Word not found.\n");
    } else {
        printf("Word: %s\n", table[index].word);
        printf("Meanings: %s, %s, %s\n", table[index].meanings[0], table[index].meanings[1], table[index].meanings[2]);
    }
}

void delete_word(struct Word table[], char* word, int use_double_hashing) {
     int index = hash(word, TABLE_SIZE);
    int i = 1;
    while (strcmp(table[index].word, word) != 0) {
        if (use_double_hashing) {
            index = (index + i * hash2(word, TABLE_SIZE)) % TABLE_SIZE;
        } else {
            index = (index + 1) % TABLE_SIZE;
        }
        i++;
        if (strcmp(table[index].word, "") == 0) {
            printf("Word not found.\n");
            return;
        }
    }
    strcpy(table[index].word, "");
}

void print_table(struct Word table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].word[0] != '\0') {
            printf("%d: %s - %s, %s, %s\n", i, table[i].word, table[i].meanings[0], table[i].meanings[1], table[i].meanings[2]);
        } else {
            printf("%d: Empty\n", i);
        }
    }
}

void load_from_file(struct Word table[]) {
    FILE *file = fopen("savedWords.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    struct Word new_word;
    char line[200];

    while (fgets(line, sizeof(line), file)) {
        memset(&new_word, 0, sizeof(new_word));
        int count = sscanf(line, "%49[^:]:%49[^#]#%49[^#]#%49[^#\n]",
                           new_word.word,
                           new_word.meanings[0],
                           new_word.meanings[1],
                           new_word.meanings[2]);

        if (count >= 1) {
            insert_double_hashing(table, new_word);
        }
    }

    fclose(file);
}
void save_to_file(struct Word table[]) {
    FILE *file = fopen("savedWords.txt", "w");
    if (file == NULL) {
        printf("Error opening file");
        exit(1);
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].word[0] != '\0') {
            fprintf(file, "%s:%s#%s#%s\n", table[i].word, table[i].meanings[0], table[i].meanings[1], table[i].meanings[2]);
        }
    }
    fclose(file);
    printf("double hashing table saved to 'savedWords.txt'\n");

}

int main() {
    struct Word quadratic_table[TABLE_SIZE] = {0};
    struct Word double_hashing_table[TABLE_SIZE] = {0};
    int quadratic_collisions = 0;
    int double_hashing_collisions = 0;
    load_from_file(quadratic_table);
    load_from_file(double_hashing_table);

    while (1) {
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
        scanf("%d", &choice);

        char word[50];
        struct Word new_word;

        switch (choice) {
        case 1:
                printf("Open quadratic Table:\n");
                print_table(quadratic_table);
                printf("Double Hashing Table:\n");
                print_table(double_hashing_table);
                break;

        case 2:
                printf("Table Size: %d\n", TABLE_SIZE);
                int count_open = 0, count_double = 0;
                for (int i = 0; i < TABLE_SIZE; i++) {
                    if (quadratic_table[i].word[0] != '\0') count_open++;
                    if (double_hashing_table[i].word[0] != '\0') count_double++;
                }
                printf("Load Factor for Open quadratic: %.2f\n", (float)count_open / TABLE_SIZE);
                printf("Load Factor for Double Hashing: %.2f\n", (float)count_double / TABLE_SIZE);
                break;

        case 3:
                printf("Primary Hash Function: hash(key) %% table_size\n");
                printf("Secondary Hash Function for Double Hashing: hash2(key)\n");
                break;
        case 4:
            printf("Enter word: ");
            scanf("%s", new_word.word);
            printf("Enter meaning 1: ");
            scanf("%s", new_word.meanings[0]);
            printf("Enter meaning 2: ");
            scanf("%s", new_word.meanings[1]);
            printf("Enter meaning 3: ");
            scanf("%s", new_word.meanings[2]);

            printf("1. Quadratic Probing Table\n");
            printf("2. Double Hashing Table\n");
            printf("3. Both\n");
            printf("Enter your choice (1, 2 or 3): ");
            int table_choice;
            scanf("%d", &table_choice);

            int index;
            int i;

            switch (table_choice) {
                case 1:
                    index = hash(new_word.word, TABLE_SIZE);
                    i = 0;
                    while (quadratic_table[index].word[0] != '\0') {
                        i++;
                        index = (index + i * i) % TABLE_SIZE;
                    }
                    quadratic_collisions++;
                    quadratic_table[index] = new_word;
                    printf("Word '%s' inserted in Quadratic Probing Table.\n",&new_word.word);
                    break;

                case 2:
                    index = hash(new_word.word, TABLE_SIZE);
                    i = 0;
                    while (double_hashing_table[index].word[0] != '\0') {
                        i++;
                        index = (index + i * hash2(new_word.word, TABLE_SIZE)) % TABLE_SIZE;
                    }
                     double_hashing_collisions++;
                    double_hashing_table[index] = new_word;
                    printf("Word '%s' inserted in Double Hashing Table.\n",new_word.word);
                    break;

                case 3:
                    index = hash(new_word.word, TABLE_SIZE);
                    i = 0;
                    while (quadratic_table[index].word[0] != '\0') {
                        i++;
                        index = (index + i * i) % TABLE_SIZE;
                    }
                    quadratic_collisions++;
                    quadratic_table[index] = new_word;
                    index = hash(new_word.word, TABLE_SIZE);
                    i = 0;
                    while (double_hashing_table[index].word[0] != '\0') {
                        i++;
                        index = (index + i * hash2(new_word.word, TABLE_SIZE)) % TABLE_SIZE;
                    }
                     double_hashing_collisions++;
                    double_hashing_table[index] = new_word;

                    printf("Word'%s' inserted in both tables.\n",&new_word.word);
                    break;

                default:
                    printf("incorrect choice please enter number between [1-3]\n");
            }
            break;



        case 5:
                printf("Enter word to search: ");
                scanf("%s", word);
                printf("Select a table to search:\n");
                printf("1. Quadratic Probing Table\n");
                printf("2. Double Hashing Table\n");
                printf("Enter your choice (1 or 2): ");
                scanf("%d", &table_choice);

                 switch (table_choice) {
                 case 1:
                        printf("Searching the word '%s' in Quadratic Table:\n",&word);
                        search_word(quadratic_table, word , 1);
                        break;
                 case 2:
                        printf("Searching the word '%s'in Double Hashing Table:\n",&word);
                        search_word(double_hashing_table, word , 0);
                        break;
                 default:
                         printf("incorrect choice please enter number between [1-2].\n");
                 }
                 break;
        break;

        case 6:
                printf("Enter word to delete: ");
                scanf("%s", word);
                printf("Select a table to delete from:\n");
                printf("1. Quadratic Table\n");
                printf("2. Double Hashing Table\n");
                printf("Enter your choice (1 or 2): ");
                scanf("%d", &table_choice);

                switch (table_choice) {
                case 1:
                        printf("The word '%s' deleting from Quadratic Table:\n", &word);
                        delete_word(quadratic_table, word, 0);
                        break;
                case 2:
                        printf("The word '%s' deleting from Double Hashing Table:\n", &word);
                        delete_word(double_hashing_table, word, 1);
                        break;
                default:
                        printf("incorrect choice please enter number between [1-2].\n");
                        break;
                        }
        break;


            case 7:
                   printf("collisions in quadratic: %d\n", quadratic_collisions);
                   printf("collisions in Double hashing: %d\n", double_hashing_collisions);
            break;

            case 8:
                   save_to_file(double_hashing_table);
            break;

            case 9:
                    printf("Thank you for using my program bye -_-.\n");
                    return 0;
            default:
                    printf("incorrect choice please enter number between [1-9]\n");
            break;
    }
  }
}


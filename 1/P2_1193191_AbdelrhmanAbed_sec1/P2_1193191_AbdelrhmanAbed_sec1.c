// Abdelrhman Abed / 1193191 /section 1
// Dr. Ahmad Abusnaina
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct stack {  // structure is similar to an object that will hod 40 strings
      int top;     //  variable tells us where the last string
      char buckts [40][40];  //is an array of buckets
} stack;

typedef struct binary_tree_node { // this structure specifies a binary tree pointing to the left and right children
    char data[40];
      struct binary_tree_node *left;
       struct binary_tree_node *right;
} binary_tree_node;

void push(stack *stk, char *item) { // adds an item to the top of the stack
    if (stk->top == 40 - 1) {
          printf("stack overflow\n");
        exit(1);
    }
      strcpy(stk->buckts [++stk->top], item);
}

char* pop(stack *stk) {            // removes and returns the item from top of the stack
    if (stk->top == -1) {
         printf("stack underflow\n");
        exit(1);
    }
        return stk->buckts [stk->top--];
}

int is_empty(stack *stk) {      // checks if the stack empty
    return stk->top == -1;
}

int opera(char c) {           // checks if a character is an operator
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

int priority(char c) {          // determines the priority of an operator by demonstrating a int value for them the higher the value the higher the priority
        return (c == '+' || c == '-') ? 1 : ((c == '*' || c == '/' || c == '%') ? 2 : 0);
}

void spilt_postfix(char *postfix, char sp_postfix[40][40], int *size) {  // the function takes a postfix expression as input
    char *token = strtok(postfix, " ");                                   //  and splits it into tokens
      int index = 0;                                                       //   postfix:input postfix expression
       while (token) {                                                     //    spit_postfix:array  store the spliy tokens
          strcpy(sp_postfix[index++], token);                          //     size : pointer to an integer that will store the size
         token = strtok(NULL, " ");
    }
    *size = index;
}

void infix_to_postfix(char *infix, char *postfix) {  //converts an infix expression to postfix
       stack stk = { .top = -1 };
    int i, j = 0;

    for (i = 0; infix[i]; i++) {   // loop through each character in the infix
        char c = infix[i];
        if (isspace(c)) continue;  // copy the entire number to the postfix
         else if (isdigit(c)) {    //  pop operator form the stack
             while (isdigit(infix[i])) postfix[j++] = infix[i++];
             i--;
             postfix[j++] = ' ';
                                                      // if the stack empty of the top operator has lower precedence
        }   else if (opera(c)) {
            while (!is_empty(&stk) && priority(stk.buckts [stk.top][0]) >= priority(c)) {
                 postfix[j++] = stk.buckts [stk.top][0];
                postfix[j++] = ' ';
                  pop(&stk);
            }
            char op[2] = {c, '\0'};    // push it onto the stack
            push(&stk, op);
        } else if (c == '(') {
            push(&stk, (char[]){c, '\0'});   // pop operas from the stack to the postfix
        } else if (c == ')') {
            while (!is_empty(&stk) && stk.buckts [stk.top][0] != '(') {
                   postfix[j++] = stk.buckts [stk.top][0];
                 postfix[j++] = ' ';
                  pop(&stk);              // after processing all characters pop any remaining operas form th stack
            }
              pop(&stk);
        }
    }

    while (!is_empty(&stk)) {
           postfix[j++] = stk.buckts [stk.top][0];
        postfix[j++] = ' ';
          pop(&stk);
    }
    postfix[j > 0 && postfix[j - 1] == ' ' ? j - 1 : j] = '\0';
}

binary_tree_node* new_node(char *data) {       // creates a new binary tree node and initializes it with the provided data
       binary_tree_node *temp = (binary_tree_node *)malloc(sizeof(binary_tree_node));
      strcpy(temp->data, data);
     temp->left = temp->right = NULL;
    return temp;                             // a pointer to the newly created binary tree node
}                                           // these it work together in the context of parsing expression
                                           //  and converting them to postfix and creating nodes for a binary expression tree
binary_tree_node* construct_tree(char postfix[][40], int size) {
      binary_tree_node *stk[40];                                     // builds a binary expression tree form postfix expression
     int stk_top = -1;                                              //  token in the postfix expression
                                                                   //   creates a new node for it and pushes it onto the stack
    for (int i = 0; i < size; i++) {                              //    it pops two nodes from stack
           binary_tree_node *t = new_node(postfix[i]);              //     the stack is the root of the binary tree , returns the root of the binary tree
        if (!opera(postfix[i][0]) || strlen(postfix[i]) > 1) stk[++stk_top] = t;
         else { t->right = stk[stk_top--]; t->left = stk[stk_top--]; stk[++stk_top] = t; }
    }
    return stk[stk_top];
}

int evaluate_tree(binary_tree_node *root) {                             // evaluates the result of a binary expression tree
     if (!root) return 0;                                               //  root of the binary tree
     if (!root->left && !root->right) return atoi(root->data);         //  recursively evaluates binary tree
                                                                     //   it coverts the data to an integer and returns it
     int left_valu = evaluate_tree(root->left);                      //    it evaluates the left and right subtrees and preforms the corresponding operation
     int right_valu = evaluate_tree(root->right);                   //     returns final operation

    switch (root->data[0]) {
        case '-': return left_valu - right_valu;
          case '+': return left_valu + right_valu;
        case '/': return right_valu != 0 ? left_valu / right_valu : 0;
          case '*': return left_valu * right_valu;
        case '%': return right_valu != 0 ? left_valu % right_valu : 0;
    }
    return 0;
}

void read_from_file(char *filename, char expressions[][40], int *num_exp) {         // reads expressions form a file into an array
              FILE *file = fopen(filename, "r");                                     //opens the specified file for reading '
                                                                                // reading expressions line by kine form the file
     if (!file) {                                                                   // num_exp: variable for each expression red
              printf("error opening file: %s\n", filename);
        exit(1);                                                              // closes the file
    }

    *num_exp = 0;
              while (fscanf(file, " %[^\n]s", expressions[*num_exp]) != EOF) (*num_exp)++;
        fclose(file);
}

void free_tree(binary_tree_node *root) {                //free memory allocated for the binary tree nodes
        if (root) {                                       // the binary tree in post order (left , right , root)
          free_tree(root->left);
      free_tree(root->right);                       // ensures all allocated memory is released
          free(root);
    }
}

void save_to_file(char expressions[][40], int num_exp, char *filename) {    // saves postfix expressions and their results
        FILE *file = fopen(filename, "w");
    if (!file) {                                                        // open the specified file for writing
          printf("error opening file : %s\n", filename);         //  save results and postfix expressions
        return;
    }                                                                 // close file

    for (int i = 0; i < num_exp; i++) {                              // print a message indicating that the results have been saved

          char postfix_expr[40] = "";
        infix_to_postfix(expressions[i], postfix_expr);

              char sp_postfix[40][40];
        int postfix_size;
          fprintf(file, "\n%d- postfix: %s\n", i+1 ,postfix_expr);

          spilt_postfix(postfix_expr, sp_postfix, &postfix_size);

        binary_tree_node *root = construct_tree(sp_postfix, postfix_size);
                int result = evaluate_tree(root);

        fprintf(file, " \n%d- result: %d\n\n", i+1 ,result);

                free_tree(root);
    }

    fclose(file);
        printf("save done to %s\n", filename);
}


int main() {
    char expressions[100][40];   // arrays to store up to 100 expressions and 40 charactes
    int num_exp = 0;
    int choice = 0;

    while (choice != 6) {                      // the program enters a loop form that continues unit the user selects 6 to exit
        printf("\nMenu\n");
        printf("1. Read	equations.\n");
        printf("2. Print equations.\n");          //this information from the project requirements
        printf("3. Evaluate using Expression tree.\n");
        printf("4. Print postfix expressions.\n");
        printf("5. Save	to output file (postfix and results).\n");
        printf("6. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                   read_from_file("input.txt", expressions, &num_exp); // read expressions from the input.txt file
               printf(" read from file done.\n");         // print message
                  break;
            case 2:
                   for (int i = 0; i < num_exp; i++)
                    printf("%d- %s\n", i + 1, expressions[i]);
                  break;   // print the stored expressions in the 'expressions' array
            case 3:
                for (int i = 0; i < num_exp; i++) {
                       char postfix_expr[40] = "";               // converts infix to postfix
                      infix_to_postfix(expressions[i], postfix_expr);

                      char sp_postfix[40][40];                // binary expression tree from the postfix expressions
                     int postfix_size;
                      spilt_postfix(postfix_expr, sp_postfix, &postfix_size);  // evaluates the result

                      binary_tree_node *root = construct_tree(sp_postfix, postfix_size);
                    printf("result %d: %d\n", i+1,  evaluate_tree(root));             // print result

                    free_tree(root);
                }
                break;
            case 4:
                for (int i = 0; i < num_exp; i++) {             // converts infix to postfix  and print all result
                       char postfix_expr[40] = "";
                    infix_to_postfix(expressions[i], postfix_expr);
                      printf("postfix %d: %s\n", i + 1, postfix_expr);
                }
                break;
            case 5:
                  save_to_file(expressions, num_exp, "output.txt");  // save postfix expressions and the result to the output.txt
                break;
            case 6:
                     printf("exiting program\n");
                break;
            default:
                       printf("not correct choice , try again <  __  >.\n");  // when enter number another 1 - 6 print this message
                break;
        }
    }

    return 0;
}

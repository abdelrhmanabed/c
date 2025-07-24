#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct TreeNode {
    char data;  // Updated to store either numeric values or operators
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new tree node
struct TreeNode* createNode(char data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to convert infix expression to postfix expression
void infixToPostfix(struct TreeNode* root, FILE* output) {
    if (root != NULL) {
        infixToPostfix(root->left, output);
        infixToPostfix(root->right, output);

        // Print operands and operators to output
        fprintf(output, "%c ", root->data);
    }
}

// Function to evaluate a binary expression tree
int evaluateExpressionTree(struct TreeNode* root) {
    // Base case: If the root is NULL, return 0
    if (root == NULL) {
        return 0;
    }

    // If the root is a leaf node, return its numeric value
    if (root->left == NULL && root->right == NULL) {
        return root->data - '0';  // Return the numeric value directly
    }

    // Recursively evaluate the left and right subtrees
    int leftValue = evaluateExpressionTree(root->left);
    int rightValue = evaluateExpressionTree(root->right);

    // Perform the operation based on the operator at the root
    switch (root->data) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            // Assuming that division by zero is not handled for simplicity
            return leftValue / rightValue;
        default:
            printf("Error: Unknown operator %c\n", root->data);
            return 0;
    }
}

// Function to construct an expression tree from a string
struct TreeNode* constructExpressionTree(char* expression, int* index) {
    if (expression[*index] == '\0' || expression[*index] == '\n') {
        return NULL;
    }

    if (expression[*index] >= '0' && expression[*index] <= '9') {
        // If the current character is a digit, parse the entire operand
        int value = 0;
        while (expression[*index] >= '0' && expression[*index] <= '9') {
            value = value * 10 + (expression[*index] - '0');
            (*index)++;
        }
        struct TreeNode* newNode = createNode(value + '0'); // Convert the operand to character
        return newNode;
    } else if (expression[*index] == '+' || expression[*index] == '-' ||
               expression[*index] == '*' || expression[*index] == '/') {
        // If the current character is an operator
        struct TreeNode* newNode = createNode(expression[*index]);
        (*index)++;
        newNode->left = constructExpressionTree(expression, index);
        (*index)++;
        newNode->right = constructExpressionTree(expression, index);
        return newNode;
    } else {
        // Ignore other characters (whitespace, etc.)
        (*index)++;
        return constructExpressionTree(expression, index);
    }
}

// Example usage
int main() {
    // Read the expression from the user
    char expression[100];
    printf("Enter an arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);

    // Construct an expression tree from the expression
    int index = 0;
    struct TreeNode* root = constructExpressionTree(expression, &index);

    // Open the output file
    FILE* output = fopen("output.txt", "w");
    if (output == NULL) {
        perror("Error opening output.txt");
        return 1;
    }

    // Save postfix expression to output.txt
    fprintf(output, "Postfix Expression: ");
    infixToPostfix(root, output);
    fprintf(output, "\n");

    // Evaluate the expression tree
    int result = evaluateExpressionTree(root);

    // Save the result to output.txt
    fprintf(output, "Result: %d\n", result);

    // Close the output file
    fclose(output);

    return 0;
}

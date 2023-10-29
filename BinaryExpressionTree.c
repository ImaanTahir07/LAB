#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct StackNode {
    struct TreeNode* treeNode;
    struct StackNode* next;
};

struct StackNode* top = NULL;

void PushInStack(struct TreeNode* treeNode) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Unable to allocate memory for the stack node!\n");
        exit(1);
    }
    newNode->treeNode = treeNode;
    newNode->next = top; // for maintaining links
    top = newNode;
}

struct TreeNode* PopFromStack() {
    if (top == NULL) {
        printf("Stack is Empty!\n");
        exit(1);
    }
    struct StackNode* curr = top;
    struct TreeNode* treeNode = top->treeNode;
    top = top->next;
    free(curr);
    return treeNode;
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int getOperatorPrecedence(char operator) {
    if (operator == '+' || operator == '-') {
        return 1;
    } else if (operator == '/' || operator == '*') {
        return 2;
    } else {
        return -1;
    }
}

struct TreeNode* CreateTreeNode(char data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Unable to allocate memory for tree node!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int isOperand(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || isdigit(ch);
}

void InfixToPostFix(char* infixExp) {
    int length = strlen(infixExp);
    char postfixExp[100];
    int postfixIndex = 0;

    for (int i = 0; i < length; i++) {
        char currChar = infixExp[i];

        if (isOperand(currChar)) {
            postfixExp[postfixIndex++] = currChar;
        } else if (currChar == '(') {
            struct TreeNode* treeNode = CreateTreeNode(currChar);
            PushInStack(treeNode);
        } else if (currChar == ')') {
            while (top != NULL && top->treeNode->data != '(') {
                postfixExp[postfixIndex++] = PopFromStack()->data; 
            }
            if (top != NULL && top->treeNode->data == '(') {
                PopFromStack();
            }
        } else if (isOperator(currChar)) {
            while (top != NULL && getOperatorPrecedence(top->treeNode->data) >= getOperatorPrecedence(currChar)) {
                postfixExp[postfixIndex++] = PopFromStack()->data;
            }
            struct TreeNode* treeNode = CreateTreeNode(currChar);
            PushInStack(treeNode);
        }
    }

    while (top != NULL) {
        postfixExp[postfixIndex++] = PopFromStack()->data;
    }

    postfixExp[postfixIndex] = '\0';
    printf("PostFix Expression: %s\n", postfixExp);
}

void PrintInOrder(struct TreeNode* root) {
    if (root != NULL) {
        PrintInOrder(root->left);
        printf("%c ", root->data);
        PrintInOrder(root->right);
    }
}

struct TreeNode* BuildExpressionTree(char* postfixExp) {
    int length = strlen(postfixExp);
    for (int i = 0; i < length; i++) {
        char currChar = postfixExp[i];
        if (isOperand(currChar)) {
            struct TreeNode* treeNode = CreateTreeNode(currChar);
            PushInStack(treeNode);
        } else if (isOperator(currChar)) {
            struct TreeNode* treeNode = CreateTreeNode(currChar);
            treeNode->right = PopFromStack();
            treeNode->left = PopFromStack();
            PushInStack(treeNode);
        }
    }
    return PopFromStack();
}

int main() {
    char infix[100];
    char postfix[100];
    printf("Enter the Infix Expression: ");
    scanf("%s", infix);

    InfixToPostFix(infix);

    printf("Enter the Postfix Expression: ");
    scanf("%s", postfix);
    struct TreeNode* root = BuildExpressionTree(postfix);

    printf("In-Order Traversal of the Expression Tree: ");
    PrintInOrder(root);

    return 0;
}

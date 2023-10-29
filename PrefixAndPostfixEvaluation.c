#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

struct StackNode
{
    int data;
    struct StackNode* next;
};

struct StackNode* top = NULL;

void PushInStack(int data){
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if(newNode == NULL){
        printf("Unable to allocate memory!");
        return;
    }
    newNode->data = data;
    newNode->next = top; // for maintaining the link between nodes now new node becomes the new top of the stack
    top= newNode; //update the top
}

int PopInStack(){
    if(top==NULL){
        printf("Stack is Empty unable to pop!");
        return -1;
    }
    struct StackNode* curr = top;
    int poppedValue = top->data;
    top = top->next;
    free(curr);
    return poppedValue;
}

void PrintStack(){
    struct StackNode* temp = top;
    if(temp == NULL){
        printf("\n\tEmpty stack!\n");
        return;
    }
    printf("\nElements in the stack are:\n");
    while(temp!=NULL){
        printf("%d",&temp->data);
        temp=temp->next;
    }
    printf("\n");
}

bool isOperator(char ch){
    return (ch == '+'||ch =='-'||ch=='*'||ch== '/');
}

int prefixExpressionEvaluation(char* expression){ // evaluation from left
    int length = strlen(expression);
    for(int i=length-1;i>=0;i--){
        char currChar = expression[i];
        if (isdigit(currChar))
        {
            PushInStack(currChar - '0'); // convert char into int because we are subtracting 48 == '0' from the char so '0'-'0' = 0 and so on
        }else if(isOperator(currChar)){
            int operand1 = PopInStack();
            int operand2 = PopInStack();
            switch (currChar)
            {
            case '+':
                PushInStack(operand1 + operand2);
                break;
            case '-':
                PushInStack(operand1 - operand2);
                break;
            case '*':
                PushInStack(operand1 * operand2);
                break;
            case '/':
                PushInStack(operand1 / operand2);
                break;
            }
        }
        
    }
    return PopInStack(); // PopInStack isiliye call kra h kion k at the end of the evaluation stack mai bas ik he element bachta h jo apka final result hota h thats why or PopInStack ki return type is int so it will definitely return a number
}
int postfixEvaluation(char* expression){ // evaluation from right
    int length = strlen(expression);
    for(int i = 0; i<length;i++){
        char currChar = expression[i];
        if(isdigit(currChar)){
            PushInStack(currChar - '0');
        }else if(isspace(currChar)){
            continue;
        }
        else if(isOperator(currChar)){
            int operand1 = PopInStack();
            int operand2 = PopInStack();
            switch (currChar)
            {
            case '+':
                PushInStack(operand1+operand2);
                break;
            case '-':
                PushInStack(operand1-operand2);
                break;
            case '*':
                PushInStack(operand1*operand2);
                break;
            case '/':
                PushInStack(operand1/operand2);
                break;
            }
        }
    }

    return PopInStack(); // PopInStack isiliye call kra h kion k at the end of the evaluation stack mai bas ik he element bachta h jo apka final result hota h thats why or PopInStack ki return type is int so it will definitely return a number
    

}
int main() {
    char expression[100];
    int choice;
    int result;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Evaluate Prefix Expression\n");
        printf("2. Evaluate Postfix Expression\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a prefix expression: ");
                scanf("%s", expression);
                result = prefixExpressionEvaluation(expression);
                printf("Prefix Evaluation result is: %d\n", result);
                break;
            case 2:
                printf("Enter a postfix expression: ");
                scanf("%s", expression);
                result = postfixEvaluation(expression);
                printf("Postfix Evaluation result is: %d\n", result);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}


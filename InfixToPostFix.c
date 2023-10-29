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
    return (ch=='+'||ch=='-'||ch=='*'||ch=='/');
}

int getOperatorPrecedence(char operator){
    if(operator == '+'||operator=='-'){
        return 1;
    }
    else if(operator == '/'||operator=='*'){
        return 2;
    }
    else{
        return -1;
    }
}
 void InfixToPostFix(char* infixExp){
    int length = strlen(infixExp);
    char postfixExp[100];
    int postfixIndex = 0;
    for (int i = 0; i < length; i++)
    {
        char currChar = infixExp[i];
        if (isdigit(currChar)||isalpha(currChar))
        {
            postfixExp[postfixIndex++] = currChar;
        }
        else if(currChar=='('){
            PushInStack(currChar);
        }
        else if(currChar == ')'){
            while (top!=NULL&&top->data=='(')
            {
                postfixExp[postfixIndex++]=PopInStack();
            }
            if (top != NULL && top->data == '(') {
                PopInStack(); 
            } 
        }else if(isOperator(currChar)){
            while (top!=NULL&&getOperatorPrecedence(top->data)>=getOperatorPrecedence(currChar))
            {
                postfixExp[postfixIndex++]=PopInStack();
            }
            PushInStack(currChar);
            
        }
        
    }
    while (top!=NULL)
    {
        if (top->data == '(')
        {
            PopInStack();
        }else
        {
            postfixExp[postfixIndex++]=PopInStack();
        }
        
        
    }

    // postfixExp[postfixIndex] = '\0';
    printf("PostFix Expression: %s",postfixExp);
    
 }

 int main()
 {
    char infix[100];
    printf("Enter Infix Expression: ");
    scanf("%s",&infix);
    InfixToPostFix(infix);
    return 0;
 }
 


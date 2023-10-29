#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

struct Node{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int maximum(int a,int b){
    return a>b?a:b;
}

int getHeight(struct Node* node){
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
    
}

struct Node* createNode(int value){
    struct Node* newNode =(struct Node*)malloc(sizeof(struct Node));
    newNode ->key =value;
    newNode ->left = NULL;
    newNode ->right = NULL;
    newNode->height=1;
    return newNode;
}

int getBalanceFactor(struct Node* node){
    if(node==NULL){
        return 0;
    }
    return getHeight(node->left)-getHeight(node->right);
}

struct Node* rightRotate(struct Node* y){
    struct Node* x = y->left;
    struct Node* T2 = x->right;
    x->right = y;
    y->left =T2 ;
    y->height = maximum(getHeight(y->right),getHeight(y->left))+1;
    x->height = maximum(getHeight(x->right),getHeight(x->left))+1;
    return x; //because this is the root node now
}
struct Node* leftRotate(struct Node* x){
    struct Node* y = x->right;
    struct Node* T2 = y->left;
    y->left = x;
    x->right =T2 ;
    y->height = maximum(getHeight(y->right),getHeight(y->left))+1;
    x->height = maximum(getHeight(x->right),getHeight(x->left))+1;
    return y; //because this is the root node now
}

struct Node* insert(struct Node* node, int data){
    if (node == NULL) //it means we've reached a leaf node or an empty tree
    {
        return createNode(data);
    }
    if (data<node->key)
    {
        node->left = insert(node->left,data);
    }else if(data>node->key){
        node->right = insert(node->right,data);
    }

    return node;
    node->height = 1 + maximum(getHeight(node->left),getHeight(node->right));
    int balanceFactor = getBalanceFactor(node);

    //left left case
    if (balanceFactor>1&&data<node->left->key)
    {
        return rightRotate(node);
    }
    //right right case
    if (balanceFactor<-1&&data>node->right->key)
    {
        return leftRotate(node);
    }
    //left right case
    if (balanceFactor>1 && data > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    //right left case
    if (balanceFactor<-1 && data < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
    
    
}
void inOrderTraversal(struct Node *node){
    if(node != NULL){
        inOrderTraversal(node -> left);
        printf("%d\n",node->key);
        inOrderTraversal(node -> right);
    }
 
}
void preOrderTraversal(struct Node *node){
    
    if(node != NULL){
        printf("%d\n",node->key);
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
    

}

int main()
{
    struct Node* ROOT = NULL;
    ROOT = insert(ROOT,73);
    ROOT = insert(ROOT,23);
    ROOT = insert(ROOT,60);
    ROOT = insert(ROOT,54);
    ROOT = insert(ROOT,99);
    ROOT = insert(ROOT,115);
    ROOT = insert(ROOT,200);
    ROOT = insert(ROOT,258);
    ROOT = insert(ROOT,119);
    ROOT = insert(ROOT,72);
    ROOT = insert(ROOT,56);
    ROOT = insert(ROOT,86);
    printf("\nIn Order Traversal");
    inOrderTraversal(ROOT);
    printf("\nPre Order Traversal");
    preOrderTraversal(ROOT);
    return 0;
}

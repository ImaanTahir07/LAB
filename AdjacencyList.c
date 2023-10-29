#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Vertex
{
    char data;
    struct Edge* edgeList;
    struct Vertex* next;
    bool visited;
};
struct Edge
{
    struct Vertex* toVertex;
     int weight; 
    struct Edge* enext;
};

struct Vertex* graph = NULL;
struct Edge* edgelist =NULL;

void InsertVertex(){
    struct Vertex* newVertex = (struct Vertex*)malloc(sizeof(struct Vertex));
    printf("Enter Vertex: \t");
    scanf(" %c",&newVertex->data);
    newVertex->edgeList=NULL;
    newVertex->next=NULL;
    
    if (graph==NULL)
    {
        graph=newVertex;
    }
    else
        {
            struct Vertex* curr = graph;
            while (curr->next!=NULL)
                {
                    curr=curr->next;
                }
            curr->next=newVertex;
         }
    
   
}


struct Vertex* searchVertex(char data){
    struct Vertex* curr = graph;
    while (curr!=NULL)
    {
        if (curr->data==data)
        {
            return curr;
        }
        curr = curr->next;
        
    }
    
}

void InsertEdge(){
    char source,destination;
    int weight; 
    printf("Enter Source Vertex: ");
    scanf(" %c",&source);
    struct Vertex  *vcurr = searchVertex(source);
    if (vcurr == NULL)
    {
        printf("Source vertex not found\n");
        return;
    }

    struct Edge* ecurr = vcurr->edgeList;
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    printf("Enter Destination Vertex: ");
    scanf(" %c",&destination);
    struct Vertex *dest = searchVertex(destination);
      if (dest == NULL)
    {
        printf("Destination vertex not found\n");
        return;
    }
    printf("Enter Edge Weight: ");
    scanf("%d", &weight);
    newEdge->toVertex = dest;
    newEdge->weight = weight;
    newEdge->enext = NULL;
    if (ecurr==NULL)
    {
       vcurr->edgeList = newEdge;
    }else
    {
        while(ecurr->enext!=NULL){
            ecurr=ecurr->enext;
        }
        ecurr->enext = newEdge;
    }
    
}

void printVertices(){
    struct Vertex* vcurr = graph;
    if (graph==NULL)
    {
        printf("\nGraph is Empty");
    }
    else
    {
        while (vcurr!=NULL)
        {
            printf("\n%c",vcurr->data);
            vcurr=vcurr->next;
        }
        
    } 
}

void printEdgesAndVertices(){
    struct Vertex* vcurr = graph;
    if (vcurr==NULL)
    {
        printf("\nNo Vertex Found");
    }else
    {
        while(vcurr!=NULL){
            printf("Vertex: %c ", vcurr->data);
            struct Edge* ecurr = vcurr->edgeList;
            if (ecurr==NULL)
            {
                printf("\nNo Edges!");
            }else
            {
                while (ecurr !=NULL)
                {
                    printf("-> %c(%d)", ecurr->toVertex->data, ecurr->weight);
                    ecurr = ecurr->enext;
                }
               printf("\n");
            
            
            }
                
             vcurr = vcurr->next;
        }
    }
    
    
}

int outDegree(){
    int count = 0;
    char source;
    printf("\nEnter Source:\t");
    scanf(" %c",&source);
    struct Vertex* vcurr = graph;
    while(vcurr!=NULL){
        if (source==vcurr->data)
        {
            break;
        }
        vcurr=vcurr->next;
        
    }
    if (vcurr==NULL)
    {
        printf("\nNo Vertex Found");
        return -1;
    }
    struct Edge* ecurr=vcurr->edgeList;
    if (ecurr==NULL)
    {
        printf("\nNo Edges");
        return -1;
    }else
    {
        while(ecurr!=NULL){
            count++;
            ecurr=ecurr->enext;
        }
    }

    return count;
    
}
int inDegree(){
    int count = 0;
    char source;
    printf("\nEnter Source:\t");
    scanf(" %c",&source);
    struct Vertex* vcurr = graph;
    if (graph==NULL)
    {
      printf("\nNo Vertex Found!");
      return -1;
    }else
    {
        while (vcurr!=NULL)
        {
            struct Edge* ecurr = vcurr->edgeList;
            while (ecurr!=NULL)
            {
                if (source==ecurr->toVertex->data)
            {
                count++;
            }
            ecurr = ecurr->enext;
            }
            vcurr=vcurr->next;

        }
        
    }
    return count;
    
    
}
void BFS(struct Vertex* startVertex){
    if (startVertex == NULL)
    {
       printf("\nNo Start Vertex Found");
       return ;
    }
    struct Vertex* queue[100];
    int rare =0; int front=0;
    struct Vertex* vcurr = graph;
    while (vcurr!=NULL)
    {
        vcurr->visited = false;
        vcurr = vcurr->next;
    }
    queue[rare++]=startVertex;
    startVertex->visited = true;
    printf("\nBFS of the graph is:\t");
    while(front<rare){
        struct Vertex* v = queue[front++];
        printf("%c",v->data);
        struct Edge* ecurr = v->edgeList;
        while (ecurr!=NULL)
        {
            struct Vertex* adj = ecurr->toVertex;
            if(!adj->visited){
                queue[rare++]=adj;
                adj->visited = true;
            }
            ecurr= ecurr->enext;
        }
        printf("\t");
        
    }

    
    
}

void DFSUtil(struct Vertex *v) {
    v->visited = true;
    printf("%c ", v->data);

    struct Edge *edge = v->edgeList;
    while (edge != NULL) {
        struct Vertex *adj = edge->toVertex;
        if (!adj->visited) {
            DFSUtil(adj);
        }
        edge = edge->enext;
    }
}

void DFS(struct Vertex *startVertex) {
    if (startVertex == NULL) {
        printf("Start vertex not found\n");
        return;
    }
    struct Vertex *current = graph;
    while (current != NULL) {
        current->visited = false;
        current = current->next;
    }

    printf("Depth-First Search: ");
    DFSUtil(startVertex);
    printf("\n");
}


int main()
{
    int Venteries;
    printf("How many vertices you want to insert? ");
    scanf("%d",&Venteries);
    for (int i = 0; i < Venteries; i++)
    {
       InsertVertex();
    }
    int Eenteries;
    printf("\nHow many edges you want to insert? ");
      scanf("%d",&Eenteries);
      for (int i = 0; i < Eenteries; i++)
      {
        InsertEdge();
      }
      
    
    printf("Edges And Vertices are: \n");
    printEdgesAndVertices();
    printVertices();
    int outDeg = outDegree();
    printf("\nOutDegree is: %d",outDeg);
    int inDeg = inDegree();
    printf("\nInDegree is: %d",inDeg);
     char startVertexData;
    printf("Enter the start vertex for BFS and DFS:");
    scanf(" %c", &startVertexData);

    struct Vertex *startVertex = searchVertex(startVertexData);

    printf("Starting BFS from vertex %c\n", startVertexData);
    BFS(startVertex);

    printf("\nStarting DFS from vertex %c\n", startVertexData);
    DFS(startVertex);
    
    return 0;
}

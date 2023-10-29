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

void DeleteVertex() {
    char vertexData;
    printf("Enter the data of the vertex to be deleted: ");
    scanf(" %c", &vertexData);

    struct Vertex* prev = NULL;
    struct Vertex* curr = graph;

    while (curr != NULL) {
        if (curr->data == vertexData) {
            struct Edge* edge = curr->edgeList;
            while (edge != NULL) {
                struct Edge* temp = edge;
                edge = edge->enext;
                free(temp);
            }
            if (prev == NULL) {
                graph = curr->next;
            } else {
                prev->next = curr->next;
            }

            free(curr);
            printf("Vertex %c has been deleted.\n", vertexData);
            return;
        }

        prev = curr;
        curr = curr->next;
    }

    printf("Vertex %c not found in the graph.\n", vertexData);
}
void DeleteEdge() {
    char source, destination;
    printf("Enter Source Vertex: ");
    scanf(" %c", &source);
    struct Vertex* sourceVertex = searchVertex(source);

    if (sourceVertex == NULL) {
        printf("Source vertex not found.\n");
        return;
    }

    printf("Enter Destination Vertex: ");
    scanf(" %c", &destination);

    struct Edge* prevEdge = NULL;
    struct Edge* edge = sourceVertex->edgeList;

    while (edge != NULL) {
        if (edge->toVertex->data == destination) {
            if (prevEdge == NULL) {
                sourceVertex->edgeList = edge->enext;
            } else {
                prevEdge->enext = edge->enext;
            }

            free(edge); 
            printf("Edge from %c to %c has been deleted.\n", source, destination);
            return;
        }

        prevEdge = edge;
        edge = edge->enext;
    }

    printf("Edge from %c to %c not found.\n", source, destination);
}

int main() {
        char startVertexData; // Declare the startVertexData variable here.
    int choice;
    while (1) {
        printf("\nMenu\n");
        printf("1. Insert Vertex\n");
        printf("2. Insert Edge\n");
        printf("3. Print Vertices\n");
        printf("4. Print Edges and Vertices\n");
        printf("5. Out Degree\n");
        printf("6. In Degree\n");
        printf("7. BFS\n");
        printf("8. DFS\n");
        printf("9. Delete Vertex\n");
        printf("10. Delete Edge\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                InsertVertex();
                break;
            case 2:
                InsertEdge();
                break;
            case 3:
                printVertices();
                break;
            case 4:
                printEdgesAndVertices();
                break;
            case 5:
                int outDeg = outDegree();
                if (outDeg != -1) {
                    printf("Out Degree is: %d\n", outDeg);
                }
                break;
            case 6:
                int inDeg = inDegree();
                if (inDeg != -1) {
                    printf("In Degree is: %d\n", inDeg);
                }
                break;
            case 7:
                printf("Enter the start vertex for BFS: ");
                scanf(" %c", &startVertexData);
                struct Vertex* startVertex = searchVertex(startVertexData);
                printf("Starting BFS from vertex %c\n", startVertexData);
                BFS(startVertex);
                break;
            case 8:
                printf("Enter the start vertex for DFS: ");
                scanf(" %c", &startVertexData);
                startVertex = searchVertex(startVertexData);
                printf("Starting DFS from vertex %c\n", startVertexData);
                DFS(startVertex);
                break;
            case 9:
                DeleteVertex();
                break;
            case 10:
                DeleteEdge();
                break;
            case 0:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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

void InsertVertex() {
    struct Vertex* newVertex = (struct Vertex*)malloc(sizeof(struct Vertex));
    printf("Enter Vertex: \t");
    scanf(" %c", &newVertex->data);
    newVertex->edgeList = NULL;
    newVertex->next = NULL;
    newVertex->visited = false;

    if (graph == NULL) {
        graph = newVertex;
    } else {
        struct Vertex* curr = graph;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newVertex;
    }
}

struct Vertex* searchVertex(char data) {
    struct Vertex* curr = graph;
    while (curr != NULL) {
        if (curr->data == data) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void InsertEdge() {
    char source, destination;
    int weight;
    printf("Enter Source Vertex: ");
    scanf(" %c", &source);
    struct Vertex* vcurr = searchVertex(source);
    if (vcurr == NULL) {
        printf("Source vertex not found\n");
        return;
    }

    struct Edge* ecurr = vcurr->edgeList;
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    printf("Enter Destination Vertex: ");
    scanf(" %c", &destination);
    struct Vertex* dest = searchVertex(destination);
    if (dest == NULL) {
        printf("Destination vertex not found\n");
        return;
    }
    printf("Enter Edge Weight: ");
    scanf("%d", &weight);
    newEdge->toVertex = dest;
    newEdge->weight = weight;
    newEdge->enext = NULL;
    if (ecurr == NULL) {
        vcurr->edgeList = newEdge;
    } else {
        while (ecurr->enext != NULL) {
            ecurr = ecurr->enext;
        }
        ecurr->enext = newEdge;
    }
}
struct Edge* edges = NULL; 

void BuildEdgeList() {
    // Traverse the graph and create a list of all edges.
    struct Vertex* vcurr = graph;
    while (vcurr != NULL) {
        struct Edge* ecurr = vcurr->edgeList;
        while (ecurr != NULL) {
            // Create a new Edge structure and add it to the edges list.
            struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
            newEdge->toVertex = ecurr->toVertex;
            newEdge->weight = ecurr->weight;
            newEdge->enext = edges;
            edges = newEdge;

            ecurr = ecurr->enext;
        }
        vcurr = vcurr->next;
    }
}

// Sort function to order edges by weight.
int cmp(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

void KruskalMST() {
    // Build the list of all edges.
    BuildEdgeList();

    // Sort the edges in ascending order by weight.
    qsort(edges, 0, sizeof(struct Edge), cmp);

    // Initialize an array to track the connected components (disjoint sets).
    struct Vertex* components = graph;

    while (components != NULL) {
        components->visited = false;
        components = components->next;
    }

    int minWeight = 0;
    struct Edge* currentEdge = edges;

    // Traverse the sorted edges list and add edges to the MST if they don't form a cycle.
    while (currentEdge != NULL) {
        struct Vertex* source = currentEdge->toVertex;
        struct Vertex* destination = currentEdge->toVertex;

        // Find the representatives of the connected components for the source and destination vertices.
        while (source->visited) source = source->next;
        while (destination->visited) destination = destination->next;

        if (source != destination) {
            printf("Edge: %c - %c, Weight: %d\n", source->data, destination->data, currentEdge->weight);
            source->visited = true;

            // Union operation to merge the connected components.
            source->next = destination;
            minWeight += currentEdge->weight;
        }

        currentEdge = currentEdge->enext;
    }

    printf("Minimum Spanning Tree Weight: %d\n", minWeight);
}
void printEdgesAndVertices() {
    struct Vertex* vcurr = graph;
    if (vcurr == NULL) {
        printf("\nNo Vertex Found");
    } else {
        while (vcurr != NULL) {
            printf("Vertex: %c ", vcurr->data);
            struct Edge* ecurr = vcurr->edgeList;
            if (ecurr == NULL) {
                printf("\nNo Edges!");
            } else {
                while (ecurr != NULL) {
                    printf("-> %c(%d)", ecurr->toVertex->data, ecurr->weight);
                    ecurr = ecurr->enext;
                }
                printf("\n");
            }
            vcurr = vcurr->next;  // This line should be outside the inner while loop
        }
    }
}

void printVertices() {
    struct Vertex* vcurr = graph;
    if (graph == NULL) {
        printf("\nGraph is Empty");
    } else {
        while (vcurr != NULL) {
            printf("\n%c", vcurr->data);
            vcurr = vcurr->next;
        }
    }
}

int main() {
    int Venteries;
        int Eenteries;
    char choice;
    do {
        printf("\n1. Insert Vertex\n2. Insert Edge\n3. Print Vertices\n4. Print Edges and Vertices\n5. Find Minimum Spanning Tree\n6. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
            printf("How many vertices you want to insert? ");
            scanf("%d",&Venteries);
            for (int i = 0; i < Venteries; i++)
                {
                        InsertVertex();
                }
                break;
            case '2':
                 printf("\nHow many edges you want to insert? ");
                 scanf("%d",&Eenteries);
                for (int i = 0; i < Eenteries; i++)
                    {
                        InsertEdge();
                    }
                break;
            case '3':
                printVertices();
                break;
            case '4':
                printEdgesAndVertices();
                break;
            case '5':
                KruskalMST();
                break;
            case '6':
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    } while (choice != '6');

    return 0;
}
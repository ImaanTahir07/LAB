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
struct Edge* findMinimumEdge(struct Vertex* vertices) {
    int minWeight = INT_MAX;
    struct Edge* minEdge = NULL;
    struct Vertex* v = vertices;
    while (v != NULL) {
        struct Edge* e = v->edgeList;
        while (e != NULL) {
            if (!e->toVertex->visited && e->weight < minWeight) {
                minWeight = e->weight;
                minEdge = e;
            }
            e = e->enext;
        }
        v = v->next;
    }

    return minEdge;
}
void primMST() {
    if (graph == NULL) {
        printf("Graph is empty. Please insert vertices and edges first.\n");
        return;
    }

    struct Vertex* selectedVertices = NULL;

    selectedVertices = graph;
    selectedVertices->visited = true;

    while (selectedVertices != NULL) {
        struct Edge* minEdge = findMinimumEdge(selectedVertices);

        if (minEdge == NULL) {
            break;  
        }

        struct Vertex* toVertex = minEdge->toVertex;
        toVertex->visited = true;

        printf("Edge: %c - %c (%d)\n", selectedVertices->data, toVertex->data, minEdge->weight);
        selectedVertices = toVertex;
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
                primMST();
                break;
            case '6':
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    } while (choice != '6');

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct Vertex {
    int data;
    struct Edge* edgeList;
    struct Vertex* next;
};

struct Edge {
    struct Vertex* toVertex;
    int weight;
    struct Edge* enext;
};

struct Vertex* graph = NULL;

void InsertVertex() {
    struct Vertex* newVertex = (struct Vertex*)malloc(sizeof(struct Vertex));
    printf("Enter Vertex: ");
    scanf("%d", &newVertex->data);
    newVertex->edgeList = NULL;
    newVertex->next = NULL;

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

struct Vertex* searchVertex(int data) {
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
    int source, destination, weight;
    printf("Enter Source Vertex: ");
    scanf("%d", &source);
    struct Vertex* vcurr = searchVertex(source);
    if (vcurr == NULL) {
        printf("Source vertex not found\n");
        return;
    }

    struct Edge* ecurr = vcurr->edgeList;
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    printf("Enter Destination Vertex: ");
    scanf("%d", &destination);
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

void Dijkstra(int source) {
    struct Vertex* sourceVertex = searchVertex(source);

    if (sourceVertex == NULL) {
        printf("Source vertex not found\n");
        return;
    }

    int numVertices = 0;
    struct Vertex* vcurr = graph;
    while (vcurr != NULL) {
        numVertices++;
        vcurr = vcurr->next;
    }

    int* distance = (int*)malloc(numVertices * sizeof(int));
    bool* visited = (bool*)malloc(numVertices * sizeof(bool));

    for (int i = 0; i < numVertices; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    distance[source - 1] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int minDist = INT_MAX;
        int u;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && distance[v] < minDist) {
                minDist = distance[v];
                u = v;
            }
        }

        visited[u] = true;

        struct Vertex* uVertex = searchVertex(u + 1);
        struct Edge* ecurr = uVertex->edgeList;

        while (ecurr != NULL) {
            int v = ecurr->toVertex->data - 1;
            if (!visited[v] && (distance[u] != INT_MAX) && (distance[u] + ecurr->weight < distance[v])) {
                distance[v] = distance[u] + ecurr->weight;
            }
            ecurr = ecurr->enext;
        }
    }

    printf("Shortest distances from vertex %d:\n", source);

    for (int i = 0; i < numVertices; i++) {
        printf("Vertex %d: %d\n", i + 1, distance[i]);
    }

    free(distance);
    free(visited);
}

int main() {
    int Venteries;
    int Eenteries;
    char choice;
    do {
        printf("\n1. Insert Vertex\n2. Insert Edge\n3. Find Shortest Path (Dijkstra)\n4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printf("How many vertices you want to insert? ");
                scanf("%d", &Venteries);
                for (int i = 0; i < Venteries; i++) {
                    InsertVertex();
                }
                break;
            case '2':
                printf("\nHow many edges you want to insert? ");
                scanf("%d", &Eenteries);
                for (int i = 0; i < Eenteries; i++) {
                    InsertEdge();
                }
                break;
            case '3':
                int source;
                printf("Enter source vertex for Dijkstra's algorithm: ");
                scanf("%d", &source);
                Dijkstra(source);
                break;
            case '4':
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    } while (choice != '4');

    return 0;
}

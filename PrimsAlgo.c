#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int numNodes = 0;
int totalWeight = 0;

struct Edge {
    struct Node* toNode;
    struct Edge* nextEdge;
    int weight;
};

struct Node {
    char data;              // Data associated with the node.
    struct Edge* edgeList;  // Points to the linked list of edges connected to this node.
    struct Node* nextNode;  // Points to the next node in the linked list.
    bool inMST;             // Flag to indicate if the node is in the MST.
    int key;                // Key value used in Prim's algorithm.
    struct Node* parentNode; // Points to the parent node in the MST.
} *graph = NULL;

void AddNode() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    printf("Enter Node: \t");
    scanf(" %c", &newNode->data);
    newNode->edgeList = NULL;
    newNode->nextNode = NULL;
    newNode->inMST = false;
    newNode->key = INT_MAX;
    newNode->parentNode = NULL;

    if (graph == NULL) {
        graph = newNode;
    } else {
        struct Node* currentNode = graph;
        while (currentNode->nextNode != NULL) {
            currentNode = currentNode->nextNode;
        }
        currentNode->nextNode = newNode;
    }
    numNodes++;
}

void AddEdge() {
    char sourceNodeData, destinationNodeData;
    int edgeWeight;
    printf("Enter Source Node: ");
    scanf(" %c", &sourceNodeData);
    struct Node* sourceNode = graph;
    while (sourceNode != NULL) {
        if (sourceNodeData == sourceNode->data) {
            break;
        }
        sourceNode = sourceNode->nextNode;
    }
    if (sourceNode == NULL) {
        printf("Invalid node\n");
        return;
    }

    struct Edge* edgeStart = sourceNode->edgeList;
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    printf("Enter Destination Node: ");
    scanf(" %c", &destinationNodeData);
    struct Node* destinationNode = NULL;
    struct Node* currentNode = graph;

    while (currentNode != NULL) {
        if (currentNode->data == destinationNodeData) {
            destinationNode = currentNode;
            break;
        }
        currentNode = currentNode->nextNode;
    }

    if (destinationNode == NULL) {
        printf("Destination node not found\n");
        free(newEdge);
        return;
    }

    printf("Enter Edge Weight: ");
    scanf("%d", &edgeWeight);

    newEdge->toNode = destinationNode;
    newEdge->weight = edgeWeight;
    newEdge->nextEdge = NULL;
    if (edgeStart == NULL) {
        edgeStart = newEdge;
        sourceNode->edgeList = newEdge;
    } else {
        struct Edge* currentEdge = edgeStart;
        while (currentEdge->nextEdge != NULL) {
            currentEdge = currentEdge->nextEdge;
        }
        currentEdge->nextEdge = newEdge;
    }
}

//  Prim's algorithm
void Prim() {
    struct Node* startNode = graph; // Initialize the starting node as the first node in the graph.
    startNode->key = 0; // Set the key of the starting node to 0

    for (int i = 0; i < numNodes - 1; i++) {
        // Iterate through the graph's nodes to find the minimum key node not in the MST.
        struct Node* currentNode = graph;
        int minKey = INT_MAX;

        while (currentNode != NULL) {
            if (!currentNode->inMST && currentNode->key < minKey) {
                // If the current node is not in the MST and has a smaller key, update the minimum key and the starting node.
                minKey = currentNode->key;
                startNode = currentNode;
            }
            currentNode = currentNode->nextNode;
        }

        startNode->inMST = true; // Mark the starting node as part of the MST.

        // Iterate through the edges connected to the starting node.
        struct Edge* currentEdge = startNode->edgeList;
        while (currentEdge != NULL) {
            struct Node* targetNode = currentEdge->toNode; // Get the target node of the edge.

            if (!targetNode->inMST && currentEdge->weight < targetNode->key) {
                // If the target node is not in the MST and the edge weight is smaller than its key, update the key and parent.
                targetNode->key = currentEdge->weight;
                targetNode->parentNode = startNode;
            }
            currentEdge = currentEdge->nextEdge;
        }

        totalWeight += startNode->key; // Update the total weight with the weight of the added edge.
    }
}


void PrintMST() {
    struct Node* currentNode = graph;
    if (graph == NULL) {
        printf("The graph is empty\n");
    } else {
        printf("Minimum Spanning Tree (MST):\n");
        while (currentNode != NULL) {
            if (currentNode->parentNode != NULL) {
                printf("Edge: %c - %c (Weight: %d)\n", currentNode->parentNode->data, currentNode->data, currentNode->key);
            }
            currentNode = currentNode->nextNode;
        }
        printf("Total Weight of MST: %d\n", totalWeight);
    }
}

int main() {
    char operation;
    int choice, entries;
    bool continueExecution = true;
    while (continueExecution) {
        printf("Menu\n 1. Add Node (N)\n 2. Add Edge (E)\n 3. Find Minimum Spanning Tree (P)\n 4. Print MST (M)\n 5. Exit (X)\n Choose: ");
        scanf(" %c", &operation);
        switch (operation) {
            case 'N':
                printf("Add Node\n How many nodes to add: ");
                scanf("%d", &entries);
                for (int i = 0; i < entries; i++) {
                    AddNode();
                }
                break;

            case 'E':
                printf("Add Edge\n How many edges to add: ");
                scanf("%d", &entries);
                for (int i = 0; i < entries; i++) {
                    AddEdge();
                }
                break;

            case 'P':
                Prim();
                break;

            case 'M':
                PrintMST();
                break;

            case 'X':
                continueExecution = false;
                break;

            default:
                break;
        }
    }
    return 0;
}

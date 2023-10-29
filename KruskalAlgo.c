#include <stdio.h>

struct Edge {
    char src, dest;
    int weight;
};

void kruskalMST(struct Edge edges[], int numEdges, int numVertices) {
    char parent[26];  // Assuming vertices are labeled from 'A' to 'Z'
    for (char vertex = 'A'; vertex <= 'Z'; vertex++) {
        parent[vertex - 'A'] = vertex;
    }

    for (int i = 0; i < numEdges; i++) {
        char srcRoot = edges[i].src;
        while (srcRoot != parent[srcRoot - 'A']) {
            srcRoot = parent[srcRoot - 'A'];
        }

        char destRoot = edges[i].dest;
        while (destRoot != parent[destRoot - 'A']) {
            destRoot = parent[destRoot - 'A'];
        }

        if (srcRoot != destRoot) {
            printf("%c - %c: %d\n", edges[i].src, edges[i].dest, edges[i].weight);
            parent[srcRoot - 'A'] = destRoot;
        }
    }
}

int main() {
    struct Edge edges[] = {
        {'A', 'B', 2}, {'A', 'C', 3}, {'A', 'D', 2}, {'B', 'H', 5},
        {'C', 'G', 1}, {'G', 'I', 3}, {'D', 'F', 3}, {'D', 'E', 6},
        {'E', 'F', 7}, {'G', 'J', 2}, {'E', 'J', 6}, {'J', 'K', 9}
    };
    int numEdges = sizeof(edges) / sizeof(edges[0]);
    int numVertices = 11;

    kruskalMST(edges, numEdges, numVertices);

    return 0;
}

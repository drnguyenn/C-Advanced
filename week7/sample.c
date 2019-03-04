#include <stdio.h>
#include "/home/long/Cprogramming/Cadvanced/libgra/udr_graph.h"

void printVertex(int v)
{
    printf("%3d",v);
}

int main()
{
    Graph g = createGraph();
    addVertex(g, 0, "0");
    addVertex(g, 1, "1");
    addVertex(g, 2, "2");
    addVertex(g, 3, "3");
    addVertex(g, 4, "4");
    addVertex(g, 5, "5");
    addEdge(g, 0, 1, 1);
    addEdge(g, 1, 2, 1);
    addEdge(g, 1, 3, 1);
    addEdge(g, 2, 3, 1);
    addEdge(g, 2, 4, 1);
    addEdge(g, 4, 5, 1);
    printf("\nBFS: start from node 1 to 4: ");
    BFS(g, 1, 4, printVertex);
    printf("\nBFS: start from node 1 to all: ");
    BFS(g, 1, -1, printVertex);
    printf("\nDFS: start from node 1 to 4: ");
    DFS(g, 1, 4, printVertex);
    printf("\nDFS: start from node 1 to all: ");
    DFS(g, 1, -1, printVertex);
    printf("\n\n");
    dropGraph(g);
    return 0;
}



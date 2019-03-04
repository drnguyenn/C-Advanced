#include <stdio.h>
#include <stdlib.h>
#include "/home/long/Cprogramming/Cadvanced/libgra/udr_graph.h"

int main()
{
    int i, n, output[10];
    Graph graph = createGraph();
    addVertex(graph, 0, "0");
    addVertex(graph, 1, "1");
    addVertex(graph, 2, "2");
    addVertex(graph, 3, "3");
    addVertex(graph, 4, "4");
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 0, 2, 1);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 2, 3, 1);
    addEdge(graph, 2, 4, 1);
    n = getAdjacentVertices(graph, 2, output);
    if(n == 0)
        printf("\nNo adjacent vertices of node 2 !\n");
    else
    {
        for(i = 0; i < n; i ++) printf("%d ", output[i]);
        printf("\n");
    }
    dropGraph(graph);
    return 0;
}

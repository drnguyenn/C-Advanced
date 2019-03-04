#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/long/Cprogramming/Cadvanced/libgra/dr_graph.h"

int main()
{
    Graph graph = createGraph();
    addVertex(graph, 2, "test");
    addVertex(graph, 3, "test");
    addVertex(graph, 4, "test");
    addVertex(graph, 0, "test");
    addVertex(graph, 1, "test");
    addVertex(graph, 5, "test");
    addVertex(graph, 6, "test");
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 4);
    addEdge(graph, 4, 6);
    addEdge(graph, 6, 8);
    printf("%d\n", DAG(graph));
    dropGraph(graph);
}

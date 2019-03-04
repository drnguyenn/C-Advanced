#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/long/Cprogramming/Cadvanced/libgra/w_graph.h"

int main()
{
    int path[1000];
    int length;
    Graph graph = createGraph();
    double weight;
    addVertex(graph, 0, "test");
    addVertex(graph, 1, "test");
    addVertex(graph, 2, "test");
    addVertex(graph, 3, "test");
    addVertex(graph, 4, "test");
    addVertex(graph, 5, "test");
    addVertex(graph, 6, "test");
    addEdge(graph, 0, 1, 2.1);
    addEdge(graph, 1, 2, 4.6);
    addEdge(graph, 2, 4, 3.1);
    addEdge(graph, 4, 6, 2.9);
    addEdge(graph, 6, 8, 3.1);
    weight = shortestPath(graph, 0, 6, path, &length);
    printf("%d\n", DAG(graph));
    printf("%.2f\n", getEdgeValue(graph, 1, 2));
    printf("Total: %.2f\nLength: %d\n", weight, length);
    dropGraph(graph);
}

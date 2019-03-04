#include <stdio.h>
#include <stdlib.h>
#include "/home/long/Cprogramming/Cadvanced/libfdr/dllist.h"
#include "/home/long/Cprogramming/Cadvanced/libfdr/jrb.h"

typedef struct Graph
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();

void addVertex(Graph graph, int id, char* name);
void addEdge(Graph graph, int v1, int v2, double weight);
char *getVertex(Graph graph, int id);
double getEdgeValue(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int v, int *output);
void BFS(Graph graph,int start,int stop,void (*func)(int));
void DFS(Graph graph,int start,int stop,void (*func)(int));
double shortestPath(Graph graph, int start, int stop, int *path, int *length);
void dropGraph(Graph graph);


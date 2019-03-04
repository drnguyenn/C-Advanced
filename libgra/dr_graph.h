#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/long/Cprogramming/Cadvanced/libfdr/dllist.h"
#include "/home/long/Cprogramming/Cadvanced/libfdr/jrb.h"

typedef struct Graph
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2, double weight);
double getEdgeValue(Graph graph, int v1, int v2);
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
int DAG(Graph graph);
void BFS(Graph graph,int start,int stop,void (*func)(int));
void DFS(Graph graph,int start,int stop,void (*func)(int));
double shortestPath(Graph graph, int start, int stop, int *path, int *length);
void dropGraph(Graph graph);

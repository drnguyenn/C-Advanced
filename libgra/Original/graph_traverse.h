#include <stdio.h>
#include "/home/long/Cprogramming/Cadvanced/libfdr/dllist.h"
#include "/home/long/Cprogramming/Cadvanced/libfdr/jrb.h"
#include "/home/long/Cprogramming/Cadvanced/libgra/udr_graph.h"

void BFS(Graph graph,int start,int stop,void (*func)(int));
void DFS(Graph graph,int start,int stop,void (*func)(int));
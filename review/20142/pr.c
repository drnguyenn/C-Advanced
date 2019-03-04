#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "/home/long/Cprogramming/Cadvanced/libgra/dr_graph.h"

Graph graph;

int file_read(FILE *f)
{
    int i,m,n,v1,v2,max_v=0;
    char name[10];
    graph = createGraph();
    fscanf(f,"%d %d",&m,&n);
    for(i=0;i<m;i++)
    {
        fscanf(f,"%s %d",name,&v1);
        addVertex(graph,v1,strdup(name));
        if(v1 > max_v) max_v = v1;
    }
    for(i=0;i<n;i++)
    {
        fscanf(f,"%d %d",&v1,&v2);
        addEdge(graph,v1,v2,1);
    }
    fclose(f);
    return max_v;
}

void id_to_name(int id)
{
    char *name;
    name=getVertex(graph,id);
    if(name!=NULL) puts(name);
}

void name_to_id(const char *name)
{
    JRB node;
    jrb_traverse(node,graph.vertices)
    {
        if(!strcmp(jval_s(node->val), name)) printf("\n%d\n\n",jval_i(node->key));
    }
}

void co_citation(int id1, int id2)
{
    int output1[10], output2[10], total1, total2;
    total1 = outdegree(graph, id1, output1);
    total2 = outdegree(graph, id2, output2);
    // printf("%d %d\n",total1,total2);
    for(int i=0; i<total1; i++)
        for(int j=0; j<total2; j++)
            if(output1[i] == output2[j])
            {
                printf("%d ",output1[i]);
                id_to_name(output1[i]);
            }
}

void co_reference(int id1, int id2)
{
    int output1[10], output2[10], total1, total2;
    total1 = indegree(graph, id1, output1);
    total2 = indegree(graph, id2, output2);
    // printf("%d %d\n",total1,total2);
    for(int i=0; i<total1; i++)
        for(int j=0; j<total2; j++)
            if(output1[i] == output2[j])
            {
                printf("%d ",output1[i]);
                id_to_name(output1[i]);
            }
}

void out_degree_greater(int k)
{
    JRB node;
    int output[10], total;
    jrb_traverse(node,graph.vertices)
    {
        if(outdegree(graph, jval_i(node->key), output) > k) puts(jval_s(node->val));
    }
}

void related(int id, int max_id)
{
    BFS(graph, id, max_id, id_to_name);
}

int main(int argc, char const *argv[])
{
    if(!strcmp(argv[1],"help")) printf("\nSupported command: help, i2n, n2i, cc, cr, odg, rel.\n\n");
    else if(!strcmp(argv[1],"about")) printf("\nC advanced 20142 final exam.\n\n");
    else
    {
        // JRB node;
        int max_id;
        FILE *f;
        f=fopen(argv[2],"r");
        if(f==NULL)
        {
            printf("\n*** Opening file error ! ***\n\n");
            exit(0);
        }
        else max_id=file_read(f);
        // jrb_traverse(node,graph.vertices) printf("%d %s\n",jval_i(node->key),jval_s(node->val));
        
        if(!strcmp(argv[1],"i2n")) id_to_name(atoi(argv[3]));

        else if(!strcmp(argv[1],"n2i")) name_to_id(argv[3]);

        else if(!strcmp(argv[1],"cc")) co_citation(atoi(argv[3]), atoi(argv[4]));
        
        else if(!strcmp(argv[1],"cr")) co_reference(atoi(argv[3]), atoi(argv[4]));

        else if(!strcmp(argv[1],"odg")) out_degree_greater(atoi(argv[3]));

        else if(!strcmp(argv[1],"rel")) related(atoi(argv[3]),max_id);
        
        dropGraph(graph);
    }
    return 0;
}

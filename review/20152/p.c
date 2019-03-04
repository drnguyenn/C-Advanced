#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "/home/long/Cprogramming/Cadvanced/libgra/dr_graph.h"

Graph graph;

int file_read(FILE *f)
{
    int i,m,n,v1,v2;
    double weight;
    char name[20];
    graph = createGraph();
    fscanf(f,"%d ",&m);
    for(i=0;i<m;i++)
    {
        fscanf(f,"%d %s",&v1,name);
        addVertex(graph,v1,strdup(name));
    }
    fscanf(f,"%d ",&n);
    for(i=0;i<n;i++)
    {
        fscanf(f,"%d %d %lf",&v1,&v2,&weight);
        addEdge(graph,v1,v2,weight);
        addEdge(graph,v2,v1,weight);
    }
    fclose(f);
    return m;
}

void min_distance(int id1, int id2)
{
    int path[20],length;
    double total;
    total = shortestPath(graph, id1, id2, path, &length);
    printf("\n%.0f\n",total);
    for(int i=0; i<length; i++) printf("%d %s\n",path[i],getVertex(graph, path[i]));
    printf("\n");
}

void direct_line(int id)
{
    int total, output[20];
    total = outdegree(graph, id, output);
    printf("\n%d\n",total);
    for(int i=0; i<total; i++)
        printf("%s\n", getVertex(graph,output[i]));
    printf("\n");
}

void subset(int *V, int n, int V_sum)
{
    int E_count=0, i, j, k, check, total, A[V_sum+1][V_sum+1], output[10];
    memset(A, 0, sizeof(A));

    printf("\n%d\n",n);
    for(i=0; i<n; i++) printf("%d %s\n",V[i],getVertex(graph, V[i]));
    printf("\n");

    for(i=0; i<n; i++)
    {
        total = outdegree(graph, V[i], output);
        for(j=0; j<total; j++)
        {
            check=1;
            for(k=0; k<n; k++)      //Check if the output[j] is in the V[] or not
                if(output[j] == V[k]) break;
            if(k==n) check=0;
            // printf("V[i] = %d, output[j] = %d, check = %d\n",V[i],output[j],check);
            if(check==1 && A[ V[i] ][ output[j] ] == 0)
            {
                printf("%d %d %.0f\n",V[i], output[j], getEdgeValue(graph, V[i], output[j]) );
                A[ V[i] ][ output[j] ] = 1;
                A[ output[j] ][ V[i] ] = 1;
                E_count ++;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    if(!strcmp(argv[1],"-h")) printf("\nC-Advanced, HK20152.\n\n");
    else
    {
        int V_sum;
        FILE *f;
        f=fopen(argv[2],"r");
        if(f==NULL)
        {
            printf("\n*** Opening file error ! ***\n\n");
            exit(0);
        }
        else V_sum=file_read(f);
        
        if(!strcmp(argv[1],"-v"))
        {
            JRB node;
            jrb_traverse(node,graph.vertices) printf("%d %s\n",jval_i(node->key),jval_s(node->val));
        }

        else if(!strcmp(argv[1],"-w"))
            printf("\n%.0f\n\n",getEdgeValue( graph, atoi(argv[3]), atoi(argv[4]) ));

        else if(!strcmp(argv[1],"-p")) min_distance(atoi(argv[3]), atoi(argv[4]));
        
        else if(!strcmp(argv[1],"-n")) direct_line(atoi(argv[3]));

        else if(!strcmp(argv[1],"-s"))
        {
            int i,j=3, n=argc-3, V[n];
            for(i=0; i<n; i++) V[i] = atoi(argv[j++]);
            subset(V, n, V_sum);
        }

        dropGraph(graph);
    }
    return 0;
}
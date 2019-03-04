#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "/home/long/Cprogramming/Cadvanced/libgra/udr_graph.h"

typedef struct Res
{
    int id, info[10][2];
} Res;

Graph graph1,graph2;
Res *res;

int product_file_read(FILE *f)
{
    int i,m,id;
    char prod_name[30];
    fscanf(f,"%d ",&m);
    // printf("%d\n",m);
    for(i=0; i<m; i++)
    {
        fscanf(f,"%s %d",prod_name,&id);
        // printf("%s %d\n",prod_name,id);
        addVertex(graph1, id, strdup(prod_name));
    }
    fclose(f);
    return m;
}

int res_file_read(FILE *f, int m)
{
    int i,j,k,n, p_id, r_id, amount, id1, id2;
    double weight;
    char res_name[30];
    fscanf(f,"%d ",&n);
    // printf("\nm = %d\n",m);
    res = (Res *) malloc(n*sizeof(Res));
    for(i=0; i<n; i++)
    {
        fscanf(f,"%s %d ",res_name,&r_id);
        addVertex(graph2, r_id, strdup(res_name));
        // printf("%s %d\n",res_name,r_id);
        res[i].id = r_id;
        for(j=0; j<m; j++)
        {
            fscanf(f,"%d %d ",&p_id,&amount);
            // printf("%d %d ",p_id,amount);
            // printf("\n");
            res[i].info[j][0] = p_id;
            res[i].info[j][1] = amount;
        }
    }
    fscanf(f,"%d ",&k);
    for(i=0; i<k; i++)
    {
        fscanf(f,"%d %d %lf ",&id1,&id2,&weight);
        // printf("%d %d %0.f\n",id1,id2,weight);
        addEdge(graph2, id1, id2, weight);
    }
    fclose(f);
    return n;
}

void getRes_info(int m, int n, int r_id, int p_id)
{
    for(int i=0; i<n; i++)
        if(res[i].id == r_id)
            for(int j=0; j<m; j++)
                if(res[i].info[j][0] == p_id)
                {
                    printf("%s %d\n", getVertex(graph1, res[i].info[j][0]) , res[i].info[j][1] );
                    break;
                }
}

void order(int m, int n, int p_id, int amount, int r1, int r2)
{
    for(int i=0; i<n; i++)
    {
        if(res[i].id == r1)
        {
            for(int j=0; j<m; j++)
            {
                if(res[i].info[j][0] == p_id)
                {
                    if(res[i].info[j][1] >= amount)
                    {
                        printf("\nDat hang thanh cong, thoi gian giao hang la 30 phut.\n");
                        break;
                    }

                    for(int k=0; k<n; k++)
                    {
                        if(res[k].id == r2)
                        {
                            for(int t=0; t<m; t++)
                                if(res[k].info[t][0] == p_id)
                                {
                                    if(res[i].info[j][1] + res[k].info[t][1] >= amount)
                                    {
                                        double dlv_time;
                                        int path[n], length;
                                        dlv_time = shortestPath(graph2, r1, r2, path, &length) / 30 + 0.5;
                                        if(dlv_time < 1)
                                            printf("\nDat hang thanh cong, thoi gian giao hang la %.0f phut.\n", dlv_time*60);
                                        else
                                            printf("\nDat hang thanh cong, thoi gian giao hang la %d gio %.0f phut.\n", (int)dlv_time, (dlv_time - (int)dlv_time)*60);
                                    }
                                    else printf("\nDat hang khong thanh cong.\n");
                                    break;
                                }
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    if(!strcmp(argv[1],"-t")) printf("\nC-Advanced, HK20182\n\n");
    else
    {
        JRB node,node1,node2;
        FILE *f1,*f2;
        graph1 = createGraph();
        graph2 = createGraph();
        if(!strcmp(argv[1],"-s"))
        {
            f1 = fopen(argv[2],"r");
            if(f1 != NULL) product_file_read(f1);
            printf("\n");
            jrb_traverse(node,graph1.vertices) printf("%s %d\n",jval_s(node->val),jval_i(node->key));
            printf("\n");
        }
        else
        {
            int m,n;
            f1 = fopen(argv[3],"r");
            if(f1 != NULL) m = product_file_read(f1);
            f2 = fopen(argv[2],"r");
            if(f2 != NULL) n = res_file_read(f2, m);

            if(!strcmp(argv[1],"-w"))
            {
                double w = getEdgeValue(graph2, atoi(argv[4]), atoi(argv[5]));
                printf("\n%0.f%s\n\n", w, w ==-1 ? "" : " km");
            }

            else if(!strcmp(argv[1],"-a"))
            {
                jrb_traverse(node2,graph2.vertices)
                {
                    printf("%s\n", getVertex(graph2, jval_i(node2->key)) );
                    jrb_traverse(node1,graph1.vertices)
                        printf("%s\n",jval_s(node1->val));
                    printf("----\n");
                }
            }
                
            else if(!strcmp(argv[1],"-h"))
            {
                int total, output[10];
                node = jrb_find_int(graph2.vertices, atoi(argv[5]));
                printf("%s\n", getVertex(graph2, jval_i(node->key)) );
                getRes_info(m, n, atoi(argv[5]), atoi(argv[4]) );

                printf("\n--- Cac kho ke la:\n");
                total = getAdjacentVertices(graph2, atoi(argv[5]), output);
                for(int i=0; i<total; i++)
                {
                    printf("\n%s\n", getVertex(graph2, output[i]) );
                    getRes_info(m, n, output[i], atoi(argv[4]) );
                }
            }

            else if(!strcmp(argv[1],"-g"))
            {
                order(m, n, atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]) );
            }
        }
        dropGraph(graph1);
        dropGraph(graph2);
    }
    return 0;
}
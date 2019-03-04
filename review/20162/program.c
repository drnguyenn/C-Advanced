#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "/home/long/Cprogramming/Cadvanced/libfdr/fields.h"
#include "/home/long/Cprogramming/Cadvanced/libgra/udr_graph.h"

#define buf_clear while(getchar()!='\n');

Graph graph;

int factorial(int n)
{
    int i,S=1;
    for(i=2; i<=n; i++) S*=i;
    return S;
}

int combination(int n, int k)
{
    return factorial(n) / (factorial(k)*factorial(n-k));
}

int weith_edit(Graph graph, int v1, int v2, double new_weight)
{
    JRB node, tree, temp;
    node = jrb_find_int(graph.edges, v1);
    if(node==NULL) return 0;
    else
    {
        tree = (JRB) jval_v(node->val);
        temp = jrb_find_int(tree, v2);
        if(temp == NULL) return 0;
        else temp->val.i = new_weight;
    }
    return 1;
}

int product_file_read(FILE *f)
{
    int i,V_sum=0;
    JRB node;
    IS is;
    is = new_inputstruct("products.txt");
    while(get_line(is) >= 0)
    {
        addVertex(graph, atoi(is->fields[0]), strdup(is->fields[1]) );
        V_sum ++;
    }
    jettison_inputstruct(is);

    printf("\n---------------------------\n");
    jrb_traverse(node,graph.vertices)
        printf("\nMã sản phẩm: %d\nTên sản phẩm: %s\n",jval_i(node->key),jval_s(node->val));
    printf("\n---------------------------\n");
    return V_sum;
}

void order_file_read(FILE *f, int V_sum)
{
    int i,j;
    double W[V_sum+1][V_sum+1];
    IS is;
    // memset(V, -1, sizeof(V));
    memset(W, -1, sizeof(W));
    for(i=0; i<V_sum+1; i++)
        for(j=0; j<V_sum+1; j++) W[i][j] = 0;
    is = new_inputstruct("orderhistory.txt");
    printf("\n---------------------------\n\n");
    while(get_line(is) >= 0)
    {
        for (i = 0; i< is->NF; i++)
        {
            printf("%s ",getVertex(graph, atoi(is->fields[i])) );
            if(i< is->NF-1)
                for(j=i+1; j< is->NF; j++)
                {
                    if(!adjacent(graph, atoi(is->fields[i]), atoi(is->fields[j]) ))
                    {
                        addEdge(graph, atoi(is->fields[i]), atoi(is->fields[j]), 1);
                        W[ atoi(is->fields[i]) ][ atoi(is->fields[j]) ] = 1;
                        W[ atoi(is->fields[j]) ][ atoi(is->fields[i]) ] = 1;
                    }
                    else weith_edit(graph, atoi(is->fields[i]), atoi(is->fields[j]), ++ W[ atoi(is->fields[i]) ][ atoi(is->fields[j]) ]);
                }
        }
        printf("\n");
    }
    printf("\n---------------------------\n");
    jettison_inputstruct(is);
}

int main()
{
    int V_sum,opt;
    FILE *f;
    graph = createGraph();
    do
    {
        printf("\n");
        printf("1. Danh sách sản phẩm\n");
        printf("2. Danh sách giao dịch\n");
        printf("3. Mức độ liên quan giữa 2 sản phẩm\n");
        printf("4. Danh sách các sản phẩm liên quan\n");
        printf("5. Mối liên hệ giữa hai sản phẩm\n");
        printf("6. Thoát chương trình\n");
        printf("\n");
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
                f=fopen("products.txt","r");
                if(f==NULL) perror("\n*** Error opening file");
                else V_sum = product_file_read(f);
                break;

            case 2:
                f=fopen("orderhistory.txt","r");
                if(f==NULL) perror("\n*** Error opening file");
                else order_file_read(f,V_sum);
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;
        }
    }
    while(opt!=6);
    dropGraph(graph);
    return 0;
}

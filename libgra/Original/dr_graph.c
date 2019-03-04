#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dr_graph.h"

Graph createGraph()
{
    Graph graph;
    graph.edges = make_jrb();
    graph.vertices = make_jrb();
    return graph;
}

void addVertex(Graph graph, int id, char *name)
{
    JRB node;
    node = jrb_find_int(graph.vertices, id);
    if(node == NULL)
        jrb_insert_int(graph.vertices, id, new_jval_s(name));
    else printf("\n*** Vertex %d already exists ! ***\n",id);
}

char *getVertex(Graph graph, int id)
{
    JRB node;
    node = jrb_find_int(graph.vertices, id);
    if(node != NULL)
        return jval_s(node->val);
    else return NULL;
}

int hasEdge(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if(node == NULL)
        return 0;
    tree = (JRB) jval_v(node->val);
    if(jrb_find_int(tree, v2) == NULL)
        return 0;
    else
        return 1;
}

void addEdge(Graph graph, int v1, int v2)
{
    JRB node, tree;
    if(!hasEdge(graph, v1, v2))
    {
        node = jrb_find_int(graph.edges, v1);
        if(node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        }
        else
            tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
}

int outdegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if(node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree)
    {
        output[total] = jval_i(node->key);
        total ++;
    }
    return total;
}

int indegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        if(jrb_find_int(tree, v) != NULL)
        {
            output[total] = jval_i(node->key);
            total ++;
        }
    }
    return total;
}

int DAG(Graph graph)
{
    JRB vertex;
    JRB node;
    int i,n,output[100],visited[1000];
    Dllist queue, temp;

    jrb_traverse(vertex, graph.vertices)
    {
        memset(visited, 0, sizeof(visited));
        queue = new_dllist();
        dll_append(queue, vertex->key);
        
        while(!dll_empty(queue))
        {
            temp = dll_first(queue);
            int value = jval_i(temp->val);
            dll_delete_node(temp);
            if(visited[value] == 0)
            {
                visited[value] == 1;
                n = outdegree(graph, value, output);
                int outkey;
                for(i = 0; i < n; i ++)
                {
                    outkey = output[i];
                    if(outkey == jval_i(vertex->key))
                    {
                        free_dllist(queue);
                        return 0;
                    }
                    if(visited[outkey] == 0)
                        dll_append(queue, new_jval_i(outkey));
                }
            }
        }
        free_dllist(queue);
    }
    return 1;
}

void BFS(Graph graph,int start,int stop,void (*func)(int))
{
    int i,n,output[100];
    JRB node;
    JRB visited;
    visited = make_jrb();
    jrb_traverse(node, graph.edges)
        jrb_insert_int(visited, jval_i(node->key), new_jval_i(0));

    Dllist temp,queue;
    queue = new_dllist();
    dll_append(queue, new_jval_i(start));

    while(!dll_empty(queue))
    {
        temp = dll_first(queue);
        Jval value = temp->val;
        dll_delete_node(temp);
        node = jrb_find_int(visited, jval_i(value));
        if(jval_i(node->val) == 0)
        {
            func(jval_i(value));
            if(jval_i(value) == stop)
            {
                free_dllist(queue);
                // printf("\nTrue\n");
                return;
            }
            node->val = new_jval_i(1);
            n = outdegree(graph, jval_i(value), output);
            JRB _node;
            for(i = 0; i < n; i ++)
            {
                _node = jrb_find_int(visited, output[i]);
                if(jval_i(_node->val) == 0)
                    dll_append(queue, new_jval_i(output[i]));
            }
        }
    }
    free_dllist(queue);
    // printf("\nFalse\n");
}

void DFS(Graph graph,int start,int stop,void (*func)(int))
{
    JRB node;
    JRB visited;
    visited = make_jrb();
    jrb_traverse(node, graph.edges)
        jrb_insert_int(visited, jval_i(node->key), new_jval_i(0));

    Dllist stack = new_dllist();
    dll_append(stack, new_jval_i(start));

    Dllist temp;
    int n, output[100];
    int i;
    while(!dll_empty(stack))
    {
        temp = dll_last(stack);
        Jval value = temp->val;
        dll_delete_node(temp);
        node = jrb_find_int(visited, jval_i(value));
        if(jval_i(node->val) == 0)
        {
            func(jval_i(value));
            if(jval_i(value) == stop)
            {
                free_dllist(stack);
                // printf("\nTrue\n");
                return;
            }
            node->val = new_jval_i(1);
            n = outdegree(graph, jval_i(value), output);
            JRB _node;
            for(i = 0; i < n; i ++)
            {
                _node = jrb_find_int(visited, output[i]);
                if(jval_i(_node->val) == 0)
                    dll_append(stack, new_jval_i(output[i]));
            }
        }
    }
    free_dllist(stack);
    // printf("\nFalse\n");
}

void dropGraph(Graph graph)
{
    JRB node;
    jrb_traverse(node, graph.edges)
        jrb_free_tree((JRB)jval_v(node->val));
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

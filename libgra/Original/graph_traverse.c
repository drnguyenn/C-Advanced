#include <stdio.h>
#include "graph_traverse.h"

void BFS(Graph graph,int start,int stop,void (*func)(int))
{
    int i,n,output[100];
    JRB node;
    JRB visited;
    visited = make_jrb();
    jrb_traverse(node, graph)
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
            n = getAdjacentVertices(graph, jval_i(value), output);
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
    jrb_traverse(node, graph)
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
            n = getAdjacentVertices(graph, jval_i(value), output);
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

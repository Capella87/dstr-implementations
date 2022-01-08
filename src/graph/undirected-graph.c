#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "undirected-graph.h"

node* get_node(const int d)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->next = new_node->prev = NULL;
    new_node->data = d;

    return new_node;
}

bool insert_node(undigraph* l, const int num)
{
    node* new_node = get_node(num);
    new_node->next = l->tail;
    new_node->prev = l->tail->prev;
    l->tail->prev->next = new_node;
    l->tail->prev = new_node;

    l->count++;
    return true;
}

bool remove_node(undigraph* l, const int num)
{
    if (l->number == -1)
    {
        fprintf(stderr, "No Entries.\n");
        return false;
    }

    node* cur = l->head;
    while (cur != l->tail)
    {
        if (cur->data == num) break;
        cur = cur->next;
    }

    if (cur == l->tail)
    {
        fprintf(stderr, "An edge leading to %d is NOT found.\n", num);
        return false;
    }
    // Remove
    cur->next->prev = cur->prev;
    cur->prev->next = cur->next;
    l->count--;
    free(cur);

    return true;
}

graph* init_graph(const int init_size)
{
    graph* gr = (graph*)malloc(sizeof(graph));

     gr->g = (undigraph*)malloc(sizeof(undigraph) * init_size);
     gr->size = init_size;
     gr->v = 0;
     gr->e = 0;

    for (int i = 0; i < init_size; i++)
    {
        gr->g[i].head = get_node(-1);
        gr->g[i].tail = get_node(-1);
        gr->g[i].head->next = gr->g[i].tail;
        gr->g[i].tail->prev = gr->g[i].head;
        gr->g[i].count = 0;
        gr->g[i].number = -1;
    }

    return gr;
}

bool add_edge(graph* gr, const int from, const int to)
{
    if (gr->g[from].number == -1 || gr->g[to].number == -1)
    {
        fprintf(stderr, "Error!\n");
        return false;
    }

    insert_node(&(gr->g[from]), to);
    insert_node(&(gr->g[to]), from);
    gr->e++;

    return true;
}

bool remove_edge(graph* gr, const int from, const int to)
{
    // Remove 2 places;
    bool rt = false;

    rt |= remove_node(&(gr->g[from]), to);
    if (!rt) goto err_exit;

    rt &= remove_node(&(gr->g[to]), from);
    if (!rt) goto err_exit;

    gr->e--;

err_exit:
    return rt;
}

bool add_vertex(graph* gr, const int num)
{
    if (num >= gr->size) return false;
    gr->g[num].number = num;

    gr->v++;
    return true;
}

bool remove_vertex(graph* gr, const int target)
{
    if (target < 0 || target >= gr->size)
    {
        fprintf(stderr, "ERROR - Out of range.\n");
        return false;
    }

    if (!gr->g)
    {
        fprintf(stderr, "ERROR - No such space.\n");
        exit(EXIT_FAILURE);
    }

    if (gr->g[target].number != target)
    {
        fprintf(stderr, "No %d in the graph.\n", target);
        return false;
    }

    // Remove all connected edges if exist.
    while (gr->g[target].count)
    {
        node* cur = gr->g[target].head->next;
        int temp_num = cur->data;
        cur = NULL;
        remove_edge(gr, target, temp_num);
    }

    // vertex 제거
    gr->g[target].number = -1;
    gr->v--;

    return true;
}

bool show_status(graph* gr)
{
    printf("Total vertices: %d\n", gr->v);
    printf("Total edges:    %d\n", gr->e);
    for (int i = 0; i < gr->size; i++)
    {
        if (gr->g[i].number != -1)
        {
            printf("Vertex %d : ", gr->g[i].number);
            
            // Show edges connected to the vertex;
            node* cur = gr->g[i].head->next;
            for (int j = 0; j < gr->g[i].count && cur != gr->g[i].tail; j++, cur = cur->next)
            {
                printf("(%d, %d) ", gr->g[i].number, cur->data);
            }
            putchar('\n');
        }
    }
    putchar('\n');

    return true;
}

void free_all(graph* gr)
{
    for (int i = 0; i < gr->size; i++)
    {
        if (gr->g[i].number == i) remove_vertex(gr, i);
        free(gr->g[i].head);
        free(gr->g[i].tail);
    }
    free(gr->g);
    free(gr);
}

int main(void)
{
    graph* gr = init_graph(100);

    add_vertex(gr, 1);
    add_vertex(gr, 2);
    add_vertex(gr, 3);
    add_vertex(gr, 0);
    add_vertex(gr, 99);

    add_edge(gr, 1, 3);
    add_edge(gr, 1, 2);
    add_edge(gr, 2, 3);

    show_status(gr);

    remove_edge(gr, 1, 3);
    show_status(gr);

    remove_edge(gr, 1, 99);
    remove_vertex(gr, 99);
    remove_vertex(gr, 2);

    show_status(gr);


    free_all(gr);
    return 0;
}
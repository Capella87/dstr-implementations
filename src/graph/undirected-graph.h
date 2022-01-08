#ifndef UNDIRECTED_GRAPH.H
#define UNDIRECTED_GRAPH.H

#include <stdbool.h>

typedef struct node
{
    int data;
    struct node* next;
    struct node* prev;
} node;

typedef struct undigraph
{
    node* head;
    node* tail;
    int number;
    int count;
} undigraph;

typedef struct graph
{
    undigraph* g;
    int v;
    int e;
    int size;
} graph;

node* get_node(const int d);
bool insert_node(undigraph* l, const int num);
bool remove_node(undigraph* l, const int num);

graph* init_graph(const int init_size);

bool add_edge(graph* gr, const int from, const int to);
bool remove_edge(graph* gr, const int from, const int to);
bool add_vertex(graph* gr, const int num);
bool remove_vertex(graph* gr, const int target);

bool show_status(graph* gr);

void free_all(graph* gr);

#endif
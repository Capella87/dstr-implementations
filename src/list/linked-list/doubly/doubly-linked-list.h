#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdbool.h>

typedef struct node
{
    struct node* next;
    struct node* prev;
    bool is_special;
    int data;
} node;

typedef struct list
{
    node* header;
    node* trailer;
    int count;
} list;

node* creat_node(int data, bool is_special);

void bind_header_n_trailer(list** lst);
list* init_list(void);

void bind_node(node* before, node* target, node* next);
node* separate_node(node* before, node* target, node* next);
void add_front(list** lst, int data);
void add_node_front(list** lst, node* n);
void append(list** lst, int data);
void append_node(list** lst, node* n);
void insert(list** lst, int data, int idx);
void insert_node(list** lst, node* n, int idx);
void insert_after(list** lst, int data, int target);
void insert_after_node(list** lst, node* n, int target);

int pop_front(list** lst);
node* pop_node_front(list** lst);
int pop_back(list** lst);
node* pop_node_back(list** lst);
int pop_at(list** lst, int idx);
node* pop_node_at(list** lst, int idx);

void traverse_all_nodes(list* lst);
void traverse_all_nodes_reversed(list* lst);

node* find_node(list* lst, int data);
node* find_last_node(list* lst, int data);

int get_at(list* lst, int idx);
node* get_node_at(list* lst, int idx);

bool is_empty(list* lst);

void free_all(list* lst);

#endif //DOUBLY_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "doubly-linked-list.h"

// Create a node
node* creat_node(int data, bool is_special)
{
    node* rt = (node*)malloc(sizeof(node));
    rt->data = data;
    rt->next = rt->prev = NULL;
    rt->is_special = is_special;

    return rt;
}

// Connect the header and the trailer node to each other
void bind_header_n_trailer(list** lst)
{
    (*lst)->header->next = (*lst)->trailer;
    (*lst)->trailer->prev = (*lst)->header;
}

// Initialize a list and return it
list* init_list(void)
{
    list* rt = (list*)malloc(sizeof(list));
    rt->header = creat_node(-1, true);
    rt->trailer = creat_node(-1, true);

    bind_header_n_trailer(&rt);
    rt->count = 0;

    return rt;
}

// Bind the target node between two given nodes in the list
void bind_node(node* before, node* target, node* after)
{
    if (!target) return;

    target->prev = before;
    target->next = after;
    if (before) before->next = target;
    if (after) after->prev = target;
}

// Separate the target node from the list and return it
node* separate_node(node* before, node* target, node* after)
{
    if (!target) return NULL;

    if (before)
        before->next = after;
    if (after)
        after->prev = before;

    target->prev = target->next = NULL;

    return target;
}

// Add a new node after the header node in the list
void add_front(list** lst, int data)
{
    node* target = creat_node(data, false);
    bind_node((*lst)->header, target, (*lst)->header->next);

    (*lst)->count++;
}

// Add an argument node after the header node in the list
void add_node_front(list** lst, node* n)
{
    if (!n || n->is_special)
    {
        printf("Invalid node\n");
        return;
    }

    bind_node((*lst)->header, n, (*lst)->header->next);
    (*lst)->count++;
}

// Append a new node to the list
void append(list** lst, int data)
{
    node* target = creat_node(data, false);

    bind_node((*lst)->trailer->prev, target, (*lst)->trailer);
    (*lst)->count++;
}

// Append an argument node to the list
void append_node(list** lst, node* n)
{
    if (!n || n->is_special)
    {
        printf("Invalid node\n");
        return;
    }

    bind_node((*lst)->trailer->prev, n, (*lst)->trailer);
    (*lst)->count++;
}

// Find the node at idx and insert the new node before it
void insert(list** lst, int data, int idx)
{
    if (idx > (*lst)->count || idx < 0)
    {
        printf("Invalid index number - idx exceeds the element count.\n");
        return;
    }
    node* target = creat_node(data, false);

    // Insert node before the idx node;
    node* cur = get_node_at(*lst, idx);
    bind_node(cur->prev, target, cur);
    (*lst)->count++;
}

// Find the node at idx and insert the argument node before it
void insert_node(list** lst, node* n, int idx)
{
    if (!n || n->is_special)
    {
        printf("Invalid node\n");
        return;
    }

    if (idx > (*lst)->count || idx < 0)
    {
        printf("Invalid index number - idx exceeds the element count.\n");
        return;
    }

    node* cur = get_node_at(*lst, idx);
    bind_node(cur->prev, n, cur);
    (*lst)->count++;
}

// Find the node at idx and insert the new node after it
void insert_after(list** lst, int data, int idx)
{
    if (idx > (*lst)->count || idx < 0)
    {
        printf("Invalid index number - idx exceeds the element count.\n");
        return;
    }
    node* target = creat_node(data, false);

    node* cur = get_node_at(*lst, idx);
    if(cur == (*lst)->trailer) bind_node(cur->prev, target, cur);
    else bind_node(cur, target, cur->next);
    (*lst)->count++;
}

// Find the node at idx and insert the argument node after it
void insert_after_node(list** lst, node* n, int idx)
{
    if (!n || n->is_special)
    {
        printf("Invalid node\n");
        return;
    }

    if (idx > (*lst)->count || idx < 0)
    {
        printf("Invalid index number - idx exceeds the element count.\n");
        return;
    }

    node* cur = get_node_at(*lst, idx);
    if (cur == (*lst)->trailer)
        bind_node(cur->prev, n, cur);
    else bind_node(cur, n, cur->next);
    (*lst)->count++;
}

// Get rid of the first node from the list and return its value
int pop_front(list** lst)
{
    if (is_empty(*lst))
    {
        printf("No element in the list.\n");
        return -1;
    }

    node* target = separate_node((*lst)->header, (*lst)->header->next, (*lst)->header->next->next);
    (*lst)->count--;
    int rt = target->data;

    free(target);
    return rt;
}

// Get rid of the first node from the list and return it
node* pop_node_front(list** lst)
{
    if (is_empty(*lst))
    {
        printf("No element in the list.\n");
        return NULL;
    }

    node* rt = separate_node((*lst)->header, (*lst)->header->next, (*lst)->header->next->next);

    return rt;
}

// Get rid of the last node from the list and return its value
int pop_back(list** lst)
{
    if (is_empty(*lst))
    {
        printf("No element in the list.\n");
        return -1;
    }

    node* target = separate_node((*lst)->trailer->prev->prev, (*lst)->trailer->prev, (*lst)->trailer);
    int rt = target->data;

    free(target);
    return rt;
}

// Get rid of the last node from the list and return it
node* pop_node_back(list** lst)
{
    if (is_empty(*lst))
    {
        printf("No element in the list.\n");
        return -1;
    }

    node* target = separate_node((*lst)->trailer->prev->prev, (*lst)->trailer->prev, (*lst)->trailer);

    return target;
}

// Remove a node at idx from the list and return its value
int pop_at(list** lst, int idx)
{
    if (idx > (*lst)->count || idx < 0)
    {
        printf("Invalid index number - idx exceeds the element count.\n");
        return -1;
    }

    node* target = get_node_at(*lst, idx);
    target = separate_node(target->prev, target, target->next);
    int rt = target->data;

    (*lst)->count--;
    free(target);
    return rt;
}

// Remove a node at idx from the list and return it
node* pop_node_at(list** lst, int idx)
{
    if (idx > (*lst)->count || idx < 0)
    {
        printf("Invalid index number - idx exceeds the element count.\n");
        return -1;
    }

    node* target = get_node_at(*lst, idx);
    target = separate_node(target->prev, target, target->next);
    (*lst)->count--;

    return target;
}

// Traverse all elements in the list from the header node
void traverse_all_nodes(list* lst)
{
    if (is_empty(lst))
    {
        printf("No element in the list.\n");
        return;
    }

    node* cur = lst->header->next;
    while (cur != lst->trailer)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    putchar('\n');
}

// Traverse all elements in the list from the trailer node
void traverse_all_nodes_reversed(list* lst)
{
    if (is_empty(lst))
    {
        printf("No element in the list.\n");
        return;
    }

    node* cur = lst->trailer->prev;
    while (cur != lst->header)
    {
        printf("%d ", cur->data);
        cur = cur->prev;
    }
    putchar('\n');
}

// Find first occurrence
node* find_node(list* lst, int data)
{
    if (is_empty(lst))
    {
        printf("No element in the list.\n");
        return NULL;
    }

    node* cur = lst->header;
    while (cur != lst->trailer)
    {
        if (cur->data == data)
            break;
        cur = cur->next;
    }

    return cur == lst->trailer ? NULL : cur;
}

// Find last occurrence
node* find_last_node(list* lst, int data)
{
    if (is_empty(lst))
    {
        printf("No element in the list.\n");
        return NULL;
    }

    node* cur = lst->trailer;
    while (cur != lst->header)
    {
        if (cur->data == data)
            break;
        cur = cur->prev;
    }

    return cur == lst->header ? NULL : cur;
}

// Get element at idx in the list
int get_at(list* lst, int idx)
{
    if (idx > lst->count || idx < 0)
    {
        printf("Invalid index number - idx exceeds the element count.\n");
        return NULL;
    }
    else if (idx == lst->count) return lst->trailer;

    node* cur = lst->header->next;
    for (int i = 0; i < idx; i++)
        cur = cur->next;

    return cur->data;
}

// Get node at idx
node* get_node_at(list* lst, int idx)
{
    if (idx > lst->count || idx < 0)
    {
        printf("Invalid index number - idx exceeds the element count.\n");
        return NULL;
    }
    else if (idx == lst->count) return lst->trailer;

    node* cur = lst->header->next;
    for (int i = 0; i < idx; i++)
        cur = cur->next;

    return cur;
}

void free_all(list* lst)
{
    while (lst->count)
        pop_front(&lst);
    free(lst);
}

bool is_empty(list* lst)
{
    return lst->count ? false : true;
}

// Driver main code
int main(void)
{
    list* lst = init_list();

    add_front(&lst, 123);
    add_front(&lst, 1245);
    append(&lst, 523);
    insert(&lst, 23, 1);

    traverse_all_nodes(lst);

    free_all(lst);
    return 0;
}
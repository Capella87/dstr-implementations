#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SUBMISSION
// #define FIRSTSEARCH
// #define TOPOSORT
#define UNDIGRAPH

typedef struct incidence incidence;
typedef struct vertex vertex;
typedef struct edge edge;

typedef struct incidence
{
    edge* edge;
    incidence* next;
    vertex* opposite;
} incidence;

// Vertex struct
typedef struct vertex
{
    incidence* outbound_header;
    incidence* inbound_header;
    int name;
    int outbound_count;
    int inbound_count;
#ifdef FIRSTSEARCH
    bool is_visited;
#endif
#ifdef TOPOSORT
    int degree;
#endif
} vertex;

// Edge struct
typedef struct edge
{
    vertex* source;
    vertex* destination;
    int weight;
    int num;
} edge;

#ifdef TOPOSORT

// Queue implementation

typedef struct qnode
{
    struct qnode* next;
    struct qnode* prev;
    vertex* data;
} qnode;

// Queue struct type
typedef struct queue
{
    struct qnode* header;
    struct qnode* trailer;
    int count;
} queue;

// Make a new node for queue
qnode* creat_qnode(vertex* data)
{
    qnode* rt = (qnode*)malloc(sizeof(qnode));
    rt->data = data;
    rt->next = rt->prev = (void*)0;

    return rt;
}

// Initialize a new queue
queue* queue_new(void)
{
    queue* rt = (queue*)malloc(sizeof(queue));
    rt->header = creat_qnode((void*)0); // header
    rt->trailer = creat_qnode((void*)0); // trailer

    rt->header->next = rt->trailer;
    rt->trailer->prev = rt->header;
    rt->count = 0;

    return rt;
}

// Return true if the queue is empty
bool queue_is_empty(queue* q)
{
    return !q->count ? true : false;
}

// Insert a node before the trailer of queue;
void queue_enqueue(queue* q, vertex* data)
{
    qnode* n = creat_qnode(data);

    n->next = q->trailer;
    n->prev = q->trailer->prev;
    q->trailer->prev->next = n;
    q->trailer->prev = n;
    q->count++;
}

// Remove the oldest node from the queue
vertex* queue_dequeue(queue* q)
{
    if (queue_is_empty(q))
        return (void*)0;

    // Update the queue
    qnode* target = q->header->next;
    q->header->next = target->next;
    target->next->prev = q->header;

    // Retrieve the data from the node which will be disposed
    vertex* rt = target->data;
    free(target); // Dispose the qnode
    q->count--; // Decrement the number of node in the queue

    return rt; // Return the value
}

// Return the front node of queue
vertex* queue_front(queue* q)
{
    if (queue_is_empty(q))
        return (void*)0;

    return q->header->next->data;
}

// Return the rear node of queue
vertex* queue_back(queue* q)
{
    if (queue_is_empty(q))
        return (void*)0;

    return q->trailer->prev->data;
}

// Dispose the queue
void queue_free(queue* q)
{
    if (!queue_is_empty(q))
        queue_dequeue(q);
    free(q->header);
    free(q->trailer);
    free(q);
}

#endif

// Create a new incidence to save the opposite vertex and edge information
incidence* incidence_creat(edge* edg, vertex* vert)
{
    incidence* rt = (incidence*)malloc(sizeof(incidence));
    rt->edge = edg;
    rt->next = (void*)0;
    rt->opposite = vert;

    return rt;
}

// Initialize the vertex array
void vertex_init(vertex** vert, int size)
{
    *vert = (vertex*)malloc(sizeof(vertex) * (size + 1));
    for (int i = 0; i <= size; i++)
    {
        (*vert)[i].inbound_count = (*vert)[i].outbound_count = 0;

        // Create headers
        (*vert)[i].inbound_header = incidence_creat((void*)0, (void*)0);
        (*vert)[i].outbound_header = incidence_creat((void*)0, (void*)0);
        (*vert)[i].name = 0;
#ifdef FIRSTSEARCH
        (*vert)[i].is_visited = false;
#endif

#ifdef PRIM
        (*vert)[i].distance = INT_MAX;
        (*vert)[i].parent_edge = (void*)0;
        (*vert)[i].heap_pos = (void*)0;
#endif
    }
}

// Initialize the edge array
void edge_init(edge** edg, int size)
{
    (*edg) = (edge*)malloc(sizeof(edge) * (size + 1));

    // Initialize information of each edge element
    for (int i = 0; i <= size; i++)
    {
        (*edg)[i].source = (*edg)[i].destination = (void*)0;
        (*edg)[i].num = -1;
        (*edg)[i].weight = 0;
    }
}

// Find the vertex which contains vert_key
int vertex_find(vertex* vert, int vert_key, int size)
{
    for (int i = 1; i <= size; i++)
        if (vert[i].name == vert_key) return i;

    // Return -1 if it could not be found or the array is full
    return -1;
}

// Find the edge which contains edge_key
int edge_find(edge* edg, int edge_key, int size)
{
    for (int i = 1; i <= size; i++)
        if (edg[i].num == edge_key) return i;

    // Return -1 if it could not be found
    return -1;
}

// Find and return the incidence node from the list
incidence* incidence_find(incidence* header, incidence** prev, int vert_key)
{
    incidence* n = header;
    incidence* pre = n;

    // Move forward while the n is not null and the vert_key is not matching
    while (n && n->opposite->name != vert_key)
    {
        pre = n;
        n = n->next;
    }

    // Save the previous node information if prev is not (void*)0
    if (prev != (void*)0)
        *prev = pre;

    // Return the result; If it could not be found, the returned value is (void*)0
    return n;
}

// Dispose the incidence node
void incidence_remove(incidence* target, incidence* prev)
{
    if (!target) return;

    prev->next = target->next;

    free(target);
}

// Find a proper location and locate the new vertex in the array
int vertex_locate(vertex* vert, int vert_key, int vert_size)
{
    // Find a proper location to be inserted a new node
    // The vertex node which has key 0 means 
    // it is a vacant element in the array in this implementation
    int idx = vertex_find(vert, 0, vert_size);
    if (idx == -1) return -1;

    // Place a new vertex in the array
    vert[idx].name = vert_key;

    // Return the index where the new node is placed
    return idx;
}

// Find a proper location and locate the new edge in the array
int edge_locate(edge* edg, int key, int edge_size, int weight)
{
    // Find a proper location;
    // In this implementation, the vacant edge element in the array has -1 as its edge_key (or edge_num)
    int idx = edge_find(edg, -1, edge_size);
    if (idx == -1) return -1;

    // Place a new edge in the array
    edg[idx].num = (key == -2) ? idx : key;
    edg[idx].weight = weight;

    // Return the index where the new node is placed
    return idx;
}

// Find a proper location and locate the new incidence node in the array
void incidence_locate(incidence* header, edge* edge_target, vertex* opposite)
{
    incidence* node = header;

    // Move while node->next is not null and node->next->vert_key is smaller than the argument vert_key
    while (node->next && node->next->opposite->name < opposite->name)
        node = node->next;

    // Create a new incidence node
    incidence* n = incidence_creat(edge_target, opposite);

    // Place the node
    n->next = node->next;
    node->next = n;
}

// Insert incidence nodes in two vertice
void incidence_insert(vertex* vert, edge* edg, int source_idx, int destination_idx,
    int edge_num)
{
    // Insert a new incidence node in the outbound incidence list which is located in the source vertex
    incidence_locate(vert[source_idx].outbound_header, &edg[edge_num], &vert[destination_idx]);
    vert[source_idx].outbound_count++;

#ifdef UNDIGRAPH
    // If this implementation is not for a digraph, inbound incidence list in the source vertex must also contain the same information
    // But they are sharing the same edge
    incidence_locate(vert[source_idx].inbound_header, &edg[edge_num], &vert[destination_idx]);
    vert[source_idx].inbound_count++;
#endif

#ifdef UNDIGRAPH
    // For the self-loop to prevent duplicate information
    if (source_idx == destination_idx) return;
#endif

    // Insert a new incidence node in the inbound incidence list of the destination vertex
    incidence_locate(vert[destination_idx].inbound_header, &edg[edge_num], &vert[source_idx]);
    vert[destination_idx].inbound_count++;

#ifdef UNDIGRAPH
    // If this implementation is not for a digraph, outbound incidence list in the destination vertex must also have the same information
    // But they are sharing the same edge
    incidence_locate(vert[destination_idx].outbound_header, &edg[edge_num], &vert[source_idx]);
    vert[destination_idx].outbound_count++;
#endif

#ifdef TOPOSORT
    // Sync the number of degree of the destincation vertex
    vert[destination_idx].degree++;
#endif
}

// Get rid of incidence nodes to disconnect two vertice and returns the obsolete edge 
edge* incidence_disconnect(vertex* vert, edge* edg, int source_idx, int destination_idx)
{
    // Find the incidence node to be deleted in the source vertex
    // prev node to help the removal work
    incidence* prev;
    incidence* target = incidence_find(vert[source_idx].outbound_header, &prev, vert[destination_idx].name);
    // Returns NULL if the targeted one is not found
    if (!target) return (void*)0;

    // Remove the node
    incidence_remove(target, prev);
    vert[source_idx].outbound_count--;
#ifdef UNDIGRAPH
    // In the undirected graph implemetation, inbound information must also be deleted
    target = incidence_find(vert[source_idx].inbound_header, &prev, vert[destination_idx].name);
        if (!target) return (void*)0;

    incidence_remove(target, prev);
    vert[source_idx].inbound_count--;
#endif

    // Find the incidence node to be deleted in the inbound incidence list of destination vertex
    target = incidence_find(vert[destination_idx].inbound_header, &prev, vert[source_idx].name);
    if (!target) return (void*)0;

    // Get the edge node to be removed
    edge* rt = target->edge;

    // Remove the found node
    incidence_remove(target, prev);
    vert[destination_idx].inbound_count--;
#ifdef TOPOSORT
    // Sync between the degree and the inbound count
    vert[destination_idx].degree--;
#endif
#ifdef UNDIGRAPH
    // Find the incidence node to be deleted in the outbound incidence list of destination vertex
    target = incidence_find(vert[destination_idx].outbound_header, &prev, vert[source_idx].name);
    if (!target) return (void*)0;

    incidence_remove(target, prev);
    vert[destination_idx].outbound_count--;
#endif

    // Return the edge
    return rt;
}

// Make a new connection between two vertice
void connect(vertex* vert, edge* edg, int src, int dest, int vert_arr_size, int edge_arr_size, int weight)
{
    // Exit this function if any argument is invalid
    if (src < 1 || dest < 1) return;

    // Find the location of vertex which contains the value of argument in the array
    int src_idx = vertex_find(vert, src, vert_arr_size);
    int dest_idx = vertex_find(vert, dest, vert_arr_size);

    // Get a proper edge location
    int edg_idx = edge_locate(edg, -2, edge_arr_size, weight);

    // if any vertice were not found or the edge slot is full, Terminate this call
    if (src_idx == -1 || dest_idx == -1 || edg_idx == -1)
        return;

    // Make a new connection
    incidence_insert(vert, edg, src_idx, dest_idx, edg_idx);

    // Make a new edge
    edg[edg_idx].source = vert + src_idx;
    edg[edg_idx].destination = vert + dest_idx;
}

// Remove the connection between two vertice
void disconnect(vertex* vert, edge* edg, int src, int dest, int vert_arr_size, int edge_arr_size)
{
    // Exit this function if any argument is invalid
    if (src < 1 || dest < 1) return;

    // Find each node's location
    int source_idx = vertex_find(vert, src, vert_arr_size);
    int destination_idx = vertex_find(vert, dest, vert_arr_size);

    // Cut the connection and get the obsolete edge
    edge* edge = incidence_disconnect(vert, edg, src, dest);
    if (!edge) return;

    // Remove the useless edge
    edge->source = edge->destination = (void*)0;
    edge->num = -1;
    edge->weight = 0;
}

// Release all resources of graph
void free_all(vertex* vert, edge* edg, int vert_arr_size, int edge_ver_size)
{
    for (int i = 0; i <= vert_arr_size; i++)
    {
        // Remove all incidence nodes
        while (vert[i].inbound_count > 0)
        {
            incidence_remove(vert[i].inbound_header->next, vert[i].inbound_header);
            vert[i].inbound_count--;
        }
        free(vert[i].inbound_header);

        while (vert[i].outbound_count > 0)
        {
            incidence_remove(vert[i].outbound_header->next, vert[i].outbound_header);
            vert[i].outbound_count--;
        }
        free(vert[i].outbound_header);
    }

    free(vert);
    free(edg);
}

#ifdef TOPOSORT

// Topological sort
void topological_sort(vertex* vert, edge* edg, int vert_arr_size, int edge_arr_size)
{
    queue* q = queue_new();
    queue* result = queue_new();
    int topo_num = 1;

    // Find non-degree nodes and enqueue
    for (int i = 1; i <= vert_arr_size; i++)
        if (!vert[i].degree)
            queue_enqueue(q, vert + i);

    // Loop while the queue q is not empty
    while (!queue_is_empty(q))
    {
        // Remove a vertex from the queue q
        vertex* v = queue_dequeue(q);
        // Enqueue it to another queue to print sorted vertice information
        queue_enqueue(result, v);
        topo_num++;

        // Find outbound connections of the vertex
        incidence* inc = v->outbound_header->next;
        while (inc)
        {
            // Find an opposite and decrement its degree
            vertex* opposite = inc->edge->destination;
            opposite->degree--;
            // If its degree is zero, enqueue
            if (!opposite->degree)
                queue_enqueue(q, opposite);
            inc = inc->next;
        }
    }

    // Indicate that the cycle is exist in the graph
    if (topo_num <= vert_arr_size)
        puts("0");
    else // No cycles
    {
        // Print sorted vertice information
        while (!queue_is_empty(result))
        {
            vertex* v = queue_dequeue(result);
            printf("%c ", v->name);
        }
        putchar('\n');
    }

    // Dispose the queue
    queue_free(q);
    queue_free(result);
}
#endif
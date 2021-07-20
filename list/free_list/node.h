#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <string.h>

typedef struct __node {
    int val;
    struct __node* next;
} node_t;

/**
 * alloc a node
 */
node_t* node_init()
{
    node_t* node;
    node = (node_t*)malloc(sizeof(node_t));
    if (!node) {
        return NULL;
    }
    memset(node, 0, sizeof(node_t));
    return node;
}

/**
 * return the reference of node->next
 */
void** node_get_ref_of_next(void* node)
{
    return (void**)&((node_t*)node)->next;
}

/**
 * return node->next
 */
void* node_get_next(void* node)
{
    return ((node_t*)node)->next;
}

/** 
 * let node_a->next = node_b
 */
int node_link(void *a, void* b)
{
    if (!a) return 1;
    ((node_t*)a)->next = (node_t*)b;
    return 0;
}

#endif

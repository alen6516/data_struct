#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <string.h>

typedef struct __node {
    int val;
    struct __node *next;
} node_t;
#define NODE_SIZE sizeof(node_t)
#define NODE_MALLOC() (node_t*)malloc(NODE_SIZE)


node_t* node_init()
{
    node_t *node;
    node = NODE_MALLOC();
    if (!node) {
        return NULL;
    }
    memset(node, 0, NODE_SIZE);
    return node;
}

void** node_get_ref_of_next(void *node)
{
    return (void**)&((node_t*)node)->next;
}

void* node_get_next(void *node)
{
    return ((node_t*)node)->next;
}

int node_link(void *a, void *b)
{
    if (!a) return 1;
    ((node_t*)a)->next = (node_t*)b;
    return 0;
}
#endif

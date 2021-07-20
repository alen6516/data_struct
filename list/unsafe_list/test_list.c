#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "list.h"
#include "node.h"

#define LEN 2

list_t* list;

int main ()
{
    node_t *root = node_init();
    if (!root) {
        printf("node mallc fail\n");
    }

    list = list_init();
    printf("&list->head: %p, list->next: %p\n", &list->head, list->next);

    node_t* node;
    void *out;
    node = node_init();
    if (!node) {
        printf("node mallc fail\n");
    }
    node->val = 1;

    list_enqueue(list, (void*)node, (void**)&node->next);
    printf("put %d, node addr: %p\n", node->val, node);
    printf("ref of node next: %p, list next: %p\n", &node->next, list->next);

    out = list_dequeue(list, node_get_next);
    printf("take %d, node addr: %p\n", ((node_t*)out)->val, out);
    printf("&list->head: %p, list next: %p\n", &list->head, list->next);
}

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

    list = list_init((void*)root, node_get_ref_of_next(root));
    printf("ref of root next: %p, list next: %p\n", &root->next, list->next);

    node_t* node;
    void *out;
    node = node_init();
    if (!node) {
        printf("node mallc fail\n");
    }
    node->val = 1;

    list_enqueue(list, (void*)node, (void**)&node->next);
    printf("put %d, node addr: %p\n", node->val, node);
    printf("root->next val: %p\n", node_get_next(list->root));
    printf("ref of node next: %p, list next: %p\n", &node->next, list->next);

    out = list_dequeue(list, node_get_next, node_link, node_get_ref_of_next);
    printf("take %d, node addr: %p\n", ((node_t*)out)->val, out);
    printf("root->next val: %p\n", node_get_next(list->root));
    printf("ref of root next: %p, list next: %p\n", &root->next, list->next);
}

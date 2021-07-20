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
    node_t* root = node_init();

    list = list_init((void*)root, node_get_ref_of_next);

    node_t* node;
    void* out;
    node = node_init();
    node->val = 1;

    list_put(list, (void*)node, (void**)&node->next);
    printf("put %d, node addr: %p\n", node->val, node);
    printf("root->next val: %p\n", node_get_next(list->root));

    out = list_take(list, node_get_next, node_link, node_get_ref_of_next);
    printf("take %d\n", ((node_t*)out)->val);
    printf("root->next val: %p\n", node_get_next(list->root));



    node = node_init();
    node->val = 2;

    list_put(list, (void*)node, (void**)&node->next);
    printf("put %d, node addr: %p\n", node->val, node);
    printf("root->next val: %p\n", node_get_next(list->root));


    out = list_take(list, node_get_next, node_link, node_get_ref_of_next);
    if (out) {
        printf("take %d\n", ((node_t*)out)->val);
        printf("root->next val: %p\n", node_get_next(list->root));
        free(out);
    }
}


#ifndef MESD_LIST_H
#define MESD_LIST_H

#include <stdlib.h>
#include <string.h>


typedef struct __list {
    void *root;
    void ** next;
    // _Atomic unsigned len;
    
} list_t;
#define LIST_SIZE   sizeof(list_t)
#define LIST_MALLOC() (list_t*) malloc(LIST_SIZE)


/** Allocate and reset list_t obj.
 *  @param root: Dummy node for the list obj.
 *  @param node_get_ref_of_next: fn of node obj to get the reference of node->next, that is, &node->next.
 *  @return: Return list_t obj, or NULL in failure.
 */
list_t* list_init(void *root, void** ref_of_root_next)
{
    if (!ref_of_root_next) return NULL;

    list_t *list = LIST_MALLOC();
    if (!list) {
        return NULL;
    }

    list->root = root;
    list->next = ref_of_root_next;
    return list;
}

/** Enqueue the node to the list.
 *  @param list: The target list obj.
 *  @param node: The target node obj.
 *  @param next: The reference of the reference of the input node obj.
 *  @return: Return 0 in success, -1 in failure. 
 */
int list_enqueue(list_t *list, void *node, void **next)
{
    if (!list || !node || !next) {
        return -1;
    }

    void **_next;
    do {
        _next = list->next;
    } while (!__sync_bool_compare_and_swap(&list->next, _next, next));

    *_next = node;
    return 0;
}

/** Dequeue the node from the list
 */
void* list_dequeue(list_t *list, void* (node_get_next)(void*), int (node_link)(void*, void*), void** node_get_ref_of_next(void*))
{
    if (!list || 
        !node_get_next || 
        !node_link || 
        !node_get_ref_of_next || 
        !node_get_next(list->root)) return NULL;

    void *ret = NULL;

    ret = node_get_next(list->root);
    if (!ret) {
        return NULL;
    }
    
    node_link(list->root, node_get_next(ret));
    __sync_bool_compare_and_swap(&list->next, node_get_ref_of_next(ret), node_get_ref_of_next(list->root));
    return ret;
}


#endif /* MESD_LIST_H */

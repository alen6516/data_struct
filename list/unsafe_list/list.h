#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>


typedef struct __list {
    void *head;     // the first node
    void **next;    // &(last_node->next)
    // _Atomic unsigned len;
    
} list_t;
#define LIST_SIZE   sizeof(list_t)
#define LIST_MALLOC() (list_t*) malloc(LIST_SIZE)


/** Allocate and reset list_t obj.
 *  @return: Return list_t obj, or NULL in failure.
 */
list_t* list_init()
{
    list_t *list = LIST_MALLOC();
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->next = &list->head;

    return list;
}

/** Enqueue the node to the list.
 *  @param list: The target list obj.
 *  @param node: The target node obj.
 *  @param node_next: The reference of the next of the input node obj.
 *  @return: Return 0 in success, -1 in failure. 
 */
int list_enqueue(list_t *list, void *node, void** node_next)
{
    if (!list || !node) {
        return -1;
    }

    *(list->next) = node;
    list->next = node_next;
    return 0;
}

/** Dequeue the node from the list
 */
void* list_dequeue(list_t *list, void* node_get_next(void*))
{
    if (!list ||
        !node_get_next) return NULL;

    void *ret, *ret_next;

    ret = list->head;
    if (!ret) {
        return NULL;
    } else {
        ret_next = node_get_next(ret);
    }

    list->head = ret_next;
    if (!ret_next) {
        list->next = &list->head;
    }

    return ret;
}

#endif /* LIST_H */

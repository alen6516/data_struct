#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "arr.h"
#include "tree.h"


void
node_show(Node *node)
{
    printf("%d", node->val);
}

void
arr_show_obj(void **arr, int len, void (*obj_show)(void *))
{
    if (!arr || len < 1) return;

    printf("arr = [ ");
    obj_show(arr[0]);
    for (int i=1; i<len; i++) {
        printf(", ");
        if (!arr[i]) {
            printf("XX");
        } else {
            obj_show(arr[i]);
        }
    }
    printf("]\n");
}

/**
 * Extend the nodes in the tree to a completed binary tree
 * and put into an array
 */
static void
tree_to_array(Node *node, Node **arr, int idx)
{
    arr[idx-1] = node;
    if (node->left) {
        tree_to_array(node->left, arr, 2*idx);
    }
    if (node->right) {
        tree_to_array(node->right, arr, 2*idx+1);
    }
}

static void
tree_show_array(Node **arr, int len, void (node_show(Node*)))
{
    int idx;
    for (int i=1; (1<<i)-1 <= len; i++) {
        for (int j=0; j<(1<<(i-1)); j++) {
            idx = (1<<(i-1))-1+j;
            //printf("%d\n", idx);
            if (arr[idx]) {
                printf("%2d  ", arr[idx]->val);
            } else {
                printf("XX  ");
            }
        }
        printf("\n");
    }
}

/**
 * Prepare an array to contain the completed binary tree,
 * and show the array
 */
void
tree_show(Tree *tree)
{
    if (!tree) return;
    
    printf("tree depth: %d\n", tree->depth);
    printf("tree node num: %d\n", tree->num);

    Node **arr;
    int len = (1 << (tree->depth)) -1;
    arr = (Node **)malloc(sizeof(Node*) * len);
    memset(arr, 0, sizeof(Node*)*len);

    tree_to_array(tree->root, arr, 1);

    //arr_show_obj((void**)arr, len, node_show);
    tree_show_array(arr, len, node_show);

    free(arr);
}

static void
tree_free_node(Node *node)
{
    if (!node) return;

    if (node->right) {
        tree_free_node(node->right);
    }
    if (node->left) {
        tree_free_node(node->left);
    }
    free(node);
}

void
tree_free(Tree *tree)
{
    if (!tree) return;

    tree_free_node(tree->root);

    free(tree);
}

/**
 * Create a binary tree with a given array
 */
Tree *
tree_create_by_array(
    int *arr,
    int len)
{
    if (!arr || len < 0) return NULL;


    Tree *tree = (Tree *)malloc(sizeof(tree));
    if (!tree) {
        goto err;
    }

    tree->root = NULL;
    
    Node *curr;
    Node **next;

    int max_depth = 1;
    int curr_depth;

    for (int i=0; i<len; i++) {
        curr = (Node *)malloc(sizeof(Node));
        if (!curr) {
            goto err;
        }

        curr->val = arr[i];
        next = &tree->root;
        curr_depth = 1;
        while (*next) {
            curr_depth ++;
            if (curr->val > (*next)->val) {
                next = &(*next)->right;
            } else {
                next = &(*next)->left;
            }
        }
        *next = curr;
        
        if (curr_depth > max_depth) {
            max_depth = curr_depth;
        }
    }

    tree->num = len;
    tree->depth = max_depth;
    return tree;

err:
    if (tree) {
        tree_free(tree);
    }
} 

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int len = 5;
    int *arr;

    // only specify the length of the input array
    if (argc == 2) {
        len = (int)strtol(argv[1], NULL, 10);
        arr = (int *)malloc(sizeof(int) * len);
        for (int i=0; i<len; i++) {
            arr[i] = rand() % 20;
        }

    // specify individual number of the array
    } else {
        len = argc-1;
        arr = (int *)malloc(sizeof(int) * len);
        for (int i=0; i<len; i++) {
            arr[i] = (int)strtol(argv[i+1], NULL, 10);
        }
    }

    arr_show(arr, len);

    Tree *tree = tree_create_by_array(arr, len);

    tree_show(tree);
}

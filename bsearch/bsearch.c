#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

/*
 * make a binary search tree which can balance itself after insertion/removal
 */

#define MAX_NUM 20

typedef struct __node {
    union {
        int val;
        int key;
    };
    struct __node *left;
    struct __node *right;
} Node;

/**
 * compare the key of node a and b,
 * return 1 if a>b,
 *        2 if b>a,
 *        0 if a=b,
 *       -1 if a or b is NULL
 */
int node_compare(Node *a, Node *b)
{
    if (!a || !b) return -1;

    if (a->key > b->key) {
        return 1;
    } else if (a->key < b->key) {
        return 2;
    } else {
        return 0;
    }
}

typedef struct __btree {
    Node *head;
    //int len;
} Btree;

static void btree_recurvie_print(Node *node)
{
    if (!node) return;

    btree_recurvie_print(node->right);
    printf("%d, ", node->val);
    btree_recurvie_print(node->left);
}

/**
 * just for print
 */
void btree_show(Btree *btree)
{
    if (!btree || !btree->head) return;

    printf("[");
    btree_recurvie_print(btree->head);
    printf("]\n");
}

/**
 * find the right place and append the node
 */
int btree_insert(Btree *btree, Node *node, int (*node_compare)(Node*, Node*))
{
    if (!btree || !node) return -1;

    if (!btree->head) {
        btree->head = node;
        return 0;

    } else {
        Node *curr = btree->head;
        
        while (1) {
            if (node->val < curr->val) {
                if (curr->left) {
                    curr = curr->left;
                } else {
                    curr->left = node;
                    return 0;
                }
            } else if (node->val > curr->val) {
                if (curr->right) {
                    curr = curr->right;
                } else {
                    curr->right = node;
                    return 0;
                }
            } else {
                // key already in the tree
                break;
            }
        }
        return -1;
    }
}

static Node *btree_find_replacement(Node *curr)
{
    if (!curr) return NULL;

    Node **next;

    if (!curr->right && !curr->left) {
        // curr is the last node
        return NULL;

    } else if (curr->right) {
        next = &curr->right;
        curr = curr->right;
        while (curr) {
            next = &curr->left;
            curr = curr->left;
        }
        *next = NULL;
        return curr;

    } else {
        next = &curr->left;
        curr = curr->left;
        while (curr) {
            next = &curr->right;
            curr = curr->right;
        }
        *next = NULL;
        return curr;
    }
}

Node *btree_remove(Btree *btree, int key)
{
    if (!btree || !btree->head) return NULL;

    Node *curr = btree->head;
    Node **prev_next = &btree->head;
    while (curr) {
        if (curr->key > key) {
            if (!curr->left) return NULL;
            prev_next = &curr->left;
            curr = curr->left;
        } else if (curr->key < key) {
            if (!curr->right) return NULL;
            prev_next = &curr->right;
            curr = curr->right;
        } else {
            Node *replacement = btree_find_replacement(curr);
            *prev_next = replacement;
            if (replacement) {
                replacement->right = curr->right;
                replacement->left = curr->left;
            }
            return curr;
        }
    }
}

Node *btree_lookup(Btree *btree, int key)
{
    if (!btree || !btree->head) return NULL;

    Node *curr = btree->head;   
    while (curr) {
        if (curr->key > key) {
            if (!curr->left) return NULL;
            curr = curr->left;
        } else if (curr->key < key) {
            if (!curr->right) return NULL;
            curr = curr->right;
        } else {
            return curr;
        }
    }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));

    int len = MAX_NUM; 
    if (argc == 2) {
        len = strtol(argv[1], NULL, 10);
        if (len > MAX_NUM) {
            len = MAX_NUM;
        }
    }

    Btree *btree = (Btree*) malloc(sizeof(Btree));
    memset(btree, 0, sizeof(Btree));

    int *arr = (int*) malloc(sizeof(int)*len);
    Node *node;
    for (int i=0; i<len; i++) {
        arr[i] = rand() % 100 + 1;
        node = (Node*) malloc(sizeof(Node));
        memset(node, 0, sizeof(Node));
        node->val = arr[i];
        if (-1 == btree_insert(btree, node, node_compare)) {
            printf("key already in the tree\n");
        }
    }

    printf("arr = [ %d", arr[0]);
    for (int i=1; i<len; i++) {
        printf(", %d", arr[i]);
    }
    printf("]\n");

    btree_show(btree);
}

#ifndef TREE_H
#define TREE_H

#include <unistd.h>
#include <time.h>

typedef struct __node {
    int val;
    struct __node *left;
    struct __node *right;
} Node;

typedef struct __tree {
    Node *root;
    int depth;      // depth of the tree, root is 1
    int num;        // number of the nodes in the tree
} Tree;

#endif

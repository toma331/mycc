#include "include/ast.h"
#include <stdlib.h>

Node *new_node(NodeType type, Node *left, Node *right, int value) {
    Node *n = malloc(sizeof(Node));
    n->type = type;
    n->left = left;
    n->right = right;
    n->value = value;
    return n;
}

void free_node(Node *n) {
    if (!n) return;
    free_node(n->left);
    free_node(n->right);
    free(n);
}


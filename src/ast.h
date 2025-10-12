#ifndef AST_H
#define AST_H

typedef enum {
    NODE_NUMBER,
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV,
    NODE_PRINT
} NodeType;

typedef struct Node {
    NodeType type;
    int value;               // для NODE_NUMBER
    struct Node *left;       // для бинарных операций
    struct Node *right;
} Node;

Node *new_node(NodeType type, Node *left, Node *right, int value);
void free_node(Node *n);

#endif


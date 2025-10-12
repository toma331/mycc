#include "parser.h"
#include "lexer.h"
#include <stdlib.h>

static Token cur;

static void next() { cur = lexer_next(); }

static Node *factor();
static Node *term();
static Node *expr();

static Node *make_number(int value) {
    return new_node(NODE_NUMBER, NULL, NULL, value);
}

static Node *factor() {
    if (cur.type == TOK_NUMBER) {
        Node *n = make_number(cur.value);
        next();
        return n;
    } else if (cur.type == TOK_LPAREN) {
        next();
        Node *n = expr();
        if (cur.type == TOK_RPAREN) next();
        return n;
    }
    return NULL;
}

static Node *term() {
    Node *n = factor();
    while (cur.type == TOK_STAR || cur.type == TOK_SLASH) {
        TokenType op = cur.type;
        next();
        Node *rhs = factor();
        n = new_node(op == TOK_STAR ? NODE_MUL : NODE_DIV, n, rhs, 0);
    }
    return n;
}

static Node *expr() {
    Node *n = term();
    while (cur.type == TOK_PLUS || cur.type == TOK_MINUS) {
        TokenType op = cur.type;
        next();
        Node *rhs = term();
        n = new_node(op == TOK_PLUS ? NODE_ADD : NODE_SUB, n, rhs, 0);
    }
    return n;
}

Node *parse() {
    next();
    if (cur.type == TOK_PRINT) {
        next();
        Node *inner = expr();
        return new_node(NODE_PRINT, inner, NULL, 0);
    }
    return expr();
}


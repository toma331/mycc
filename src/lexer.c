#include "include/lexer.h"
#include <ctype.h>
#include <string.h>

static const char *p;

void lexer_init(const char *src) {
    p = src;
}

static void skip_spaces() {
    while (*p == ' ' || *p == '\t' || *p == '\n') p++;
}

Token lexer_next() {
    skip_spaces();
    Token t = {0};
    if (*p == '\0') { t.type = TOK_EOF; return t; }

    if (isdigit(*p)) {
        t.type = TOK_NUMBER;
        t.value = 0;
        while (isdigit(*p)) {
            t.value = t.value * 10 + (*p - '0');
            p++;
        }
        return t;
    }

    if (strncmp(p, "print", 5) == 0 && !isalnum(p[5])) {
        p += 5;
        t.type = TOK_PRINT;
        return t;
    }

    switch (*p) {
        case '+': t.type = TOK_PLUS; p++; break;
        case '-': t.type = TOK_MINUS; p++; break;
        case '*': t.type = TOK_STAR; p++; break;
        case '/': t.type = TOK_SLASH; p++; break;
        case '(': t.type = TOK_LPAREN; p++; break;
        case ')': t.type = TOK_RPAREN; p++; break;
        default: t.type = TOK_EOF; p++; break;
    }
    return t;
}


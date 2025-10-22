#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOK_NUMBER,
    TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH,
    TOK_LPAREN, TOK_RPAREN,
    TOK_PRINT,
    TOK_EOF
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;

void lexer_init(const char *src);
Token lexer_next();

#endif


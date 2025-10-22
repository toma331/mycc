#include "include/codegen.h"
#include <stdio.h>

static void gen(Node *n, FILE *out) {
    if (!n) return;

    switch (n->type) {
        case NODE_NUMBER:
            fprintf(out, "    mov $%d, %%rax\n", n->value);
            fprintf(out, "    push %%rax\n");
            break;
        case NODE_ADD:
        case NODE_SUB:
        case NODE_MUL:
        case NODE_DIV:
            gen(n->left, out);
            gen(n->right, out);
            fprintf(out, "    pop %%rbx\n");
            fprintf(out, "    pop %%rax\n");
            switch (n->type) {
                case NODE_ADD: fprintf(out, "    add %%rbx, %%rax\n"); break;
                case NODE_SUB: fprintf(out, "    sub %%rbx, %%rax\n"); break;
                case NODE_MUL: fprintf(out, "    imul %%rbx, %%rax\n"); break;
                case NODE_DIV: fprintf(out, "    cqo\n    idiv %%rbx\n"); break;
                default: break;
            }
            fprintf(out, "    push %%rax\n");
            break;
        case NODE_PRINT:
            gen(n->left, out);
            fprintf(out, "    pop %%rdi\n");
            fprintf(out, "    mov $0, %%rax\n");
            fprintf(out, "    call print_int\n");
            break;
    }
}

void codegen(Node *root, const char *outfile) {
    FILE *out = fopen(outfile, "w");
    fprintf(out, ".global main\nmain:\n");
    gen(root, out);
    fprintf(out, "    mov $0, %%rax\n    ret\n");
    fprintf(out, "\nprint_int:\n"
                 "    mov %%rdi, %%rsi\n"
                 "    lea fmt(%%rip), %%rdi\n"
                 "    mov $0, %%rax\n"
                 "    call printf@PLT\n"
                 "    ret\n"
                 ".section .rodata\n"
                 "fmt: .string \"%%d\\n\"\n");
    fclose(out);
}


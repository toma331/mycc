#include <stdio.h>
#include <stdlib.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/codegen.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s file.my\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) { perror("fopen"); return 1; }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *src = malloc(size + 1);
    fread(src, 1, size, f);
    src[size] = '\0';
    fclose(f);

    lexer_init(src);
    Node *root = parse();

    codegen(root, "build/out.s");
    system("as -o build/out.o build/out.s");
    system("gcc build/out.o -o result");
    printf("compiling is done!!! \n");

    free(src);
    return 0;
}


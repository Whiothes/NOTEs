/**
 *   @file     cdecl.c
 *   @date     2020-02-09
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    The Piece of Code that Understandeth All Parsing
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTOKENS 100
#define MAXTOKENLEN 64

enum type_tag { IDENTIFIER, QUALIFIER, TYPE };

struct token {
    char type;
    char string[MAXTOKENLEN];
};

int top = -1;
struct token stack[MAXTOKENS];
struct token this;

#define pop stack[top--]
#define push(s) stack[++top] = s

/* 推断标识符的类型 */
enum type_tag classify_string(void) {
    char *s = this.string;
    if (strcmp(s, "const") == 0) {
        strcpy(s, "read-only");
        return QUALIFIER;
    }

    if (strcmp(s, "volatile") == 0) {
        return QUALIFIER;
    }
    if (strcmp(s, "void") == 0) {
        return TYPE;
    }
    if (strcmp(s, "char") == 0) {
        return TYPE;
    }
    if (strcmp(s, "signed") == 0) {
        return TYPE;
    }
    if (strcmp(s, "unsigned") == 0) {
        return TYPE;
    }
    if (strcmp(s, "short") == 0) {
        return TYPE;
    }
    if (strcmp(s, "int") == 0) {
        return TYPE;
    }
    if (strcmp(s, "long") == 0) {
        return TYPE;
    }
    if (strcmp(s, "float") == 0) {
        return TYPE;
    }
    if (strcmp(s, "double") == 0) {
        return TYPE;
    }
    if (strcmp(s, "struct") == 0) {
        return TYPE;
    }
    if (strcmp(s, "union") == 0) {
        return TYPE;
    }
    if (strcmp(s, "enum") == 0) {
        return TYPE;
    }

    return IDENTIFIER;
}

/* 读取下一个标记到 "this" */
void gettoken(void) {
    char *p = this.string;

    while ((*p = getchar()) == ' ')
        ;

    if (isalnum(*p)) {
        while (isalnum(*++p = getchar()))
            ;
        ungetc(*p, stdin);
        *p = '\0';
        this.type = classify_string();
        return;
    }

    if (*p == '*') {
        strcpy(this.string, "pointer to");
        this.type = '*';
        return;
    }

    this.string[1] = '\0';
    this.type = *p;
    return;
}

/* 理解所有分析过程的代码段 */
void read_to_first_identifier() {
    gettoken();
    while (this.type != IDENTIFIER) {
        push(this);
        gettoken();
    }
    printf("%s is ", this.string);
    gettoken();
}

void deal_with_arrays() {
    while (this.type == '[') {
        printf("array");
        gettoken();
        if (isdigit(this.string[0])) {
            printf("0..%d ", atoi(this.string) - 1);
            gettoken();
        }
        gettoken();
        printf("of ");
    }
}

void deal_with_function_args() {
    while (this.type != ')') {
        gettoken();
    }
    gettoken();
    printf("function returning ");
}

void deal_with_pointers() {
    while (stack[top].type == '*') {
        printf("%s ", pop.string);
    }
}

void deal_with_declarator() {
    switch (this.type) {
    case '[':
        deal_with_arrays();
        break;
    case '(':
        deal_with_function_args();
        break;
    }

    deal_with_pointers();

    while (top >= 0) {
        if (stack[top].type == '(') {
            pop;
            gettoken();
            deal_with_declarator();
        } else {
            printf("%s ", pop.string);
        }
    }
}

int main() {
    read_to_first_identifier();
    deal_with_declarator();
    printf("\n");
    return 0;
}

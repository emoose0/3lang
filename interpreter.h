#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "lexer.h"
#include <stdint.h>

typedef struct{
    token* tokens;
    token currentToken;

    uint8_t vars[3];

    int i; //to be used as index for tokens
    int currentVar; //current variable being referenced by default this is a
}interpreter;

int initInterpreter(token* tokenList, int count);
void print();
RESULT interpret();
void freeInterpreter();

#endif
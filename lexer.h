#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>

typedef enum{

    SUCCESS, INTERPRETING_ERROR, RUNTIME_ERROR

}RESULT;

typedef enum{
    INCREMENT, DECREMENT,
    LPAREN, RPAREN, //B actions
    LBRACK, RBRACK, //C actions
    LBRACE, RBRACE, //Loops
    INPUT, OUTPUT,

    END

}token;

typedef struct{
    token* tokens;
    int size; //size of token array
    int count; //count of tokens

    int LBRACECOUNT;
    int RBRACECOUNT;

    char* code;
    int i; //lexer code position
    char c; //current character
}lexer;

int initLexer(char* contents);
RESULT tokenise();
void printTokens();
RESULT startInterpreter();
void freeLexer();


#endif
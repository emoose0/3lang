#include <stdio.h>
#include "lexer.h"
#include "interpreter.h"

lexer* lex;

int initLexer(char* contents){
    lex = (lexer*)malloc(sizeof(lexer));
    if(lex == NULL){
        fprintf(stderr ,"ERR: NOT ENOUGH MEMORY TO MAKE LEXER");
        return -1;
    }
    lex->code = contents;

    if(lex->code == NULL){
        fprintf(stderr, "FILE IS NULL");
        return -1;
    }

    lex->i = 0;
    lex->c = lex->code[lex->i];

    lex->size = 4;
    lex->count = 0;
    lex->tokens = (token*)malloc(lex->size*(sizeof(token)));

    if(lex->tokens == NULL){
        fprintf(stderr, "ERR: NOT ENOUGH MEMORY TO MAKE TOKENS");
        return -1;
    }

    lex->LBRACECOUNT = 0;
    lex->RBRACECOUNT = 0;

    return 0;
}

int addToken(token type){
    if((lex->count*4) > lex->size){ //reallocating memory
        lex->size += 4;
        lex->tokens = realloc(lex->tokens, lex->size*(sizeof(token)));

        if(lex->tokens == NULL){
            fprintf(stderr, "ERR: NOT ENOUGH MEMORY TO ALLOCATE MORE TOKENS");
            return -1;
        }
    }
    lex->tokens[lex->count++] = type; 

    return 0;
}

void lexerAdvance(){
    lex->i++;
    lex->c = lex->code[lex->i];
}

RESULT tokenise(){
    while(lex->c != '\0'){
        //printf("|%c|",lex->c);
        switch(lex->c){
            case '+':
                if(addToken(INCREMENT) == -1){
                    return INTERPRETING_ERROR;
                }
            break;
            case '-':
                if(addToken(DECREMENT) == -1){
                    return INTERPRETING_ERROR;
                }
            break;

            case '(':
                if(addToken(LPAREN) == -1){
                    return INTERPRETING_ERROR;
                }
            break;
            case ')':
                if(addToken(RPAREN) == -1){
                    return INTERPRETING_ERROR;
                }
            break;

            case '[':
                if(addToken(LBRACK) == -1){
                    return INTERPRETING_ERROR;
                }
            break;
            case ']':
                if(addToken(RBRACK) == -1){
                    return INTERPRETING_ERROR;
                }
            break;

            case '{':
                if(addToken(LBRACE) == -1){
                    return INTERPRETING_ERROR;
                }
                lex->LBRACECOUNT++;
            break;
            case '}':
                if(addToken(RBRACE) == -1){
                    return INTERPRETING_ERROR;
                }
                lex->RBRACECOUNT++;
            break;

            case ',':
                if(addToken(INPUT) == -1){
                    return INTERPRETING_ERROR;
                    break;
                }
            break;
            case '.':
                if(addToken(OUTPUT) == -1){
                    return INTERPRETING_ERROR;
                    break;
                }
            break;
        }
        lexerAdvance();
    }
    addToken(END);
    lex->tokens = realloc(lex->tokens, lex->count*(sizeof(token)));

    if(lex->LBRACECOUNT < lex->RBRACECOUNT){
        fprintf(stderr, "ERR: STRAY } FOUND WHEN TOKENISING");
        return INTERPRETING_ERROR;
    } else if(lex->LBRACECOUNT > lex->RBRACECOUNT){
        fprintf(stderr, "ERR: MISSING }");
        return INTERPRETING_ERROR;
    }

    return SUCCESS;
}

void printTokens(){
    for(int i = 0; i < lex->count; i++){
        printf("%d ", lex->tokens[i]);
    }
}

RESULT startInterpreter(){
    initInterpreter(lex->tokens, lex->count);
    return interpret();
}

void freeLexer(){
    free(lex->code);
    free(lex->tokens);
    free(lex);
    lex->tokens = NULL;
    lex->code = NULL;
    lex = NULL;
}
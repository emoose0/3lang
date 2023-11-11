#include <stdio.h>
#include "interpreter.h"
#define STACKMAX 1000

interpreter* tri; //stands for 3langinterpreter idk why but i call it trilly in my head this is trilly now

const int a = 0, b = 1, c = 2; //variables are stored in an array, this is a way to keep track of them

int top = -1;
int stack[STACKMAX]; //stack for loops

int push(int data){
    if(top != STACKMAX-1){
        top++;
        stack[top] = data;

        return 0;
    } else{
        fprintf(stderr, "ERR: STACK FULL, COULD NOT DO LOOP");
        return -1;
    }
}

int pop(){
    if(top == -1){
        return -1;
    }else{
        return stack[top];
        top--;
    }
}


int initInterpreter(token* tokenList, int count){
    tri = (interpreter*)malloc(sizeof(interpreter));
    if(tri == NULL){
        fprintf(stderr, "ERR: NOT ENOUGH MEMORY TO CREATE INTERPRETER");
        return -1;
    }
    tri->tokens = tokenList;
    tri->i = 0;
    for(int i = 0; i < STACKMAX; i++){
        if(i < 3) tri->vars[i] = 0;

        stack[i] = 0;
    }
    tri->currentToken = tri->tokens[tri->i];
    tri->currentVar = a;

    return 0;
}

void triNext(){
    tri->i++;
    tri->currentToken = tri->tokens[tri->i]; 
}

RESULT interpret(){
    int lBraceCount = 0;
    while(tri->currentToken != END){
        switch(tri->currentToken){
            case INCREMENT:;
                tri->vars[tri->currentVar]++;
                break;
            case DECREMENT:
                tri->vars[tri->currentVar]--;
                break;
            
            case LPAREN:
                tri->currentVar = b;
                break;
            case RPAREN:
                tri->currentVar = a;
                break;

            case LBRACK:
                tri->currentVar = c;
                break;
            case RBRACK:
                tri->currentVar = a;
                break;

            case INPUT:
                printf("%c", tri->vars[tri->currentVar]);
                break;
            case OUTPUT:
                tri->vars[tri->currentVar] = getchar();
                while(getchar() != '\n'); //flush input buffer
                break;
            
            case LBRACE:
                if(tri->vars[tri->currentVar] == 0){
                    lBraceCount++;
                    while(lBraceCount != 0){
                        triNext();
                        if(tri->currentToken == LBRACE) lBraceCount++;
                        else if(tri->currentToken == RBRACE) lBraceCount--; 

                        if(lBraceCount == 0){
                            break;
                        }
                    }
                }else{
                    if(push(tri->i) == -1){
                        return RUNTIME_ERROR;
                    }
                }
                break;
            case RBRACE:
                if(tri->vars[tri->currentVar] != 0){
                    tri->i = pop();
                    if(tri->i == -1){
                        fprintf(stderr, "ERR: STRAY } BRACE");
                        return RUNTIME_ERROR;
                    }else{
                        tri->currentToken = tri->tokens[tri->i];
                    }
                }
                break;

            case END:
                return SUCCESS;
        }
        triNext();
    }
    return SUCCESS;
}

void print(){
    printf("\n\na: %d b: %d c: %d", tri->vars[a], tri->vars[b], tri->vars[c]);
}

void freeInterpreter(){
    free(tri);
    tri = NULL;
}
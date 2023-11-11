#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.h"
#include "interpreter.h"

bool checkName(const char* filename){ //stupid function to check if extension is .3
    char* dot = strrchr(filename, '.');
    char* extension = ".3";

    if(dot == NULL){ //you might be wondering why we need this. without this some thingy happens and the entire freaking program stops working
        return false;
    }
    else if(strcmp(dot, extension) == 0){
        return true;
    }
    return false;

}

int main(int argc, char* argv[]){
    bool r = true; //if results should be shown
    char* filename;
    int size = 10;
    char* code = (char*)malloc(size);
    char c;
    int count = 0;

    if(argc < 2){
        printf("usage: 3l file.3 -r");
    } else{
        if(argc == 3){
            if(strcmp(argv[2], "-r") == 0) r = false;
            else{ 
                fprintf(stderr, "ERR: INVALID ARG '%s", argv[2]);
                return -1;
            }
        }
        filename = argv[1];

        if(checkName(filename)){
            FILE* file;
            if((file = fopen(filename, "r")) != NULL){ //checking if file exists
                while((c = fgetc(file)) != EOF){
                    if(count > size-1){
                        size += 10;
                        code = realloc(code, size); //reallocation of code if length of file exceeds size of code array
                        if(code == NULL){
                            fprintf(stderr, "OUT OF MEMORY CANT READ FILE");
                            return -1;
                        }
                    }
                    code[count++] = c;
                }
                code = realloc(code, size+1);
                code[count++] = '\0';
                code = realloc(code, strlen(code)+1); //final reallocation in case size of pointer is bigger than number of elements in array

                if(code == NULL){
                    fprintf(stderr, "ERR: RAN OUT OF MEMORY WHEN READING FILE");
                    return -1;
                }
                
                fclose(file);
                file = NULL;
                
                if(initLexer(code) == 0){
                    if(tokenise() == SUCCESS){
                        //printTokens();
                        if(startInterpreter() == SUCCESS){
                            if(r){
                                print();
                            }
                        }
                    }
                    freeInterpreter();
                }
                freeLexer();
            }else{
                fprintf(stderr, "ERR: FILE DOES NOT EXIST");
            }
        }else{
            fprintf(stderr, "ERR: INCORRECT FILE TYPE [MAKE SURE FILE HAS .3 EXTENSION]");
        }
    }

    printf("\n");

    return 0;
}
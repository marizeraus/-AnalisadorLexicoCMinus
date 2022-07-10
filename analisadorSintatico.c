#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum tokenType {
    EMPTY = 0,
    INT,
    VOID,
    ID,
    OPENPAREN,
    CLOSEPAREN,
    OPENCHAVES,
    CLOSECHAVES,
    OPENCOLCHETE,
    CLOSECOLCHETE,
    COMMA,
    NUMTOKEN,
    SEMICOLON
};
typedef struct
{
	char valor[50];
	enum tokenType tipo;
} Token;

static Token currToken;
int tokenPos = 0;

int program(Token * tokens);
int declarationList(Token * tokens);
int declarationListLinha(Token * tokens);
int declaration(Token * tokens);
int varDeclaration(Token * tokens);
int numVarDec(Token * tokens);
int typeSpec(Token * tokens);
int funDec(Token * tokens);
int paramList(Token * tokens);
int paramListLinha(Token * tokens);
int param(Token * tokens);
int params(Token * tokens);
int paramLinha(Token * tokens);
int compoundStmt(Token * tokens);
int localDec(Token * tokens);
int localDecLinha(Token * tokens);
int stmtList(Token * tokens);
int stmtListLinha(Token * tokens);
int stmt(Token * tokens);
int expStmt(Token * tokens);
int selecStmt(Token * tokens);
int elseStmt(Token * tokens);
int iterationStmt(Token * tokens);
int returnStmt(Token * tokens);
int returnExp(Token * tokens);
int expression(Token * tokens);
int var(Token * tokens);
int varExp(Token * tokens);
int simpleExp(Token * tokens);
int relop(Token * tokens);
int addExp(Token * tokens);
int addExpLinha(Token * tokens);
int addop(Token * tokens);
int term(Token * tokens);
int termLinha(Token * tokens);
int mulOp(Token * tokens);
int factor(Token * tokens);
int call(Token * tokens);
int args(Token * tokens);
int argList(Token * tokens);
int argListLinha(Token * tokens);

void consomeToken(Token* tokens){
    tokenPos++;
    currToken = tokens[tokenPos];
}
int program(Token * tokens){
    return declarationList(tokens);
}

int declarationList(Token* tokens){
    return declarationListLinha(tokens);
}

int declarationListLinha(Token* tokens){
    int i = declaration(tokens);
    while(currToken.tipo != EMPTY && i){

        i = declaration(tokens) && i;
        printf("TOKEN: %s", currToken.valor);
        consomeToken(tokens);
    }
    return i;
}

int declaration(Token* tokens){
    if(typeSpec(tokens)){
        consomeToken(tokens);
        if(currToken.tipo == ID){
            consomeToken(tokens);
            printf("ID\n");
            if(currToken.tipo == OPENPAREN){ // is functino
                return funDec(tokens);
            } else {
                printf("NUMDECL\n");

                if(numVarDec(tokens)){
                    printf("NUMVARDEC %d\n", currToken.tipo);
                    if(currToken.tipo == SEMICOLON){
                        consomeToken(tokens);
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int typeSpec(Token* tokens){
    if(currToken.tipo == INT || currToken.tipo == VOID){
        return 1;
    }
    return 0;
}

int numVarDec(Token * tokens){
    if(currToken.tipo == OPENCOLCHETE){
        printf("OPENC %d\n", currToken.tipo);
        printf("%d\n", tokens[3].tipo);
        consomeToken(tokens);
        printf("%d\n", currToken.tipo);
        if(currToken.tipo == NUMTOKEN){
        printf("NUM\n");

            consomeToken(tokens);
            if(currToken.tipo == CLOSECOLCHETE){
                consomeToken(tokens);
                    return 1;
                }
            }
        }
    if(currToken.tipo == EMPTY){
        return 1;
    }
    return 0;
}

int funDec(Token * tokens){
    if(currToken.tipo == OPENPAREN){
        consomeToken(tokens);
        int i = params(tokens);
        if(i) {
            if(currToken.tipo == CLOSEPAREN){
                consomeToken(tokens);
                return compoundStmt(tokens);
            }
        }
    }
    return 0;
}

int params(Token * tokens){
    if(currToken.tipo == VOID) {
        consomeToken(tokens);
        return 1;
    } else {
        return paramList(tokens);
    }
}

int paramList(Token * tokens){
    int i = param(tokens);
    if(i) {
        consomeToken(tokens);
        return paramListLinha(tokens);
    }
    return i;
}

int paramListLinha(Token * tokens){
    if(currToken.tipo == EMPTY) return 1;
    if(currToken.tipo == COMMA) {
        consomeToken(tokens);
        int i = param(tokens);
        if(i){
            consomeToken(tokens);
            return paramListLinha(tokens);
        }
    } else {
        return param(tokens);
    }
}
int param(Token * tokens){
    if(typeSpec(tokens)){
        consomeToken(tokens);
        if(currToken.tipo == ID){
            consomeToken(tokens);
            return paramLinha(tokens);
        }
    }
    return 0;
}

int paramLinha(Token* tokens){
    if(currToken.tipo == EMPTY) return 1;
    else {
        if(currToken.tipo == OPENCOLCHETE){
            consomeToken(tokens);
            if(currToken.tipo == CLOSECOLCHETE){
                return 1;
            }
        }
    }
    return 0;
}

int compoundStmt(Token * tokens){
    
}

int main(int argc, char *argv[ ]){

    printf("INIT\n\n");
    Token teste;
    strcpy( teste.valor, "int");
    teste.tipo = INT;
    Token empty;
    Token teste2;
    Token teste3;
    Token teste4;
    Token teste5;
    Token teste6;
    strcpy( teste2.valor, "main");
    teste2.tipo = ID;
    strcpy( empty.valor, "token");
    empty.tipo = OPENCOLCHETE;
    teste3.tipo = NUMTOKEN;
    teste4.tipo = CLOSECOLCHETE;
    teste5.tipo = SEMICOLON;
    teste6.tipo = EMPTY;
    Token* tokens = (Token*)malloc(10 * sizeof(Token));
    tokens[0] = teste;
    tokens[1] = teste2;
    tokens[2] = empty;
    tokens[3] = teste3;
    tokens[4] = teste4;
    tokens[5] = teste5;
    tokens[6] = teste6;
    printf("%d\n", teste3.tipo);
    currToken = tokens[0];
    printf("%d", program(tokens));

}



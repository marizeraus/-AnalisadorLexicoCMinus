#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum tokenType {
    EMPTY = 1,
    INT,
    VOID,
    ID,
    OPENPAREN,
    CLOSEPAREN,
    OPENCHAVES,
    CLOSECHAVES,
    OPENCOLCHETE,
    CLOSECOLCHETE
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
            if(currToken.tipo == OPENPAREN){ // is functino
                return 1; //funDec(tokens);
            } else {
                return 1; //numVarDec(tokens);
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

int funDec(Token * tokens){
    if(currToken.tipo == OPENPAREN){
        consomeToken(tokens);
        int i = 1; //params(tokens);
        if(i) {
            consomeToken(tokens);
            if(currToken.tipo == CLOSEPAREN){
                return 1;
            }
        }
    }
    return 0;
}


int main(int argc, char *argv[ ]){

    printf("INIT\n\n");
    Token teste;
    strcpy( teste.valor, "int");
    teste.tipo = INT;
    Token empty;
    Token teste2;
    strcpy( teste2.valor, "main");
    teste2.tipo = ID;
    strcpy( empty.valor, "token");
    empty.tipo = EMPTY;

    Token* tokens = (Token*)malloc(10 * sizeof(Token));
    tokens[0] = teste;
    tokens[1] = teste2;
    tokens[2] = empty;
    currToken = tokens[0];
    printf("START TOKEN: %d %s\n", currToken.tipo, currToken.valor);
    printf("%d", program(tokens));

}



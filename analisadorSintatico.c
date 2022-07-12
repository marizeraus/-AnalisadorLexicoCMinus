#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum tokenType
{
    EMPTY = 1,
    INT,
    VOID,
    IF,
    RETURN,
    WHILE,
    ID,
    ELSE,
    OPENPAREN,
    CLOSEPAREN,
    OPENCHAVES,
    CLOSECHAVES,
    OPENCOLCHETE,
    CLOSECOLCHETE,
    VIRGULA,
    PONTOVIRGULA,
    NUM,
    IGUAL,
    MENORIGUAL,
    MAIORIGUAL,
    MAIOR,
    MENOR,
    IGUALIGUAL,
    DIFERENTE,
    MAIS,
    MENOS,
    MULT,
    DIV
};
typedef struct
{
    char valor[50];
    enum tokenType tipo;
} Token;

static Token currToken;
int tokenPos = 0;

int program(Token *tokens);
int declarationList(Token *tokens);
int declarationListLinha(Token *tokens);
int declaration(Token *tokens);
int varDeclaration(Token *tokens);
int numVarDec(Token *tokens);
int typeSpec(Token *tokens);
int funDec(Token *tokens);
int paramList(Token *tokens);
int paramListLinha(Token *tokens);
int param(Token *tokens);
int params(Token *tokens);
int paramLinha(Token *tokens);
int compoundStmt(Token *tokens);
int localDec(Token *tokens);
int localDecLinha(Token *tokens);
int stmtList(Token *tokens);
int stmtListLinha(Token *tokens);
int stmt(Token *tokens);
int expStmt(Token *tokens);
int selecStmt(Token *tokens);
int elseStmt(Token *tokens);
int iterationStmt(Token *tokens);
int returnStmt(Token *tokens);
int returnExp(Token *tokens);
int expression(Token *tokens);
int var(Token *tokens);
int varExp(Token *tokens);
int simpleExp(Token *tokens);
int relop(Token *tokens);
int addExp(Token *tokens);
int addExpLinha(Token *tokens);
int addop(Token *tokens);
int term(Token *tokens);
int termLinha(Token *tokens);
int mulOp(Token *tokens);
int factor(Token *tokens);
int call(Token *tokens);
int args(Token *tokens);
int argList(Token *tokens);
int argListLinha(Token *tokens);

void consomeToken(Token *tokens)
{
    tokenPos++;
    currToken = tokens[tokenPos];
}
int program(Token *tokens)
{
    return declarationList(tokens);
}

int declarationList(Token *tokens)
{
    return declarationListLinha(tokens);
}

int declarationListLinha(Token *tokens)
{
    int i = declaration(tokens);
    while (currToken.tipo != EMPTY && i)
    {

        i = declaration(tokens) && i;
        consomeToken(tokens);
    }
    return i;
}

// int declaration(Token* tokens){
//     if(typeSpec(tokens)){
//         consomeToken(tokens);
//         if(currToken.tipo == ID){
//             consomeToken(tokens);
//             if(currToken.tipo == OPENPAREN){ // is functino
//                 // return 1; //funDec(tokens);
//                 if(params(tokens)){
//                     consomeToken(tokens);
//                     if(currToken.tipo == CLOSEPAREN){
//                         // compound-stmt
//                         return 1;
//                     }
//                 }
//             } else {
//                 return 1; //numVarDec(tokens);
//             }
//         }
//     }
//     return 0;
// }

int declaration(Token *tokens)
{
    int curr = tokenPos;
    if (varDeclaration(tokens))
    {
        return 1;
    }
    currToken = tokens[curr];
    tokenPos = curr;
    if (funDec(tokens))
    {
        return 1;
    }
}

int varDeclaration(Token *tokens)
{
    if (typeSpec(tokens))
    {
        consomeToken(tokens);
        if (currToken.tipo == ID)
        {
            consomeToken(tokens);
            if (numVarDec(tokens))
            {
                if (currToken.tipo == PONTOVIRGULA)
                {
                    consomeToken(tokens);
                    return 1;
                }
            }
        }
    }
    return 0;
}

int numVarDec(Token *tokens)
{
    int curr = tokenPos;
    if (currToken.tipo == OPENCOLCHETE)
    {
        consomeToken(tokens);
        if (currToken.tipo == NUM)
        {
            consomeToken(tokens);
            if (currToken.tipo == CLOSECOLCHETE)
            {
                consomeToken(tokens);
                return 1;
            }
        }
    }
    tokenPos = curr;
    currToken = tokens[curr];
    return 1;
}

int typeSpec(Token *tokens)
{
    if (currToken.tipo == INT || currToken.tipo == VOID)
    {
        return 1;
    }
    return 0;
}

int funDec(Token *tokens)
{
    if (typeSpec(tokens))
    {
        consomeToken(tokens);
        if (currToken.tipo == ID)
        {
            consomeToken(tokens);
            if (currToken.tipo == OPENPAREN)
            {
                consomeToken(tokens);
                int i = params(tokens);
                if (i)
                {
                    if (currToken.tipo == CLOSEPAREN)
                    {
                        consomeToken(tokens);

                        return compoundStmt(tokens);
                    }
                }
            }
        }
    }
    return 0;
}

int params(Token *tokens)
{
    if (currToken.tipo == VOID)
    {
        consomeToken(tokens);
        return 1;
    }

    if (paramList(tokens))
    {
        return 1;
    }
    return 0;
}

int paramList(Token *tokens)
{
    if (param(tokens))
    {
        consomeToken(tokens);
        if (paramListLinha(tokens))
        {
            return 1;
        }
    }
}

int paramListLinha(Token *tokens)
{
    int curr = tokenPos;
    if (param(tokens))
    {
        return 1;
    }

    if (currToken.tipo == VIRGULA)
    {
        if (param(tokens))
        {
            consomeToken(tokens);
            if (paramListLinha(tokens))
            {
                return 1;
            }
        }
    }
    tokenPos = curr;
    currToken = tokens[curr];
    return 1;
}

int param(Token *tokens)
{
    if (typeSpec(tokens))
    {
        if (currToken.tipo == ID)
        {
            consomeToken(tokens);
            if (paramLinha)
            {
                return 1;
            }
        }
    }
}

int paramLinha(Token *tokens)
{
    int curr = tokenPos;

    if (currToken.tipo == OPENCOLCHETE)
    {
        consomeToken(tokens);
        if (currToken.tipo == CLOSECOLCHETE)
        {
            consomeToken(tokens);
            return 1;
        }
    }
    if (varDeclaration(tokens))
    {
        return 1;
    }
    currToken = tokens[curr];
    tokenPos = curr;
    return 1;
}

int compoundStmt(Token *tokens)
{
    if (currToken.tipo == OPENCHAVES)
    {
        consomeToken(tokens);
        if (localDec(tokens))
        {
            if (localDec(tokens))
            {
                if (stmtList(tokens))
                {
                    if (currToken.tipo == CLOSECHAVES)
                    {
                        consomeToken(tokens);
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int localDec(Token *tokens)
{
    if (localDecLinha(tokens))
    {
        return 1;
    }
}

int localDecLinha(Token *tokens)
{
    int curr = tokenPos;
    if (varDeclaration(tokens))
    {
        if (localDecLinha(tokens))
        {
            return 1;
        }
    }
    currToken = tokens[curr];
    tokenPos = curr;
    return 1;
}

int stmtList(Token *tokens)
{
    int curr = tokenPos;
    if (stmtListLinha(tokens))
    {
        return 1;
    }
    currToken = tokens[curr];
    tokenPos = curr;
    return 1;
}

int stmtListLinha(Token *tokens)
{
    int curr = tokenPos;

    if (stmt(tokens))
    {
        if (stmtListLinha(tokens))
        {
            return 1;
        }
    }
    currToken = tokens[curr];
    tokenPos = curr;
    return 1;
}

int stmt(Token *tokens)
{
    int curr = tokenPos;

    if (expStmt(tokens))
    {
        return 1;
    }
    currToken = tokens[curr];
    tokenPos = curr;

    if (compoundStmt(tokens))
    {
        return 1;
    }
    currToken = tokens[curr];
    tokenPos = curr;

    if (selecStmt(tokens))
    {
        return 1;
    }
    currToken = tokens[curr];
    tokenPos = curr;

    if (iterationStmt(tokens))
    {
        return 1;
    }
    currToken = tokens[curr];
    tokenPos = curr;

    if (returnStmt(tokens))
    {
        return 1;
    }
    currToken = tokens[curr];
    tokenPos = curr;
    return 0;
}

int expStmt(Token *tokens)
{
    if (expression(tokens))
    {
        if (currToken.tipo == PONTOVIRGULA)
        {
            consomeToken(tokens);
            return 1;
        }
    }

    if (currToken.tipo == PONTOVIRGULA)
    {
        consomeToken(tokens);
        return 1;
    }
    return 0;
}

int selecStmt(Token *tokens)
{
    if (currToken.tipo == IF)
    {
        consomeToken(tokens);
        if (currToken.tipo == OPENPAREN)
        {
            consomeToken(tokens);
            if (expression(tokens))
            {
                if (currToken.tipo == CLOSEPAREN)
                {
                    consomeToken(tokens);
                    if (stmt(tokens))
                    {
                        if (elseStmt(tokens))
                        {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int elseStmt(Token *tokens)
{
    int curr = tokenPos;
    if (currToken.tipo == ELSE)
    {
        consomeToken(tokens);
        if (stmt(tokens))
        {
            return 1;
        }
    }
    tokenPos = curr;
    currToken = tokens[curr];
    return 1;
}

int iterationStmt(Token *tokens)
{
    if (currToken.tipo == WHILE)
    {
        consomeToken(tokens);
        if (currToken.tipo == OPENPAREN)
        {
            consomeToken(tokens);
            if (expression(tokens))
            {
                if (currToken.tipo == CLOSEPAREN)
                {
                    consomeToken(tokens);
                    if (stmt(tokens))
                    {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int returnStmt(Token *tokens)
{
    if (currToken.tipo == RETURN)
    {
        consomeToken(tokens);
        if (returnExp(tokens))
        {
            if (currToken.tipo == PONTOVIRGULA)
            {
                consomeToken(tokens);
                return 1;
            }
        }
    }
    return 0;
}

int returnExp(Token *tokens)
{
    int curr = tokenPos;
    if (expression(tokens))
    {
        return 1;
    }
    currToken = tokens[curr];
    tokenPos = curr;
    return 1;
}

int expression(Token *tokens)
{
    int curr = tokenPos;
    if (var(tokens))
    {
        if (currToken.tipo == IGUAL)
        {
            consomeToken(tokens);
            if (expression(tokens))
            {
                return 1;
            }
        }
    }
    tokenPos = curr;
    currToken = tokens[curr];
    if (simpleExp(tokens))
    {
        return 1;
    }
}

int var(Token *tokens)
{
    int curr = tokenPos;
    if (currToken.tipo == ID)
    {
        consomeToken(tokens);
        return 1;
    }
    currToken = tokens[curr];
    tokenPos = curr;
    if (varExp(tokens))
    {
        return 1;
    }
    return 0;
}

int varExp(Token *tokens)
{
    int curr = tokenPos;
    if (currToken.tipo == OPENCOLCHETE)
    {
        consomeToken(tokens);
        if (expression(tokens))
        {
            if (currToken.tipo == CLOSECOLCHETE)
            {
                return 1;
            }
        }
    }
    currToken = tokens[curr];
    tokenPos = curr;
    return 1;
}

int simpleExp(Token *tokens)
{
    if (addExp(tokens))
    {
        int curr = tokenPos;
        if (relop(tokens))
        {
            if (addExp(tokens))
            {
                return 1;
            }
        }
        currToken = tokens[curr];
        tokenPos = curr;
        return 1;
    }
    return 0;
}

int relop(Token *tokens)
{
    if (currToken.tipo == MENORIGUAL)
    {
        consomeToken(tokens);
        return 1;
    }

    if (currToken.tipo == MENOR)
    {
        consomeToken(tokens);
        return 1;
    }
    if (currToken.tipo == MAIOR)
    {
        consomeToken(tokens);
        return 1;
    }

    if (currToken.tipo == MAIORIGUAL)
    {
        consomeToken(tokens);
        return 1;
    }
    if (currToken.tipo == IGUALIGUAL)
    {
        consomeToken(tokens);
        return 1;
    }

    if (currToken.tipo == DIFERENTE)
    {
        consomeToken(tokens);
        return 1;
    }
    return 0;
}

int addExp(Token *tokens)
{
    if (term(tokens))
    {
        if (addExpLinha(tokens))
        {
            return 1;
        }
    }
    return 0;
}

int addExpLinha(Token *tokens)
{
    int curr = tokenPos;
    if (addop(tokens))
    {
        if (term(tokens))
        {
            if (addExpLinha(tokens))
            {
                return 1;
            }
        }
    }
    currToken = tokens[curr];
    tokenPos = curr;
    return 1;
}

int addop(Token *tokens)
{
    if (currToken.tipo == MAIS)
    {
        consomeToken(tokens);
        return 1;
    }

    if (currToken.tipo == MENOS)
    {
        consomeToken(tokens);
        return 1;
    }
    return 0;
}

int term(Token *tokens)
{
    if (factor(tokens))
    {
        if (termLinha(tokens))
        {
            return 1;
        }
    }
    return 0;
}

int termLinha(Token *tokens)
{
    int curr = tokenPos;
    if (mulOp(tokens))
    {
        if (factor(tokens))
        {
            if (termLinha(tokens))
            {
                return 1;
            }
        }
    }
    tokenPos = curr;
    currToken = tokens[curr];
    return 1;
}

int mulOp(Token *tokens)
{
    if (currToken.tipo == MULT)
    {
        consomeToken(tokens);
    }

    if (currToken.tipo == DIV)
    {
        consomeToken(tokens);
    }
    return 0;
}

int factor(Token *tokens)
{
    if (currToken.tipo == OPENPAREN)
    {
        consomeToken(tokens);
        if (expression(tokens))
        {
            if (currToken.tipo == CLOSEPAREN)
            {
                consomeToken(tokens);
                return 1;
            }
        }
    }

    if (var(tokens))
    {
        return 1;
    }

    if (call(tokens))
    {
        return 1;
    }

    if (currToken.tipo == NUM)
    {
        consomeToken(tokens);
        return 1;
    }
    return 0;
}

int call(Token *tokens)
{
    if (currToken.tipo == ID)
    {
        consomeToken(tokens);
        if (currToken.tipo == OPENPAREN)
        {
            if (args(tokens))
            {
                if (currToken.tipo == CLOSEPAREN)
                {
                    consomeToken(tokens);
                    return 1;
                }
            }
        }
    }
    return 0;
}

int args(Token *tokens)
{
    int curr = tokenPos;
    if (argList(tokens))
    {
        return 1;
    }
    currToken = tokens[curr];
    tokenPos = curr;
    return 1;
}

int argList(Token *tokens)
{
    if (expression(tokens))
    {
        if (argListLinha(tokens))
        {
            return 1;
        }
    }

    return 0;
}

int argListLinha(Token *tokens)
{
    int curr = tokenPos;
    if (currToken.tipo == VIRGULA)
    {
        consomeToken(tokens);
        if (expression(tokens))
        {
            if (argListLinha(tokens))
            {
                return 1;
            }
        }
    }
    currToken = tokens[curr];
    tokenPos = curr;
    return 1;
}

Token *readTokensFromFile()
{
    FILE *arq;
    arq = fopen("tokens.txt", "rt");
    int n;
    fscanf(arq, "%d", &n);

    Token *tokens = (Token *)malloc(n * sizeof(Token));
    int i = 0;
    while (!feof(arq))
    {
        int tipo;
        char valor[50];
        Token token;
        fscanf(arq, "%d %s", &tipo, valor);
        printf("%d %s\n", tipo, valor);
        token.tipo = tipo;
        strcpy(token.valor, valor);
        tokens[i] = token;
        i++;
    }
    fclose(arq);
    return tokens;
}

int main(int argc, char *argv[])
{
    Token *tokens = readTokensFromFile();
    currToken = tokens[0];
    if (program(tokens))
    {
        printf("Análise concluída com sucesso\n");
    }
    else
    {
        printf("Análise concluída com erro\n");
    }
}
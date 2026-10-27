%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct
{
    char name[20];
    char type[10];
} Symbol;

Symbol symbolTable[MAX];
int symbolCount = 0;

void addSymbol(char *name, char *type)
{
    strcpy(symbolTable[symbolCount].name, name);
    strcpy(symbolTable[symbolCount].type, type);
    symbolCount++;
}

char *getType(char *name)
{
    int i;
    for (i = 0; i < symbolCount; i++)
    {
        if (strcmp(symbolTable[i].name, name) == 0)
            return symbolTable[i].type;
    }
    return "undefined";
}

void checkType(char *var, char *exprType)
{
    char *varType = getType(var);

    if (strcmp(varType, "undefined") == 0)
    {
        printf("Error: Variable %s is not declared\n", var);
        return;
    }

    if (strcmp(varType, exprType) == 0)
        printf("Type Checking Successful: %s = %s\n", var, exprType);
    else
        printf("Type Error: Cannot assign %s to %s\n", exprType, varType);
}

int yylex();
void yyerror(char *s);
%}

%union
{
    char str[20];
}

%token INT FLOAT CHAR
%token <str> ID
%token INTEGER REAL CHARACTER
%token ASSIGN SEMICOLON

%type <str> type
%type <str> expression

%%

program:
        declarations assignments
        ;

declarations:
        declarations declaration
        | declaration
        ;

declaration:
        type ID SEMICOLON
        {
            addSymbol($2, $1);
        }
        ;

type:
        INT     { strcpy($$, "int"); }
        | FLOAT { strcpy($$, "float"); }
        | CHAR  { strcpy($$, "char"); }
        ;

assignments:
        assignments assignment
        | assignment
        ;

assignment:
        ID ASSIGN expression SEMICOLON
        {
            checkType($1, $3);
        }
        ;

expression:
        INTEGER     { strcpy($$, "int"); }
        | REAL      { strcpy($$, "float"); }
        | CHARACTER { strcpy($$, "char"); }
        ;

%%

void yyerror(char *s)
{
    printf("Syntax Error: %s\n", s);
}

int main()
{
    printf("Enter declarations and assignment statements:\n");
    yyparse();
    return 0;
}

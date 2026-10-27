%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);

char stack[100];
int top = -1;

void push(char c)
{
    stack[++top] = c;
}

char pop()
{
    if (top == -1)
        return '\0';
    return stack[top--];
}

int match(char open, char close)
{
    if (open == '(' && close == ')') return 1;
    if (open == '[' && close == ']') return 1;
    if (open == '{' && close == '}') return 1;
    return 0;
}
%}

%token OPEN_PAREN CLOSE_PAREN
%token OPEN_BRACKET CLOSE_BRACKET
%token OPEN_BRACE CLOSE_BRACE
%token OTHER

%%

input:
        symbols
        {
            if (top == -1)
                printf("Balanced Symbols\n");
            else
                printf("Unbalanced Symbols\n");
        }
        ;

symbols:
        symbols symbol
        | symbol
        ;

symbol:
        OPEN_PAREN    { push('('); }
        | CLOSE_PAREN
        {
            char c = pop();
            if (!match(c, ')')) { yyerror("Unbalanced Symbols"); YYABORT; }
        }
        | OPEN_BRACKET { push('['); }
        | CLOSE_BRACKET
        {
            char c = pop();
            if (!match(c, ']')) { yyerror("Unbalanced Symbols"); YYABORT; }
        }
        | OPEN_BRACE   { push('{'); }
        | CLOSE_BRACE
        {
            char c = pop();
            if (!match(c, '}')) { yyerror("Unbalanced Symbols"); YYABORT; }
        }
        | OTHER
        ;

%%

void yyerror(char *s)
{
    printf("%s\n", s);
}

int main()
{
    printf("Enter an expression:\n");
    yyparse();
    return 0;
}

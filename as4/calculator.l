%{
#include <stdio.h>
#include <stdlib.h>

int a, b;
%}

%%

[0-9]+"+"[0-9]+ {
    sscanf(yytext, "%d+%d", &a, &b);
    printf("Result = %d\n", a + b);
}

[0-9]+"-"[0-9]+ {
    sscanf(yytext, "%d-%d", &a, &b);
    printf("Result = %d\n", a - b);
}

[0-9]+"*"[0-9]+ {
    sscanf(yytext, "%d*%d", &a, &b);
    printf("Result = %d\n", a * b);
}

[0-9]+"/"[0-9]+ {
    sscanf(yytext, "%d/%d", &a, &b);
    if (b == 0)
        printf("Error: Division by zero\n");
    else
        printf("Result = %.2f\n", (float)a / b);
}

[\n]   return 0;

.      ;

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter an arithmetic expression: ");
    yylex();
    return 0;
}

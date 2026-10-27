%{
#include <stdio.h>

int keywords = 0, identifiers = 0, numbers = 0;
int arithmetic = 0, relational = 0;
int delimiters = 0, comments = 0;
%}

letter      [A-Za-z]
digit       [0-9]
id          {letter}({letter}|{digit}|_)*
number      {digit}+

%%

"int"|"float"|"char"|"double"|"if"|"else"|"for"|"while"|"return"|"void" {
    printf("%-15s : KEYWORD\n", yytext);
    keywords++;
}

{id} {
    printf("%-15s : IDENTIFIER\n", yytext);
    identifiers++;
}

{number} {
    printf("%-15s : NUMBER\n", yytext);
    numbers++;
}

"=="|"!="|"<="|">="|"<"|">" {
    printf("%-15s : RELATIONAL OPERATOR\n", yytext);
    relational++;
}

"//".* {
    printf("%-15s : SINGLE LINE COMMENT\n", yytext);
    comments++;
}

"/*"([^*]|\*+[^*/])*\*+"/" {
    printf("%-15s : MULTI LINE COMMENT\n", "/* ... */");
    comments++;
}

"+"|"-"|"*"|"/"|"%" {
    printf("%-15s : ARITHMETIC OPERATOR\n", yytext);
    arithmetic++;
}

";"|","|"("|")"|"{"|"}" {
    printf("%-15s : DELIMITER\n", yytext);
    delimiters++;
}

[ \t\n]+      ;

.             ;

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter a C program (Press Ctrl+D to finish):\n\n");

    yylex();

    printf("\n------ TOKEN COUNT ------\n");
    printf("Keywords              : %d\n", keywords);
    printf("Identifiers           : %d\n", identifiers);
    printf("Numbers               : %d\n", numbers);
    printf("Arithmetic Operators  : %d\n", arithmetic);
    printf("Relational Operators  : %d\n", relational);
    printf("Delimiters            : %d\n", delimiters);
    printf("Comments              : %d\n", comments);

    return 0;
}


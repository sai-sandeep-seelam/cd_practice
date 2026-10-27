%{
#include "typecheck.tab.h"
#include <string.h>
%}

%%

"int"       { return INT; }
"float"     { return FLOAT; }
"char"      { return CHAR; }

[0-9]+      { return INTEGER; }

[0-9]+\.[0-9]+  { return REAL; }

\'[a-zA-Z]\'    { return CHARACTER; }

[a-zA-Z_][a-zA-Z0-9_]*  {
                strcpy(yylval.str, yytext);
                return ID;
            }

"="         { return ASSIGN; }

";"         { return SEMICOLON; }

[ \t\n]+    ;

.           { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}

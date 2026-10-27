%{
#include "balance.tab.h"
%}

%%

"("     { return OPEN_PAREN; }
")"     { return CLOSE_PAREN; }
"["     { return OPEN_BRACKET; }
"]"     { return CLOSE_BRACKET; }
"{"     { return OPEN_BRACE; }
"}"     { return CLOSE_BRACE; }

[ \t\n]+    ;

.       { return OTHER; }

%%

int yywrap()
{
    return 1;
}

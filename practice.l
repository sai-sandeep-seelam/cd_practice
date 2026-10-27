%{
    #include <stdio.h>
    #include <stdlib.h>
    int a,b;
    %
}
%%
[0-9]+"+"[0-9]+{
    sscanf(yytext,"%d+%d",&a,&b);
    printf("Result = %d\n",a+b);
}
[0-9]+"-"[0-9]+{
    sscanf(yytext,"%d-%d",&a,%b);
    printf("Result = %d\n",a-b);
}
%%
int yywrap(){
    return 1;
}
int main(){
    printf("Enter exp: ");
    yylex();
    return 0;
}
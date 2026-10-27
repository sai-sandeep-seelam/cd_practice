#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100
#define NAME 32

const char *p;
int tempCount = 0;

void expr(char *out);

void skip(void)
{
    while (isspace((unsigned char)*p))
        p++;
}

void factor(char *out)
{
    int n = 0;
    skip();

    if (*p == '(')
    {
        p++;
        expr(out);
        skip();
        if (*p != ')')
        {
            printf("Error: missing ')'\n");
            exit(1);
        }
        p++;
    }
    else if (isalnum((unsigned char)*p) || *p == '_')
    {
        while ((isalnum((unsigned char)*p) || *p == '_') && n < NAME - 1)
            out[n++] = *p++;
        out[n] = '\0';
    }
    else
    {
        printf("Error: unexpected character '%c'\n", *p ? *p : '?');
        exit(1);
    }
}

void term(char *out)
{
    char left[NAME], right[NAME];
    factor(left);
    skip();
    while (*p == '*' || *p == '/')
    {
        char op = *p++;
        factor(right);
        printf("t%d = %s %c %s\n", ++tempCount, left, op, right);
        sprintf(left, "t%d", tempCount);
        skip();
    }
    strcpy(out, left);
}

void expr(char *out)
{
    char left[NAME], right[NAME];
    term(left);
    skip();
    while (*p == '+' || *p == '-')
    {
        char op = *p++;
        term(right);
        printf("t%d = %s %c %s\n", ++tempCount, left, op, right);
        sprintf(left, "t%d", tempCount);
        skip();
    }
    strcpy(out, left);
}

int main(void)
{
    char input[MAX], result[NAME];

    printf("Enter an arithmetic expression: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
        return 1;
    input[strcspn(input, "\n")] = '\0';

    p = input;
    printf("\nThree-Address Code:\n");
    expr(result);

    skip();
    if (*p != '\0')
    {
        printf("Error: unexpected character '%c'\n", *p);
        return 1;
    }
    return 0;
}
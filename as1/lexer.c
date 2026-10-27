#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main()
{
    char s[10000];
    int len = 0, ch;
    int i = 0, j, found;

    char *keywords[] = {
        "int", "float", "char", "if", "else", "while", "return"
    };

    printf("Enter code (finish with Ctrl+D or Ctrl+Z):\n");

    while ((ch = getchar()) != EOF && len < 9999) {
        s[len++] = ch;
    }
    s[len] = '\0';

    while (s[i] != '\0') {
        if (isspace((unsigned char)s[i])) {
            i++;
        }
        else if (isalpha((unsigned char)s[i]) || s[i] == '_') {
            char word[100];
            j = 0;

            while (isalnum((unsigned char)s[i]) || s[i] == '_') {
                if (j < 99)
                    word[j++] = s[i];
                i++;
            }

            word[j] = '\0';
            found = 0;

            for (j = 0; j < 7; j++) {
                if (strcmp(word, keywords[j]) == 0) {
                    found = 1;
                    break;
                }
            }

            if (found)
                printf("<%s, KEYWORD>\n", word);
            else
                printf("<%s, IDENTIFIER>\n", word);
        }
        else if (isdigit((unsigned char)s[i])) {
            char num[100];
            j = 0;

            while (isdigit((unsigned char)s[i])) {
                if (j < 99)
                    num[j++] = s[i];
                i++;
            }

            num[j] = '\0';
            printf("<%s, INTEGER_CONSTANT>\n", num);
        }
        else {
            char c = s[i++];

            if (strchr("+-*/%", c))
                printf("<%c, ARITHMETIC_OPERATOR>\n", c);
            else if (c == '=')
                printf("<%c, ASSIGNMENT_OPERATOR>\n", c);
            else if (c == ';' || c == ',')
                printf("<%c, SEPARATOR>\n", c);
            else if (c == '(')
                printf("<%c, LEFT_PARENTHESIS>\n", c);
            else if (c == ')')
                printf("<%c, RIGHT_PARENTHESIS>\n", c);
            else if (c == '<' || c == '>')
                printf("<%c, RELATIONAL_OPERATOR>\n", c);
            else if (c == '{')
                printf("<%c, LEFT_BRACE>\n", c);
            else if (c == '}')
                printf("<%c, RIGHT_BRACE>\n", c);
            else
                printf("<%c, UNKNOWN>\n", c);
        }
    }

    return 0;
}

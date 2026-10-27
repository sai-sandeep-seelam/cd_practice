#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100
#define MAXN 100

/* Remove leading and trailing whitespace in place */
void trim(char *s)
{
    int start = 0, end = (int)strlen(s) - 1, k;

    while (s[start] && isspace((unsigned char)s[start]))
        start++;
    while (end >= start && isspace((unsigned char)s[end]))
        end--;

    for (k = 0; start + k <= end; k++)
        s[k] = s[start + k];
    s[k] = '\0';
}

int main(void)
{
    int n, i, k, count = 0;
    char line[SIZE];
    char lines[MAXN][SIZE];

    printf("Enter the number of TAC instructions: ");
    if (fgets(line, sizeof(line), stdin) == NULL || sscanf(line, "%d", &n) != 1
        || n < 1 || n > MAXN)
    {
        printf("Invalid number of instructions.\n");
        return 1;
    }

    printf("Enter the TAC instructions:\n");

    /* Read exactly n non-blank lines */
    while (count < n && fgets(line, sizeof(line), stdin) != NULL)
    {
        trim(line);
        if (line[0] == '\0')
            continue;
        strcpy(lines[count++], line);
    }

    printf("\nGenerated Target Code:\n");

    for (i = 0; i < count; i++)
    {
        char dest[SIZE], rhs[SIZE], op1[SIZE], op2[SIZE];
        char *eq = strchr(lines[i], '=');
        char operator = 0;
        int pos = -1;

        if (eq == NULL)
        {
            printf("Invalid TAC instruction: %s\n", lines[i]);
            continue;
        }

        /* Split into destination and right-hand side */
        strncpy(dest, lines[i], eq - lines[i]);
        dest[eq - lines[i]] = '\0';
        trim(dest);
        strcpy(rhs, eq + 1);
        trim(rhs);

        if (dest[0] == '\0' || rhs[0] == '\0')
        {
            printf("Invalid TAC instruction: %s\n", lines[i]);
            continue;
        }

        /* Find an operator after the first character (so -5 is not an operator) */
        for (k = 1; rhs[k] != '\0'; k++)
        {
            if (rhs[k] == '+' || rhs[k] == '-' || rhs[k] == '*' || rhs[k] == '/')
            {
                pos = k;
                operator = rhs[k];
                break;
            }
        }

        if (pos == -1)
        {
            /* Simple assignment */
            printf("MOV R0, %s\n", rhs);
            printf("MOV %s, R0\n", dest);
        }
        else
        {
            strncpy(op1, rhs, pos);
            op1[pos] = '\0';
            trim(op1);
            strcpy(op2, rhs + pos + 1);
            trim(op2);

            if (op1[0] == '\0' || op2[0] == '\0')
            {
                printf("Invalid TAC instruction: %s\n", lines[i]);
                continue;
            }

            printf("MOV R0, %s\n", op1);
            switch (operator)
            {
                case '+': printf("ADD R0, %s\n", op2); break;
                case '-': printf("SUB R0, %s\n", op2); break;
                case '*': printf("MUL R0, %s\n", op2); break;
                case '/': printf("DIV R0, %s\n", op2); break;
            }
            printf("MOV %s, R0\n", dest);
        }
    }

    return 0;
}
/*#include <stdio.h>
#include <string.h>

int main()
{
    int n, i;
    char s[100], dest[20], a[20], op, b[20];

    printf("Enter number of instructions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter TAC instructions:\n");

    for (i = 0; i < n; i++)
    {
        fgets(s, sizeof(s), stdin);

        if (sscanf(s, "%s = %s %c %s", dest, a, &op, b) == 4)
        {
            printf("MOV R0, %s\n", a);

            switch (op)
            {
                case '+': printf("ADD R0, %s\n", b); break;
                case '-': printf("SUB R0, %s\n", b); break;
                case '*': printf("MUL R0, %s\n", b); break;
                case '/': printf("DIV R0, %s\n", b); break;
                default: printf("Invalid operator\n"); continue;
            }

            printf("MOV %s, R0\n", dest);
        }
        else if (sscanf(s, "%s = %s", dest, a) == 2)
        {
            printf("MOV R0, %s\n", a);
            printf("MOV %s, R0\n", dest);
        }
        else
            printf("Invalid TAC instruction\n");
    }

    return 0;
}*/
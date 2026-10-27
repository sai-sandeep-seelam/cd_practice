#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

/* Returns 1 if s is an integer constant such as 10 or -5 */
int isConstant(const char s[])
{
    int i = 0;

    if (s[0] == '-' && s[1] != '\0')
        i = 1;

    if (s[i] == '\0')
        return 0;

    for (; s[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)s[i]))
            return 0;
    }

    return 1;
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

    printf("\nOptimized Three-Address Code:\n");

    for (i = 0; i < count; i++)
    {
        char dest[SIZE], rhs[SIZE], op1[SIZE], op2[SIZE];
        char *eq = strchr(lines[i], '=');
        char operator = 0;
        int pos = -1;
        long a, b, result;

        if (eq == NULL)
        {
            printf("Invalid instruction: %s\n", lines[i]);
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
            printf("Invalid instruction: %s\n", lines[i]);
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

        /* Simple assignment: nothing to fold */
        if (pos == -1)
        {
            printf("%s = %s\n", dest, rhs);
            continue;
        }

        strncpy(op1, rhs, pos);
        op1[pos] = '\0';
        trim(op1);
        strcpy(op2, rhs + pos + 1);
        trim(op2);

        if (op1[0] == '\0' || op2[0] == '\0')
        {
            printf("Invalid instruction: %s\n", lines[i]);
            continue;
        }

        if (isConstant(op1) && isConstant(op2))
        {
            a = atol(op1);
            b = atol(op2);

            switch (operator)
            {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0)
                    {
                        printf("%s = %s %c %s  (division by zero; unchanged)\n",
                               dest, op1, operator, op2);
                        continue;
                    }
                    result = a / b;
                    break;
            }

            printf("%s = %ld\n", dest, result);
        }
        else
        {
            printf("%s = %s %c %s\n", dest, op1, operator, op2);
        }
    }

    return 0;
}
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n, i;
    char s[100], a[20], op, b[20], dest[20];
    long x, y, r;

    printf("Enter number of instructions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter TAC instructions:\n");

    for (i = 0; i < n; i++)
    {
        fgets(s, sizeof(s), stdin);

        if (sscanf(s, "%s = %s %c %s", dest, a, &op, b) == 4)
        {
            if (sscanf(a, "%ld", &x) == 1 &&
                sscanf(b, "%ld", &y) == 1)
            {
                switch (op)
                {
                    case '+': r = x + y; break;
                    case '-': r = x - y; break;
                    case '*': r = x * y; break;
                    case '/':
                        if (y == 0)
                        {
                            printf("%s = %s %c %s\n", dest, a, op, b);
                            continue;
                        }
                        r = x / y;
                        break;
                    default:
                        printf("Invalid instruction\n");
                        continue;
                }
                printf("%s = %ld\n", dest, r);
            }
            else
                printf("%s = %s %c %s\n", dest, a, op, b);
        }
        else if (sscanf(s, "%s = %s", dest, a) == 2)
            printf("%s = %s\n", dest, a);
        else
            printf("Invalid instruction\n");
    }

    return 0;
}*/

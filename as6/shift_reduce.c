#include <stdio.h>
#include <string.h>

#define MAXP 20

char lhs[MAXP];
char rhs[MAXP][30];
int n;

char stack[200];
char input[200];

/* try to reduce top of stack using any production; returns production index or -1 */
int tryReduce(void)
{
    int sl = strlen(stack);
    for (int p = 0; p < n; p++)
    {
        int rl = strlen(rhs[p]);
        if (rl <= sl && strcmp(stack + sl - rl, rhs[p]) == 0)
            return p;
    }
    return -1;
}

int main(void)
{
    char str[100];

    printf("Enter the number of productions:\n");
    scanf("%d", &n);

    printf("\nEnter the productions (format E->E+E):\n");
    for (int i = 0; i < n; i++)
    {
        char prod[60];
        scanf("%59s", prod);
        lhs[i] = prod[0];
        strcpy(rhs[i], prod + 3);
    }

    printf("\nEnter the input string:\n");
    scanf("%99s", str);

    printf("\nGrammar:\n");
    for (int i = 0; i < n; i++)
        printf("%c->%s\n", lhs[i], rhs[i]);
    printf("\nInput String: %s\n\n", str);

    strcpy(input, str);
    strcat(input, "$");
    stack[0] = '\0';
    int ip = 0;
    char startSym = lhs[0];

    printf("---------------------------------------------------------\n");
    printf("%-16s %-16s %s\n", "Stack", "Input", "Action");
    printf("---------------------------------------------------------\n");

    int accepted = 0;

    while (1)
    {
        /* reduce whenever possible */
        int p;
        while ((p = tryReduce()) != -1)
        {
            /* leave a pending shift if we could still extend, handled by greedy rule:
               reduce immediately only when it is the final handle or id-like rule */
            printf("%-16s %-16s Reduce %c->%s\n", stack, input + ip, lhs[p], rhs[p]);
            int sl = strlen(stack) - strlen(rhs[p]);
            stack[sl] = lhs[p];
            stack[sl + 1] = '\0';
        }

        if (input[ip] == '$')
        {
            if (strlen(stack) == 1 && stack[0] == startSym)
            {
                printf("%-16s %-16s Accept\n", stack, input + ip);
                accepted = 1;
            }
            break;
        }

        /* shift: id is treated as one symbol, handled by shifting "id" together */
        printf("%-16s %-16s Shift\n", stack, input + ip);
        if (input[ip] == 'i' && input[ip + 1] == 'd')
        {
            strcat(stack, "id");
            ip += 2;
        }
        else
        {
            int sl = strlen(stack);
            stack[sl] = input[ip++];
            stack[sl + 1] = '\0';
        }
    }

    printf("---------------------------------------------------------\n");
    printf("Result: String %s\n", accepted ? "Accepted" : "Rejected");
    return 0;
}

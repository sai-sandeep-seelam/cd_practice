#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Grammar is stored one production per entry: lhs + rhs string.
   Each symbol is a single character. Use 'e' for epsilon.
   Non-terminals are uppercase letters. E' is written as X, T' as Y here is
   handled by a rename table so the output prints E' and T'. */

#define MAXP 20
#define MAXS 20

char lhs[MAXP];
char rhs[MAXP][20];
int np = 0;

char first[128][MAXS];
char follow[128][MAXS];
char startSym;

int addTo(char set[128][MAXS], char nt, char c)
{
    char *s = set[(int)nt];
    if (strchr(s, c)) return 0;
    int n = strlen(s);
    s[n] = c;
    s[n + 1] = '\0';
    return 1;
}

int isNonTerminal(char c) { return isupper((unsigned char)c); }

void computeFirst(void)
{
    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (int p = 0; p < np; p++)
        {
            char A = lhs[p];
            char *r = rhs[p];
            int allEps = 1;

            for (int i = 0; r[i]; i++)
            {
                char X = r[i];
                if (!isNonTerminal(X))
                {
                    if (X == 'e') { changed |= addTo(first, A, 'e'); }
                    else          { changed |= addTo(first, A, X); allEps = 0; }
                    if (X != 'e') break;
                    continue;
                }
                for (char *f = first[(int)X]; *f; f++)
                    if (*f != 'e')
                        changed |= addTo(first, A, *f);

                if (!strchr(first[(int)X], 'e')) { allEps = 0; break; }
            }
            if (allEps) changed |= addTo(first, A, 'e');
        }
    }
}

/* FIRST of a string beta; result in out, includes 'e' if beta can vanish */
void firstOfString(const char *beta, char *out)
{
    out[0] = '\0';
    int allEps = 1;
    for (int i = 0; beta[i]; i++)
    {
        char X = beta[i];
        if (!isNonTerminal(X))
        {
            if (X != 'e')
            {
                if (!strchr(out, X)) { int n = strlen(out); out[n] = X; out[n + 1] = 0; }
                allEps = 0;
                break;
            }
            continue;
        }
        for (char *f = first[(int)X]; *f; f++)
            if (*f != 'e' && !strchr(out, *f)) { int n = strlen(out); out[n] = *f; out[n + 1] = 0; }
        if (!strchr(first[(int)X], 'e')) { allEps = 0; break; }
    }
    if (allEps && !strchr(out, 'e')) { int n = strlen(out); out[n] = 'e'; out[n + 1] = 0; }
}

void computeFollow(void)
{
    addTo(follow, startSym, '$');
    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (int p = 0; p < np; p++)
        {
            char A = lhs[p];
            char *r = rhs[p];
            for (int i = 0; r[i]; i++)
            {
                char B = r[i];
                if (!isNonTerminal(B)) continue;

                char fb[MAXS];
                firstOfString(r + i + 1, fb);

                for (char *f = fb; *f; f++)
                    if (*f != 'e')
                        changed |= addTo(follow, B, *f);

                if (r[i + 1] == '\0' || strchr(fb, 'e'))
                    for (char *f = follow[(int)A]; *f; f++)
                        changed |= addTo(follow, B, *f);
            }
        }
    }
}

/* pretty-print names: X -> E', Y -> T' */
void printName(char c)
{
    if (c == 'X') printf("E'");
    else if (c == 'Y') printf("T'");
    else printf("%c", c);
}

void printSet(char *s)
{
    printf("{ ");
    for (int i = 0; s[i]; i++)
    {
        if (i) printf(", ");
        if (s[i] == 'e') printf("ε");
        else if (s[i] == 'i') printf("id");
        else printf("%c", s[i]);
    }
    printf(" }\n");
}

int main(void)
{
    /* E->TX, X->+TX|e, T->FY, Y->*FY|e, F->(E)|i   (i = id) */
    const char *g[] = {"E=TX", "X=+TX", "X=e", "T=FY", "Y=*FY", "Y=e", "F=(E)", "F=i"};
    np = 8;
    for (int i = 0; i < np; i++)
    {
        lhs[i] = g[i][0];
        strcpy(rhs[i], g[i] + 2);
    }
    startSym = 'E';

    printf("Grammar:\n");
    printf("E  -> T E'\nE' -> + T E' | ε\nT  -> F T'\nT' -> * F T' | ε\nF  -> ( E ) | id\n\n");

    computeFirst();
    computeFollow();

    char nts[] = {'E', 'X', 'T', 'Y', 'F'};

    printf("FIRST Sets\n");
    for (int i = 0; i < 5; i++)
    {
        printf("FIRST(");  printName(nts[i]);  printf(") = ");
        printSet(first[(int)nts[i]]);
    }

    printf("\nFOLLOW Sets\n");
    for (int i = 0; i < 5; i++)
    {
        printf("FOLLOW("); printName(nts[i]); printf(") = ");
        printSet(follow[(int)nts[i]]);
    }
    return 0;
}

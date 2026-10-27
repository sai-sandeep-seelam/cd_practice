#include <stdio.h>
#include <string.h>

#define MAX 100

struct Symbol {
    char name[32];
    char type[10];
    int size;
    int address;
    char scope[10];
};

int getSize(const char *type)
{
    if (strcmp(type, "int") == 0)    return 4;
    if (strcmp(type, "float") == 0)  return 4;
    if (strcmp(type, "char") == 0)   return 1;
    if (strcmp(type, "double") == 0) return 8;
    return 0;
}

int main(void)
{
    struct Symbol table[MAX];
    int count = 0, address = 1000;
    char type[20], name[40], line[100];

    printf("Enter declarations (one per line, e.g. int x;). Ctrl+D to finish:\n");

    while (fgets(line, sizeof line, stdin))
    {
        if (sscanf(line, "%19s %39[^;=\n ]", type, name) != 2)
            continue;

        int size = getSize(type);
        if (size == 0)
        {
            printf("Skipping unsupported type: %s\n", type);
            continue;
        }

        strcpy(table[count].name, name);
        strcpy(table[count].type, type);
        table[count].size = size;
        table[count].address = address;
        strcpy(table[count].scope, "Global");

        address += size;
        count++;
    }

    printf("\n%-12s %-10s %-14s %-8s %-6s\n",
           "Identifier", "Data Type", "Size (Bytes)", "Address", "Scope");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
        printf("%-12s %-10s %-14d %-8d %-6s\n",
               table[i].name, table[i].type, table[i].size,
               table[i].address, table[i].scope);

    return 0;
}

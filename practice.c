#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    int n,i;
    char s[100],a[20],op,b[20],dest[20];

    scanf("%d",&n);
    getchar();

    for (int i=0;i<n;i++){
        fgets(s,sizeof(s),stdin);
        if (sscanf(s,"%s = %s %c %s",dest,a,&op,b)==4){
            printf("MOV R0, %s",a);
            switch (op){
                case '+':
            }
        }
    }
}
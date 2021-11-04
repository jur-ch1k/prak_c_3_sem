#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *head, *ex_head;
    int let, i=0, tall;
    head=(char*)malloc(4*sizeof(char));
    tall=4;
    head[3]='\0';
    let=getchar();
    while (let!=EOF){
        head[i]=let;
        i++;
        if (i==tall-2) {
            ex_head = (char *) malloc(sizeof(char) * tall + 4);
            tall+=4;
            ex_head[tall-1]='\0';
            strcpy(ex_head, head);
            free(head);
            head = ex_head;
        }
        let=getchar();
    }
    printf("Введённая строка: %s\n", head);
    free(head);
    return 0;
}
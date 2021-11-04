#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str_in();

int main() {
    char *str;
    str=str_in();
    printf("Введённая строка: %s\n", str);
    free(str);
    return 0;
}

char *str_in(){
    char *head, *ex_head;
    int let, i=0, tall, j;
    head=(char*)malloc(4*sizeof(char));
    tall=4;
    for (j=0; j<4; j++)
        head[j]='\0';
    let=getchar();
    while (let!=EOF){
        head[i]=let;
        i++;
        if (i==tall-2) {
            ex_head = (char *) malloc(sizeof(char) * tall + 4);
            tall+=4;
            for (j=1; j<5; j++)
                ex_head[tall-j]='\0';
            strcpy(ex_head, head);
            free(head);
            head = ex_head;
        }
        let=getchar();
    }
    return (head);
}
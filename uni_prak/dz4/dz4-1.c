#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void lprint(int, int);
int *first_scan(int, int *);

int main(int argc, char **argv){
    int *arr=NULL;
    int fd, l, j=0;
    if (argc!=2)
        return 1;
    fd=open(argv[1], O_RDONLY);
    if (fd==-1)
        return 2;

    arr= first_scan(fd, &j);

    scanf("%d", &l);
    while (l!=0){
        if (l>j){
            printf("Строка №%d отсутвует в файле, введите другую или 0 для завершения\n", l);
            scanf("%d", &l);
            continue;
        }
        lprint(fd, arr[l-1]);
        putchar('\n');
        scanf("%d", &l);
    }
    close(fd);
    free(arr);
    return 0;
}

int *first_scan(int fd, int *i){
    char let=0;
    int pos=0, *head;
    long flag=1;
    head=malloc(sizeof(int));
    head[*i]= 0;
    while (flag){
        flag=read(fd, &let, 1);
        while (let!='\n'&&flag){
            flag=read(fd, &let, 1);
            pos++;
        }
        head = realloc(head, sizeof(int) * (++(*i)+1));
        head[*i] = ++pos; //начало записи информации об (i+1)-й строке
    }
    return head;
}

void lprint(int fd, int pos){//печать в файле с файловым дискриптором fd строки,
    char let=0;              //начинающейся с элемента под номером pos
    long flag=1;
    lseek(fd, pos, SEEK_SET);
    while (let!='\n'&&flag){
        printf("%c", let);
        flag=read(fd, &let, 1);
    }
}
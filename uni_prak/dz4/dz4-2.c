#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

//подобие функций из задания 4-1
void head(FILE *, int *, int, char *);
int *first_scan(int, int *);
void lprint(int, int);

int main(int argc, char **argv) {
    FILE* f;
    int fd, k=10, i, flag[3]={0,0,0};//[0]:="-n"; [1]:="-c"; [2]:="-v"
    if (argc<2)
        return 1;
    for (i=0; i<argc; i++){
        if (!strcmp(argv[i], "-n"))
            flag[0]=1;
        else if (!strcmp(argv[i], "-c"))
            flag[1]=1;
        else if (!strcmp(argv[i], "-v"))
            flag[2]=1;
    }

    for (i=1; i<argc; i++){
        f= fopen(argv[i], "r");
        if (!f){
            if (!strcmp(argv[i], "-n")||!strcmp(argv[i], "-c")) {
                k = atoi(argv[i+1]);
                if (!k) {
                    k=10;
                }
            }
            continue;
        }
        head(f, flag, k, argv[i]);
    }

    return 0;
}


void head(FILE *fin, int *arr, int num, char *name){
    int *str_arr=NULL;
    struct stat data;
    int fd, j=0, i;//j:= вобщее кол-во строк в файле
    int let;
    if (arr[2])
        printf("\n==> %s <==\n", name);

    fd= fileno(fin);
    fstat(fd, &data);
    str_arr= first_scan(fd, &j);

    if ((arr[0]&&num>0)||(!arr[0]&&!arr[1]))
        for (i=0; i<num&&i<j; i++){
            lprint(fd, str_arr[i]);
            putchar('\n');
        }
    else if (arr[0]&&num<0){
        num*=-1;
        for (i=0; i<j-num; i++){
            lprint(fd, str_arr[i]);
            putchar('\n');
        }
    }
    else if (arr[1]&&num>0){
        fseek(fin, 0, SEEK_SET);
        printf(" %d\n", num);
        for (i=0; i<num; i++){
            let=putchar(getc(fin));
        }
    }
    else if (arr[1]&&num<0){
        fseek(fin, 0, SEEK_SET);
        for (i=0; i<data.st_size+num; i++)
            putchar(getc(fin));
    }
    putchar('\n');
    free(str_arr);
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
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void last_word(int, int, int);
int del_lines(int, int, char *);

int main(int argc, char **argv){
    struct stat data;
    int fd, n=atoi(argv[2]), m=atoi(argv[3]), k;
    char let=0;
    if (argc!=4)
        return 1;
    fd=open(argv[1], O_RDWR);
    if (fd==-1){
        fd=open(argv[1], O_CREAT|O_RDWR, 0666);
        for (int i=0; i<n; i++){
            scanf("%c", &let);
            while (let!='\n'){
                write(fd, &let, 1);
                scanf("%c", &let);
            }
            write(fd, &let, 1);
        }
    }

    last_word(fd, m, n);

    fstat(fd, &data);
    printf("%ld %ld %ld\n", data.st_ino, data.st_size, data.st_nlink);
    scanf("%d", &k);
    if (k)
        fd=del_lines(fd, k, argv[1]);

    close(fd);

    return 0;
}

void last_word(int fd, int len, int n){
    char *word, let=0;
    int i, count, flag=0, pos;

    word=malloc(1);
    word[0]=0;
    read(fd, &let, 1);

    for (int j=0; j<n; j++){
        count=0;
        while (let!='\n'&&let!=EOF) {
            if (let==' ')
                read(fd, &let, 1);
            i = 0;
            while (let != ' ' && let != EOF && let != '\n') {
                word = realloc(word, i + 2);
                word[i++] = let;
                word[i + 1] = 0;
                count++;
                read(fd, &let, 1);
            }
            if (let != '\n') {
                free(word);
                word = malloc(1);
                word[0] = 0;
            }
        }

        if (count>len){
            pos=lseek(fd, 0, SEEK_CUR);
            lseek(fd, -1, SEEK_END);
            read(fd, &let, 1);
            if (let!='\n'){
                let='\n';
                write(fd, &let, 1);
            }
            write(fd, word, strlen(word));
            lseek(fd, pos, SEEK_SET);
            flag++;
        }
        read(fd, &let, 1);
    }

    if (!flag){
        printf("в файле нет строк длины больше заданной\n");
    }
}

int del_lines(int fd, int k, char *name){
    int temp, count=0, pos=-1, i;
    char let='0';
    read(fd, &let, 1);
    lseek(fd, 2, SEEK_END);
    while (count!=k&&pos!=0){
        lseek(fd, -1, SEEK_CUR);
        pos=lseek(fd, 0, SEEK_CUR);
        read(fd, &let, 1);
        if (let=='\n'){
            count++;
        }
        lseek(fd, -1, SEEK_CUR);
    }

    if (!pos){
        close(fd);
        fd=open(name, O_TRUNC);
        printf("ok");
        return fd;
    }
    lseek(fd, 1, SEEK_CUR);

    lseek(fd, 0, SEEK_SET);
    let=0;
    for (i=0; i<k&&let!=EOF; i++){
        read(fd, &let, 1);
        while (let!='\n'&&let!=EOF) {
            read(fd, &let, 1);
        }
    }

    if (let==EOF||pos<=lseek(fd, 0, SEEK_CUR)){
        close(fd);
        fd=open(name, O_TRUNC);
        return fd;
    }

    temp=open("teamf.txt", O_CREAT|O_RDWR|O_TRUNC, 0600);
    while (lseek(fd, 0, SEEK_CUR)!=pos){
        read(fd, &let, 1);
        write(temp, &let, 1);
    }
    let=EOF;
    write(temp, &let, 1);

    close(fd);
    fd=open(name, O_TRUNC|O_WRONLY);
    lseek(temp, 0, SEEK_SET);
    while (let!=EOF&&count<100){
        read(temp, &let, 1);
        write(fd, &let, 1);
    }
    close(temp);
    return fd;
}
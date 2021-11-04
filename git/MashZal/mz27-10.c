//так как по условию, вводится сначала число, а потом строка, то после окончания ввода строк требуется ввести число перед вводом exit

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    pid_t pid;
    int fd, x2, len2, buf, fd_arr[2], fd_arr2[2], i;
    char str[81], ex='*';
    pipe(fd_arr); // сын -> отец
    pipe(fd_arr2); // отец -> сын
    if (argc!=2)
        return 1;
    fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0777);
    if ((pid=fork())==-1){
        fprintf(stderr, "fork error");
        return 2;
    }
    else if (!pid){
        int x, len;
        close(fd_arr[0]);
        close(fd_arr2[1]);
        while (1){
            read(fd_arr2[0], &buf, sizeof(int)); //
            scanf("%d", &x);
            len = read(0, str, 80);
            str[len-1]='\0';
            if (!strcmp(str, "exit")){
                write(fd_arr[1], &x, sizeof(int));
                write (fd_arr[1], str, len);
                close (fd_arr[1]);
                exit (0);
            }
            else
                str[len-1]='\n';
            lseek(fd, 0, SEEK_END);
            write(fd_arr[1], &x, sizeof(int)); // x в поток
            write(fd_arr[1], str, len); // str в поток
            write(fd, str, len); // str в файл
        }
    }
    //wait(NULL);
    buf=1;
    close(fd_arr2[0]);
    write(fd_arr2[1], &buf, sizeof(int));
    while (1){
        read(fd_arr[0], &x2, sizeof(int)); // чтение из потока х
        len2 = read(fd_arr[0], str, 80); // чтение из потока str
        str[len2 - 1] = '\0';
        if (!strcmp(str, "exit")) {
            close(fd_arr[0]);
            close(fd_arr[1]);
            close(fd);
            return 0;
        }

        lseek(fd, 0, SEEK_END);
        if (x2<len2&&x2){
            if (((strlen(str))%2)==1){
                str[(strlen(str))/2]='*';
                i=1;
                x2--;
                while (x2!=1&&x2!=2&&x2){
                    str[(strlen(str))/2+i]='*';
                    str[(strlen(str))/2-i]='*';
                    x2-=2;
                    i++;
                }
                if (x2==1)
                    str[(strlen(str))/2-i]='*';
                else if (x2==2){
                    str[(strlen(str))/2+i]='*';
                    str[(strlen(str))/2-i]='*';
                }
            }
            else{
                i=0;
                while (x2!=1&&x2){
                    str[(strlen(str))/2+i]='*';
                    str[(strlen(str))/2-1-i]='*';
                    x2-=2;
                    i++; 
                }
                if (x2 == 1)
                    str[strlen(str) / 2 - i-1] = '*';
            }
            str[len2 - 1] = '\n';
        }
        else if (x2){
            for (i=0; i<x2; i++){
                str[i] = '*';
            }
            str[x2] = '\n';
            len2 = x2+1;
        }
        else {
            str[len2 - 1] = '\n';
        }

        write(fd, str, len2);
        write(fd_arr2[1], &buf, sizeof(int)); 
    }
}

#include <stdio.h>
#include <sys/dirent.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void rec_dir_print(DIR *, int);

int main() {
    char *name=NULL;
    DIR *d;
    struct dirent *info;
    chdir ("."); //дислокация в начале работы
    d = opendir(".");
    name = getcwd(NULL, PATH_MAX);
    rec_dir_print(d, 0);
    return 0;
}

void rec_dir_print(DIR *d, int flag){
    struct dirent *data = readdir(d);
    DIR *ex;
    char *path;
    printf("%s\n", getcwd(NULL, PATH_MAX));
    //поиск первого каталога (если вообще есть) после "." и ".."
    while (data&&(data->d_type!=DT_DIR ||(!strcmp(data->d_name, ".") || !strcmp(data->d_name, ".."))))
            data = readdir(d);
    if (data==NULL){
        chdir("..");
        if (!flag)
            printf("NO DIRS INSIDE\n");
        return;
    }
    flag++; //показатель того, что в папке уровнем выше есть вложенный каталог
    path = getcwd(NULL, PATH_MAX);
    strcat(path, "/");
    strcat(path, data->d_name);
    chdir(path);
    ex= opendir(".");
    free(path);
    rec_dir_print(ex, 0);
    data = readdir(d);
    while (data){ //проверка наличия иных каталогов в данном
        if (data->d_type!=DT_DIR ||(!strcmp(data->d_name, ".") || !strcmp(data->d_name, ".."))){
            data = readdir(d);
            continue;
        }
        path = getcwd(NULL, PATH_MAX);
        strcat(path, "/");
        strcat(path, data->d_name);
        chdir(path);
        free(path);
        ex= opendir(".");
        rec_dir_print(ex, 0);
        data = readdir(d);
    }
    chdir("..");
}
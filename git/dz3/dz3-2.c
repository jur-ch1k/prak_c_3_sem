#include <stdio.h>
#include <stdlib.h>

void del_line(FILE *, int );

int main(int argc, char **argv){
    int len;
    FILE *f_in;
    if (argc!=3)
        return 1;
    f_in= fopen(argv[1], "r+");
    if (!f_in)
        return 2;
    len= atoi(argv[2]);

    del_line(f_in, len);
    fclose(f_in);
    return 0;
}

void del_line(FILE *f, int len){
    int count=0, i;
    char sym;
    long pos;
    fread(&sym, sizeof(char), 1, f);
    while (!feof(f)){
        pos= ftell(f);
        while(sym!='\n'&&!feof(f)){
            fread(&sym, sizeof(char), 1, f);
            count++;
        }
        if (count==len){
            fseek(f, pos-1, SEEK_SET);
            for (i=0; i<len; i++)
                putc('\0', f);
        }
        fread(&sym, sizeof(char), 1, f);
        count=0;
    }
}
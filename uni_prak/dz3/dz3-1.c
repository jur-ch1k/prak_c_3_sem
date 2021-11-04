#include <stdio.h>

int copyfilez(FILE *, FILE *, FILE *);
void printfile(FILE *, int);

int main(int argc, char **argv) {
    //файлы содержащие тип double
    FILE *f1, *f2, *f_out;
    int i, j;
    double x;
    //проверка правильности ввода
    if (argc!=4)
        return 1;
    f1= fopen(argv[1], "r");
    f2= fopen(argv[2], "r");
    f_out= fopen(argv[3], "w+");
    if (!f1&&!f2&&!f_out)
        return 2;
    //копирование в новый файл и вывод
    i=copyfilez(f1, f2, f_out);
    fclose(f_out);
    f_out= fopen(argv[3], "r");
    printfile(f_out, i);
    putchar('\n');
    //закрытие файлов
    fclose(f1);
    fclose(f2);
    fclose(f_out);
    return 0;
}

int copyfilez(FILE *f1_in, FILE *f2_in, FILE *new_f_out){
    double dig1, dig2;
    int i=0;
    fread(&dig1, sizeof(double), 1, f1_in);
    fread(&dig2, sizeof(double), 1, f2_in);

    while (!feof(f1_in)&&!feof(f2_in)) {
        if (dig1 < dig2) {
            fwrite(&dig1, sizeof(double), 1, new_f_out);
            fread(&dig1, sizeof(double), 1, f1_in);
            i++;
        }
        else {
            fwrite(&dig2, sizeof(double), 1, new_f_out);
            fread(&dig2, sizeof(double), 1, f2_in);
            i++;
        }
    }

    if (feof(f1_in))
        while (!feof(f2_in)){
            fwrite(&dig2, sizeof(double), 1, new_f_out);
            fread(&dig2, sizeof(double), 1, f2_in);
            i++;
        }
    else
        while (!feof(f1_in)){
            fwrite(&dig1, sizeof(double), 1, new_f_out);
            fread(&dig1, sizeof(double), 1, f1_in);
            i++;
        }
    return i;
}

void printfile(FILE *new_f_out, int i){
    double dig;
    int j;
    for (j=0; j<i; j++){
        fread(&dig, sizeof(double), 1, new_f_out);
        printf("%lf ", dig);
    }
}
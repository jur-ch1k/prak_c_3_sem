#include <stdio.h>
#include "myfunc.h"

void print_bin(unsigned int);
void sort(int*, int);
int numofones(unsigned int);

int main(){
    int i, size;

    printf("Введите размер массива:\n");
    scanf("%d", &size);
    int numarr[size];

    printf("Введите массив:\n");
    for (i=0; i<size; i++)
        scanf("%d", &numarr[i]);


    for (i=0; i<size; i++){
        printf("%d = ", numarr[i]);
        print_bin(numarr[i]);
        putchar('\n');
    }

    sort(numarr, size);

    printf("Отсортированный массив:\n");
    for (i=0; i<size; i++)
        printf("%d ", numarr[i]);
    putchar('\n');

    return 0;
}

int numofones(unsigned int num){
    int sum=0, i, y;
    char str[32];
    str[32]='\0';

    for (i=0; i<32; i++)
        str[i]='0';
    i=31;
    while (num){
        y=num%2;
        str[i]=y+'0';
        i--;
        num/=2;
    }

    for (i=0; i<32; i++){
        sum+=str[i]-'0';
    }
    return sum;
}

void sort(int *arr, int s){
    int i, j, sw, sum1, sum2=0;
    char st[32];

    for (i=0; i<s-1; i++){
        for (j=i+1; j<s; j++){
            sum1=numofones(arr[i]);
            sum2=numofones(arr[j]);
            if (sum1>sum2){
                sw=arr[i];
                arr[i]=arr[j];
                arr[j]=sw;
            }
        }
    }
    for (i=0; i<s-1; i++)
        for (j=i+1; j<s; j++)
            if (numofones(arr[i])==numofones(arr[j])&&arr[i]<arr[j]){
                sw=arr[i];
                arr[i]=arr[j];
                arr[j]=sw;
            }
}

void print_bin(unsigned int a){
    int y=0, i;
    char b[32];
    b[32]='\0';

    for (i=0; i<32; i++)
        b[i]='0';
    i=31;
    while (a){
        y=a%2;
        b[i]=y+'0';
        i--;
        a/=2;
    }
    printf("%s", b);
}
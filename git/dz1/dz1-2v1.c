#include <stdio.h>
#include <stdlib.h>

struct list{
    char data;
    struct list *next;
};

struct list *new_list();
void del_list(struct list*);
void list2arr(struct list*, char*);
int count_list(struct list*);

int main(){
    int tall;
    struct list *head;

    head=new_list();
    tall=count_list(head);
    char str[tall+1];
    list2arr(head, str);
    del_list(head);
    str[tall+1]='\0';

    printf("%s", str);

    return 0;
}

struct list *new_list(){
    char x;
    if (scanf("%c", &x)!=1)
        return NULL;
    struct list *new= malloc(sizeof(struct list));
    new->data=x;
    new->next=new_list();
    return new;
}

void del_list(struct list *mylist){
    if (!mylist)
        return;
    del_list(mylist->next);
    free(mylist);
    mylist=NULL;
}

void list2arr(struct list *mylist, char *arr){
    int i=0;
    while (mylist){
        arr[i]=mylist->data;
        mylist=mylist->next;
        ++i;
    }
}

int count_list(struct list *mylist){
    int i=0;
    while (mylist){
        i++;
        mylist=mylist->next;
    }
    return i;
}
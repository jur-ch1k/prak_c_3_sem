#include <stdio.h>
#include <stdlib.h>

struct list{
    char* word;
    struct list *next;
};

struct list *read_line(FILE *, int);
struct list *add_word(char *, struct list *);
void del_list(struct list *);
void print_list(struct list *);

int main(int argc, char **argv) {
    FILE *text;
    int a;
    struct list *root;

    if (argc==2)
        text= fopen(argv[1], "r");
    else
        return 1;
    scanf("%d", &a);
    root=read_line(text, a);
    print_list(root);
    del_list(root);

    return 0;
}

struct list *read_line(FILE *f, int line){
    struct list *st;
    char let='\0';
    char *sl;
    int i, len=1;
    sl= malloc(sizeof(char));
    sl[0]='\0';
    
    for (i=1; i<line; i++)
        while (let!='\n'&&let!=EOF)
            fread(&let, sizeof(char), 1, f);

    if (let==EOF)
        return NULL;

    let='\0';
    while (let!='\n'&&let!=EOF){
        while (let!=' ') {
            fread(&let, sizeof(char), 1, f);
            sl=realloc(sl, len+1);
            sl[len]=let;
            sl[len+1]='\0';
        }
        st=add_word(sl, st);
        free(sl);
        sl= malloc(sizeof(char));
        sl[0]='\0';
    }
    free(sl);
    return st;
}

struct list *add_word(char *sl, struct list *head){
    struct list *ex;
    if (!head){
        head= malloc(sizeof(struct list));
        head->word=sl;
        head->next=NULL;
        return head;
    }
    ex=head;
    while (!ex->next)
        ex=ex->next;
    ex->next= malloc(sizeof(struct list));
    ex=ex->next;
    ex->word=sl;
    ex->next=NULL;
    return head;
}

void del_list(struct list *mylist){
    if (!mylist)
        return;
    del_list(mylist->next);
    free(mylist);
    mylist=NULL;
}

void print_list(struct list *mylist){
    while (mylist){
        printf("%s ", mylist->word);
        mylist=mylist->next;
    }
}
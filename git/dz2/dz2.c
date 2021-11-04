#include <stdio.h>
#include <stdlib.h>

struct tree{
    int data;
    struct tree *left;
    struct tree *right;
};

struct list{
    int data;
    struct list *next;
    struct list *prev;
};

struct tree *rec_new_node(struct tree *, int);
void loop_new_node(struct tree *, int);
void print_tree(struct tree *);
void del_tree(struct tree *);

struct list *tree2list(struct tree *, struct list *);
struct list *new_elem(struct list *, int);
void print_list(struct list *);
void del_elem(struct list **, int);
void del_list(struct list *);

int main() {
    struct tree *head;
    struct list *spisok;
    int x;
    head=NULL;
    spisok=NULL;
    printf("Введите дерево: ");
    scanf("%d", &x);

    //построение путём добавления новых листьев
    //признак конца ввода - 0, который не входит в дерево
    while (x!=0){
        head= rec_new_node(head, x);
        scanf("%d", &x);
    }

    printf("Исходное дерево: ");
    print_tree(head); //исходное дерево

    printf("\nВведите дополнительный лист: ");
    scanf("%d", &x);
    loop_new_node(head, x); //добавление листа нерекурсивно
    printf("Изменённое дерево: ");
    print_tree(head);

    spisok=tree2list(head, spisok);
    printf("\nПолучившися список: ");
    print_list(spisok);

    printf("\nВведите элемент для удаления из списка: ");
    scanf("%d", &x);
    del_elem(&spisok, x);
    printf("Получившися список: ");
    print_list(spisok);

    del_tree(head);
    del_list(spisok);
    return 0;
}

//рекурсивное добавление листьев
struct tree *rec_new_node(struct tree *root, int dig){
    if (!root) {
        root=malloc(sizeof(struct tree));
        root->data=dig;
        root->left=NULL;
        root->right=NULL;
    }
    else if(dig<root->data)
        root->left=rec_new_node(root->left, dig);
    else
        root->right=rec_new_node(root->right, dig);
    return root;
}

void loop_new_node(struct tree *root, int dig){
    struct tree *pred;
    int flag=-1;
    while (root&&(root->right||root->left)){
        if (dig>root->data){
            pred=root;
            flag=0;
            root=root->right;
        }
        else{
            pred=root;
            flag=1;
            root=root->left;
        }
    }
    if (root){
        if (dig > root->data) {
            root->right = malloc(sizeof(struct tree));
            root = root->right;
        } else {
            root->left = malloc(sizeof(struct tree));
            root = root->left;
        }
    }
    else{
        if (flag) {
            pred->left= malloc(sizeof(struct tree));
            root=pred->left;
        }
        else{
            pred->right= malloc(sizeof(struct tree));
            root=pred->right;
        }
    }
    root->data=dig;
    root->left=NULL;
    root->right=NULL;
}

//печать дерева с использованием прямого обхода
void print_tree(struct tree *root){
    if (!root)
        return;
    printf("%d ", root->data);
    print_tree(root->left);
    print_tree(root->right);
}

void del_tree(struct tree *root){
    if (!root)
        return;
    del_tree(root->left);
    del_tree(root->right);
    free(root);
}

struct list *new_elem(struct list *head, int dig){
    struct list *new, *st=NULL;
    new=malloc(sizeof(struct list));
    if (!head) {
        new->data = dig;
        new->next = NULL;
        new->prev = NULL;
        head=new;
        return head;
    }
    st=head;
    while (head->next)
        head=head->next;
    head->next=new;
    new->prev=head;
    new->next=NULL;
    new->data=dig;
    return st;
}

struct list *tree2list(struct tree *root, struct list *head){
    if (!root)
        return NULL;
    head=new_elem(head, root->data);
    tree2list(root->left, head);
    tree2list(root->right, head);
    return head;
}

void print_list(struct list *mylist){
    while (mylist){
        printf("%d ", mylist->data);
        mylist=mylist->next;
    }
}

void del_list(struct list *head){
    if (!head)
        return;
    del_list(head->next);
    free(head);
}

void del_elem(struct list **head, int dig){
    struct list *ex, *st=*head;
    if (st->data==dig){
        *head=st->next;
        free (st);
        st=*head;
        st->prev=NULL;
        return;
    }
    while (st->data!=dig){
        st=st->next;
    }
    if (!st->next){
        ex=st->prev;
        ex->next=NULL;
        free(st);
        return;
    }
    ex=st->prev;
    ex->next=st->next;
    free(st);
    st=ex->next;
    st->prev=ex;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define buf_clear while(getchar()!='\n');

typedef struct BST
{
    void *key;
    void *val;
    struct BST *left,*right;
} BST;

BST *root;

int name_compare(char *key1,char *key2)
{
    return(strcmp(key1,key2));
}

BST *bst_crt_node(char *p1,char *p2)
{
    BST *new=(BST *) malloc(sizeof(BST));
    new->key=p1;
    new->val=p2;
    return new;
}

BST *bst_insert(BST *temp,char *p1,char *p2, int (*compare)(char *,char *))
{
    if(root==NULL) root=bst_crt_node(p1,p2);
    else
    {
        if(compare(p1,temp->key)<0)
        {
            if(temp->left==NULL)
            {
                BST *new=bst_crt_node(p1,p2);
                temp->left=new;
                return new;
            }
            else bst_insert(temp->left,p1,p2,name_compare);
        }
        else if(compare(p1,temp->key)>0)
        {
            if(temp->right==NULL)
            {
                BST *new=bst_crt_node(p1,p2);
                temp->right=new;
                return new;
            }
            else bst_insert(temp->right,p1,p2,name_compare);
        }
    }
}

BST *bst_search(BST *temp,char *key, int (*compare)(char *,char *))
{
	if(temp==NULL) return NULL;
	else if(compare(key,temp->key)==0) return temp;
	else if(compare(key,temp->key)>0) return bst_search(temp->right,key,name_compare);
	else return bst_search(temp->left,key,name_compare);
}

BST *bst_del_node(BST *temp,void *key, int (*compare)(char *,char *))
{
    if(temp==NULL) return temp;
    if(compare(key,temp->key)<0)
        temp->left = bst_del_node(temp->left,key,name_compare);
    else if(compare(key,temp->key)>0)
        temp->right = bst_del_node(temp->right,key,name_compare);
    else
    {
        BST *temp1;
        if(temp->left==NULL)
        {
            temp1 = temp->right;
            free(temp);
            return temp1;
        }
        else if(temp->right==NULL)
        {
            temp1 = temp->left;
            free(temp);
            return temp1;
        }
        while(temp1->left!=NULL) temp1 = temp1->left;
        temp->key = temp1->key;
        temp->val = temp1->val;
        temp->right = bst_del_node(temp->right,temp1->key,name_compare);
    }
    return temp;
}

void bst_inorder_print(BST *temp)
{
    if(temp!=NULL)
    {
        bst_inorder_print(temp->left);
        printf("%s %s\n",(char *)temp->key,(char *)temp->val);
        bst_inorder_print(temp->right);
    }
}

void bst_free(BST *temp)
{
    if(temp==NULL) return;
    bst_free(temp->left);
    bst_free(temp->right);
    free(temp);
    return;
}

void edit()
{
    char name[10],num[12];
    BST *temp;
    while(1)
    {
        printf("\nNhap ten lien lac moi: ");
        gets(name);
        if(name[0]=='\0') break;
        temp=bst_search(root,name,name_compare);
        if(temp==NULL)
        {
            printf("\n ~ %s ~\nSo dien thoai: ",name);
            gets(num);
            if(num[0]=='\0') break;
            bst_insert(root,strdup(name),strdup(num),name_compare);
            printf("\n*** Da them ~ %s ~ vao danh ba ! ***\n\n",name);
        }
        else
        {
            while(1)
            {
                printf("\n*** Ten lien lac da ton tai ! ***\n\n ~ %s ~\nNhap so lien lac moi: ",name);
                gets(num);
                if(num[0]=='\0') break;
                temp->val=strdup(num);
                printf("\n\n*** Chinh sua thanh cong ! ***\n\n");
                break;
            }
        }
    }
}

void search()
{
    char name[10];
    BST *temp;
    while(1)
    {
        printf("\nNhap ten lien lac: ");
        gets(name);
        if(name[0]=='\0') break;
        temp=bst_search(root,name,name_compare);
        if(temp==NULL)
        {
            printf("\n\n*** Ten vua nhap khong co trong danh ba ! ***\nNhan Enter de nhap lai.......");
            buf_clear;
        }
        else printf("\n~ %s ~\n%s\n",(char *)temp->key,(char *)temp->val);
    }
}

void delete()
{
    char name[10];
    while(1)
    {
        printf("\nNhap ten lien lac can xoa: ");
        gets(name);
        if(name[0]=='\0') break;
        if(bst_search(root,name,name_compare)==NULL)
        {
            printf("\n\n*** Ten vua nhap khong co trong danh ba ! ***\nNhan Enter de nhap lai.......");
            buf_clear;
        }
        else
        {
            bst_del_node(root,name,name_compare);
            printf("\n *** Da xoa ~ %s ~ khoi danh ba ! ***\n\n",name);
        }
    }
}

int main()
{
    int opt;
    do
    {
        printf("\n----- PHONE BOOK -----\n");
        printf("\n");
        printf("1. Hien thi danh ba\n");
        printf("2. Tim kiem so lien lac theo ten\n");
        printf("3. Them/chinh sua so lien lac\n");
        printf("4. Xoa so lien lac\n");
        printf("5. Thoat chuong trinh\n");
        printf("\n");
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
                bst_inorder_print(root);
                break;

            case 2:
                buf_clear;
                search();
                break;

            case 3:
                buf_clear;
                edit();
                break;

            case 4:
                buf_clear;
                delete();
                break;
        }
    }
    while(opt!=5);
    bst_free(root);
    return 0;
}
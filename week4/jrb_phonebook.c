#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/home/long/Cprogramming/Cadvanced/libfdr/jrb.h"
#define buf_clear while(getchar()!='\n');

JRB tree;

void file_read(FILE *f)
{
    char name[10];
    Jval j;
    while(1)
    {
        j.s=(char *) malloc(12*sizeof(char));
        fscanf(f,"%s ",j.s);
        if(feof(f)) break;
        fgets(name,10,f);
        name[strlen(name)-1]='\0';
        jrb_insert_str(tree,strdup(name),j);
    }
    fclose(f);
}

void edit()
{
    char name[10];
    JRB temp;
    Jval j;
    while(1)
    {
        printf("\nNhap ten lien lac moi: ");
        gets(name);
        if(name[0]=='\0') break;
        temp=jrb_find_str(tree,strdup(name));
        if(temp==NULL)
        {
            printf("\n ~ %s ~\nSo dien thoai: ",name);
            j.s=(char *) malloc(12*sizeof(char));
            gets(j.s);
            if(j.s[0]=='\0')
            {
                free(j.s);
                break;
            }
            jrb_insert_str(tree,strdup(name),j);
            printf("\n*** Da them ~ %s ~ vao danh ba ! ***\n\n",name);
        }
        else
        {
            while(1)
            {
                printf("\n*** Ten lien lac da ton tai ! ***\n\n ~ %s ~\nNhap so lien lac moi: ",name);
                j.s=(char *) malloc(12*sizeof(char));
                gets(j.s);
                if(j.s[0]=='\0')
                {
                    free(j.s);
                    break;
                }
                strcpy(temp->val.s,j.s);
                printf("\n\n*** Chinh sua thanh cong ! ***\n\n");
                break;
            }
        }
    }
}

void delete()
{
    char name[10];
    JRB temp;
    while(1)
    {
        jrb_traverse(temp,tree) printf("%s %s\n",temp->key.s,temp->val.s);
        printf("\nNhap ten lien lac can xoa: ");
        gets(name);
        if(name[0]=='\0') break;
        temp=jrb_find_str(tree,strdup(name));
        if(temp==NULL)
        {
            printf("\n\n*** Ten vua nhap khong co trong danh ba ! ***\nNhan Enter de nhap lai.......");
            buf_clear;
        }
        else
        {
            jrb_delete_node(temp);
            printf("\n *** Da xoa ~ %s ~ khoi danh ba ! ***\n\n",name);
        }
    }
}

int main()
{
    int opt;
    FILE *f;
    JRB temp;
    tree=make_jrb();
    f=fopen("phonebook.txt","r");
    if(f!=NULL) file_read(f);
    do
    {
        printf("\n----- PHONE BOOK -----\n");
        printf("\n");
        printf("1. Hien thi danh ba\n");
        printf("2. Them/chinh sua so lien lac\n");
        printf("3. Xoa so lien lac\n");
        printf("4. Thoat chuong trinh\n");
        printf("\n");
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
                jrb_traverse(temp,tree) printf("%s %s\n",temp->key.s,temp->val.s);
                break;

            case 2:
                buf_clear;
                edit();
                break;

            case 3:
                buf_clear;
                delete();
                break;

            case 4:
                f=fopen("phonebook.txt","w");
                jrb_traverse(temp,tree) fprintf(f,"%s %s\n",temp->val.s,temp->key.s);
                fclose(f);
                jrb_free_tree(tree);
                break;
        }
    }
    while(opt!=4);
    return 0;
}
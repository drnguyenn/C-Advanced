#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/long/Cprogramming/Cadvanced/bt-5.0.0/inc/btree.h"
#define buf_clear while(getchar()!='\n');

BTA *tree;

void display()
{
    int size;
    char name[10]="\0",num[12];
    // btsel(tree,"",num,12,&size);
    btpos(tree,1);
    while(btseln(tree,name,num,12,&size)==0)
    {
        printf("\n%s %s %d",name,num,size);
    }
}

void edit()
{
    int size;
    char name[10],num[12];
    while(1)
    {
        printf("\n- Nhap ten lien lac moi: ");
        gets(name);
        if(name[0]=='\0') break;
        if(btsel(tree,name,num,12,&size)!=0)
        {
            printf("\n ~ %s ~\nSo dien thoai: ",name);
            gets(num);
            if(num[0]=='\0') break;
            btins(tree,name,num,strlen(num)+1);
            printf("\n*** Da them ~ %s ~ vao danh ba ! ***\n\n",name);
        }
        else
        {
            while(1)
            {
                printf("\n*** Ten lien lac da ton tai ! ***\n\n ~ %s ~\n- Nhap so lien lac moi: ",name);
                gets(num);
                if(num[0]=='\0') break;
                btupd(tree,name,num,strlen(num)+1);
                printf("\n\n*** Chinh sua thanh cong ! ***\n\n");
                break;
            }
        }
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
        if(btdel(tree,name)!=0)
        {
            printf("\n\n*** Ten vua nhap khong co trong danh ba ! ***\nNhan Enter de nhap lai.......");
            buf_clear;
        }
        else
        {
            btdel(tree,name);
            printf("\n *** Da xoa ~ %s ~ khoi danh ba ! ***\n\n",name);
        }
    }
}

int main()
{
    int opt;
    btinit();
    tree=btopn("phonebook.dat",0,0);
    if(tree==NULL)
    {
        tree=btcrt("phonebook.dat",0,0);
        printf("\n*** Data file created ! ***\n");
        tree=btopn("phonebook.dat",0,0);
    }
    
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
                display();
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
                btcls(tree);
                break;
        }
    }
    while(opt!=4);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int int_compare(const void *x,const void *y)
{
    int m,n;
    m= *((int*)x);
    n= *((int*)y);
    return m-n;
}

int search(void *buf,int size,int l,int r,void *item,int (*compare)(const void *,const void *))
{
    int i,res;
    if(r < l) return -1;
    i = (l + r)/2;
    res = compare(item,(char*) buf+(size*i) );
    if(res==0)
    return i;
    else if(res < 0) return search(buf, size, l, i-1, item, compare);
    else return search(buf, size, i+1, r, item, compare);
}

int main()
{
    int a[100],n = 100,item = 5,res;
    for(int i=0;i<n;i++) a[i] = rand();
    qsort(a, n, sizeof(int), int_compare);
    res = search(a,sizeof(int),0,n-1,&item,int_compare);
    printf("%d\n",res);
    return 0;
}
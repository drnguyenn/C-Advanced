#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(type,a,b) { type temp=a; a=b; b=temp; }

void quicksort_2way(int a[],int L,int R)
{
    int pivot=a[L+rand()% (R-L+1)];
    int i=L,j=R;
    while(i<j)
    {
        while(a[i]<pivot) i++;      
        while(a[j]>pivot) j--;      
        if(i<=j)
        {
            if(i<j) swap(int,a[i],a[j]); 
            i++;
            j--;
        }
    }
    if(L<j) quicksort_2way(a,L,j);
    if(i<R) quicksort_2way(a,i,R);
}

void quicksort_3way(int a[],int L,int R)
{
    int pivot=a[L+rand()% (R-L+1)];
    int i=L,j=R,p=L-1,q=R-1,k;
    while(i<=j)
    {
        while(a[i]<pivot) i++;      
        while(a[j]>pivot) j--;      
        if(i<=j)
        {
            if(i<j) swap(int, a[i], a[j]); 
            if(j==L || i==R) break;
            if(a[i]==pivot)
            {
                swap(int,a[p],a[i]);
                p++;
            }
            if(j<p-1)
            {
                i++;
                break;
            }
            if(a[j]==pivot)
            {
                swap(int,a[q],a[j]);
                q--;
            } 
            if(i==j)
            {
                if(i==L) break;
                else
                {
                    i++;
                    break;
                }
            }
            i++;
            j--;
            if(p==q) break;
        }
    }
    if(q!=R-1)
        for(k=q+1;k<=R-1;k++)
        {
            swap(int,a[i],a[k]);
            i++;
        }
    if(p!=L)
        for(k=p-1;k>=L;k--)
        {
            swap(int,a[j],a[k]);
            j--;
        }
    if(L<j) quicksort_3way(a,L,j);
    if(i<R-1) quicksort_3way(a,i,R);
}

int main()
{
    int *a,*b,n,i;
    time_t start,end;
    printf("\nNhap so phan tu can sap xep: ");
    scanf("%d",&n);
    a=(int *) malloc(n*sizeof(int));
    b=(int *) malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    {
        /*printf("Nhap phan tu thu %d: ",i+1);
        scanf("%d",&a[i]);*/
        a[i]=rand();
        b[i]=a[i];
    }
    start=time(NULL);
    quicksort_2way(a,0,n-1);
    end=time(NULL);
    // for(i=0;i<n;i++) printf("%d ",a[i]);
    printf("\nRun in %f seconds.\n",difftime(end,start));

    start=time(NULL);
    quicksort_3way(b,0,n-1);
    end=time(NULL);
    // for(i=0;i<n;i++) printf("%d ",b[i]);
    printf("\nRun in %f seconds.\n",difftime(end,start));
    free(a);
    free(b);
    return 0;
}
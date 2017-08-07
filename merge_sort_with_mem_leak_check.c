//Author : Kalyan Pingali
//Date : August 6th 2017
//Contact : pnglkalyan@gmail.com

#include <stdio.h>
#include <stdlib.h>


int made=0;
int freed=0;

void *mymalloc(size_t n){
    made++;
    
    void *r=(void*)malloc(n);
    
    return r;
    
}

void myfree(void *ptr){
    if(ptr){
        free(ptr);
        freed++;
    }
}



//#define Debug
#ifdef Debug
    #define malloc mymalloc
    #define free myfree
    void check(){
    if(made==freed){
        printf("\nNo mem leaks!\n");
    }
    else{
        printf("\nMem leak!!!\n");
    }
}
#endif
#ifndef Debug
void check(){
    return;
}
#endif

void merge(int *A, int *L, int nL, int *R, int nR){
    int n = nL+nR;
    int r=0,l=0,a=0;
    while(l<nL&&r<nR){
        if(L[l]<R[r]){
            A[a]=L[l];
            l++;
        }
        else{
            A[a]=R[r];
            r++;
        }
        a++;
    }
    while(l<nL) A[a++] = L[l++];
    while(r<nR) A[a++] = R[r++];
}

void merge_sort(int *A, int n){
    if(n<2) return;
    int mid = n/2;
    int * L = (int*)malloc(mid*sizeof(int));
    int * R = (int*)malloc((n-mid)*sizeof(int));
    int i;
    for(i=0;i<mid;i++){
        L[i]=A[i];
    }
    for(i=mid;i<n;i++){
        R[i-mid]=A[i];
    }
    merge_sort(L,mid);
    merge_sort(R,n-mid);
    merge(A,L,mid,R,n-mid);
    free(L);//free(R);
}


int main()
{
    int A[10] = {5,22,3,22,71,100,7,18,9,50};
    int c,n;
    n = sizeof(A)/sizeof(A[0]);
    merge_sort(A,n);
    for(c=0;c<n;c++){
        printf(" %d",A[c]);
    }
    check();
    return 0;
}

#include<stdio.h>
#define SIZE 6
void reserse(int *b, int n);
int main(){
    int a[SIZE]={1,3,4,5,6,7};
    for(int i=0; i<SIZE; i++)
        printf("%d ", a[i]);
    printf("\n");
    reserse(a, SIZE);
    for(int i=0; i<6; i++)
        printf("%d ", a[i]);
    return 0;
}

void reserse(int *b, int n){
    int *p=b+n-1;
    while(p>b){
        int temp=*p;
        *p=*b;
        *b=temp;
        p--;
        b++;
    }
}
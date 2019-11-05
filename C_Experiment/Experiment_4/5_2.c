// coding: GB2312
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 1000
void make(int a[]);     //生成随机数组
int sum(int a[], int c[]);     //计算不同数的次数
void put(int a[], int c[]);    //以序对方式输出数组
int main(){
    int array[N],count[N]={0}, total;  //array数组用来存储随机数，count数组用来
    make(array);
    total=sum(array, count);
    printf("Total numbers: %d\n", total);
    put(array, count);
}

void make(int a[]){
    srand(time(NULL));
    int n=N;
    while(n--)
        a[n]=rand()%10001;
}
int sum(int a[], int c[]){
    for(int i=0; i<N; i++){
        int flag=1;
        
        for(int j=0; j<i; j++)  //之前出现过了就舍去
            if(a[i]==a[j]){
                flag=0;
                break;
            }

        if(flag){
            c[i]++;     //次数先加一
            for(int j=i+1; j<N;j++)
                if(a[i]==a[j])
                    c[i]++;     //后面有相同的，次数就加一
        } 
    }

    int total=0;
    for(int i=0; i<N; i++)
        if(c[i])
            total++;    //计算次数
    return total;
}
void put(int a[], int c[]){
    int nline=0;
    for(int i=0; i<N; i++)
        if(c[i]){
            printf("(%5d,%d)  ", a[i], c[i]);   //输出
            nline++;
            if(nline && nline%5==0)
                printf("\n");      //换行
        }
}

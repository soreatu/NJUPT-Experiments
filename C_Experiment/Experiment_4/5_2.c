// coding: GB2312
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 1000
void make(int a[]);     //�����������
int sum(int a[], int c[]);     //���㲻ͬ���Ĵ���
void put(int a[], int c[]);    //����Է�ʽ�������
int main(){
    int array[N],count[N]={0}, total;  //array���������洢�������count��������
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
        
        for(int j=0; j<i; j++)  //֮ǰ���ֹ��˾���ȥ
            if(a[i]==a[j]){
                flag=0;
                break;
            }

        if(flag){
            c[i]++;     //�����ȼ�һ
            for(int j=i+1; j<N;j++)
                if(a[i]==a[j])
                    c[i]++;     //��������ͬ�ģ������ͼ�һ
        } 
    }

    int total=0;
    for(int i=0; i<N; i++)
        if(c[i])
            total++;    //�������
    return total;
}
void put(int a[], int c[]){
    int nline=0;
    for(int i=0; i<N; i++)
        if(c[i]){
            printf("(%5d,%d)  ", a[i], c[i]);   //���
            nline++;
            if(nline && nline%5==0)
                printf("\n");      //����
        }
}

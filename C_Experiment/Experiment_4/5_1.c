#include<stdio.h>
#define N 10
void input(int a[]);
void output(int a[]);
int maxnum(int a[]);
int minnum(int a[]);
int find(int a[], int n);
double ave(int a[]);
void sort(int a[]);
int main(){
    int array[N], max, min, index, x;
    double average;
    printf("Please enter 10 integers: \n");
    input(array);
    printf("array: \n");
    output(array);
    max = maxnum(array);
    printf("max:%3d\n", max);
    min = minnum(array);
    printf("min:%3d\n", min);
    printf("Please enter the integer you want to find: ");
    scanf("%d", &x);
    index = find(array, x);
    if(index==-1)
        printf("Not found!\n");
    else
        printf("index is %d\n", index);
    average = ave(array);
    printf("average is %.2lf\n", average);
    sort(array);
    printf("after sorting: \n");
    output(array);
    return 0;
}

void input(int a[]){
    int n = N;
    while(n--)
        scanf("%d", &a[N-n-1]);
}
void output(int a[]){
    int n = N; 
    while(n--)
        printf("%3d",a[N-n-1]);
    printf("\n");
}
int maxnum(int a[]){
    int n = N-1;
    int max = a[n];
    while(n--)
        if(a[n]>max)
            max = a[n];
    return max;
}
int minnum(int a[]){
    int n = N-1;
    int min = a[n];
    while(n--)
        if(a[n]<min)
            min = a[n];
    return min;
}
int find(int a[], int n){
    int i = N;
    while(i--)
        if(a[i] == n)
            return i;
    return -1;
}
double ave(int a[]){
    int sum = 0, n = N;
    while(n--)
        sum+=a[n];
    return (double)sum/N;

}
void sort(int a[]){
    for(int i=0; i<N-1; i++)
        for(int j=i; j<N-1; j++)
            if(a[j]>a[j+1])
                a[j]^=a[j+1]^=a[j]^=a[j+1];
}

#include<stdio.h>
#define N 3
void input(int a[][N]);
void output(int a[][N]);
void rev(int a[][N]);
int sum(int a[][N]);
int main(){
    int a[N][N];
    input(a);
    output(a);
    rev(a);
    output(a);
    printf("sum is %2d\n",sum(a));
    return 0;
}

void input(int a[][N]){
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            scanf("%d", &a[i][j]);
}
void output(int a[][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++)
             printf("%3d", a[i][j]);
        printf("\n");
    }
}
void rev(int a[][N]){
    for(int i=0; i<N-1; i++)
        for(int j=i+1; j<N; j++)
            a[i][j]^=a[j][i]^=a[i][j]^=a[j][i];
}
int sum(int a[][N]){
    int total=0;
    for(int i=0; i<N; i++)
        total+=a[i][i];
    return total;
}

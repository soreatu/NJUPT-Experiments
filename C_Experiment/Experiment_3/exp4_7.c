#include<stdio.h>
int judge(int a, int b);
int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    printf("%d", judge(n, m));
    return 0;
}

int judge(int a, int b){
    if(a % b)
        b=judge(b, a%b);
    return b;
}
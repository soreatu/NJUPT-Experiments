#include<stdio.h>
int main(){
    int a, m = 0;
    scanf("%d", &a);
    for(; a; a /= 10)
        m = m * 10 + a % 10;
    printf("%d\n", m);
}
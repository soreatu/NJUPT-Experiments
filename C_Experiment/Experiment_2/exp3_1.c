#include<stdio.h>
#include<math.h>
int main(){
    int n;
    scanf("%d", &n);
    double a = 1.0, b = 1.0, term = 0.0, sum = 0.0;
    for(int i = 0; i<n; i++){
        b += a;
        a = b-a;
        term = (double)b/(double)a;
        sum += (i%2?-1:1)*term;
    }
    printf("sum = %lf", sum);
}
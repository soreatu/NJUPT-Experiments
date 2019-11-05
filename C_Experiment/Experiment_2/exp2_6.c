// coding: GB 2312
#include<stdio.h>
#include<math.h>
int main(){
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);
    if(a+b>c && a+c>b && b+c>a){
        if(a==b && b==c)
            printf("构成等边三角形\n");
        else if(fabs(a*a+b*b-c*c)<1e-6 || fabs(a*a+c*c-b*b)<1e-6 || fabs(c*c+b*b-b*b)<1e-6){
            if(a==b || b==c || a==c)
                printf("构成等腰直角三角形\n");
            else
                printf("构成直角三角形\n");
        }
        else if(a==b || b==c || c==a)
            printf("构成等腰三角形\n");
        else
            printf("构成一般三角形\n");
    }
    else
        printf("不能构成三角形\n");
    return 0;
}
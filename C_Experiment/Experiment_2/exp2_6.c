// coding: GB 2312
#include<stdio.h>
#include<math.h>
int main(){
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);
    if(a+b>c && a+c>b && b+c>a){
        if(a==b && b==c)
            printf("���ɵȱ�������\n");
        else if(fabs(a*a+b*b-c*c)<1e-6 || fabs(a*a+c*c-b*b)<1e-6 || fabs(c*c+b*b-b*b)<1e-6){
            if(a==b || b==c || a==c)
                printf("���ɵ���ֱ��������\n");
            else
                printf("����ֱ��������\n");
        }
        else if(a==b || b==c || c==a)
            printf("���ɵ���������\n");
        else
            printf("����һ��������\n");
    }
    else
        printf("���ܹ���������\n");
    return 0;
}
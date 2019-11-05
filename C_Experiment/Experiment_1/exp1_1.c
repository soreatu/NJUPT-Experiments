#include<stdio.h>

int main(){
    int a, b;
    int sum, diff, pro, Int_quo, Int_ave;
    double Dou_quo, Dou_ave;
    scanf("%d %d", &a, &b);
    sum = a + b;
    diff = a - b;
    pro = a * b;
    Int_quo = a / b;
    Int_ave = (a + b) / 2;
    Dou_quo = (double)a / b;
    Dou_ave = (a + b) / 2.0;
    printf("sum = %d\ndiff = %d\npro = %d\nInt_quo = %d\nINt_ave = %d\n", sum, diff, pro,                                                                 Int_quo, Int_ave);
    printf("Dou_quo = %lf\nDou_ave = %lf\n", Dou_quo, Dou_ave);

    return 0; 
}

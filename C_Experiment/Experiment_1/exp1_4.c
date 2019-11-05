#include<stdio.h>
#include<math.h>
#define PI acos(-1)
#define PRICE 10.0
int main(){
    double radius, height, area, fees;
    scanf("%lf %lf", &radius, &height);
    area = radius * radius * PI * 2 + 2 * PI *radius * height;
    fees = PRICE *area;
    printf("area = %.2lf, fees = %.2lf", area, fees);
    return 0;
}
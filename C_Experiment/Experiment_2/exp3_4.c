// coding: GB2312
#include<stdio.h>
#include<math.h>
int main(){
    int a, b, newline = 0;
    printf("请输入范围a和b: ");
    scanf("%d %d", &a, &b);
    while(!(a>=10 && b<=1000 && a<=b)){
        printf("请重新输入a和b(范围在[10,1000]内，且a<b): ");
        scanf("%d %d", &a, &b);
    }
    for(int k = a; k<=b; k++){
        int flag = 1;
        
        for(int i = 2; i<=sqrt(k); i++)
            if(k % i == 0){
                flag = 0;
                break;
            }
        if(flag){
            newline++;
            printf("%d  ", k);
            if(newline!=0 && newline % 5 == 0)
                printf("\n");
        }
    }
    if(newline == 0)
        printf("在%d和%d之间无质数", a, b);
}
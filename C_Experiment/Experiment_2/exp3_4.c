// coding: GB2312
#include<stdio.h>
#include<math.h>
int main(){
    int a, b, newline = 0;
    printf("�����뷶Χa��b: ");
    scanf("%d %d", &a, &b);
    while(!(a>=10 && b<=1000 && a<=b)){
        printf("����������a��b(��Χ��[10,1000]�ڣ���a<b): ");
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
        printf("��%d��%d֮��������", a, b);
}
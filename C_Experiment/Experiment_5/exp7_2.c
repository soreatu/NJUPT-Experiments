// coding: GB2312
#include<stdio.h>
#include<ctype.h>
#define SIZE 100
void find(char st[], char result[][SIZE/2], int (*pf)(int), int flag);

int main(){
    char st1[SIZE];
    char st2[SIZE];
    char username[SIZE/2]={0};
    char password[SIZE/2]={0};
    //读取输入
    fgets(st1, SIZE, stdin);
    fgets(st2, SIZE, stdin);
    //调用函数
    find(st1, &username, isdigit, 1);
    find(st2, &password, isalpha, 0);
    //打印结果
    printf("string1:%s  username:%s\n", st1, username);
    printf("string2:%s  password:%s\n", st2, password);

    return 0;
}
//因为要修改username和password字符串的内容，所以传入数组名的地址；
//isdigit和isalpha的原型都是int xxx(int )，所以函数指针要相对应
//flag用来判断是取奇数位还是偶数位
void find(char st[], char result[][SIZE/2], int (*pf)(int), int flag){
    int i=0;
    while(st[i]){
        if( pf( (int)st[i] ) ){  //函数形参是int型，强制转换一下
            int j=i;
            while(st[j]){
                st[j]=st[j+1];
                j++;
            }
        }
        else
             i++;
    }
    i=0;
    while(st[i]){
        if(flag?i%2==0:i%2 && st[i]!='\n')//fgets会连同换行也读入
            (*result)[i/2]=st[i];
        i++;
    }
}
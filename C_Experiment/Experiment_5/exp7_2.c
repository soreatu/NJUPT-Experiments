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
    //��ȡ����
    fgets(st1, SIZE, stdin);
    fgets(st2, SIZE, stdin);
    //���ú���
    find(st1, &username, isdigit, 1);
    find(st2, &password, isalpha, 0);
    //��ӡ���
    printf("string1:%s  username:%s\n", st1, username);
    printf("string2:%s  password:%s\n", st2, password);

    return 0;
}
//��ΪҪ�޸�username��password�ַ��������ݣ����Դ����������ĵ�ַ��
//isdigit��isalpha��ԭ�Ͷ���int xxx(int )�����Ժ���ָ��Ҫ���Ӧ
//flag�����ж���ȡ����λ����ż��λ
void find(char st[], char result[][SIZE/2], int (*pf)(int), int flag){
    int i=0;
    while(st[i]){
        if( pf( (int)st[i] ) ){  //�����β���int�ͣ�ǿ��ת��һ��
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
        if(flag?i%2==0:i%2 && st[i]!='\n')//fgets����ͬ����Ҳ����
            (*result)[i/2]=st[i];
        i++;
    }
}
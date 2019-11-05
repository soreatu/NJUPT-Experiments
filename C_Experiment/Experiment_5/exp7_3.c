#include<stdio.h>
#include<stdlib.h>
int main(){
    char string[100];
    fgets(string, 100, stdin);
    int i=0;
    while(string[i]){
        if(string[i]==' '){
            int j=i;
            while(string[j]){
                string[j]=string[j+1];
                j++;
            }
        }
        else{
            i++;
        }
    }
    printf("%s\n", string);
    return 0;
}
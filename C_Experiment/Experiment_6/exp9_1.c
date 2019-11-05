#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main(){
    FILE * fp;
    char ch;

    fp=fopen("D:\\f1.txt", "w+");
    if(fp==0){
        printf("File error\n");
        exit(1);
    }
    while(scanf("%c", &ch)){
        if(ch=='#')
            break;
        fputc(ch, fp);
    }
    fclose(fp);
    
    fp=fopen("D:\\f1.txt", "r+");
    if(fp==0){
        printf("File error\n");
        exit(1);
    }
    while(!feof(fp)){
        ch=fgetc(fp);
        if(isdigit(ch))
            fputc(ch, stdout);
        if(isalpha(ch))
            fputc(toupper(ch), stdout);
    }
    fclose(fp);
    
    return 0;
}
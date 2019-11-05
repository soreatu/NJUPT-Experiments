#include<stdio.h>
void DrawTriangle(int n, char c);
int main(){
    DrawTriangle(5, '*');
    DrawTriangle(10, '#');
    return 0;
}

void DrawTriangle(int n, char c){
    for(int i=0; i<n; i++){
        int cspace=n-i;
        int cchar=2*i+1;
        while(cspace--)
            printf(" ");
        while(cchar--)
            printf("%c", c);
        printf("\n");
    }
}
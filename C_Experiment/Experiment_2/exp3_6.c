#include<stdio.h>
int main(){
    int n;
    scanf("%d", &n);               
    int m = n%2?n/2+1:n/2;                    
    for (int line = 0; line<m; line++){  
        for(int s = 0;s<m-line;s++)
            printf("  ");          
        for(int j=0;j<line*2+1;j++)
        printf("* ");           
        printf("\n");             
    }

    for(int line = n%2?n-m:n-m-1;line>0;line--){
        for( int s = 0;s<(n%2?n-m-line+2:n-m-line+1);s++)
            printf("  ");
        for(int j=0;j<line*2-1;j++)
            printf("* ");
            printf("\n");
    }
}
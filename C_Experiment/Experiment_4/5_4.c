#include<stdio.h>
#include<stdlib.h>
int main(){
    int n;
    printf("Please enter n: ");
    scanf("%d", &n);
    int **a=(int **)malloc(n*sizeof(int *));
    for(int i=0; i<n; i++){
        a[i]=(int *)malloc(n*sizeof(int ));
        for(int j=0; j<n; j++)
            a[i][j]=0;
    }
    int s=1, row=0, col=0, flag=1;
    while(s<=n*n){
        a[row][col]=s++;
        switch(flag){
            case 1: col++;
                    if(col==n-1 || a[row][col+1])
                        flag=2;
                    break;
            case 2: row++;
                    if(row==n-1 || a[row+1][col])
                        flag=3;
                    break;
            case 3: col--;
                    if(col==0 || a[row][col-1])
                        flag=4;
                    break; 
            case 4: row--;
                    if(row==0 || a[row-1][col])
                        flag=1;
                    break;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            printf("%5d", a[i][j]);
        printf("\n");
    }
    for(int i=0; i<n; i++)
        free(a[i]);
    free(a);
    return 0;
}
#include<stdio.h>
void swap1(int a, int b )
{  	int temp= a;
    a = b;
    b = temp; 
}

void swap2(int *a, int b )
{   int temp= *a;
*a = b;
b = temp; 
}

void swap3(int *a, int *b )
{  int temp = *a;
*a = *b;
*b = temp; 
}

void swap4(int *a, int *b )
{  int *temp = a;
a=b;
b=temp;
}

int main()
{
	int x=1,y=2;
swap4( &x , &y );
	printf("x=%d,y=%d\n",x,y);
	return 0;
}

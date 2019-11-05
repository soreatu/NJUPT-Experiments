#include<stdio.h>
typedef struct Date{
    int year;
    int month;
    int day;
}Date;

int checkDate(Date date);

int main(){
    Date date;
    scanf("%d %d %d", &date.year, &date.month, &date.day);
    while(checkDate(date)==0){
        printf("Please input again.\n");
        scanf("%d %d %d", &date.year, &date.month, &date.day);
    }
    printf("Your Date:%4d %2d %2d", date.year, date.month, date.day);
    return 0;
}

int checkDate(Date date){
    switch(date.month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
                if(date.day>=1 && date.day<=31)
                    return 1;
                else
                    return 0;
        case 4:
        case 6:
        case 9:
        case 11:
                if(date.day>=1 && date.day<=30)
                    return 1;
                else
                    return 0;
        case 2:
                if(date.year % 100 != 0 && date.year % 4 ==0 || date.year % 400 == 0)
                    if(date.day>=1 && date.day<=29)
                        return 1;
                    else 
                        return 0;
                else
                    if(date.day>=1 && date.day<=28)
                        return 1;
                    else 
                        return 0;
        default:
                return 0;
    }
}
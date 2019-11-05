#include<stdio.h>
#include<stdlib.h>

typedef struct Student{
    char ID[20];
    char name[30];
    int age;
    double score;
}Student;

void CreateFile(int n);
void ReadOut(int n);
void Sort(int n);

int main(){
    int n;
    printf("Please input the number of students\n");
    scanf("%d", &n);

    printf("\nPlease input the information of students\n");
    CreateFile(n);
    
    printf("\nHere shows the information of students\n");
    ReadOut(n);

    printf("\nHere shows the information of students after sorting\n");
    Sort(n);

    return 0;
}

void CreateFile(int n){
    Student *stu=(Student *)malloc(n*sizeof(Student));
    for(int i=0; i<n; i++)
        scanf("%s %s %d %lf", stu[i].ID, stu[i].name, &stu[i].age, &stu[i].score);

    FILE * fp =fopen("D:\\Info.dat", "wb");
    if(fp==0){
        printf("File error!\n");
        exit(1);
    }
    
    fwrite(stu, sizeof(Student), n, fp);
    fclose(fp);

}

void ReadOut(int n){
    FILE * fp;
    fp=fopen("D:\\Info.dat", "rb");
    if(fp==0){
        printf("File error!\n");
        exit(1);
    }

    Student *stu=(Student *)malloc(n*sizeof(Student));
    for(int i=0; i<n; i++){
        fread(&stu[i], sizeof(Student), 1, fp);
        printf("ID:%20s name:%30s age:%3d score:%4.2lf\n", stu[i].ID, stu[i].name, stu[i].age, stu[i].score);
    }
    fclose(fp);
}

void Sort(int n){
    FILE * fp;
    fp=fopen("D:\\Info.dat", "rb");
    if(fp==0){
        printf("File error!\n");
        exit(1);
    }

    Student *stu=(Student *)malloc(n*sizeof(Student));
    int *index=(int *)malloc(n*sizeof(int));
    for(int i=0; i<n; i++){
        fread(&stu[i], sizeof(Student), 1, fp);
        index[i]=i;
    }

    for(int i=0; i<n-1; i++){
        double max=stu[index[i]].score;
        int i_max=i;
        for(int j=i+1; j<n; j++)
            if(max<stu[index[j]].score){
                max=stu[index[j]].score;
                i_max=j;
            }
        int temp=index[i_max];
        index[i_max]=index[i];
        index[i]=temp;
    }

    for(int i=0; i<n; i++)
        printf("ID:%20s name:%30s age:%3d score:%4.2lf\n", stu[index[i]].ID, stu[index[i]].name, stu[index[i]].age, stu[index[i]].score);
    
    fclose(fp);
}
/*Create a structure called Student and create members for name, dob, dept and reg_no,. create read and display function,
and create a function to print students of specific dept.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
   char name[25];
   char dob[12];
   char dept[20];
   int age;
} Student;

void read(Student *student){
    printf("Enter the details of Student\n");
    printf("Enter name : ");
    scanf("%s", student->name);
    printf("Enter date of birth : ");
    scanf("%s", student->dob);
    printf("Enter deptartment : ");
    scanf("%s", student->dept);
    printf("Enter age : ");
    scanf("%d", &student->age);
    printf("\n");
}

void display(Student *student){
    printf("The details of the students are, \n");
    printf("Name : %s\nDob : %s\nDeptartment : %s\nAge : %d\n", student->name, student->dob, student->dept, student->age);
    printf("\n");
}

void displayDeptStudent(Student *students, char *dept, int n){
    for(int i = 0; i < n; i++)
        if(strcmp((students+i)->dept, dept)==0) display(students+i);
}

int main(){
    int n;
    printf("Enter the no of students : ");
    scanf("%d", &n);

    Student *students = (Student *) malloc (n * sizeof(Student));
    if(!students){
        printf("Memory allocation failed. \n");
        return 1;
    }

    for(int i = 0; i < n; i++) read(students+i);

    for(int i = 0; i < n; i++) display(students+i);

    char dept[20];
    printf("Enter the deptartment, for the students : ");
    scanf("%s", dept);

    displayDeptStudent(students, dept, n);


    free(students);
    return 0;
}
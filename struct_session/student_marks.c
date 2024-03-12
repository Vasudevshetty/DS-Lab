/*Define a structure called student with members: name, reg_no, marks in 3 tests and average_marks.
Develop a menu driven program to perform the following by writing seperate function with each opertion: a) read information of N students,
b) display student information, and c) Calculate the average of best two test marks of each student.
Note: Illustrate the use of pointer to an array of structure and allocate memory dynamically using malloc()/calloc()/realloc().*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure for student
typedef struct Student
{
    char name[30];
    int reg_no;
    int marks[3];
    float average_marks;
} Student;

float calculateAverageMarks(const int marks[])
{
    int sum = 0, min = marks[0];
    for (int i = 0; i < 3; i++)
    {
        sum += marks[i];
        min = marks[i] < min ? marks[i] : min;
    }
    return (sum - min) / 2.0;
}

Student *initStudent(const char *name, int reg_no, int marks[])
{
    Student *student = (Student *)malloc(sizeof(Student));
    if (!student)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strncpy(student->name, name, sizeof(student->name));
    student->name[sizeof(name)] = '\0';
    student->reg_no = reg_no;
    for (int i = 0; i < 3; i++)
        student->marks[i] = marks[i];
    student->average_marks = calculateAverageMarks(marks);
    return student;
}

void displayInfo(const Student *student)
{
    printf("\nThe information of the student are,\nName : %s\nRegistration no : %d\nMarks : %d %d %d\nAverage Marks : %.2f\n\n",
           student->name, student->reg_no, student->marks[0], student->marks[1], student->marks[2], student->average_marks);
}

void readStudent(Student *students, int i)
{
    printf("\nEnter the details of the student, \n");
    char name[24];
    int reg_no, marks[3];
    printf("Enter name : ");
    scanf("%s", name);
    printf("Enter reg no: ");
    scanf("%d", &reg_no);
    printf("Enter marks : ");
    scanf("%d %d %d", &marks[0], &marks[1], &marks[2]);
    students[i] = *initStudent(name, reg_no, marks);
    printf("\n");
}

// function for displaying information of N students
int main()
{
    int N;
    printf("Enter number of students: ");
    scanf("%d", &N);

    Student *students = (Student *)malloc(sizeof(Student) * N);
    if (!students)
    {
        printf("Memory allocatin failed.\n");
        exit(1);
    }

    int choice;
    do
    {
        printf("\nMenu\n");
        printf("1. Read Student Information\n");
        printf("2. Display Student Information\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        for (int i = 0; i < N && choice != 3; i++)
        {
            switch (choice)
            {
            case 1:
                readStudent(students, i);
                break;
            case 2:
                displayInfo(students + i);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid Choice... Try again.\n");
                break;
            }
        }
    } while (choice != 3);
    return 0;
}
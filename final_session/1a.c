/*a) Define a structure called Student with the members: Name, Reg_no, marks in 3 tests and average_ marks.
Develop a menu driven program to perform the following by writing separate function for each operation: a) read
information of N students b) display student’s information c) to calculate the average of best two test marks of each
student.
Note: Allocate memory dynamically and illustrate the use of pointer to an array of structure.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *strCpy(const char *src, char *dest)
{
    char *temp = dest; // to store the starting address to return

    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';
    return temp;
}

typedef struct Student
{
    char *name;
    int reg_no;
    int marks[3];
    float average_marks;
} Student;

float calculateAverage(int marks[])
{
    int min = marks[0], sum = 0;
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
    student->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    if (!student->name)
    {
        printf("Memory allocation failed.\n");
        free(student);
        exit(1);
    }
    student->name = strCpy(name, student->name);
    student->reg_no = reg_no;
    for (int i = 0; i < 3; i++)
        student->marks[i] = marks[i];
    student->average_marks = calculateAverage(marks);
    return student;
}

Student *read()
{
    int reg_no, marks[3];
    char name[25];
    printf("Enter name : ");
    scanf("%s", name);
    printf("Enter reg no : ");
    scanf("%d", &reg_no);
    printf("Enter marks : ");
    scanf("%d %d %d", &marks[0], &marks[1], &marks[2]);
    printf("\n");
    return initStudent(name, reg_no, marks);
}

void display(const Student *student)
{
    printf("\nThe details of the student are, \n");
    printf("Name : %s\nReg no : %d\n", student->name, student->reg_no);
    printf("Marks : %d %d %d\n", student->marks[0], student->marks[1], student->marks[2]);
    printf("Average Marks : %.2f\n\n", student->average_marks);
}

void freeStudents(Student **students, int n)
{
    for (int i = 0; i < n; i++)
        free(*(students + i));
}

int main()
{
    int n;
    printf("Enter the number of students : ");
    scanf("%d", &n);
    Student **students = (Student **)malloc(sizeof(Student *) * n);
    if (!students)
    {
        printf("Memory allcoation failed.\n'");
        exit(1);
    }

    int choice;
    bool readFlag = false;

    do
    {
        printf("\nMenu\n");
        printf("1. Read\n2. Display\n3. Exit\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            if (readFlag == true)
            {
                readFlag = false;
                freeStudents(students, n);
            }
            for (int i = 0; i < n; i++)
                *(students + i) = read();
            break;
        case 2:
            for (int i = 0; i < n; i++)
                display(*(students + i));
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Enter valid choice only...\n");
            break;
        }
        if (choice == 1)
            readFlag = true;
    } while (choice != 3);
    freeStudents(students, n);
    free(students);
    return 0;
}

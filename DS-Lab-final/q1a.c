/* Define a structure called Student with the members: Name, Reg_no, marks in 3 tests and
average_ marks.
Develop a menu driven program to perform the following by writing separate function for each
operation: a) read information of N students b) display student’s information c) to calculate the
average of best two test marks of each student.
Note: Allocate memory dynamically and illustrate the use of pointer to an array of structure.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    char name[30];
    int reg_no;
    int marks[3];
    float average_marks;
} Student;

// function prototypes.
Student *initStudent(const char *, int, int[]);
float calculateAverageMarks(const Student *);
void displayInfo(const Student *);

Student *initStudent(const char *name, int reg_no, int marks[])
{
    Student *student = (Student *)malloc(sizeof(Student));
    if (!student)
    {
        printf("Memory allocatin failed.\n");
        exit(1);
    }
    strncpy(student->name, name, sizeof(student->name));
    student->name[sizeof(student->name) - 1] = '\0';
    student->reg_no = reg_no;
    for (int i = 0; i < 3; i++)
        student->marks[i] = marks[i];
    student->average_marks = calculateAverageMarks(student);
    return student;
}

float calculateAverageMarks(const Student *student)
{
    int min = student->marks[0] < student->marks[1] ? student->marks[0] < student->marks[2] ? student->marks[0] : student->marks[2] : student->marks[1] < student->marks[2] ? student->marks[1]
                                                                                                                                                                            : student->marks[2];
    return (student->marks[0] + student->marks[1] + student->marks[2] - min) / 2.0;
}

void displayInfo(const Student *student)
{
    printf("The information of the student are,\nName : %s\nRegistration no : %d\nMarks : %d %d %d\nAverage Marks : %.2f\n",
           student->name, student->reg_no, student->marks[0], student->marks[1], student->marks[2], student->average_marks);
}

int main()
{
    Student *students = (Student *)malloc(sizeof(Student) * 5);
    int marks[] = {24, 25, 23};
    students[0] = *initStudent("vasu", 1324, marks);
    displayInfo(&students[0]);
    free(students);
    return 0;
}
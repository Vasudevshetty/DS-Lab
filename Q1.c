/*Define a structure called student with members: name, reg_no, marks in 3 tests and average_marks.
Develop a menu driven program to perform the following by writing seperate function with each opertion: a) read information of N students,
b) display student information, and c) Calculate the average of best two test marks of each student.
Note: Illustrate the use of pointer to an array of structure and allocate memory dynamically using malloc()/calloc()/realloc().*/

#include <stdio.h>
#include <stdlib.h>

// structure for student
struct student
{
    char name[30];
    int reg_no;
    int marks[3];
    float average_marks;
};

// function for reading information of N students
void readStudentInfo(struct student *students, int N)
{ // students is sent as a pointer to a array of structures.
    for (int i = 0; i < N; i++)
    {
        printf("Enter details of student %d,\n", i + 1);
        printf("Enter name : ");
        scanf("%s", students[i].name);
        printf("Enter Registration number : ");
        scanf("%d", &students[i].reg_no);
        printf("Marks in 3 tests: ");
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &students[i].marks[j]);
        }
        printf("\n");
    }
}

// function for calculating average marks , best of two in the marks of the students.
void calculateAverageMarks(struct student *students, int N)
{
    for (int i = 0; i < N; i++)
    {  
        // calculate the average of best two marks and assign to the structure.
        // The array is sorted so the last few elements are the best.
        students[i].average_marks = ((float)students[i].marks[1] + students[i].marks[2]) / 2.0;
        // type cast it & index are (n-2) and (n-1) respectively. (n = 3) marks array.;
    }
}

void sortMarks(struct student *students, int N)
{
    for (int i = 0; i < N; i++)
    {
        // sort the array so to get the best marks.
        for (int j = 0; j < 2; j++)
        {
            for (int k = j + 1; k < 3; k++)
            {
                if (students[i].marks[j] > students[i].marks[k])
                {
                    int temp = students[i].marks[j];
                    students[i].marks[j] = students[i].marks[k];
                    students[i].marks[k] = temp;
                }
            }
        }
    }
}

// function for displaying information of N students
void displayStudentInfo(struct student *students, int N)
{
    int anyStudents = 0; // Check if information is entered or not.
    int calculated = 0;  // Check if average marks is calculated or not.

    for (int i = 0; i < N; i++)
    {
        if (students[i].reg_no == 0)
            anyStudents = 1;
        if (students[i].average_marks == 0.0)
            calculated = 1;
    }

    if (anyStudents)
    {
        printf("No Students entered. Please select option 1 to enter student information\n");
        return;
    }
    else if (calculated)
    {
        printf("Average marks not calculated. Please select option 2 to calculate and select option 3 later.\n");
        return;
    }

    printf("Student Information:\n\n");
    for (int i = 0; i < N; i++)
    {
        printf("Student %d\n", i + 1);
        printf("Name : %s\n", students[i].name);
        printf("Registration number: %d\n", students[i].reg_no);
        printf("Marks in 3 tests are : ");
        for (int j = 0; j < 3; j++)
            printf("%d, ", students[i].marks[j]);
        printf("\nAverage marks (best of two): %.2f\n", students[i].average_marks);
        printf("\n");
    }
}

int main()
{
    int N;
    printf("Enter number of students: ");
    scanf("%d", &N);

    if (N == 0)
    {
        printf("No students..\nEnter a valid number: ");
        scanf("%d", &N);
    }

    /*We use calloc since upon dynamically creating a array of structures using malloc will create a array of structures with garbage value
    so as to initalise with 0(or respecive acc. to its type) can be done through calloc.*/
    struct student *students = (struct student *)calloc(N, sizeof(struct student));
    // struct student *students = (struct student *)malloc(N * sizeof(struct student)); (We can also use malloc, but cases cannot be handled.)

    if (students == NULL)
    {
        printf("Memory allocation failed\n Exiting.....");
        return 1;
    }
    int choice;
    do
    {
        printf("\n\n");
        printf("Menu\n");
        printf("1. Read Student Information\n");
        printf("2. Calculate Average Marks\n");
        printf("3. Display Student Information\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n\n\n");
        switch (choice)
        {
        case 1:
            readStudentInfo(students, N);
            sortMarks(students, N);
            break;
        case 2:
            calculateAverageMarks(students, N);
            break;
        case 3:
            displayStudentInfo(students, N);
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid Choice... Try again.\n");
            break;
        }
        printf("\n\n");
    } while (choice != 4);
    free(students);
    return 0;
}

// Please format the way you want, i.e the indentation on the terminal..
/*handled 2 cases, if not calculating average marks and not entering the information,
where one tries to display by printing appropriate messages.*/
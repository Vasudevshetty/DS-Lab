/*Define a structure called Time containing 3 integer members (hour, minute, seconds). Develop  a menu driven programme
to perform the following by writing seperate functions for each operations.
a) To read time. b) To display time. c) To Update time. d) Add two times by writing Add(T1, T2) returning a new time.
Update function increments the time by one second and return the new time (if the increment results in 60s, the second
member is set to zero and minute member is incremented by one. If the result is 60m, the minute member is set to zero,
and the hour member is incremented by one. Finally, when the hour member is 24, Time should be reset to zero.)
Note: Illustrate the use of pointer to a structure variable and passing and returning of structure type to and
fromt the function(both by value and reference.)*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Time
{
    int seconds;
    int minutes;
    int hours;
} Time;

Time *initTime(int hours, int minutes, int seconds)
{
    Time *time = (Time *)malloc(sizeof(Time));
    if (!time)
    {
        printf("Memory alloation failed.\n");
        exit(1);
    }
    time->hours = hours;
    time->minutes = minutes;
    time->seconds = seconds;
    return time;
}

// function to read time
Time *readTime()
{
    int hours, minutes, seconds;
    // handeled case where the time format goes invalid.
    printf("Enter time (HH MM SS): ");
    scanf("%d %d %d", &hours, &minutes, &seconds);

    return initTime(hours, minutes, seconds);
}

// function to display time
void displayTime(const Time *t)
{
    printf("Time is %02d : %02d : %02d", t->hours, t->minutes, t->seconds);
    printf("\n\n");
}

/* Arrow opertor(->) is used to access the ures members usings its pointer as demonstrated above.*/

// function to update time
void updateTime(Time *t)
{
    // this function is demonstrated using call by value.

    t->seconds++;
    if (t->seconds == 60)
    {
        t->seconds = 0;
        t->minutes++;
        if (t->minutes == 60)
        {
            t->minutes = 0;
            t->hours++;
        }
        if (t->hours == 24)
        {
            t->hours = 0;
        }
    }
}

// this function adds two times correspondigly checks the format of 24 and matches it.
Time *addTime(Time *T1, Time *T2)
{
    // this function demonstrates call by reference.
    int hours, minutes, seconds;

    seconds = T1->seconds + T2->seconds;
    minutes = T1->minutes + T2->minutes;
    hours = T1->hours + T2->hours;

    if (seconds >= 60)
    {
        seconds -= 60;
        minutes++;
    }
    if (minutes >= 60)
    {
        minutes -= 60;
        hours++;
    }
    if (hours >= 24)
        hours -= 24;

    return initTime(hours, minutes, seconds);
}

int main()
{
    Time *time;
    int choice;
    do
    {
        printf("Menu\n");
        printf("1. Read Time.\n");
        printf("2. Display Time.\n");
        printf("3. Update Time.\n");
        printf("4. Add Time.\n");
        printf("5. Exit.\n");
        printf("Enter choice : ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            time = readTime();
            break;
        case 2:
            displayTime(time);
            break;
        case 3:
            updateTime(time);
            displayTime(time);
            break;
        case 4:
            displayTime(addTime(readTime(), readTime()));
            break;
        case 5:
            printf("Exiting....\n");
            break;
        default:
            printf("Enter valid choice... Try again\n");
            break;
        }
    } while (choice != 5);

    return 0;
}
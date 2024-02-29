/*Define a structure called Time containing 3 integer members (hour, minute, seconds). Develop  a menu driven programme
to perform the following by writing seperate functions for each operations.
a) To read time. b) To display time. c) To Update time. d) Add two times by writing Add(T1, T2) returning a new time.
Update function increments the time by one second and return the new time (if the increment results in 60s, the second
member is set to zero and minute member is incremented by one. If the result is 60m, the minute member is set to zero,
and the hour member is incremented by one. Finally, when the hour member is 24, Time should be reset to zero.)
Note: Illustrate the use of pointer to a structure variable and passing and returning of structure type to and
fromt the function(both by value and reference.)*/

#include <stdio.h>

struct Time
{
    int seconds;
    int minutes;
    int hours;
};

// function to read time
void readTime(struct Time *t)
{
    // handeled case where the time format goes invalid.
    int isTimeValid = 0;
    do
    {
        printf("Enter time (HH MM SS): ");
        scanf("%d %d %d", &t->hours, &t->minutes, &t->seconds);
        printf("\n");

        if ((t->hours >= 0 && t->hours <= 23) && (t->minutes >= 0 && t->minutes <= 59) && (t->seconds >= 0 && t->seconds <= 59))
            isTimeValid = 1;
        else
            printf("Invalid Time format! Please enter a valid time.\n");
    } while (!isTimeValid);
}

// function to display time
void displayTime(const struct Time *t)
{
    printf("Time is %02d : %02d : %02d", t->hours, t->minutes, t->seconds);
    printf("\n\n");
}

/* Arrow opertor(->) is used to access the structures members usings its pointer as demonstrated above.*/

// function to update time
struct Time updateTime(struct Time t)
{
    // this function is demonstrated using call by value.

    t.seconds++;
    if (t.seconds == 60)
    {
        t.seconds = 0;
        t.minutes++;
        if (t.minutes == 60)
        {
            t.minutes = 0;
            t.hours++;
        }
        if (t.hours == 24)
        {
            t.hours = 0;
        }
    }
    return t;
}

// this function adds two times correspondigly checks the format of 24 and matches it.
struct Time addTime(struct Time *T1, struct Time *T2)
{
    // this function demonstrates call by reference.

    struct Time result;
    result.seconds = T1->seconds + T2->seconds;
    result.minutes = T1->minutes + T2->minutes;
    result.hours = T1->hours + T2->hours;

    if (result.seconds >= 60)
    {
        result.seconds -= 60;
        result.minutes++;
    }
    if (result.minutes >= 60)
    {
        result.minutes -= 60;
        result.hours++;
    }
    if (result.hours >= 24)
        result.hours -= 24;

    return result;
}

int main()
{
    struct Time currentTime = {};
    struct Time updatedTime = {};
    struct Time addedTime = {};
    // Initalised to 0 upon not reading.
    struct Time T1, T2;

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
            readTime(&currentTime);
            break;
        case 2:
            displayTime(&currentTime);
            break;
        case 3:
            updatedTime = updateTime(currentTime);
            currentTime = updatedTime;
            printf("Updated time is,\n");
            displayTime(&updatedTime);
            break;
        case 4:
            printf("Enter first Time to add,\n");
            readTime(&T1);
            printf("Enter second Time to add,\n");
            readTime(&T2);
            addedTime = addTime(&T1, &T2);
            printf("The added time is\n");
            displayTime(&addedTime);
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
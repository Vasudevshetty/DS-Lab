/*) Define a structure called Time containing 3 integer members (Hour, Minute, Second).Develop a menu driven
program to perform the following by writing separate function for each operation.
a) Read (T) :To read time b) Display (T):To display time c) update(T):To Update time d) Add(T1, T2) : Add two
time variables.
Update function increments the time by one second and returns the new time (if the incrementresults in 60
seconds, then the second member is set to zero and minute member is incrementedby one. If the result is 60
minutes, the minute member is set to zero and the hour member isincremented by one. Finally, when the hour
becomes 24, Time should be reset to zero. Whileadding two time variables, normalize the resultant time value as in
the case of update function. Note: Illustrate the use of pointer to pass time variable to different functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Time
{
    int hours, minutes, seconds;
} Time;

Time *initTime(int hours, int minutes, int seconds)
{
    Time *time = (Time *)malloc(sizeof(Time));
    if (!time)
    {
        printf("Memory allocatin failed.\n");
        exit(1);
    }
    time->hours = hours;
    time->minutes = minutes;
    time->seconds = seconds;
    return time;
}

Time *readTime()
{
    int hours, minutes, seconds;
    printf("Enter the time (HH:MM:SS) : ");
    scanf("%d %d %d", &hours, &minutes, &seconds);
    return initTime(hours, minutes, seconds);
}

void displayTime(const Time *time)
{
    printf("\nThe time is (HH:MM:SS) (24hr) => %02d : %02d : %02d\n", time->hours, time->minutes, time->seconds);
}

Time *addTime(const Time *time1, const Time *time2)
{
    int hours, minutes, seconds;
    hours = time1->hours + time2->hours;
    minutes = time1->minutes + time2->minutes;
    seconds = time1->seconds + time2->seconds;

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

void updateTime(Time *time)
{
    time->seconds++;
    if (time->seconds == 60)
    {
        time->seconds = 0;
        time->minutes++;
        if (time->minutes == 60)
        {
            time->minutes = 0;
            time->hours++;
        }
        if (time->hours == 24)
            time->hours = 0;
    }
}

int main()
{
    Time *time;
    int choice = 0;
    bool readFlag = false;

    do
    {
        printf("\nMenu\n");
        printf("1. Read\n2. Display\n3. Update\n4. Add Time\n5. Exit\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            if (readFlag)
                free(time);
            time = readTime();
            displayTime(time);
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
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
            break;
        }
        if (choice == 1)
            readFlag = true;
    } while (choice != 5);
    free(time);
    return 0;
}
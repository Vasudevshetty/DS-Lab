/*Define a structure called Time containing 3 integer members (Hour, Minute, Second).
Develop a menu driven program to perform the following by writing separate function for
each operation.
a) Read (T) :To read time b) Display (T):To display time c) update(T):To Update time d) Add
(T1, T2) : Add two time variables.
Update function increments the time by one second and returns the new time (if the increment
results in 60 seconds, then the second member is set to zero and minute member is incremented
by one. If the result is 60 minutes, the minute member is set to zero and the hour member is
incremented by one. Finally, when the hour becomes 24, Time should be reset to zero. While
adding two time variables, normalize the resultant time value as in the case of update function.
Note: Illustrate the use of pointer to pass time variable to different functions*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Time
{
    int hours;
    int minutes;
    int seconds;
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

Time *read()
{
    int hours, minutes, seconds;
    printf("Enter the time : ");
    scanf("%d %d %d", &hours, &minutes, &seconds);
    return initTime(hours, minutes, seconds);
}

void display(const Time *time)
{
    printf("The time is %d : %d : %d\n", time->hours, time->minutes, time->seconds);
}

void update(Time *time)
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
            if (time->hours == 24)
            {
                time->hours = 0;
            }
        }
    }
}

Time *add(const Time *time1, const Time *time2)
{
    int hours = time1->hours + time2->hours;
    int minutes = time1->minutes + time2->minutes;
    int seconds = time1->seconds + time2->seconds;

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

int main(){
    display(add(read(), read()));
    return 0;
}
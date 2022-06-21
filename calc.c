#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int time_to_sleep=15;
struct tm *p_cur_time=0,wake_time,*p_wake_time=0,custom_time; 
void menu();
void wake_x();
void bed(struct tm *p_temp_time);
void power_nap();
void settings();
void get_time();
void input_time();
void main()
{
    p_wake_time=&wake_time;
    menu();
    
}

void menu()
{   
    int i=0;
    char a;
    printf("1: I want to wake up at _ _ _ time\n"); 
    printf("2: I want to go to bed at _ _ _ time\n");
    printf("3: When do I wake up if I go to bed now?\n");
    printf("4: When do I wake up if I have a power nap?\n");
    printf("s: Adjust settings\n");
    printf("e: Exit\n");
    printf("   Enter choice ");
    a=getch();
    a=='1'   ? wake_x()
    : a=='2' ? get_time(), input_time(), bed(&custom_time)
    : a=='3' ? get_time(), bed(p_cur_time)
    : a=='4' ? power_nap() 
    : a=='s' ? settings()
    : a=='e' ? exit(0)
    : (printf("\nInvalid input. Try again\n\n"), menu());
    // i++;
    // printf("\nTest for exit %d\n",i); //due to recursion, lines after the ternary one get executed
    //as many times as menu() is called.
    //2 invalid inputs, 1 correct input =>  3 times printed
    //surprisingly, i++ only gets executed once. hmmm
    //might just have to use if else to use goto at this point
    //or just not have anything below that line
}
void wake_x()  //I want to wake at the following time
{
    printf("wake_X"); 
    // difftime(input_time, EPOCH value of ideal sleep cycles). show as long as EPOCH value greater than cur_time 
    //for loop's range might have to start from 1. instead of constantly printing get more sleep, print line at  6
    //cycles or last one to say to aim for this much or more sleep  
}
void input_time() //might have to initialize custom_time=cur_time
{
    char am_pm[3];
    int h,m;
    custom_time=*p_cur_time;   //done just to fill values of other members in struct.
    //else error occurs
    printf("\nInput time in format like 9:10 pm  ");
    scanf("%d:%d %s",&h,&m,&am_pm);
    strlwr(am_pm);
    if(am_pm=="pm" && h<12) h+=12;
    custom_time.tm_hour=h;
    custom_time.tm_min=m;
    _mktime64(&custom_time);
}
void get_time()
{
    time_t my_time=time(NULL); //gets system time in EPOCH format
    p_cur_time=localtime(&my_time);
    p_cur_time->tm_isdst=0; //change to 1 if you use Daylight Savings 
    wake_time=*p_cur_time;  //done just to fill values of other members in struct.
    //else error occurs
}
void bed(struct tm *p_temp_time)
{
    int i;
    char buff[9];
    printf("\nYou should set alarm to: \n");
    for(i=4;i<=6;i++) 
    {
        p_wake_time->tm_hour=p_temp_time->tm_hour;
        p_wake_time->tm_min=(p_temp_time->tm_min) + (i*90);
        _mktime64(&wake_time);
        strftime(buff,9,"%I:%M %p",p_wake_time);
        printf("\n%s\t(%.1f hours)",buff,i*1.5);
        if(i==4) printf(" Try sleeping more than this.");
    }
    getch();
}
void power_nap()
{
    printf("power_nap");
}
void settings() //could use pointer to change variable value locally but change would only be temporary. 
//probably file handling to have it be permanent change
{
    printf("settings");
    /*change:
    time to sleep 
    daylight savings time
    buffer for how many minutes later you're going to sleep
    */
}
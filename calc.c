#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int time_to_sleep=15;

void menu();
void wake_x();
void sleep_x();
void sleep_now();
void power_nap();
void settings();
void main()
{
    menu();
    
}

void menu()
{   
    int i=0;
    char a;
    printf("1: I want to wake up at _ _ _ time\n");
    printf("2: I want to sleep at _ _ _ time\n");
    printf("3: When do I wake up if I go to sleep now?\n");
    printf("4: When do I wake up if I have a power nap?\n");
    printf("s: Adjust settings\n");
    printf("e: Exit");
    printf("\nEnter choice ");
    a=getch();
    printf("\n%c\n",a);
    //try formatting this to see if it works in C
    a=='1'   ? wake_x()
    : a=='2' ? sleep_x()
    : a=='3' ? sleep_now()
    : a=='4' ? power_nap() 
    : a=='s' ? settings()
    : a=='e' ? exit(0)
    : (printf("Invalid input. Try again\n"), menu());
    i++;
    printf("\nTest for exit %d\n",i); //due to recursion, lines after the ternary one get executed
    //as many times as menu() is called.
    //2 invalid inputs, 1 correct input =>  3 times printed
    //surprisingly, i++ only gets executed once. hmmm
    //might just have to use if else to use goto at this point
    //or just not have anything below that line
}
void wake_x()
{
    printf("wake_X"); // printf statements are just placeholders for now to test if 
                      // correct functions get called or not
}
void sleep_x()
{
    printf("sleep_X");
}
void sleep_now()
{
    printf("sleep_now");
}
void power_nap()
{
    printf("power_nap");
}
void settings() //might need pointer to change variable value locally. also might need to have arguments for the remaining functions.
{
    printf("settings");
}
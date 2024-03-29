#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int time_to_sleep = 10;  // change this manually here or in settings
struct tm *p_cur_time = 0, wake_time, *p_wake_time = 0, custom_time;

void menu();
void wake_x();
void bed(struct tm *p_temp_time);
void power_nap();
void settings();
void get_time();
void input_time();

int main() {
  p_wake_time = &wake_time;
  menu();
  if (time_to_sleep > 0) {
    printf("\n\nAssuming you need %d minutes to fall asleep.", time_to_sleep);
    printf("\nAdjust value if needed in settings or manually in code.");
  }
  getch();  // Needed to pause output screen if using standalone .exe
  return 0;
}

void menu() {
  int i = 0;
  char a;

  printf("1: I want to wake up at _ _ _ time\n");
  printf("2: I want to go to bed at _ _ _ time\n");
  printf("3: When do I wake up if I go to bed now?\n");
  printf("4: When do I wake up if I have a power nap?\n");
  printf("s: Adjust settings\n");
  printf("e: Exit\n");
  printf("\nEnter choice ");

  a = getch();
    a == '1' ? get_time(), input_time(), wake_x() 
  : a == '2' ? get_time(), input_time(), bed(&custom_time) 
  : a == '3' ? get_time(), bed(p_cur_time) 
  : a == '4' ? get_time(), power_nap()
  : a == 's' ? settings()
  : a == 'e' ? exit(0)
  : (printf("\nInvalid input. Try again\n\n"), menu());
  // i++;
  // printf("\nTest for exit %d\n",i);
  // due to recursion, lines after the ternary statement keep getting executed
  // as long as invalid input is entered. 2 invalid inputs, 1 correct input =>
  // 3 times printed surprisingly, i++ only gets executed once. hmmm might just
  // have to use if else to use goto at this point or just not have anything
  // below that line
}
void wake_x()  // I want to wake at the following time
{
  char buff[9];
  int i, time_value[2];
  time_value[0] = p_cur_time->tm_hour * 60 + p_cur_time->tm_min; 
  // Ironically I am using wake_time struct to store ideal time to sleep.
  printf("Go to bed at: \n");
  for (i=6; i>=4; i--)
  {
    wake_time.tm_hour = custom_time.tm_hour;
    wake_time.tm_min = custom_time.tm_min - (i * 90) - time_to_sleep;
    _mktime64(p_wake_time);
    time_value[1] = wake_time.tm_hour * 60 + wake_time.tm_min;

    if (time_value[1] >= time_value[0]) {
      //To only print a time value if it is past current time
      strftime(buff, 9, "%I:%M %p", p_wake_time);
      printf("\n %s \t (%.1f hours)", buff, i * 1.5);
      
      if (i == 4) printf("\t Try sleeping more than this");
    }
  }  
  printf("\nPlease use choice 1 only when you are about to sleep.");
  printf("\nCurrent system time is used to calculate viable sleep times.");
  printf("\n So, some times  may not be shown if you use this quite earlier");
}

void input_time() {
  char am_pm[3];
  int h, m;
  custom_time = *p_cur_time;  // done just to fill values of other members in
                              // struct. else error occurs
  printf("\nInput time in format like 9:10 pm  ");
  scanf("%d:%d %s", &h, &m, &am_pm);
  strlwr(am_pm);
  if (strcmp(am_pm, "pm") == 0 && h < 12) {
    h += 12;
  } else if (strcmp(am_pm, "am") == 0 && h == 12) {
    h = 0;
  }
  custom_time.tm_hour = h;
  custom_time.tm_min = m;
  _mktime64(&custom_time);
}

void get_time() {
  time_t my_time = time(NULL);  // gets system time in EPOCH format
  p_cur_time = localtime(&my_time);
  p_cur_time->tm_isdst = 0;  // change to 1 if you use Daylight Savings
  wake_time = *p_cur_time;   // done just to fill values of other members in
                             // struct. else error occurs
}

// bed is the only function with input parameter
// because same logic can be used to calculate 
// ideal alarm using both current time & custom sleep time  

void bed(struct tm *p_temp_time) {
  int i;
  char buff[9];

  printf("\nYou should set alarm to: \n");
  for (i = 4; i <= 6; i++) {
    p_wake_time->tm_hour = p_temp_time->tm_hour;
    p_wake_time->tm_min = (p_temp_time->tm_min) + (i * 90) + time_to_sleep;

    _mktime64(&wake_time);
    strftime(buff, 9, "%I:%M %p", p_wake_time);

    printf("\n %s \t (%.1f hours)", buff, i * 1.5);
    if (i == 4) printf(" Try sleeping more than this.");
  }
}
void power_nap() {
  char nap[2][10];
  int i, nap_duration;

  for (i = 0, nap_duration = 20; i <= 1; i++, nap_duration += 70) {
    wake_time.tm_min = p_cur_time->tm_min + nap_duration + time_to_sleep;
    mktime(&wake_time);
    strftime(nap[i], 9, "%I:%M %p", &wake_time);
  }

  printf("\nYou should set alarm to \n%s (quick 20 min nap)", nap[0]); 
  printf("\nor %s (90 min nap. 1 full sleep cycle)", nap[1]);
}
void settings()  // could use pointer to change variable value locally but
                 // change would only be temporary.
// probably file handling to have it be permanent change
{
  printf("settings");

  /*change:
  time to sleep
  daylight savings time
  buffer for how many minutes later you're going to sleep
  */
}
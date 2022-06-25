## test
Program to find ideal morning alarm. Basically just copying [Sleep Calculator](https://sleep-calculator.com/) but I'm doing this to learn more, & test myself. Also, I have my browser set to be blocked after 10 pm so might as well make a simple .exe file to put on my desktop.

### Basic functionality
- [x] 1. wake at x (keep deducting 90 mins, show between 4 & 6 cycles)
- [x] 2. go to bed at x (add 90 mins, show at same cycles as above)
    - [x] call same f'n used for 3, just change arguement to custom user input.
- [x] 3. go to bed exactly now 
    - [x] convert to am/pm using strftime?
- [x] 4. power nap (wake up during N1,N2 stage or end of cycle)   
&nbsp; &nbsp; *check how the site has done this*
    - [x] doesn't show print statements inside main() along with getch. instead, ends automatically after few seconds

---
### Extra Functions after finishing above ones
- [ ] instead of time, if 'b' entered, go back to menu
- [ ] Order functions based on which ones may get called 1st. To improve code readability.
- [x] for go to beds & power naps, add 15 mins as time to sleep. inform user about this

- [ ] Settings:
- - [ ] Change time to sleep. *need to implement a way to make this change permanent. file handling prob*
- - [ ] Daylight savings time. *this should be permanent too* prob have program read from file & assign values to variables at start of execution
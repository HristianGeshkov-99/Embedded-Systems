/* 
* LED.h
*
* Created: 11/14/2019 9:01:58 AM
* Author: geshk
*/

/*
FRee hand

CLASS LED
?private method setcommand(0x44) ALWAYS .. led on

function(randnumber[])
{
setcommand(0x44)
Runcommand(rando


}

algorithm ?{
for (i=0, i<n, i++){
x = randNumber[i] + 1

}
						MAYBE ALWAYS HAVE A FUNCTION THAT CONVERTS AND SELECTS THE ADDRESS INSTEAD OF ALGORITHM
CLASS BUTTON 
?private method setcommand(0x42) ALWAYS ..listen to buttons
*/
#ifndef __LED_H__
#define __LED_H__


class LED
{
//variables
public:
protected:
private:

//functions
public:
	LED();
	~LED();
void SetCommand(char command);
void RunCommand(int d, char command);
//int* counter();
void showLED(int n, int randNumber[100]);
char dig2pat(char digit);
char dig2add(int digit);
void Reset();
void gamelost();
void displaychar(char address, char command);
void nextlevel(char command);
protected:
private:
	LED( const LED &c );
	LED& operator=( const LED &c );

}; //LED

class Button
{
public:
bool input(int n, int randNumber[100]);


private:
	Button();
	Button& operator=(const LED &c);

};

#endif //__LED_H__

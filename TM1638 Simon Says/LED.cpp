/* 
* LED.cpp
*
* Created: 11/14/2019 9:01:58 AM
* Author: geshk
*/
#define STB  0
#define STBLO  (PORTB &= ~(1<<0))
#define STBHI  (PORTB |= (1<<0))
#define CLK	 1
#define CLKLO  (PORTB &= ~(1<<1))
#define CLKHI  (PORTB |= (1<<1))
#define DIO	 2
#define DIOLO  (PORTB &= ~(1<<2))
#define DIOHI  (PORTB |= (1<<2))
#define led1 0xC1
#define led2 0xC3
#define led3 0xC5
#define led4 0xC7
#define led5 0xC9
#define led6 0xCB
#define led7 0xCD
#define led8 0xCF
#define F_CPU 8000000
#include <stdlib.h>
#include "LED.h"
#include <avr/io.h>
#include <util/delay.h>


// default constructor
LED::LED()
{

} //LED



// default destructor
LED::~LED()
{
} //~LED


void LED::showLED(int n, int randNumber[100]){
	int i;
	nextlevel(0b11111111); //turn all leds on
	_delay_ms(200);
	nextlevel(0b00000000); //turn all leds off
	_delay_ms(1000); // hiatus between levels
	
	for (i = 0; i < n; i++)
	{
		_delay_ms(250); // time between blinks
		RunCommand(randNumber[i], 5); //LSB determines if an LED is on or off
		_delay_ms(600); // duration of blinks
		RunCommand(randNumber[i], 1);
	}
}


char LED::dig2pat(char digit){ //converts digit to the command pattern for the display
	
	if (digit == 0) {return 0b00111111;}
	else if (digit == 1) {return 0b00000110;}
	else if (digit == 2) {return 0b01011011;}
	else if (digit == 3) {return 0b01001111;}
	else if (digit == 4) {return 0b01100110;}
	else if (digit == 5) {return 0b01101101;}
	else if (digit == 6) {return 0b01111101;}
	else if (digit == 7) {return 0b00000111;}
	else if (digit == 8) {return 0b01111111;}
	else {return 0b01101111;}
	
}
char LED::dig2add( int digit){ //converts digit to LED address used in showLED/RunCommand
	
	if (digit==1){return 0xC1;}
	else if (digit==2){return 0xC3;}
	else if (digit==3){return 0xC5;}
	else if (digit==4){return 0xC7;}
	else if (digit==5){return 0xC9;}
	else if (digit==6){return 0xCB;}
	else if (digit==7){return 0xCD;}
	else {return 0xCF;}

}

void LED::displaychar(char address, char command){
	STBLO;
	for (int i=0;i<=7;i++)
	{
		CLKLO;
		if (((1<<i) & address) > 0 )// SETS ADDRESS
		{
			DIOHI;
		}
		else
		{
			DIOLO;
		}
		CLKHI;
	}
	for (int i=0;i<=7;i++)
	{
		CLKLO;
		if (((1<<i) & command) > 0 ) // SETS WHAT DIGIT IT IS NOT THE ADDRESS
		{
			DIOHI;
		}
		else
		{
			DIOLO;
		}
		CLKHI;
	}
	STBHI;

}
void LED::nextlevel(char command){ //lights up all LEDs
 	for (char i=193;i<=207;i+=2)
 	{
 		PORTB &= ~(1<<0);
 		
 		for (int n=0;n<=7;n++)
 		{
 			PORTB &= ~(1<<1);
 			if (((1<<n) & i) > 0 )
 			{
 				PORTB |= (1<<2);
 			}
 			else
 			{
 				PORTB &= ~(1<<2);
 			}
 			PORTB |= (1<<1);
 		}
 		for (int n=0;n<=7;n++)
 		{
 			PORTB &= ~(1<<1);
 			if (((1<<n) & (command)) > 0 )
 			{
 				PORTB |= (1<<2);
 			}
 			else
 			{
 				PORTB &= ~(1<<2);
 			}
 			PORTB |= (1<<1);
 		}
 		PORTB |= (1<<0);
 	}
 }

void LED::gamelost(){ //display LOST
	
	displaychar(0xC0, 0b00111000);//L
	displaychar(0xC2, 0b00111111);//O
	displaychar(0xC4, 0b01101101);//S
	displaychar(0xC6, 0b01111000);//T
}
void LED::SetCommand(char command)
{
	STBLO;
	for (int n=0;n<=7;n++)
	{
		CLKLO;
		if (((1<<n) & command) > 0 )
		{
			DIOHI;
		}
		else
		{
			DIOLO;
		}
		
		CLKHI;
	}
	STBHI;
}

void LED::RunCommand(int d, char command)
{
	STBLO;
	for (int i=0;i<=7;i++)
	{
		CLKLO;
		if (((1<<i) & dig2add(d)) > 0 )// SETS ADDRESS
		{
			DIOHI;
		}
		else
		{
			DIOLO;
		}
		CLKHI;
	}
	for (int i=0;i<=7;i++)
	{
		CLKLO;
		if (((1<<i) & dig2pat(command)) > 0 ) // SETS WHAT DIGIT IT IS NOT THE ADDRESS
		{
			DIOHI;
		}
		else
		{
			DIOLO;
		}
		CLKHI;
	}
	STBHI;

}

void LED::Reset()
{
	SetCommand(0x40);
	
	STBLO;
	
	for(int m =0;m<16;m++)
	{
		for (int n=0;n<=7;n++)
		{
			CLKLO;
			if (((1<<n) & 0x00) > 0 )
			{
				DIOHI;
			}
			else
			{
				DIOLO;
			}
			CLKHI;
		}
	}
	STBHI;
}
Button::Button()
{ 
	
}


bool Button::input(int n, int randNumber[100]){
	int i;
	int but;
	bool result;
	for (i=0; i<n; i++)
	{
	//	but = the button number pressed
	if (but == randNumber[i]){
		return result = true;
	}
	else{
		return result = false;}
	}

}

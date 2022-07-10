/*/*
 * GccApplication1.cpp
 *
 * Created: 11/5/2019 10:01:08 AM
 * Author : geshk
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
#define DIOOut (DDRB |= (1<<2))
#define DIOIn (DDRB &= ~(1<<2))
#define led1 0xC1
#define led2 0xC3
#define led3 0xC5
#define led4 0xC7
#define led5 0xC9
#define led6 0xCB
#define led7 0xCD
#define led8 0xCF
#define F_CPU 8000000
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include "LED.h"

char Readings[4];
void ReadButton(){
	
	Readings[0] = 0;
	Readings[1] = 0;
	Readings[2] = 0;
	Readings[3] = 0;
	STBLO;
	
	for (int n=0;n<=7;n++)
	{
		CLKLO;
		if (((1<<n) & 0x42) > 0 ) // sets it to 42, had to use bcs of private class
		{
			DIOHI;
		}
		else
		{
			DIOLO;
		}
		
		CLKHI;
	}

	
	DIOIn;
	for (int a = 0; a<4 ; a++){
		for(int b =0; b<8; b++){
			CLKHI;
			Readings[a] |= (!!(PINB & (1<<2)))<<b;
			CLKLO;
		}
	}
	STBHI;
	DIOOut;
}


int retbutnum(){	//returns the number of the button pressed
	ReadButton();
	if ((Readings[0] & 0b00000010)>0){return 1;}
	else if ((Readings[0] & 0b00100000)>0){return 5;}
	else if ((Readings[1] & 0b00000010)>0){return 2;}
	else if ((Readings[1] & 0b00100000)>0){return 6;}
	else if ((Readings[2] & 0b00000010)>0){return 3;}
	else if ((Readings[2] & 0b00100000)>0){return 7;}
	else if ((Readings[3] & 0b00000010)>0){return 4;}
	else if ((Readings[3] & 0b00100000)>0){return 8;}

	
	};
void counter(int randNumber[100]){ // generates a random number and stores it in a global array
	int i;

	for (i = 0; i < 100; i++)
	{
		randNumber[i]= ( rand()%8 ) + 1;
	}
	
}

int randNumber[100];


int main(void)
{
	DDRB = 0x07;  //STB, CLK, DIO  is outputs
	PORTB = 0x07;  //STB, CLK, DIO  are all set to '1'
	srand(4);
 	LED simon;
	simon.Reset();
	int val;
	simon.SetCommand(0x8F);

    while (1) 
    {	
		counter(randNumber);
		int level;
		for (level = 1; level < 100; level++) //for loop that determines what level the game is at
		{
			simon.SetCommand(0x44);
			simon.showLED(level, randNumber);
			for (int i=0; i<level; i++)
			{	

				int but;
				
				while ((but = retbutnum()) == 0) // stops until buttons are entered
				{
					
				}
				if (!(randNumber[i] == but)) //user is wrong
				{
					simon.gamelost(); //display lost
					simon.displaychar(0xCE, simon.dig2pat(level%10));	// display level
					if (level>9){
					simon.displaychar(0xCC, simon.dig2pat(level/10)); 
					}
					exit(0);
				}
				while (retbutnum() != 0)
				{
				}

			}

	}
		
}
}
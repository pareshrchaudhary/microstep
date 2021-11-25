#include "c8051F340.h"
//#define SYSCLK 12000000
//unsigned int aa = 0,bb = 0,cc = 0,dd = 0;

//pins and other declerations
sbit aa = P2 ^ 5;
sbit bb = P2 ^ 3;
sbit cc = P2 ^ 7;
sbit dd = P2 ^ 1;

long duty = 50;
int waitMicroSeconds = 500;
int pulseCount = 5;

void delay(unsigned int ms)
{
  unsigned int i, n;

  for(n=0; n<ms; n++);
  {
     for(i=0; i<65; i++)
     {
     }
  }
}

void one()
{

	aa = 1;
    bb = 0;
    cc = 1;
    dd = 0;
}

void two()
{
    aa = 1;
    bb = 0;
    cc = 0;
    dd = 1;
}

void three()
{
    aa = 0;
    bb = 1;
    cc = 0;
    dd = 1;
}

void four()
{
    aa = 0;
    bb = 1;
    cc = 1;
    dd = 0;
}

void oneB()
{
    aa = 1;
    bb = 0;
    cc = 0;
    dd = 0;
}

void twoB()
{
	aa = 0;
    bb = 0;
    cc = 0;
    dd = 1;
}

void threeB()
{
    aa = 0;
    bb = 1;
    cc = 0;
    dd = 0;
}

void fourB()
{
    aa = 0;
    bb = 0;
    cc = 1;
    dd = 0;
}


// main routine to microstep
void microstep(int st)
{
  long dt1 = waitMicroSeconds * duty / 100;
  long dt2 = waitMicroSeconds * (100-duty) / 100;
  int j;
  for ( j = 0; j < pulseCount; j++)
  {
    switch (st)
	{
    case 1: one();break;
    case 2: two();break;
    case 3: three();break;
    case 4: four();break;
    case 11: oneB();break;
    case 12: twoB();break;
    case 13: threeB();break;
    case 14: fourB();break;

    case 21: one();break;
    case 22: two();break;
    case 23: three();break;
    case 24: four();break;
    case 31: oneB();break;
    case 32: twoB();break;
    case 33: threeB();break;
    case 34: fourB();break;
    }
    delay(dt1);

    switch (st)
	{
    case 1: one();break;
    case 2: two();break;
    case 3: three();break;
    case 4: four();break;
    case 11: oneB();break;
    case 12: twoB();break;
    case 13: threeB();break;
    case 14: fourB();break;

    case 21: oneB();break;
    case 22: twoB();break;
    case 23: threeB();break;
    case 24: fourB();break;
    case 31: two();break;
    case 32: three();break;
    case 33: four();break;
    case 34: one();break;
    }
    delay(dt2);

  }
}

void motorOff()
{
  /* Important note:
       Turning off the motor will make it go into a 'rest' state.
       When using microsteps (or even full steps), this may not be the last active step.
       So using this routine may change the position of the motor a bit.
  */

	aa = 0;
	bb = 0;
	cc = 0;
	dd = 0;
}

void do16Steps(int cnt, int forwards)
{
	int i;
	const int list[] = {1,21,11,31,2,22,12,32,3,23,13,33,4,24,14,34};
    for ( i = 0; i < cnt; i++)
    {
		duty = 80;
		if (forwards)
		{
			int j;
			for ( j = 0; j <= 15; j++)
			{
				microstep(list[j]);
			}
		}
		else
		{
			int j;
			for ( j = 15; j >= 0; j--)
			{
				microstep(list[j]);
			}
      }
    }
}

//main() routine
void main()
{
	XBR1 = 0x40;
	P4MDOUT = 0xFF;
	while(1)
	{
		char true,false;
		waitMicroSeconds = 500;
		pulseCount = 5;

		do16Steps(50, true);
//		motorOff();
//		delay(100);

//		do16Steps(500, false);
//		motorOff();
//		delay(10000);
	}

}
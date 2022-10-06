/* mipslabwork.c
   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall
   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):
   This file modified 2022-09-28 by Adam Tovatt
   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

int prime = 1234567;
int mytime = 0x5957;
unsigned int tickValue = 0x1;
volatile int *trise = (volatile int *)0xbf886100;
volatile int *porte = (volatile int *)0xbf886110;
int ticks = 0;
int count = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr(void)
{
  if (IFS(0))
  {
    IFSCLR(0) = 0x100;
    count++;
    if (count == 10)
    {
      time2string(textstring, mytime);
      display_string(3, textstring);
      display_update();
      tick(&mytime);
      count = 0;
    }
  }
  return;
}

void labinit(void)
{
  T2CON = 0b111 << 4;     // sätter prescale till 256
  PR2 = 31250;            // sätter period
  TMR2 = 0;               // nollar timer 2
  IECSET(0) = 0x00000100; // sätter så interupt är enable på timer 2
  IPCSET(2) = 0b11111;    // sätter prioritet

  enable_interrupt();

  T2CONSET = 0x8000; // aktiverar timer 2

  *trise = 0x00;
  *porte = 0xff;

  TRISD |= 0x7f;

  count = 0;

  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  prime = nextprime(prime);
  display_string(0, itoaconv(prime));
  display_update();
}
/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h"
volatile int *p_led = (volatile int *)0xbf886110;
int counter;
int mytime = 0x5957;
int prime = 1234567;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr(void)
{
  if (IFS(0))
  {
    IFSCLR(0) = 0x100;
    counter++;
    if (counter == 10)
    {
      time2string(textstring, mytime);
      display_string(3, textstring);
      display_update();
      tick(&mytime);
      counter = 0;
    }
  }
  return;
}

/* Lab-specific initialization goes here */
void labinit(void)
{

  T2CON = 0b111 << 4;                               // sätter prescalree till 256
  PR2 = (80000000 / 256) / 10;                      // sätter period
  TMR2 = 0;                                         // nollar timer 2
  IECSET(0) = 0x00000100;                           // sätter så interupt är enable på timer 2
  IPCSET(2) = 0b11111;                              // sätter prioritet priritet 3 och sub prio 1
  enable_interrupt();                               // sätter interupt global
  T2CONSET = 0x8000;                                // aktiverar timer 2
  volatile int *trise = (volatile int *)0xbf886100; // make a pointer to adress were led are initilized 0 for output we need zero
  *trise = 0;                                       // make sure that the leds are set as output (0)

  TRISDSET = 0x0ff0; // make sure that btns/sw are input leave the others same

  counter = 0;
  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  prime = nextprime(prime);
  display_string(0, itoaconv(prime));
  display_update();
}

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

int mytime = 0x5957;
unsigned int tickValue = 0x1;
volatile int *trise = (volatile int *)0xbf886100;
volatile int *porte = (volatile int *)0xbf886110;
int ticks = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr(void)
{
  return;
}

/* Lab-specific initialization goes here */
void labinit(void)
{
  *trise = 0x00;
  *porte = 0xff;

  TRISD |= 0x7f;

  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  delay(1000);
  time2string(textstring, mytime);
  display_string(3, textstring);
  display_update();
  tick(&mytime);

  ticks++;
  *porte = ticks & 0xff;

  int buttons = getbtns();
  if (buttons & 0x1)
  {
    mytime = (mytime & 0xff0f) | (getsw() << 4); // pretty self explanatory tbh
  }

  if (buttons & 0x2)
  {
    mytime = (mytime & 0xf0ff) | (getsw() << 8);
  }

  if (buttons & 0x4)
  {
    mytime = (mytime & 0x0fff) | (getsw() << 12);
  }

  display_image(96, icon);
}

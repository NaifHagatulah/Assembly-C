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

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr(void)
{
  return;
}

/* Lab-specific initialization goes here */
void labinit(void)
{
  volatile int *tris_e = (volatile int *)0xbf886100; // make a pointer to adress were led are initilized 0 for output we need zero
  *tris_e = 0;                                       // make sure that the leds are set as output (0)
  TRISD |= 0x00000ff0;                               // make sure that btns/sw are input leave the others same
  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  volatile int *p_led = (volatile int *)0xbf886110; // port e the adress was given in the question
  delay(10);
  time2string(textstring, mytime);
  display_string(3, textstring);
  display_update();
  tick(&mytime);
  *p_led = *p_led + 0x1; // lägger till 1 dit led pekar dvs ökar så en till lampa lyser index 0-7 är lampor
  if (*p_led & 0xffff00) // if we are abow index 7 we dont know what happens if we switch between 0-1
  {
    *p_led = 0x00; // reset incase we come abow index 7
  }

  if (getbtns() & 0x02) // kontrollerar om någon av de tre knapparna trycks
  {
    mytime &= 0xff0f;         // nollar minuterna
    mytime |= (getsw()) << 4; // sätter in getsw() in i minuterna allt annat förblir densamma då de bara är nollor
  }
  if (getbtns() & 0x04) // kontrollerar om någon av de tre knapparna trycks
  {
    mytime &= 0xf0ff;         // reset the number connected to the btn
    mytime |= (getsw()) << 8; // insert switch value to time
  }
  if (getbtns() & 0x08) // kontrollerar om någon av de tre knapparna trycks
  {
    mytime &= 0x0fff;
    mytime |= (getsw()) << 12;
  }
  display_image(96, icon);

  delay(300);
}

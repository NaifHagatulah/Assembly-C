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
  /*
  3 stycken funktioner för timer finns för varje timer.
  funktion 3
  TMRx  hold current count
  PRx period register när den ska rulla över
  txcon   kontrollerar hur den är Prescaller
  count = TMR2
  PR2 = 20000; ska bli noll efter 20000 räkingar! vi ska ha 4 000 000 för få 1 per sekund
  Timer 1 prescaler: 1,8,64,256

  */
  volatile int *trise = (volatile int *)0xbf886100; // make a pointer to adress were led are initilized 0 for output we need zero

  *trise = 0; // make sure that the leds are set as output (0)
  //*prote = 0;
  TRISD |= 0x00000ff0; // make sure that btns/sw are input leave the others same
  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  volatile int *p_led = (volatile int *)0xbf886110;
  // delay(10);
  time2string(textstring, mytime);
  display_string(3, textstring);
  display_update();
  tick(&mytime);

  int a = 0;
  // TMR2 = 0;
  unsigned int count = TMR2; // så den räknar från 0 till 62499
  PR2 = 62499;               // de blir 1 sek om de körs 16 miljoner ggr
  // T2CON = 0xF0;          // prescaler till 256 så de räknar varje gång de körs 256 ggr
  *p_led = *p_led + 0x1; // lägger till 1 dit led pekar dvs ökar så en till lampa lyser index 0-7 är lampor
  if (*p_led & 0xffff00) // if we are abow index 7 we dont know what happens if we switch between 0-1
  {
    *p_led = 0x00; // reset incase we come abow index 7
  }

  if (getbtns() & 0x02) // kontrollerar om någon av de tre knapparna trycks
  {
    // timer = 200;
    // mytime = 0x1111; //ettar allt
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
  while (1)
  {
    if (count == 62498)
    {
      break;
    }
  }

  //  delay(3);
}

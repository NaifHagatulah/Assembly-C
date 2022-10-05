#include <pic32mx.h>
void f()
{

    volatile int *buttons = (volatile int *)0x8000abc;
    volatile int *port = (volatile int *)0x8007bc0;

    while (1)
    {
        if ((1 << 3) & *buttons)
        {
            *port |= 0b111111; // or så vi kommer inte ändra de andra
        }
        else
        {
            *port &= ~0b111111; // and vi kommer nolla endast de som vi är inreserade av
        }
    }
}
void q3()
{
    volatile int *trisse = (volatile int *)0xbf886100;
    *(trisse + 1) = 0b1110;
    TRISECLR = 0b1110;
    PORTE = (PORTE & ~0b111111) | 0b1010;
}

// T2CON har set invers och cler använd!!
void q4()
{
    // prescale till 1:64
    T2CON = 0b110 << 4; // index 4 använd inte set /clr
    PR2 = (8000000 / 64) / 100;
    TMR2 = 0;
    IECSET(0) = 1 << 8;  // sätt 1 på index 8 på IEC(0) enabel interupt på tmt2
    IPCSET(0) = 0b11111; // sätter priorety och subprio, prioritet handlar om vi får en interupt o är i våra handler och får en ny interupt och den har högre prio har den lägre prio sker de inte
    enable_interupt();   // startar interupts för våra program
    T2CONSET = 1 << 15;  // använd set/clr
}

void q4b()
{
    // if(TMR2 == PR2) //funkar ej pga timer tickar för snabbt vi har en interupt i en register
    if (IFS(0) & (1 << 8))
    {
        IFSCLR(0) = 1 << 8; // bara clear drf använd clear o inte direkt noll
    }
}
//enable interupt kör bara (ei)
// MÅSTE SLÅ PÅ INTERUPT!!!
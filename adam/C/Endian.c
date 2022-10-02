#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    volatile uint32_t i = 0x01234567;
    // return 0 for big endian, 1 for little endian.
    printf("%d", (*((uint8_t *)(&i))) == 0x67);
}
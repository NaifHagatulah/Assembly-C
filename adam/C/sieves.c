/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6
int currentColumn = 0;

void print_number(int number)
{
    printf("%10d ", number);

    currentColumn++;

    if (currentColumn >= COLUMNS)
    {
        printf("\n");
        currentColumn = 0;
    }
}

int is_prime(int n)
{
    for (int i = n - 1; i > 1; i--)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

void print_sieves(const int maxPrimes)
{
    char array[maxPrimes];

    for (int i = 0; i < maxPrimes; i++)
    {
        array[i] = 1;
    }

    for (int i = 2; i * i <= maxPrimes; i++)
    {
        for (int j = 2; j < maxPrimes; j++)
        {
            int multiple = i * j;

            if (multiple > maxPrimes)
                break;

            array[multiple] = 0;
        }
    }

    for (int i = 2; i < maxPrimes; i++)
    {
        if (array[i] == 1)
            print_number(i);
    }

    int coolDistances = 0;
    for (int i = 2; i < maxPrimes; i++)
    {
        if (array[i] == 1)
        {
            if (i + 8 < maxPrimes)
            {
                if (array[i + 8] == 1)
                    coolDistances++;
            }
        }
    }

    printf("\ncool distances: %d", coolDistances);
    printf("\n");
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[])
{
    if (argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an interger number.\n");
    return 0;
}

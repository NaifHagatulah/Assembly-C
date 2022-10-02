/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define COLUMNS 6
int counter = 0;
void print_number(int n)
{
    printf("%10d ", n);
    counter++;

    if (counter % COLUMNS == 0)
    {
        printf("\n");
    }
}
int is_prime(int n)
{

    for (int i = (n - 1); i > 1; i--)
    {

        if (n % i == 0)
        {
            return 0;
        }
    }

    return 1;
}
void print_sieves(int n)
{
    // Should print out all prime numbers less than 'n'
    // with the following formatting. Note that
    // the number of columns is stated in the define
    // COLUMNS
    char numbers[n];                      // hela array initaliserar storlek av n
    memset(numbers, 1, n * sizeof(char)); // set whole array to  0 == false 1==true
    // for (int l = 0; l < n; l++)
    //{
    //     numbers[l] = 1;
    // }
    for (int i = 2; i * i < n; i++) // loop igenom alla tal tills sqrt(n) behövs inte mer än så
    {

        if (numbers[i] == 1) // kontrollerar om de är 1 sen körs algortimen
        {
            for (int j = 0; j < n; j++)
            {

                int index = i * i + j * i;

                if (index > n)
                {
                    break;
                }
                numbers[index] = 0;
            }
        }
    }

    for (int l = 2; l < n; l++) // kontrollerar vilka tal som inte blev noll för de inte är primtal
    {
        if (numbers[l] == 1)
        {
            print_number(l);
        }
    }
    printf("\n");
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        print_sieves(atoi(argv[1]));
        printf("%d ", counter);
    }

    else
        printf("Please state an interger number.\n");
    return 0;
}

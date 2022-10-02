/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

#include <stdio.h>

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

int main(void)
{
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}


void copycodes(const char *point1, int *point, int *count)
{
  while (point1 != 0)
  {
    *point = *point1;
    *point1++;
    *point++;
    (*count)++;
  }
}

void work()
{

  copycodes(text1, list1, &count);
  copycodes(text2, list2, &count);
}




#include <stdio.h>

char *text1 = "This is a string.";
char *text2 = "Yet another thing.";
// char 20 is 80 bytes 20*4=80
char list1[80];
char list2[80];
// 32 bit to zero
int count = 0;

void printlist(const int *lst)
{
  printf("ASCII codes and corresponding characters.\n");
  while (*lst != 0)
  {
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char *c)
{
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
         (int)*c, (int)*(c + 1), (int)*(c + 2), (int)*(c + 3));
}
void copycodes(char *a0, int *a1, int *count)
{
  while (1)
  {
    char t0 = *a0;
    if (t0 == 0)
      break;

    *a1 = t0;

    *a0++;
    *a1++;

    *count = *count + 1;
  }
}

void work()
{
  copycodes(text1, list1, &count);

  copycodes(text2, list2, &count);
}

int main(void)
{
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char *)&count);
}

#include <stdio.h>

char *text1 = "This is a string.";
char *text2 = "Yet another thing.";
int list1[20]; //
int list2[20]; // lista int med 20 platser == 80 bytes
int count = 0; // 32 bits / 4bytes to zero

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

void copycodes(char *point1, int *point, int *count)
{
  while (1)
  {

    char translate = *point1; //save pointer value to translate
    *point = translate; //transfer pointer value to an other pointer
    *point1++;  //increment pointer one stepp 1 nibbel 
    *point++;
    (*count)++;
    if (translate == 0)
    {
      break;
    }
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
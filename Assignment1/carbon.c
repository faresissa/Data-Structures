/*CIS*2520 - Assignment 1
Fares Issa - issaf
0925274
September 24th, 2018

C program modified from my previous work in CIS 2910
Calculates all permutation of a string predefined in carbon()
 */

#include <stdio.h>
#include <string.h>

/*Simple function that swaps the values at two pointers*/
void swap(char *a, char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/*This function prints the permutations of the letters provided in carbon() 
 in a recursive manner. This function accepts a string which is initialized in
 main.c "CARBON", a starting position (0 by default), and the end position (strlen-1)
 */
void carbon(char *string, int start, int end)
{
   int i;
   if (start == end)
     printf("%s\n", string);
   else
   {
       for (i = start; i <= end; i++)
       {
          swap((string+start), (string+i));
          carbon(string, start+1, end);
          swap((string+start), (string+i));
       }
   }
}

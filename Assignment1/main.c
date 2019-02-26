/*CIS*2520 - Assignment 1
Fares Issa - issaf
0925274
September 24th, 2018*/

#include "carbon.h"
#include "ackermannFunction.h"
#include "newton.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*Driver program for Assignment 1*/
int main (void)
{

	char str[] = "CARBON";
	int input;
	int m;
	int n;
	int ackermann;
	int x;
	double e;
	int length;
	int exit;

	input = 0;
	m = 0;
	n = 0;
	ackermann = 0;
	x = 0;
	e = 0.00;
	length = strlen(str);
	exit = 1;

	while(exit)
	{
		printf("\nWhich question would you like to select?\n");
		printf("1. Carbon?\n");
		printf("2. Ackermann?\n");
		printf("3. Newton's method?\n");
		printf("4. Exit.\n\n");
		printf("Please select an option:\n");
		scanf("%d", &input);
		printf("\n\n");

		if (input == 1)
		{
    		carbon(str, 0, length-1); //Accepts the carbon string, starting position, end position of string.
		}
		
		if (input == 2)
		{
			printf("Enter a value for m:\n");
			scanf("%d", &m);
			printf("Enter a value for n:\n");
			scanf("%d", &n);
		
			if ((m <= 3)&&(n <= 14)) //Maximum accepted value.
			{
				ackermann = ackermannFunction(m,n);
				printf("A(%d, %d) = %d.\n", m, n, ackermann);
			}
			else
			{
				printf("Please input values of m <=3, and n <= 14.\n");
			}
		}
	
		if (input == 3)
		{
			printf("Which Newton program would you like to execute?\n");
			printf("1. Recursive.\n");
			printf("2. Non-recursive.\n");
			scanf("%d", &input);

			printf("Enter a value for x:\n");
			scanf("%d", &x);
			printf("Enter a value for e:\n");
			scanf("%lf", &e);

			if (input == 1)
			{
				newtonInitialize(x, e);
			}
			if (input == 2){
				newtonNormal(x,e);
			}
		}
	
		if (input == 4){ //Exit
			exit = 0;
		}
	}

return 0;
}

/*CIS*2520 - Assignment 1
Fares Issa - issaf
0925274
September 24th, 2018*/

#include <stdio.h>
#include <math.h>

void newtonRecursive(int x, double e, double a);


/*This is a simple non-recursive Newton function that approximates A.
 *The steps used to calculated A are as follows:
 *Calculate a
 *If the condition below is met, print that value of a.
 *If the condition is not met, calculate a new approximation, then print.
 */
void newtonNormal(int x, double e)
{
	double a;
	int exit;

	a = 0.00;
	exit = 1;

	a = x/2; //Calculating the first approximation of a.

	while (exit)
	{
		if (fabs(a*a - x) <= e) //If the absolute value of this expression is less than or equal to e, proceed
		{
			exit = 0;
		}
		else
		{
			a = ((a + (x/a))/2); //If the previous if statement is not executed. Approximate new a.
		}
	}
	printf("\nThe approximate square root is: %lf.\n", a);
}

/*This function is used to initialize the recursive call for the Newton expression.
This separate function is used so that a is not approximated a second time as a = x/2.
Since the entire function would be recalled, it does not behave like a while loop and
therefore can't leave the a = x/2 expression "out of the while loop".*/
void newtonInitialize(int x, double e)
{
	double a;
	a = 0.00;
	a = x/2; //Calculating the first approximation of a.

	if (fabs(a*a - x) <= e)
	{
		printf("\nApproximate square root is: %lf.\n", a);
	}
	else
	{
		newtonRecursive(x, e, ((a + (x/a))/2)); //If the previous statement is not executed, run newtonRecusive
	}

}
/*This function finds the square root of x using Newton's method to the closest epsilon value
specified by the user, and it does so recursively.*/
void newtonRecursive(int x, double e, double a)
{
	if (fabs(a*a - x) <= e)
	{
		printf("\nApproximate square root is: %lf.\n", a);
	}
	else
	{
		newtonRecursive(x, e, ((a + (x/a))/2));
	}
}

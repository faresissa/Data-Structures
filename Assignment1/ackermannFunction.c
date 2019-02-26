/*CIS*2520 - Assignment 1
Fares Issa - issaf
0925274
September 24th, 2018*/

#include <stdio.h>

/*Simple function that returns the values of the ackermann function based on the conditions
provided in the Assignment 1 handout.*/
int ackermannFunction(int m, int n)
{
	if (m == 0)
	{
		return (n + 1);
	}
	else if (n == 0)
	{
		return ackermannFunction(m-1,1);
	}
	else
	{
		return ackermannFunction((m-1), ackermannFunction(m, (n-1)));
	}
}

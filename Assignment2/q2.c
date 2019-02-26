/* Assignment 2: Question 2
 * Fares Issa
 * issaf - 0925274
 * October 15th, 2018
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct Numbers{
	float value;
	struct Numbers* next;
} Numbers;

Numbers * create(Numbers* node, int newVal);
Numbers * operator(Numbers* node, char op);
Numbers * freeNumbers(Numbers * node);

/* Driver program that takes two commandline arguments.
 * First argument is the executable, second being an RPN expression
 * to be operated upon. Program outputs the result within 2 decimal places.
 */
int main(int argc, char *argv[])
{
	int i;
	char input;
	double val;

	i = 0;
	val = 0.00;

	Numbers* node;
	node = NULL;

	if (argc != 2) //Ensure only 2 arguments are entered
	{
		printf("Please enter only 2 commandline arguments!\n");
		printf("The program will now perminate. Press enter.\n");
		getchar();
		exit(1); //safe exit
	}

	while(i < strlen(argv[1]))
	{
		input = argv[1][i]; //arg2[i] is current character being operated on
		if(isdigit(input))
		{
			val = argv[1][i] - '0'; //Subtracts ASCII value of '0' (which is 48) from input to obtain int
			node = create(node, val); //Add number to list
		}
		else if ((input == '*')||(input == '+')||(input == '-')||(input == '/'))
		{
			node = operator(node, input); //Go to operator function and determine operation
		}
	i++; //iterate through number of characters in the second argument
	}
	printf("%.2f\n\n", node->value);

return 0;

}

/* Simple function that allocates memory for new elements being added to the list.
 * Assigns new head to the list in order to store user input sequentially in order
 * to perform correct mathematic expressions.
 */
Numbers * create(Numbers* node, int newVal)
{
	Numbers* out;

	out = malloc(sizeof(struct Numbers)); //Allocating memory
	if (out == NULL)
	{
		printf("Not enough memory has been allocated. \nProgram will terminate. Press enter.\n");
		getchar();
		exit(1); //Safely exit if memory was not able to be allocated
	}

	out->value = newVal; //Store val (passed from main) in list
	out->next = node; //Assign new head of list
	return out;

}

/* When this function is called, means an operator has been passed to the list
 * Takes the head of the list and the next element and performs respective operation
 * Removes these inputs from the list and assigns the output as the front of the list.
 */ 
Numbers * operator(Numbers* node, char op)
{
	double a, b;
	a = b = 0.00;
	a = node->value;
	b = node->next->value;


	if (op == '*') b = b * a; //perform multiplication
	if (op == '+') b = b + a; //preform addition
	if (op == '-') b = b - a; //preform subtraction
	if (op == '/') b = b / a; //preform division

	node = freeNumbers(node); //Removes the inputs from list
	node->value = b; //Result of operation is now at the front of list
	return node;
}

/* Simple function that frees the memory allocated by elements within list
 * that have already been operated on and are no longer needed.
 */
Numbers * freeNumbers(Numbers* node)
{
	Numbers* temp;
	temp = node->next;
	free(node); //Freeing the memory of Numbers head
	return temp;
}

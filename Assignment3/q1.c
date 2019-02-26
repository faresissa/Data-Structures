/* Assignment 3: Question 1
 * Fares Issa
 * issaf - 0925274
 * November 5th, 2018
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{
	int type;
	int equal;
	int varNumber;
	float value;
	char* print;

	struct node* left;
	struct node* right;
	struct node* next;
} node;

/*pushes a node on top of the stack*/
node* push(node* head, node* toAdd);

/*Pops the first node off the stack*/
node* pop(node* head);

/*creates a node*/
node* create(int type, float value, int equal, int varNumber, char* print);

/*Prints all the contents of the tree in preorder form*/
void inOrder(node* head);

/*Prints all the contents of the tree in postorder form*/
void postOrder(node* head);

/*Prints all the contents of the tree in preorder form*/
void preOrder(node* head);

/*Traverses the heap as it calculates the value of it.*/
float calculate(node* head);

/*Print the binary tree list.*/
void print(node* head, int space);

/*Searches the tree for specified variable then replaces that variable
with the new value.*/
void search(node* head, int toSearch, float newVal);

int main(int argc, char* argv[])
{
	char source[900];
	char temp[5];
	char tempOut[5];
	char searchInput[15];
	int newSearch;
	int i;
	int l;
	int userIn;
	int type;
	int equal;
	int varNumber;

	float value;
	float newVal;
	float calc;

	struct node* number;
	struct node* symbol;
	struct node* tempPointer;

	newSearch = 0;
	newVal = 0.0;
	i = 0;
	l = 0;
	userIn = 0;
	calc = 0.0;
	type = 0;
	value = 0.0;
	equal = 0;
	varNumber = 0;

	number = NULL;
	symbol = NULL;

	strcpy(source, argv[1]);
	l = strlen(source);
	/*Parser algorithm that goes through the entire expression provided.*/
	while (i < l)
	{
		if (source[i] == '(')
		{
			type = 0;
			value = 0.0;
			equal = 0;
			varNumber = 0;
			tempOut[0] = '\0';
		}
		else if (source[i] == '-')
		{
			type = 0;
			value = 0.0;
			equal = 1;
			varNumber = 0;
			tempOut[0] = '-';
			tempOut[1] = '\0';
		}
		else if (source[i] == '+')
		{
			type =0;
			value = 0.0;
			equal = 1;
			varNumber = 0;
			tempOut[0] = '+';
			tempOut[1] = '\0';
		}
		else if (source[i] == '*')
		{
			type = 0;
			value = 0.0;
			equal = 2;
			varNumber = 0;
			tempOut[0] = '*';
			tempOut[1] = '\0';
		}
		else if (source[i] == '/')
		{
			type = 0;
			value = 0.0;
			equal = 2;
			varNumber = 0;
			tempOut[0] = '/';
			tempOut[1] = '\0';
		}
		else if (source[i] == ')')
		{
			type = 0;
			value = 0.0;
			equal = 3;
			varNumber = 0;
			tempOut[0] = '\0';
		}
		else if (isdigit(source[i]))
		{
			strncpy(temp, &source[i], 4);
			temp[4] = '\0';

			type = 1;
			value = atof(temp);
			equal = 0;
			varNumber = 0;
			strcpy(tempOut, temp);
			i = i + 3;
		}
		else if (source[i] == 'x')
		{
			temp[0] = source[(i+1)];
			temp[1] = '\0';

			type = 1;
			value = 0.0;
			equal = 0;
			varNumber = atoi(temp);
			tempOut[0] = 'x';
			tempOut[1] = temp[0];
			tempOut[2] = '\0';
			i = i + 1;
		}
		tempPointer = create(type, value, equal, varNumber, tempOut); //create a new node

		if (type == 0)
		{
			if (source[i] == ')') //if a right bracket is encountered
			{
				/*loops until the struct is empty or until a left bracket is encountered*/
				while ((symbol != NULL)&&(symbol->equal != 0))
				{
					tempPointer = symbol->next;

					//makes first number on the stack become the right child of struct
					symbol->right = number;

					//take the number off the stack
					number = pop(number);

					//makes second number on stack be left child of symbol
					symbol->left = number;

					//take the number off the stack
					number = pop(number);

					//pushes this new tree onto the stack
					number = push(number, symbol);

					//removes the symbol from stack
					symbol = tempPointer;
				}
				symbol = pop(symbol);
			}
			else if (source[i] == '(')
			{
				symbol = push(symbol, tempPointer);
			}
			else if (symbol == NULL)
			{
				symbol = push(symbol, tempPointer);
			}
			else if (tempPointer->equal <= symbol->equal)
			{
				//makes first number on stack become right child of struct
				symbol->right = number;

				//take the number off the stack
				number = pop(number);

				//makes second number on the stack be left child of symbol
				symbol->left = number;

				//take the number off the stack
				number = pop(number);

				//pushes this new tree onto the stack
				number = push(number, symbol);

				//removes the symbol from the stack
				symbol = pop(symbol);

				//pushes result on stack
				symbol = push(symbol, tempPointer);
			}
			else if (tempPointer->equal > symbol->equal)
			{
				symbol = push(symbol, tempPointer);
			}
		}
		else if (type == 1)
		{
			number = push(number, tempPointer);
		}
		i++;
	}

	//self explanatory menu loop
	while(i != 7)
	{
		printf("Please select one of the options below.\n");
		printf("1. Display\n");
		printf("2. Preorder\n");
		printf("3. Inorder\n");
		printf("4. Postorder\n");
		printf("5. Update\n");
		printf("6. Calculate\n");
		printf("7. Exit\n\n");

		scanf("%d", &userIn);

		if (userIn == 1)
		{
			printf("Tree: \n");
			print(number, 0);
		}
		else if (userIn == 2)
		{
			printf("Preorder Notation:\n");
			preOrder(number);
			printf("\n");
		}
		else if (userIn == 3)
		{
			printf("Inorder Notation:\n");
			inOrder(number);
			printf("\n");
		}
		else if (userIn == 4)
		{
			printf("Postorder Notation: \n");
			postOrder(number);
			printf("\n");
		}
		else if (userIn == 5)
		{
			printf("Please enter input in the form: (xX, #.##) excluding brackets.\n");
			fgets(searchInput, 14, stdin);
			fgets(searchInput, 14, stdin);
			temp[0] = searchInput[1];
			temp[1] = '\0';
			newSearch = atoi(temp); //string to int

			strncpy(temp, &searchInput[4], 4);
			temp[4] = '\0'; //null terminate my string.
			newVal = atof(temp); //string to float conversion
			search(number, newSearch, newVal); //search for the var -> replace the val
		}
		else if (userIn == 6)
		{
			calc = calculate(number);
			printf("Result of expression is: %.2f\n", calc);
		}
		else if (userIn == 7)
		{
			exit(0);
		}
		else
		{
			printf("Incorrect input.");
			getchar();
			exit(1);
		}
	}
return 0;
}

node* push(node* head, node* toAdd)
{
	if (toAdd == NULL)
	{
		return NULL;
	}
	else
	{
		toAdd->next = head; //new struct now points to the original head
		return toAdd;
	}
}

node* pop(node* head)
{
	if (head == NULL)
	{
		return NULL;
	}
	else
	{
		node* temp = NULL;
		temp = head->next;
		return temp;
	}
}

node* create(int type, float value, int equal, int varNumber, char* print)
{
	node* temp;
	temp = NULL;
	temp = malloc(sizeof(struct node));
	if (temp == NULL)
	{
		printf("Not enough memory has been allocated. \nProgram will terminate. Press enter.\n");
		getchar();
		exit(1);
	}
	temp->print = malloc(sizeof(char)*6);
	temp->type = type;
	temp->value = value;
	temp->equal = equal;
	temp->varNumber = varNumber;
	strcpy(temp->print, print);
	temp->left = NULL;
	temp->right = NULL;
	temp->next = NULL;
	return temp;
}

void inOrder(node* head)
{
	if (head->type != 1)
	{
		printf("(");
		inOrder(head->left);
	}
	printf("%s", head->print);
	if (head->type != 1)
	{
		inOrder(head->right);
		printf(")");
	}
}

void postOrder(node* head)
{
	if (head->type != 1)
	{
		postOrder(head->left);
	}
	if (head->type != 1)
	{
		postOrder(head->right);
	}
	printf("%s", head->print);
}

void preOrder(node* head)
{
	printf("%s", head->print);
	if (head->type != 1)
	{
		preOrder(head->left);
	}
	if (head->type != 1)
	{
		preOrder(head->right);
	}
}

float calculate(node* head)
{
	float leftVal;
	float rightVal;

	leftVal = 0;
	rightVal = 0;

	if (head->type != 1)
	{
		leftVal = calculate(head->left);
	}
	if (head->type != 1)
	{
		rightVal = calculate(head->right);
	}
	if (head->type == 1)
	{
		return head->value;
	}

	if (head->print[0] == '-')
	{
		return (leftVal - rightVal);
	}
	else if (head->print[0] == '+')
	{
		return (leftVal + rightVal);
	}
	else if (head->print[0] == '*')
	{
		return (leftVal * rightVal);
	}
	else if (head->print[0] == '/')
	{
		if (rightVal != 0)
			return (leftVal / rightVal);
	}
	else
	{
		printf("Divide by zero error. Exiting program.");
		getchar();
		exit(1);
	}
	return 0;
}

void print(node* head, int space)
{
	int i;
	i = 0;
	if (head->type != 1)
	{
		print(head->right, (space+1));
	}
	while (i < (space-1))
	{
		printf("    \n");
		i++;
	}
	while (i < space)
	{
		printf("----\n");
		i++;
	}
	if (head->type == 0)
	{
		printf("[%s]\n", head->print);
	}
	if (head->type == 1)
	{
		printf("[%.2f]\n", head->value);
	}
	if (head->type != 1)
	{
		print(head->left, (space+1));
	}
}


void search(node* head, int toSearch, float newVal)
{
	if (head->type != 1)
	{
		search(head->left, toSearch, newVal);
	}
	if (head->type != 1)
	{
		search(head->right, toSearch, newVal);
	}
	if (head->type == 1)
	{
		if (head->varNumber == toSearch)
		{
			head->value = newVal;
		}
	}
}

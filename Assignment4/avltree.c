/* Assignment 4: Question 1
 * Fares Issa
 * issaf - 0925274
 * November 26th, 2018
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{
	struct node* left;
	struct node* right;
	char* word;
	int height;
	int freq;
} node;
/* Prints the menu each time the program loops.*/
void menu();

/*Balances the tree if it is right right weighted.*/
node* rotateRR(node* x);
/*Balances the tree if it is left left weighted.*/
node* rotateLL(node* x);
/*Balances the tree if it is right left weighted.*/
node* rotateRL(node* x);
/*Balances the tree if it is left right weighted.*/
node* rotateLR(node* x);

/*Searches the tree.*/
int search(node* current, char* term);

/*Finds the height of the tree.*/
int findHeight(node* current);

/*Finds the number of nodes in the tree.*/
int findSize(node* current);

/*Finds all nodes greater than or equal to a given a frequency.*/
void findAll(node* current, int frequency);

/*Inserts a node and balances the tree.*/
node* insert(char* word, node* current, int type);

/*Creates a node struct and initializes it.*/
node* create(char* word);

/*Deletes a specific node from the tree, rebalances.*/
node* delete(char* word, node* current);

/*Finds a replacement for the node that has been deleted.*/
node* findReplacement(node* current);

/* Driver program. Parses the file.
 * takes user input and selects which option to go
 * to based on the menu options. Exits upon entry of
 * bad input, error in opening file, or option 7.
 */
int main()
{
	FILE * inputFile;
	int i;
	int j;
	int freqNum;
	int userIn;
	int height;
	int size;
	int numWords;

	i = 0;
	j = 0;
	freqNum = 0;
	userIn = 0;
	height = 0;
	size = 0;
	numWords = 0;

	char find[401];
	char buffer[10001];
	char* insertWord;
	char space;

	node* head = NULL;

	/*Continous looping until user enters a 7*/
	while(userIn != 7)
	{
		menu();
		printf("avl/> ");
		scanf("%d", &userIn);
		if (userIn == 1)
		{
			inputFile = fopen("A4_data_f18.txt", "r");
			if (inputFile != NULL)
			{
				j = 0;
				//Parsing file contents into buffer.
				while ((fgets(buffer, 10001, inputFile) != NULL))
				{
					numWords = 0;

					/* The following block of code is responsible for ensuring
					 * the line isn't all spaces/blank/newlines*/
					if (buffer[0] != '\n')
					{
						j = 0;
						space = buffer[j];
						while (space == ' ')
						{
							j++;
							space = buffer[j];
						}
						numWords = 0;

						while (space != '\0')
						{
							if ((space == ' ') && (buffer[j+1] != ' ') && (buffer[j+1] != '\0') && (buffer[j+1] != '\n'))
							{
								numWords++;
							}
							if (space == '\n')
								buffer[j] = '\0';
							j++;
							space = buffer[j];
						}
						//Using strtok to tokenize the input line of the file
						insertWord = strtok(buffer, " ");
						head = insert(insertWord, head, 0);
						j = 0;

						/* Looping until each string in the file has been 
						 * tokenized and is inserted into the struct.
						 */
						while(j < numWords){
							insertWord = strtok(NULL, " ");
							if (strlen(insertWord) > 0)
							{
								head = insert(insertWord, head, 0);
							}
							j++;
						}
					}
				}
			}
			else
			{
				printf("Error opening file. Program will now terminate.\n");
				exit(0);
			}
			fclose(inputFile);
		}

		/*Takes user input of a specific key, then searches for it*/
		else if (userIn == 2)
		{
			printf("find key: ");
			scanf("%s", find);

			//If the key is not found, the user is informed through no_such_key.
			if (search(head, find) == 0)
			{
				printf("no_such_key\n");
			}
		}

		/*Takes a key from the user to insert into the tree.*/
		else if (userIn == 3)
		{
			printf("insert key: ");
			scanf("%s", find);
			head = insert(find, head, 1);
		}

		/*Removes a specific key from the tree, if found in the tree.*/
		else if (userIn == 4)
		{
			printf("remove key: ");
			scanf("%s", find);
			head = delete(find, head);
		}

		/*Finds the height and number of nodes of the tree.*/
		else if (userIn == 5)
		{
			height = findHeight(head);
			size = findSize(head);
			printf("height: %d, size: %d\n", height, size);
		}

		/* Given a specific frequency, the program shows all nodes
		 * greater than or equal to that frequency.*/
		else if (userIn == 6)
		{
			printf("frequency: ");
			scanf("%d", &freqNum);
			findAll(head, freqNum);
		}

		/*Exits program.*/
		else if (userIn == 7)
		{
			exit(0);
		}
		else
		{
			printf("Bad input. Program will exit.\n");
		}
	}
return 0;
}

/*Printing the menu at each menu loop.*/
void menu()
{
	printf("\nChoose a number betwen 1-7 to execute the respective action.\n");
	printf("1. Initialization.\n");
	printf("2. Find.\n");
	printf("3. Insert.\n");
	printf("4. Remove.\n");
	printf("5. Check Height and Size.\n");
	printf("6. Find All (above a given frequency).\n");
	printf("7. Exit.\n");
}

/*Balancing the tree if it is right right weighted.*/
node* rotateRR(node* x)
{
	node* y = NULL;
	y = x->right;
	x->right = y->left;
	y->left = x;
	return (y);
}

/*Blanacing the tree if it is left left weighted.*/
node* rotateLL(node* x)
{
	node* y = NULL;
	y = x->left;
	x->left = y->right;
	y->right = x;
	return(y);
}

/*Balancing the tree if it is left right weighted.*/
node* rotateLR(node *x)
{
	x->left = rotateRR(x->left);
	return (rotateLL(x));
}

/*Balancing the tree if it is right left weighted.*/
node* rotateRL(node* x)
{
	x->right = rotateLL(x->right);
	return (rotateRR(x));
}

/* Searches the tree in alphabetical order from the head of the node
 * in order to find a specific term that the user requested. If found,
 * the term is printed (key), and the frequency. Otherwise the program
 * will print that the term is not found.
 */
int search(node* current, char* term)
{
	if (strcmp(current->word, term) > 0)
	{
		if (current->left == NULL)
		{
			return 0;
		}
		else
		{
			return (search(current->left, term));
		}
	}
	else if (strcmp(current->word, term) == 0)
	{
		printf("key: %s, frequency: %d\n", current->word, current->freq);
		return 1;
	}
	else if (strcmp(current->word, term) < 0)
	{
		if (current->right == NULL)
		{
			return 0;
		}
		else
		{
			return (search(current->right, term));
		}
	}
	return 0;
}
/* Finds the height of the tree by looking at the height of all
 * the nodes below it.
 */
int findHeight(node* current)
{
	int leftH;
	int rightH;

	leftH = 0;
	rightH = 0;

	if (current == NULL)
	{
		return 0;
	}
	if (current->left != NULL)
	{
		leftH = findHeight(current->left);
	}

	if (current->right != NULL)
	{
		rightH = findHeight(current->right);
	}

	if ((current->left == NULL) && (current->right == NULL))
	{
		return 0;
	}
	if (leftH > rightH)
	{
		return (leftH + 1);
	}
	else
	{
		return (rightH + 1);
	}
}

/* Finds the number of nodes in the tree.*/
int findSize(node* current)
{
	int size = 0;

	if (current->left != NULL)
	{
		size = findSize(current->left);
	}

	if (current->right != NULL)
	{
		size = size + findSize(current->right);
	}

	if ((current->left = NULL) && (current->right == NULL))
	{
		return 1;
	}

	return (size + 1);
}

/* Finds the nodes greater than or equal to a given frequency.*/
void findAll(node* current, int frequency)
{
	if (current->freq >= frequency)
	{
		printf("key: %s, frequency: %d\n", current->word, current->freq);
	}
	if (current->left != NULL)
	{
		findAll(current->left, frequency);
	}
	if (current->right != NULL)
	{
		findAll(current->right, frequency);
	}
}

/* Inserts a node into the tree and then balances the tree.*/
node* insert(char* word, node* current, int type)
{
	if (current == NULL)
	{
		current = create(word);
		if (type == 1)
		{
			printf("key: %s, frequency: %d\n", current->word, current->freq);
		}
	}
	else if (strcmp(word, current->word) == 0)
	{
		current->freq++;
		if (type == 1)
		{
			printf("key: %s, frequency: %d\n", current->word, current->freq);
		}
	}
	else if (strcmp(word, current->word) < 0)
	{
		current->left = insert(word, current->left, type);
		if (findHeight(current->left) - findHeight(current->right) == 2)
		{
			if (strcmp(word, current->left->word) < 0)
			{
				current = rotateLL(current);
			}
			else
			{
				current = rotateLR(current);
			}
		}
	}
	else if (strcmp(word, current->word) > 0)
	{
		current->right = insert(word, current->right, type);
		if (findHeight(current->right) - findHeight(current->left) == 2)
		{
			if (strcmp(word, current->right->word) > 0)
			{
				current = rotateRR(current);
			}
			else
			{
				current = rotateRL(current);
			}
		}
	}
	current->height = findHeight(current);
	return (current);
}

/* Creates a node struct and initializes the values.*/
node* create(char* word)
{
	node* temp = NULL;

	temp = malloc(sizeof(struct node));
	if (temp == NULL)
	{
		printf("Not enough memory has been allocated. \nProgram will terminate. Press enter.\n");
		getchar();
		exit(1);
	}

	temp->word = malloc(sizeof(char)*50);
	strcpy(temp->word, word);
	temp->left = temp->right = NULL;
	temp->height = 0;
	temp->freq = 1;
	return temp;
}

/* Deletes a specified word inputted by the user by first
 * searching for the word in the tree, if the node cannot be found,
 * the user is prompted, if it is found, the frequency is updated.
 * If the frequency has become 0, the node is removed from the tree.
 * The tree is rebalanced upon removal.
 */

node* delete(char* word, node* current)
{
	node* temp = NULL;
	if (current == NULL)
	{
		printf("no_such_key\n");
		return current;
	}
	else if (strcmp(word, current->word) == 0)
	{
		if ((current->left == NULL) && (current->right == NULL))
		{
			current->freq--;
			if (current->freq == 0)
			{
				free(current);
				printf("key: %s, frequency: %d\n", word, 0);
				return NULL;
			}
			printf("key: %s, frequency: %d\n", word, current->freq);
			return current;
		}
		else if (current->left == NULL)
		{
			current->freq--;
			if (current->freq == 0)
			{
				temp = current;
				current = current->right;
				printf("key: %s, frequency: %d\n", word, 0);
				free(temp);
				return current;
			}
			printf("key: %s, frequency: %d\n", word, current->freq);
		}
		else if (current->right == NULL)
		{
			current->freq--;
			if (current->freq == 0)
			{
				temp = current;
				current = current->left;
				printf("key: %s, frequency: %d\n", word, 0);
				free(temp);
				return current;
			}
			printf("key: %s, frequency: %d\n", word, current->freq);
			return current;
		}
		else
		{
			temp = findReplacement(current->left);
			temp->left = current->left;
			temp->right = current->right;
			free(current);
			return temp;
		}
	}
	else if (strcmp(word, current->word) < 0)
	{
		current->left = delete(word, current->left);
		if (findHeight(current->left) - findHeight(current->right) == 2)
		{
			if(strcmp(word, current->left->word) < 0)
			{
				current = rotateLL(current);
			}
			else
			{
				current = rotateLR(current);
			}
		}
	}
	else if (strcmp(word, current->word) > 0)
	{
		current->right = delete(word, current->right);
		if (findHeight(current->right) - findHeight(current->left) == 2)
		{
			if (strcmp(word, current->right->word) > 0)
			{
				current = rotateRR(current);
			}
			else
			{
				current = rotateRL(current);
			}
		}
	}
	else
	{
		printf("no_such_key\n");
		return NULL;
	}
	return current;
}

/* Finds the replacement for a node that is going to be deleted.
 * Alongside rotate(RR, LL, RL, LR), used to rebalance tree.*/
node* findReplacement(node* current)
{
	node* temp;
	if (current->right != NULL)
	{
		if (current->right->right == NULL)
		{
			temp = current->right;
			current->right = current->right->left;
			return temp;
		}
		else
		{
			return (findReplacement(current->right));
		}
	}
	else
	{
		temp = current;
		current = current->left;
		return temp;
	}
}

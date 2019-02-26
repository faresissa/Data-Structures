/* Assignment 2: Question 1
 * Fares Issa
 * issaf - 0925274
 * October 15th, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>


typedef struct carData{
	int milage;
	char * plateNum;
	int returnDate;
	int type;
	struct carData* next;

} carData;

/* Creates a struct of type carData from the given data bt the user. Returns a pointer to the struct.*/
carData* create(carData* head, int newMilage, char* newPlateNum, int newReturnDate, int newType);

/* Adds to the front of the linked list.*/
carData* toFront(carData* head, carData* toAdd);

/* Adds to the end of the linked list.*/
carData* toBack(carData* head, carData* toAdd);

/* Searches the list for a particular plate number.*/
carData* search(carData* head, char* searchedPlateNum);

/* Finds respective position for the data in the list of all cars. Calls create function which
 * creates a struct and places it in the correct sorted position based on milage/type.
 */
carData* findPos(carData* head, int newMilage, char* newPlateNum, int newReturnDate, int newType);

/* Removes a struct from one list to be added to a different list.*/
carData* removeFromList(carData* prev, carData* toDelete);

/* Adds a car after a specified point in the carData struct.*/
void addAfter(carData* position, carData* toAdd);

/* Prints the three different lists.*/
void printList(carData* head);

/* Driver program that initializes and begins parsing the "cars.txt" file.
 * assigns certain cars within the file (based on unique structure), to a certain
 * list, new car, returned, or repaired. Then prompts the user to add, transfer,
 * change state of care (repair), or renting. Calculates a cost for renting or repairing
 * and informs user of the total balance owed/income made through this program.
 */

int main(void)
{
	FILE* file;
	int i;
	char source[900];
	int tempMilage;
	int tempDate;
	int tempType;
	char tempPlate[200];
	char* tempString;
	int extraMiles;
	float rate;
	float income;
	char input;

	tempString = NULL;

	i = 0;
	tempMilage = 0;
	tempDate = 0;
	tempType = 0;
	extraMiles = 0;
	rate = income = 0.00;

	carData* temp;
	carData* newCar;
	carData* currHead;
	carData* rentHead;
	carData* repairHead;

	temp = NULL;
	newCar = NULL;
	currHead = NULL;
	rentHead = NULL;
	repairHead = NULL;

	tempString = malloc(sizeof(char)*9);


	file = fopen("cars.txt", "r"); //open file for reading
	if (file != NULL)
	{
		while (fgets(source, 900, file) != NULL) //Go until file end
		{
			if (i == 0)
			{
				tempMilage = atoi(source);
			}
			else if (i == 1)
			{
				strcpy(tempPlate, source);
			}
			else if (i == 2)
			{
				tempDate = atoi(source);
			}
			else if (i == 3)
			{
				tempType = atoi(source);
			}

			i++;

			if (i == 4)
			{
				if (tempType == 0) //Assigns type 0 to list 1
				{
					currHead = findPos(currHead, tempMilage, tempPlate, tempDate, tempType);
				}
				else if (tempType == 1) //Assigns type 1 to list 2
				{
					newCar = create(repairHead, tempMilage, tempPlate, tempDate, tempType);
					rentHead = toFront(rentHead, newCar);
				}
				else if (tempType == 2) //Assignts type 2 to list 3
				{
					newCar = create(repairHead, tempMilage, tempPlate, tempDate, tempType);
					repairHead = toFront(repairHead, newCar);
				}
				i = 0;
			}
		}
	}
	else
	{
		exit(0);
	}
	fclose(file); //safely close file.
	i = 0; //re-initialize i to reduce error.

	while (i == 0)
	{
		printf("Please select one of the options below.\n");
		printf("1. Add a new car to the available-for-rent list.\n");
		printf("2. Add a returned car to the available-for-rent list.\n");
		printf("3. Add a returned car to the repair list.\n");
		printf("4. Transfer a car from the repair list to the available-for-rent list.\n");
		printf("5. Rent the first available car.\n");
		printf("6. Print all the lists.\n");
		printf("7. Quit.\n");
		printf("Please select an option: ");

		input = fgetc(stdin);

		if (input == '1')
		{
			printf("Please enter a mileage: ");
			scanf("%d", &tempMilage);
			printf("Please enter a license plate: ");
			scanf("%s", tempPlate);
			strcat(tempPlate, "\n");
			tempDate = 000000;
			tempType = 0;
			//creates a new car with type 0 (list 1) in the "available-for-rent" list. Ordered by mileage.
			currHead = findPos(currHead, tempMilage, tempPlate, tempDate, tempType);
			printf("The new car has been added to the list.\n\n");
		}

		else if (input == '2')
		{
			printf("Please enter a mileage: ");
			scanf("%d", &tempMilage);
			printf("Please enter a license plate: ");
			scanf("%s", tempString);
			/* Searches for the location of the string inputted by user. If there is a match
			 * assigns it to list 1, removes it from list 2 and calculates how much the rate
			 * for the trip is.
			 */
			temp = search(rentHead, tempString);

			if (temp == NULL)
			{
				printf("Error finding this license plate. Please try again.\n\n");
				exit(1);
			}
			else
			{
				temp->returnDate = 0;
				temp->type = 0;
				currHead = findPos(currHead, tempMilage, temp->plateNum, temp->returnDate, temp->type);
				rate = 40.00;

				extraMiles = tempMilage - temp->milage - 100; //Under 100 miles is a flat rate.

				//printf("TEMP MILE: %d", extraMiles);
				if (extraMiles > 0)
				{
					//If the extra miles > 0 (meaning over 100) based on previous calculation, the rate is rate + 0.15 * extra miles.
					rate += (extraMiles * 0.15); 
				}
				printf("The rate for this trip is: $%.2f.\n", rate);
				income += rate;
				free(temp->plateNum); 
				free(temp);
				printf("The returned car has been re-added to the list.\n\n");
			}
		}

		else if (input == '3')
		{
			printf("Please enter a mileage: ");
			scanf("%d", &tempMilage);
			printf("Please enter a license plate: ");
			scanf("%s", tempString);

			temp = search(rentHead, tempString);

			if (temp == NULL)
			{
				printf("Error finding this license plate. Please try again.\n\n");
			}
			else
			{
				temp->returnDate = 0;
				temp->type = 2;
				toFront(repairHead, temp);

				rate = 40.00;
				extraMiles = tempMilage - temp->milage - 100;
				if (extraMiles > 0)
				{
					rate += (extraMiles * 0.15);
				}
				printf("The rate for this trip is: $%.2f.\n", rate);
				income += rate;
				free(temp->plateNum);
				free(temp);
				printf("The returned car has been added to the list of cars under repair.\n\n");
			}
		}

		else if (input == '4')
		{
			printf("Please enter a license plate: ");
			scanf("%s", tempString);

			temp = search(repairHead, tempString);

			if (temp == NULL)
			{				
				printf("Error finding this license plate. Please try again.\n\n");
			}
			else
			{
				temp->type = 0;
				currHead = findPos(currHead, temp->milage, temp->plateNum, temp->returnDate, temp->type);
				free(temp->plateNum);
				free(temp);
				printf("This specified car has been added to the list of available cars.\n\n");
			}
		}

		else if (input == '5')
		{
			printf("You have selected to rent the first available car. \nHere is the corresponding information.\n");
			printf("Mileage: %d\n", currHead->milage);
			printf("License Plate: %s\n", currHead->plateNum);
			printf("What is the expected return date? (YYMMDD)\n");
			scanf("%d", &tempDate);

			currHead->returnDate = tempDate; //update return date
			currHead->type = 1;
			temp = currHead;
			currHead = temp->next; //update head pointer

			rentHead = toFront(rentHead, temp);
			printf("The first available car has been rented.\n\n");
		}

		else if (input == '6')
		{
			printList(currHead);
			printList(rentHead);
			printList(repairHead);
		}

		else if (input == '7')
		{
			file = fopen("cars.txt", "w");
			if (file != NULL)
			{
				i = 0;

				while (i < 3)
				{
					if (i == 0) temp = currHead; //Update list 1 based on loop iteration
					if (i == 1) temp = rentHead; //Update list 2 based on loop iteration
					if (i == 2) temp = repairHead; //Update list 3 based on loop iteration

					if (temp != NULL)
					{
						/* Prints all the new values inputted by the user on the linked list
						 * to the file "cars.txt".
						 */
						fprintf(file, "%d\n", temp->milage); 
						fprintf(file, "%s", temp->plateNum);
						fprintf(file, "%d\n", temp->returnDate);
						fprintf(file, "%d\n", temp->type);

						/* Prints next values after the head of the list to the
						 * file "cars.txt".
						 */
						while (temp->next != NULL)
						{
							temp = temp->next;
							fprintf(file, "%d\n", temp->milage);
							fprintf(file, "%s", temp->plateNum);
							fprintf(file, "%d\n", temp->returnDate);
							fprintf(file, "%d\n", temp->type);
						}
					}
					i++;
				}
			}
			else
			{
				printf("There was an error opening the file.\n\n");
			}
			fclose(file); //safely close file.

			//Freeing memory for all the lists.
			while (currHead != NULL)
			{
				temp = currHead->next;

				free(currHead->plateNum);
				free(currHead);

				currHead = temp;
			}
			while(rentHead != NULL)
			{
				temp = rentHead->next;

				free(rentHead->plateNum);
				free(rentHead);

				rentHead = temp;
			}
			while(repairHead != NULL)
			{
				temp = repairHead->next;

				free(repairHead->plateNum);
				free(repairHead);

				repairHead = temp;
			}
			printf("The total income from current session is: $%.2f.\n\n", income);
			exit(0);
		}
		input = fgetc(stdin);

	}
	return 0;
}

carData* create(carData* head, int newMilage, char* newPlateNum, int newReturnDate, int newType)
{
	carData* temp;
	temp = NULL;

	temp = malloc(sizeof(struct carData));
	if (temp == NULL)
	{
		printf("Not enough memory has been allocated. \nProgram will terminate. Press enter.\n");
		getchar();
		exit(1);
	}

	temp->plateNum = malloc(sizeof(char)*(strlen(newPlateNum)+1));
	temp->milage = newMilage;
	strcpy(temp->plateNum, newPlateNum);
	temp->returnDate = newReturnDate;
	temp->type = newType;
	temp->next = NULL;

	return temp;
}

carData* toFront(carData* head, carData* toAdd)
{
	/* This function makes the new struct point to what the
	 * head originally pointed to prior to call.
	 */
	toAdd->next = head;
	return toAdd;
}

carData* toBack(carData* head, carData* toAdd)
{
	carData* temp;
	if (head == NULL) //is list empty?
	{
		return toAdd;
	}
	else
	{
		temp = head; //saves the current value of head in a temp
		while (head->next != NULL) //Finding the end of the list
		{
			head = head->next;
		}
		head->next = toAdd; //Adds the struct to the end of the list.
		return temp;
	}
}

carData* search(carData* head, char* searchedPlateNum)
{
	carData* temp;
	carData* test;
	test = head;
	temp = test->next;

	while(test != NULL) //continues looping until a match with the license plate occurs
	{
		if (strncmp(test->plateNum, searchedPlateNum, 5) == 0)
		{
			temp->next = removeFromList(temp, test);
			return test;
		}
		temp = test;
		test = temp->next;
	}
	return test;
}

carData* findPos(carData* head, int newMilage, char* newPlateNum, int newReturnDate, int newType)
{
	carData* currentPos;
	carData* nextPos;
	carData* newCar;

	currentPos = NULL;
	nextPos = NULL;
	newCar = NULL;

	//if there is nothing at the head of the list, add a new car at the front of the list
	if (head == NULL)
	{
		newCar = create(head, newMilage, newPlateNum, newReturnDate, newType);
		head = toFront(head, newCar);
		return head;
	}

	currentPos = head;
	nextPos = currentPos->next;

	/*if the next position in the list is empty, add a new car if the newMilage is
	 * less than the current positions' milage.
	 */
	if (nextPos == NULL)
	{
		if (newMilage <= currentPos->milage)
		{
			newCar = create(head, newMilage, newPlateNum, newReturnDate, newType);
			head = toFront(head, newCar);
			return head;
		}
		else 
		{
			newCar = create(head, newMilage, newPlateNum, newReturnDate, newType);
			head->next = newCar;
			return head;
		}
	}
	//If the new milage inputted by user is < than milage of the first item, add it to front of list.
	if (newMilage <= currentPos->milage)
	{
		newCar = create(head, newMilage, newPlateNum, newReturnDate, newType);
		head = toFront(head, newCar);
		return head;
	}
	else
	{
		while (nextPos->next != NULL)
		{
			if ((newMilage >= currentPos->milage) && (newMilage <= nextPos->milage))
			{
				newCar = create(head, newMilage, newPlateNum, newReturnDate, newType);
				addAfter(currentPos, newCar);
				return head;
			}
			else
			{
				currentPos = nextPos;
				nextPos = currentPos->next;
			}
		}
	}
	/* If the new mileage is greater than the current positions mileage, AND the new mileage
	 * is less than the next positions mileage, add this car right after the current position.
	 * (second last position).
	 */
	if (nextPos->next == NULL)
	{
		if((newMilage >= currentPos->milage) && (newMilage<= nextPos->milage))
		{
			newCar = create(head, newMilage, newPlateNum, newReturnDate, newType);
			addAfter(currentPos, newCar);
			return head;
		}
		else
		{
			///Add to the end of the list.
			newCar = create(head, newMilage, newPlateNum, newReturnDate, newType);
			addAfter(nextPos, newCar);
			return head;
		}
	}
	return head;
}

carData* removeFromList(carData* prev, carData* toDelete)
{
	carData* temp;
	if ((prev != NULL) && (toDelete != NULL))
	{
		temp = toDelete->next;
		return temp;
	}
	else if (toDelete == NULL)
	{
		return NULL;
	}
	return toDelete;
}

void addAfter(carData* position, carData* toAdd)
{
	/* Adds the struct data to the end of 
	 *where the previous struct pointed to.
	 */

	toAdd->next = position->next;
	position->next = toAdd;
}

void printList(carData* head)
{
	if (head != NULL) //prints the head of the list value.
	{
		printf("Mileage: %d\n", head->milage);
		printf("License Plate: %s", head->plateNum);
		printf("Return Date: %d\n", head->returnDate);
		printf("Type: %d\n\n", head->type);

		while (head->next != NULL) //prints the next head of the list value in a loop until NULL is encountered (end of list).
		{
			head = head->next;

			printf("Mileage: %d\n", head->milage);
			printf("License Plate: %s", head->plateNum);
			printf("Return Date: %d\n", head->returnDate);
			printf("Type: %d\n\n", head->type);
		}
	}
}

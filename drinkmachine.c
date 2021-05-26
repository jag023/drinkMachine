

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drinkmachine.h"

const int STRING_BUFFER_SIZE = 128;
const int INVALID_INDEX = -1;
const char * INPUT_FILE_NAME = "drink_machine.txt";

DrinkMachine* create() {
	DrinkMachine* dm = malloc(sizeof(DrinkMachine));
	dm->versionNum = 1;
	dm->location = INVALID_INDEX;
	//return dm;

	FILE* inFile;		// input file stream

	// A pointer to one of our data structures.  We will allocate space
	// for it later.
	DrinkMachine * drinkMachine;

	int stringLen;

	// Remember... this buffer only exists inside the readFile function.  Anything
	// put in here will "go away" once we exit this function.
	//char tmpBuffer[STRING_BUFFER_SIZE];

	// Open the input file for reading
	inFile = fopen(INPUT_FILE_NAME, "r");

	if (!inFile) {
		printf("Error opening file\n");
		return NULL;
	}

	// Allocate memory to hold one of our data structures.
	// I choose to use calloc to show you that we are creating
	// just enough memory to hold 1 data structure.  We could also
	// use malloc here.
	drinkMachine = calloc(1, sizeof(DrinkMachine));

	if (drinkMachine == NULL)	// Check that the calloc was successful
		return NULL;

	// Read the array length from the file
	fscanf(inFile, "%d", &(drinkMachine->numDrinkItems));
	printf("DEBUG read file numDrinkItems: %d\n", drinkMachine->numDrinkItems);

	// Dynamically create an array of integers that is the correct size
	drinkMachine->drinkItemArr = calloc(drinkMachine->numDrinkItems,
			sizeof(DrinkItem));
	for (int i = 0; i < drinkMachine->numDrinkItems; ++i) {
		char tmpBuffer[STRING_BUFFER_SIZE];
		fscanf(inFile, "%s", tmpBuffer);
		stringLen = strlen(tmpBuffer);
		printf("DEBUG String %d is '%s' and has length %d\n", i, tmpBuffer,
				stringLen);

		// Allocate memory to hold the string plus the NULL character
		(*drinkMachine).drinkItemArr[i].name = malloc(stringLen + 1); // +1 for the NULL terminator that makes it a C-Style string

		if (drinkMachine == NULL) {
			printf(
					"ERROR: Failed to allocate string memory for string %d in function readFile",
					i);
			return NULL;
		}

		// Copy the string from the tmpBuffer to the newly allocated space
		memcpy(drinkMachine->drinkItemArr[i].name, tmpBuffer, stringLen + 1); // destination, source, size
		fscanf(inFile, "%lf %d", &(drinkMachine->drinkItemArr[i].price),
				&(drinkMachine->drinkItemArr[i].numDrinks));
		drinkMachine->drinkItemArr[i].id = i + 1;
		drinkMachine->drinkItemArr[i].numPurchased = 0;
		printf("%s\n %lf\n %d\n", (drinkMachine->drinkItemArr[i].name),
				(drinkMachine->drinkItemArr[i].price),
				(drinkMachine->drinkItemArr[i].numDrinks));
		printf("%i\n", (drinkMachine->drinkItemArr[i].id));
	}

	if (drinkMachine->drinkItemArr == NULL) {
		printf("ERROR: Failed to allocate int array in function readFile\n");
		return NULL;
	}

	// what we open... we must close
	fclose(inFile);

	// Make sure we force any output to screen
	printf("DEBUG readFile Success!\n");
	//fflush(stdout);
	//printf("hello1\n");

	return drinkMachine;

}

void destroy(DrinkMachine* drinkMachine) {
	if (drinkMachine == NULL)	// Safety check
		return;
	for (int i = 0; i < drinkMachine->numDrinkItems; ++i) {
		printf("DEBUG: Freeing drink Item Array\n");
		free(&(drinkMachine->drinkItemArr[i]));
	}
	free(drinkMachine);
}
DrinkItem* firstDrink(DrinkMachine* inputMachine) {
	if (inputMachine->numDrinkItems < 0) {
		inputMachine->location = INVALID_INDEX;
		return NULL;
	}
	inputMachine->location = 0;
	return &(inputMachine->drinkItemArr[0]);
}
DrinkItem* nextDrink(DrinkMachine* inputMachine) {
	if (inputMachine->location == INVALID_INDEX) {
		return NULL;
	}

	inputMachine->location = inputMachine->location + inputMachine->location;
	return &(inputMachine->drinkItemArr[inputMachine->location]);

}
int item(DrinkMachine* differentDrinks) {
	return differentDrinks->numDrinkItems;
}
int available(DrinkMachine* drinkAvail, int drinkId) {
	for (int i = 0; i < drinkAvail->numDrinkItems; i++) {
		if (drinkAvail->drinkItemArr[i].id == drinkId) {
			if (drinkAvail->drinkItemArr[i].numDrinks == 0)
				return 0;
			else
				return 1;
		}
	}
	return 0;

}
double cost(DrinkMachine* drinkPrice, int drinkId) {
	for (int i = 0; i < drinkPrice->numDrinkItems; i++) {
		if (drinkPrice->drinkItemArr[i].id == drinkId) {
			return drinkPrice->drinkItemArr[i].price;
		}
	}
	return -9.00;
}
Purchase purchase(DrinkMachine* machine, int drinkId, double payAmount,
		double*changeDue) {
	for (int i = 0; i < machine->numDrinkItems; i++) {
		if (machine->drinkItemArr[i].id == drinkId) {
			*changeDue = payAmount - machine->drinkItemArr[i].price;
			if (*changeDue < 0)
				return INSUFFICIENT_FUNDS;
			else {
				if (available(machine, drinkId) > 0) {
					machine->drinkItemArr[i].numDrinks--;
					machine->drinkItemArr[i].numPurchased++;
					return PURCHASED;
				}
				return NOT_AVAILABLE;
			}

		}

	}
	return INVALID;

}

void dumpDrinkMachine(DrinkMachine* machine)
{
					printf("Id");
					printf("%*s", 15, "Name");
					printf("%*s", 11, "Price");
					printf("%*s", 6, "Qty");
					printf("%*s", 6, "Sold");
					printf("%*s", 0, "\n");

					for(int i=0; i<machine->numDrinkItems;i++)
					{
						printf("%d %15s %10.2lf %5d %5d\n",
								(machine->drinkItemArr[i].id),
								(machine->drinkItemArr[i].name),
								(machine->drinkItemArr[i].price),
								(machine->drinkItemArr[i].numDrinks),
								(machine->drinkItemArr[i].numPurchased));
                    }
					fflush(stdout);
}









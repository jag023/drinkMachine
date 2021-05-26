/*
 * drinkMachineDriver.c
 *
 *      Author: jesus garza
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drinkmachine.h"

int main(void) {

	DrinkMachine *myDrinkMachine;

	myDrinkMachine = create();

	if (myDrinkMachine == NULL) {
		printf("Error Reading File Data\n");
		return EXIT_FAILURE;
	}

	int size = item(myDrinkMachine);
	dumpDrinkMachine(myDrinkMachine);
	int drinkId;

	do {

		double money;
		double i = 0.0;
		double* changeDue = &i;
		int drinkPrice;
		Purchase result;

		printf(
				"Enter a drink id for the drink you want to purchase or 0 to quit.\n");
		fflush(stdout);
		//scanf("%d", &drinkId);
		//printf("%d\n", drinkId);
		fflush(stdout);
		//if (drinkId != 0)
			printf("Drink Id");
			printf("%*s", 16, "Name");
			printf("%*s", 11, "Price");
			//printf("%*s", 6, "Qty");
			//printf("%*s", 6, "Sold");
			printf("%*s", 0, "\n");
			fflush(stdout);
			for (int i = 0; i < size; i++) {
				printf("%8d %15s %10.2lf\n",
						(myDrinkMachine->drinkItemArr[i].id),
						(myDrinkMachine->drinkItemArr[i].name),
						(myDrinkMachine->drinkItemArr[i].price));
			}
			fflush(stdout);
			scanf("%d", &drinkId);
			/*int id=-1;
				for(int i=0; i<size; i++)
				{
					if(myDrinkMachine->drinkItemArr[i+1].id==drinkId)
					{
						id=drinkId;
					}
				}*/
				//if(id==drinkId)
			if(drinkId>=0 && drinkId<size)
				{
					if (drinkId == 0) {
								printf("Thank you for using the drink machine\n");
								break;
							}

					drinkPrice = cost(myDrinkMachine, drinkId);
					if (drinkPrice < 0) {
						printf("The drink id is not valid.\n");
					} else {
						printf("Enter the amount for the purchase (up to $2.00):");
						fflush(stdout);
						scanf("%lf", &money);
						while(money>=2.00){
							printf("The amount entered is not valid.\n");
							printf("Enter the amount for the purchase (up to $2.00):");
							fflush(stdout);
							scanf("%lf", &money);

						}

						/*printf("Drink Id");
									printf("%*s", 16, "Name");
									printf("%*s", 11, "Price");
									//printf("%*s", 6, "Qty");
									//printf("%*s", 6, "Sold");
									printf("%*s", 0, "\n");
									fflush(stdout);
									for (int i = 0; i < myDrinkMachine->numDrinkItems; i++) {
										printf("%8d %15s %10.2lf\n",
												(myDrinkMachine->drinkItemArr[i].id),
												(myDrinkMachine->drinkItemArr[i].name),
												(myDrinkMachine->drinkItemArr[i].price));
									}
									fflush(stdout);*/
						result = purchase(myDrinkMachine, drinkId, money, changeDue);
						if (result == PURCHASED) {
							if (*changeDue > 0.0) {
								printf(
										"Your drink has been purchased. Your change is $");
								printf("%.2lf\n", *changeDue);
							} else
								printf(
										"Your drink has been purchased. you have no change\n");

						} else if (result == INSUFFICIENT_FUNDS) {
							printf(
									"The amount you entered is insufficient to purchase the drink. The price is %.2lf\n",
									(myDrinkMachine->drinkItemArr[drinkId-1].price));
						} else if (result == NOT_AVAILABLE) {
							printf(
									"Sorry, we are out of your drink. Please select another drink \n");
						} else if (result == INVALID)
							printf("The amount entered is not valid. \n");
						fflush(stdout);

					}

				}
				else
					printf("The drink id is not valid.\n");



		fflush(stdout);
	} while (drinkId != 0);
	if (drinkId == 0) {
		dumpDrinkMachine(myDrinkMachine);
	}

	//printDrinkMachine(myDrinkMachine);

	//freeDrinkMachine(myDrinkMachine);
	fflush(stdout);
	return EXIT_SUCCESS;
}


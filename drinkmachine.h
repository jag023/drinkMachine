/*
 * drinkmachine.h
 *
 *      Author: jesus garza
 */

#ifndef DRINKMACHINE_H_
#define DRINKMACHINE_H_

typedef struct _DrinkItem
{
	int id;
    double price;
    char* name;
    int numDrinks;
	int numPurchased;
} DrinkItem;

typedef struct _DrinkMachine // this is a template for Drink Machines
{
	int numDrinkItems;
	int versionNum;
	int location;
	DrinkItem* drinkItemArr;
} DrinkMachine;

typedef enum _Purchase
		{
		PURCHASED,INVALID,NOT_AVAILABLE,INSUFFICIENT_FUNDS
		}Purchase;


DrinkMachine * create(void);
void destroy(DrinkMachine* drinkMachine);
void printDrinkMachine(const DrinkMachine* drinkMachine);
void freeDrinkMachine(DrinkMachine*fileData);
DrinkItem* firstDrink(DrinkMachine*);
DrinkItem* nextDrink(DrinkMachine*);
int item(DrinkMachine*);
int available(DrinkMachine*, int);
double cost(DrinkMachine*,int);
Purchase purchase(DrinkMachine*,int,double,double*);
void dumpDrinkMachine(DrinkMachine*);

// DrinkMachine* newthing = create();

#endif /* DRINKMACHINE_H_ */

#include "display.h"

void displayLogo() {
/**
 * This is a FigLET Font Generated through the use of https://patorjk.com/software/taag/#p=display&v=2&c=c&f=Cybermedium&t=J%26K's%20Electronics.
 * Modifications with the text were made in order to allow printing in console.
 */
	printf("\t\t\t  _ _  _ . ____    ____ _    ____ ____ ___ ____ ____ _  _ _ ____ ____\n");
	printf("\t\t\t  | |_/  ' [__     |___ |    |___ |     |  |__/ |  | |\\ | | |    [__ \n");
	printf("\t\t\t _| | \\_   ___]    |___ |___ |___ |___  |  |  \\ |__| | \\| | |___ ___] \n\n");
}

//prints a border depending on the input symbol
void displayBorder(int iteration, char symbol) {
	printf("\n");
	for (int x = 0; x < iteration; x++ )
		printf("%c",symbol);
	printf("\n");
}

//calculates the center basedd on the text length
void center(int textLength) {
	for (int x = 0; x < (WIDTH/2)-(textLength/2); x++ )
		printf(" ");
}

//displays text at the center of the console
void displayCenterTitle(char title[]) {
	center(strlen(title));
	printf("%s",title);
}

//displays a fixed layout for the menu
void displayMenu() {
	system("cls");
	displayLogo();
	displayBorder(WIDTH,'*');
	displayCenterTitle("PRODUCT LIST\n\n");
	listMenu();
	displayBorder(WIDTH,'*');
}

//displays a fixed layout for the different options
void displayOptions() {
	displayMenu();
	displayCenterTitle("OPTIONS\n\n");
	displayCenterTitle("01 Take Order  \n");
	displayCenterTitle("02 Log Out     \n");
	displayCenterTitle("03 Exit Program\n");
}

//displays a fixed layout for the edit screen
void displayEdit(int orderList[99][2], int orderNumber) {
	system("cls");
	displayLogo();
	displayBorder(WIDTH,'*');
	displayCenterTitle("EDIT MODE\n\n");
	listOrder(orderList, orderNumber);
	displayBorder(WIDTH,'*');
	displayCenterTitle("TOTAL: PHP ");
}

//displays a fixed layout for the receipt
void displayReceipt(int orderList[99][2], int orderNumber, float total, float discount, float cashPaid){
	system("cls");
	displayLogo();
	displayBorder(WIDTH,'*');
	displayCenterTitle("RECEIPT\n\n");
	listReceipt(orderList, orderNumber);
}

//displays a fixed layout for taking orders
void displayTakeOrder(){
	displayMenu();
	displayCenterTitle("TOTAL: PHP ");
	
}

/*
	displays error message
	allow = 1; prompts error
	allow = 0; does not prompt error
*/
void displayError(int allow, char errorMsg[]) {
	if (allow)
		printf("%s", errorMsg);
}

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

void displayBorder(int iteration, char symbol) {
	printf("\n");
	for (int x = 0; x < iteration; x++ )
		printf("%c",symbol);
	printf("\n");
}

void center(int textLength) {
	for (int x = 0; x < (WIDTH/2)-(textLength/2); x++ )
		printf(" ");
}

void displayCenterTitle(char title[]) {
	center(strlen(title));
	printf("%s",title);
}

void displayMenu() {
	system("cls");
	displayLogo();
	displayBorder(WIDTH,'*');
	displayCenterTitle("PRODUCT LIST\n\n");
	listMenu();
	displayBorder(WIDTH,'*');
}

void displayOptions() {
	displayMenu();
	displayCenterTitle("OPTIONS\n\n");
	displayCenterTitle("01 Take Order  \n");
	displayCenterTitle("02 Log Out     \n");
	displayCenterTitle("03 Exit Program\n");
}

void displayEdit(float total, int orderList[99][2], int orderNumber) {
	system("cls");
	displayLogo();
	displayBorder(WIDTH,'*');
	displayCenterTitle("EDIT MODE\n\n");
	listOrder(orderList, orderNumber);
	displayBorder(WIDTH,'*');
	displayCenterTitle("TOTAL: PHP ");
	printf("%.2f\n",total);
}

void displayReceipt(int orderList[99][2], int orderNumber, float total, float discount, float cashPaid){
	system("cls");
	displayLogo();
	displayBorder(WIDTH,'*');
	displayCenterTitle("RECEIPT\n\n");
	listReceipt(orderList, orderNumber, total, discount, cashPaid);
	displayBorder(WIDTH,'*');
}

void displayTakeOrder(float total){
	displayMenu();
	displayCenterTitle("TOTAL: PHP ");
	printf("%.2f\n",total);
}

void displayError(int allow, char errorMsg[]) {
	if (allow)
		printf("%s", errorMsg);
}

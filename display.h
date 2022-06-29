#define WIDTH 118
#include "options.h"

void center(int textLength);
void displayCenterTitle(char title[]);
void displayLogo();
void displayBorder(int iteration, char symbol);
void displayMenu();
void displayOptions();
void displayError(int allow, char erroMsg[]);
void displayTakeOrder();
void displayEdit(int orderList[99][2], int orderNumber);
void displayReceipt(int orderList[99][2], int orderNumber, float total, float discount, float cashPaid);

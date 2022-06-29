#include "menu.h"
#include "display.h"

int options();
void takeOrder();
int codeInt(char itemCode[]);
int threeChociePrompt(char prompt[], char c1[], char c2[],char c3[]);
void listOrder();
int getTotal(int method);
void listReceipt(int orderList[99][2], int orderNumber, float total, float discount, float cashPaid);
void getCash(float cashPaid, float total);
int reset();
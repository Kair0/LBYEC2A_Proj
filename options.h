#include "menu.h"


int options();
void takeOrder();
int codeInt(char itemCode[]);
int threeChociePrompt(char prompt[], char c1[], char c2[],char c3[]);
void listOrder();
int getTotal(int method);
void listReceipt(int orderList[99][2], int orderNumber);
float getCash(float cashPaid, float total);
void getFinalTotal(float total, float discount, float cashPaid);
int reset();
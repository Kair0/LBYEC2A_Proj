#include <stdio.h>
#include "options.h"

//displays the different options that the program will allow
int options() {
	int run = 1;
	int error = 0;
	
	while(run) {
		displayOptions();
		displayError(error, "===INVALID OPTION! TRY AGAIN!===\n");
		
		char userInput[2];
		getchar();
		printf("Option: ");
		scanf("%s", userInput);
		
		if(!strcmp(userInput,"01")) 
			return 1;
		if(!strcmp(userInput,"02")) 
			return 2;
		if(!strcmp(userInput,"03")) 
			return 3;
		error = 1;		
	}
}

//this is the bulk of the POS system. This function is responsible for taking the order and aggregating the total 
void takeOrder() {
	
	int run = 1;
	int error = 0;
	int orderList[99][2];
	int orderNumber = 0;
	float total = 0.0;
	float cashPaid = 0.0;
	float discount = 0.0;

	
	while(run) {
		
		//checks if array is at zero to prevent overflow	
		if (orderNumber != -1) {
			
			char itemCode[3];
			int qty = 0;
			int addOption = 0;
			
			displayTakeOrder();
			printf("%.2f\n",total);
			displayError(error, "===INVALID CODE! TRY AGAIN!===\n");
			
			printf("\nEnter Order: ");
			scanf("%s", itemCode);
			
			//checks if the input is valid. Will return an error code if it is invalid
			if(codeInt(itemCode) != -1) {
				
				error = 0;
				int errorQty = 1;
				
				//Error Checking for QTY
				do {		
					printf("Enter Quantity: ");
					scanf("%d", &qty);
					if(qty>0)
						errorQty = 0;
					displayError(errorQty, "===INVALID QUANTITY! TRY AGAIN!===\n");
				} while (errorQty);
					
				orderList[orderNumber][0] = codeInt(itemCode);
				orderList[orderNumber][1] = qty;
				total += orderList[orderNumber][1]*getPrice(codeInt(itemCode));
				
				getchar();
				displayTakeOrder();
				printf("%.2f\n",total);
				
				//Asks the user for an option after adding an order
				int promptRun = 1;
				while(promptRun) {
					switch(threeChociePrompt("Additional Order?", "Yes", "No" ,"Edit")) {
						//adds an additional order
						case 1:
							orderNumber++;
							promptRun = 0;
							break;
						//stops taking order and prints a receipt
						case 2: {
							int runReceipt = 1;
							int errorReceipt = 0;
							while(runReceipt) {
								system("cls");
								displayError(errorReceipt, "===INVALID OPTION! TRY AGAIN!===\n");
								
								int promptRunReceipt = 1;
								while (promptRunReceipt) {
									switch(threeChociePrompt("Discount?", "None", "Seniors/PWD" ,"Member")) {
										//no discount
										case 1:
											discount = 0.0;
											cashPaid = getCash(cashPaid,total,discount);										
											displayReceipt(orderList, orderNumber);
											getFinalTotal(total, discount, cashPaid);
											promptRunReceipt = 0;
											runReceipt = 0;
											run = 0;
											break;
										//seniors/pwd
										case 2:
											discount = 15.0;
											printf("\nA discount of 15%% is applied!\n");
											cashPaid = getCash(cashPaid,total,discount);
											displayReceipt(orderList, orderNumber);
											getFinalTotal(total, discount, cashPaid);
											promptRunReceipt = 0;
											runReceipt = 0;
											run = 0;
											break;
										//member discount
										case 3:
											discount = 10.0;
											if(authMember()) {
												printf("\nA discount of 10%% is applied!\n");
												cashPaid = getCash(cashPaid,total,discount);
												displayReceipt(orderList, orderNumber);
												getFinalTotal(total, discount, cashPaid);
												promptRunReceipt = 0;
												runReceipt = 0;
												run = 0;
											}
											break;
										default:
											errorReceipt = 1;
											break;
									}	
								}
							}
							promptRun = 0;
							run = 0;
							break;
						}
						//enter edit mode	
						case 3: {
							int runEdit = 1;
							int errorEdit = 0;
							while(runEdit) {
															
								int option = 0;
								int qty = 0;
								int itemCode;
								
								displayEdit(orderList,orderNumber);
								printf("%.2f\n",total);
								displayError(errorEdit, "===INVALID OPTION! TRY AGAIN!===\n");
								switch(threeChociePrompt("Choose an Option", "Change Qty", "Remove" ,"Exit")) {
									//change qty
									case 1:
										printf("Enter Item Number: ");
										scanf("%d", &itemCode);
										if(itemCode>orderNumber) {
											errorEdit = 1;
											break;
										}			
										//Error Checking for QTY
										int errorQty = 1;
										do {		
											printf("Enter Quantity: ");
											scanf("%d", &qty);
											if(qty>0)
												errorQty = 0;
											displayError(errorQty, "===INVALID QUANATITY! TRY AGAIN!===\n");
										} while (errorQty);
										total -= orderList[itemCode][1]*getPrice(orderList[itemCode][0]);
										orderList[itemCode][1] = qty;
										total += orderList[itemCode][1]*getPrice(orderList[itemCode][0]);
										errorEdit = 0;
										break;
									//remove item
									case 2:
										printf("Enter Item Number: ");
										scanf("%d", &itemCode);
										if(itemCode>orderNumber) {
											errorEdit = 1;
											break;
										}
										total -= orderList[itemCode][1]*getPrice(orderList[itemCode][0]);
										orderList[itemCode][0] = -1;
										errorEdit = 0;
										break;
									//exit edit mode
									case 3:
										runEdit = 0;
										break;
									default:
										errorEdit = 1;
										break;
								}
							}
							break;
						}
					}
				}
			} else //applies the error code if invalid input
				error = 1;
		}	
	}
}

//lists all the order input 
void listOrder(int orderList[99][2], int orderNumber) {
	int row = 0;
	for (row; row <= orderNumber; row++) {
		printf("Item Number:%d", row);
		if(orderList[row][0]!=-1) {
			printf("\tQTY:%d\t",orderList[row][1]);
			int stringLength = printMenuDetails(orderList[row][0],1);
			
			//prints white space for layout purposes
			for(int i = stringLength; i < ITEMLENGTH; i++) {
				printf(" ");
			}
				
			printf("PHP %.2f\n",orderList[row][1]*getPrice(orderList[row][0]));
		} else {
			printf("\t#####ITEM REMOVED#####\n");
		}	
	}
}

//list the receipt 
void listReceipt(int orderList[99][2],int orderNumber) {	
	int row = 0;
	for (row; row <= orderNumber; row++) {
		if(orderList[row][0]!=-1) {
			int stringLength = printMenuDetails(orderList[row][0],1);
			//prints white space for layout purposes
			for(int i = stringLength; i < ITEMLENGTH; i++) {
				printf(" ");
			}
			printf("\tQTY:%d\t",orderList[row][1]);
			printf("\t\tPHP %.2f\n",orderList[row][1]*getPrice(orderList[row][0]));
		} else {
			printf("#####ITEM REMOVED#####\n");
		}	
	}	
}

//gets the final total based on the discount 
void getFinalTotal(float total, float discount, float cashPaid) {
	
	float discountedAmount = total*(discount/100.0);
	float newTotal = total - discountedAmount;
	float change = cashPaid - newTotal;
	
	printf("\n\nDISCOUNT: -PHP %.2f\n", discountedAmount);
	printf("TOTAL: PHP %.2f\n", newTotal);
	printf("CASH: PHP %.2f\n", cashPaid);
	printf("CHANGE: PHP %.2f\n", change);
	displayBorder(118,'*');
}

//prompts the user to provide cash details
float getCash(float cashPaid, float total, float discount) {
	int run = 1;
	while(run) {
		float cash = 0.0;
		printf("Enter Cash: ");
		scanf("%f", &cash);
		
		if(cash >= total-(total*(discount/100.0))) {
			run = 0;
			return cash;
		} else {
			displayError(1, "===INVALID AMOUNT! TRY AGAIN!===\n");
		}
	}
}

/*
	prompts the user to choose between three options
	takes 4 string parameters: Question prompt, option1, option 2, and option 3
*/
int threeChociePrompt(char prompt[], char c1[], char c2[],char c3[]) {
	
	int run = 1;
	int error = 0;
	
	while(run) {
		
		displayError(error, "===INVALID OPTION! TRY AGAIN!===\n");
		
		int option = 0;
		printf("%s (1-%s, 2-%s, 3-%s): ", prompt, c1, c2, c3);
		scanf("%d", &option);
		
		if(option == 1)
			return 1;
		else if(option == 2)
			return 2;
		else if(option == 3)
			return 3;
		else
			error = 1; 	
	}
}

//resets the bulk of the program and displays an option to restart, logout or exit
int reset() {
	int run = 1;
	int error = 0;
	
	while(run) {
		
		displayError(error, "===INVALID OPTION! TRY AGAIN!===\n");
		
		switch(threeChociePrompt("Choose an Option", "Restart", "Log out" ,"Exit")) {
			case 1:
				return 1;
				break;
			case 2:
				return 2;
				break;
			case 3:
				return 3;
				break;
			default:
				error = 1;
				break;
			}
	}
}

/*
	converts the string item code to an integer.
	If input is invalid, it will return an integer value of -1.
*/
int codeInt(char itemCode[]) {
	if(!strcmp(itemCode,"001")) 
		return 0;
	else if(!strcmp(itemCode,"002")) 
		return 1;
	else if(!strcmp(itemCode,"003")) 
		return 2;
	else if(!strcmp(itemCode,"004")) 
		return 3;
	else if(!strcmp(itemCode,"005")) 
		return 4;
	else if(!strcmp(itemCode,"006")) 
		return 5;
	else if(!strcmp(itemCode,"007")) 
		return 6;
	else if(!strcmp(itemCode,"008")) 
		return 7;
	else if(!strcmp(itemCode,"009")) 
		return 8;
	else if(!strcmp(itemCode,"010")) 
		return 9;
	else if(!strcmp(itemCode,"011")) 
		return 10;
	else if(!strcmp(itemCode,"012")) 
		return 11;
	else if(!strcmp(itemCode,"013")) 
		return 12;
	else if(!strcmp(itemCode,"014")) 
		return 13;
	else if(!strcmp(itemCode,"015")) 
		return 14;
	else if(!strcmp(itemCode,"016")) 
		return 15;
	else if(!strcmp(itemCode,"017")) 
		return 16;
	else if(!strcmp(itemCode,"018")) 
		return 17;
	else if(!strcmp(itemCode,"019")) 
		return 18;
	else if(!strcmp(itemCode,"020")) 
		return 19;
	else 
		return -1;
}
#include <stdio.h>
#include "options.h"

//itemcode, qty
int orderList[99][2];
int orderNumber = 0;
float total = 0.0;
float cashPaid = 0.0;
float discount = 0.0;

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



void takeOrder() {
	int run = 1;
	int error = 0;
	
	while(run) {		
		//shows error code if there is a wrong input
		if (orderNumber != -1) {		
			
			char itemCode[3];
			int qty = 0;
			int addOption = 0;
			
			displayTakeOrder(total);
			displayError(error, "===INVALID OPTION! TRY AGAIN!===\n");
			printf("\nEnter Order: ");
			scanf("%s", itemCode);
			
			if(codeInt(itemCode) != -1) {
				printf("Enter Quantity: ");
				scanf("%d", &qty);
				orderList[orderNumber][0] = codeInt(itemCode);
				orderList[orderNumber][1] = qty;
				total += orderList[orderNumber][1]*getPrice(codeInt(itemCode));
				
				getchar();
				displayTakeOrder(total);
				
				int promptRun = 1;
				while(promptRun) {
					switch(threeChociePrompt("Additional Order?", "Yes", "No" ,"Edit")) {
						case 1:
							orderNumber++;
							promptRun = 0;
							break;
						case 2:
							getReceipt();
							promptRun = 0;
							run = 0;
							break;
						case 3:
							editOrder();
							break;
					}
				}
			} 
			else
				error = 1;	
		}		
	}
}


void listOrder() {
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

void editOrder() {
	int run = 1;
	int error = 0;
	while(run) {
		displayEdit(total);
		displayError(error, "===INVALID OPTION! TRY AGAIN!===\n");
		
		int option = 0;
		int qty = 0;
		int itemCode;
		
		switch(threeChociePrompt("Choose an Option", "Change Qty", "Remove" ,"Exit")) {
			case 1:
				printf("Enter Item Number: ");
				scanf("%d", &itemCode);
				if(itemCode>orderNumber) {
					error = 1;
					break;
				}
				printf("Enter Quantity: ");
				scanf("%d", &qty);
				total -= orderList[itemCode][1]*getPrice(orderList[itemCode][0]);
				orderList[itemCode][1] = qty;
				total += orderList[itemCode][1]*getPrice(orderList[itemCode][0]);
				error = 0;
				break;
			case 2:
				printf("Enter Item Number: ");
				scanf("%d", &itemCode);
				if(itemCode>orderNumber) {
					error = 1;
					break;
				}
				total -= orderList[itemCode][1]*getPrice(orderList[itemCode][0]);
				orderList[itemCode][0] = -1;
				error = 0;
				break;
			case 3:
				run = 0;
				orderNumber++;
				break;
			default:
				error = 1;
				break;
		}
	}
}

void getReceipt() {
	int run = 1;
	int error = 0;
	while(run) {
		system("cls");
		displayError(error, "===INVALID OPTION! TRY AGAIN!===\n");
		
		int option = 0;
		
		int promptRun = 1;
		while (promptRun) {
			switch(threeChociePrompt("Discount?", "None", "Seniors/PWD" ,"Member")) {
				case 1:
					getCash();
					discount = 0.0;
					displayReceipt();
					promptRun = 0;
					run = 0;
					break;
				case 2:
					getCash();
					discount = 15.0;
					displayReceipt();
					promptRun = 0;
					run = 0;
					break;
				case 3:
					getCash();
					discount = 10.0;
					if(authMember()) {
						displayReceipt();
						promptRun = 0;
						run = 0;
					}
					break;
				default:
					error = 1;
					break;
			}	
		}
	}
}

void listReceipt() {
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
	
	float discountedAmount = total*(discount/100.0);
	float newTotal = total - discountedAmount;
	float change = cashPaid - newTotal;
	
	printf("\n\nDISCOUNT: -PHP %.2f\n", discountedAmount);
	printf("TOTAL: PHP %.2f\n", newTotal);
	printf("CASH: PHP %.2f\n", cashPaid);
	printf("CHANGE: PHP %.2f\n", change);
}

void getCash() {
	int run = 1;
	while(run) {
		float cash = 0.0;
		printf("Enter Cash: ");
		scanf("%f", &cash);
		
		if(cash >= total) {
			cashPaid = cash;
			run = 0;
		} else {
			displayError(1, "===INVALID AMOUNT! TRY AGAIN!===\n");
		}
	}
}

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


int reset() {
	int run = 1;
	int error = 0;
	
	orderNumber = 0;
	discount = 0.0;
	total = 0.0;
	cashPaid = 0.0;
	orderList[0][0] = 0;
	orderList[0][1] = 0;
	
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
	SUBJECT TO CHANGE
	Hindi ako sure if papayag si sir gagamit ako ng built-in function para magconvert ng string to int.
	So mano-mano muna hehe
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
#include "menu.h"

//itemCode,itemName,itemPrice
char menu[][3][40] = {
	{"001","Banana JPhone 13", "PHP 44 990.00"},
	{"002","Samsing Milkyway 20","PHP 27 990.00"},
	{"003","Highway P50","PHP 69 999.00"},
	{"004","GG 55in Television LED Display","PHP 91 256.72"},
	{"005","Samsing 55in Television OLED Display","PHP 115 320.18"},
	{"006","Banana JWatch Series 6","PHP 49 990.00"},
	{"007","Samsing Milkyway Watch 4","PHP 14 990.00"},
	{"008","DaMianBao Note 10","PHP 7 938.42"},
	{"009","SleepStation 5 Pro","PHP 27 607.77"},
	{"010","SpaghettiBook Air","PHP 54 990.00"},
	{"011","LandWall Portable 1TB Hard Drive","PHP 2 620.25"},
	{"012","Ybox  Series Y","PHP 26 156.83"},
	{"013","Waterpods Pro","PHP 7 690.00"},
	{"014","Samsing Earbuds Pro","PHP 9 990.00"},
	{"015","SUSA Vivabook Pro 16x","PHP 88 999.00"},
	{"016","Boss Noise Cancelling Headphones 700","PHP 19 856.76"},
	{"017","LBJ Flip 3 Portable Bluetooth Speaker","PHP 9 902.18"},
	{"018","Sory Camera Alpha 9","PHP 149 999.00"},
	{"019","GonePro Villain 10","PHP 59 380.00"},
	{"020","Bipolaroid Camera Go","PHP 15,250.67"}
};

float price[] = {
	44990.00,
	27990.00,
	69999.00,
	91256.72,
	115320.18,
	49990.00,
	14990.00,
	7938.42,
	27607.77,
	54990.00,
	2620.25,
	26156.83,
	7690.00,
	9990.00,
	88999.00,
	19856.76,
	9902.18,
	149999.00,
	59380.00,
	15250.67
};

//prints the item code, menu and the price
void displayMenu() {
	int row, column;
	for (row=0; row<20; row++) {
		for (column=0; column<3; column++) {
			//checks if column index is at itemName
			if(column == 1) {
				//fills up the string with white spaces for layout purposes
				char itemName[40] = "";
				strcat(itemName,menu[row][column]);
				for(int i = 0; strlen(itemName) < 40; i++) {
					strcat(itemName," ");
				}
				printf("%s\t", itemName);
			} else {
				printf("%s\t", menu[row][column]);
			}	
		}
		printf("\n");
	}
}

//Takes the price of an item depending on the code
float getPrice(int itemCode) {
	return price[itemCode-1];
}


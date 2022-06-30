#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "menu.h"
#include "auth.h"
#include "options.h"
#include "display.h"


int main() {
	
	//variables necessary for looping the program
	int run = 1;
	int allowAuth = 1;
	
	while(run) {
		
		int allowReset = 0;
		displayLogo();
		
		//login authentication wont proceed to the next code if not validated
		if(allowAuth) {
			while(authenticate()) {
				system("cls");
				displayLogo();
				displayError(1,"===INVALID CREDENTIALS! TRY AGAIN!===\n");
			}
		}

		//Shows possible options if validated
		switch(options()){
			case 1:
				takeOrder(); //runs the bulk of the POS system
				run = 0;
				allowReset = 1;    
				break;
			case 2:
				//log out
				run = 1;
				system("cls"); 
				break;
			case 3:
				run = 0; //exits the program
				break;
		}
		
		/*
			Option to reset the whole program when takeOrder is finish
			1: reset
			2: logout
			3: exit
		*/
		if (allowReset) {
			//waits for a return value from the reset function to faciliate reset, logout and exit
			switch(reset()) {
				case 1:
					run = 1;
					allowAuth = 0;
					break;
				case 2:
					system("cls");
					run = 1;
					allowAuth = 1;
					break;
				case 3:
					run = 0;
					break;
			}		
		}
	}
	return 0;
}

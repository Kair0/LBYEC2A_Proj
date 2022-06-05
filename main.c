#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "menu.h"
#include "auth.h"
#include "options.h"
#include "display.h"


int main() {
	int run = 1;
	int allowAuth = 1;
	
	while(run) {
		int allowReset = 0;
		//login authentication wont proceed to the next code if not validated
		displayLogo();
		
		if(allowAuth) {
			while(authenticate()) {
				system("cls");
				displayLogo();
				displayError(1,"===INVALID CREDENTIALS! TRY AGAIN!===\n");
			}
		}

		//Shows option if validated
		switch(options()){
			case 1:
				takeOrder();
				run = 0;
				allowReset = 1;    
				break;
			case 2:
				run = 1;
				system("cls");
				break;
			case 3:
				run = 0;
				break;
		}
		
		if (allowReset) {
			switch(reset()) {
				case 1:
					run = 1;
					allowAuth = 0;
					break;
				case 2:
					run = 1;
					allowAuth = 1;
					break;
				case 3:
					run = 0;
					break;
			}		
		}
	}
	return 1;
}

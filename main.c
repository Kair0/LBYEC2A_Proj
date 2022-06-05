#include "menu.h"
#include "auth.h"
#include "display.h"
#include "options.h"

int main() {
	int run = 1;
	
	while(run) {
		//login authentication wont proceed to the next code if not validated
		displayLogo();
		while(authenticate()) {
			system("cls");
			displayLogo();
			printf("===INVALID CREDENTIALS! TRY AGAIN!===\n");
		}
		
		//Shows option if validated
		switch(options()) {
			case 1:
				printf("Taking order...");
				run = 0; //will be removed once taking order option is added
				break;
			case 2:
				run = 1;
				system("cls");
				break;
			case 3:
				run = 0;
				break;
		}	
	}
	return 1;
}

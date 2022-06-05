#include "options.h"

int options() {
	
	int run = 1;
	int error = 0;
	
	while(run) {
		displayOptions();
		
		//shows error code if there is a wrong input
		if (error)
			printf("===INVALID OPTION! TRY AGAIN!===\n");
		
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
		
		//asks for userinput if there was an invalid choice
		error = 1;
		run = 1;
	}
}
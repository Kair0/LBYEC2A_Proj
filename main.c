#include <stdio.h>
#include <stdlib.h>
#include "menu.h"


void logo() {
/**
 * This is a FigLET Font Generated through the use of https://patorjk.com/software/taag/#p=display&v=2&c=c&f=Cybermedium&t=J%26K's%20Electronics.
 * Modifications with the text were made in order to allow printing in console.
 */
	printf("  _ _  _ . ____    ____ _    ____ ____ ___ ____ ____ _  _ _ ____ ____\n");
	printf("  | |_/  ' [__     |___ |    |___ |     |  |__/ |  | |\\ | | |    [__ \n");
	printf(" _| | \\_   ___]    |___ |___ |___ |___  |  |  \\ |__| | \\| | |___ ___] \n\n");
}
	
int main() {
	logo();
	displayMenu();
	return 0;
}
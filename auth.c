#include "auth.h"

//username, password
char adminInfo[][2][20] = {
	{"adminKAID","3l3ctr0n!cS"},
	{"adminJMGGA","3ngIn3Er1nG"},
	{"adminMG","PR0f35$0r"},
};

/*
	This function authenthicates user loging
	returns a value of 0 if the input was valid
	reurnss a value of 1 if the input was invalid
*/

int authenticate() {
	char username[20];
	char password[20];
	
	printf("Username: ");
	scanf("%s", username);
	
	int acceptPassword = 0;
	int userIndex;
	
	for (int i = 0; i < 3; i++) {
		if (strcmp(username, adminInfo[i][0]) == 0) {
			acceptPassword = 1;
			userIndex = i;
		}
	}
	
	getchar();
	printf("Password: ");
	scanf("%s", password);
	if (acceptPassword && strcmp(password, adminInfo[userIndex][1]) == 0) 
		return 0;
	else
		return 1;
}
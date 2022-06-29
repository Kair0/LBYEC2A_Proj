#include "auth.h"

/*
	This function authenthicates user loging
	returns a value of 0 if the input was valid
	reurnss a value of 1 if the input was invalid
*/
int authenticate() {
	
	//username, password
	char adminInfo[][2][STRLENGTH] = {
		{"adminKAID","3l3ctr0n!cS"},
		{"adminJMGGA","3ngIn3Er1nG"},
		{"adminMG","PR0f35$0r"},
		{"admin", "admin"} //this is temporary
	};
	
	char username[STRLENGTH];
	char password[STRLENGTH];
	
	printf("Username: ");
	scanf("%s", username);
	
	int acceptUser = 0;
	int userIndex;
	
	for (int i = 0; i < 4; i++) { //change 4 to 3 if "admin" user will be remove (sizeof) should be used though idk if sir will allow
		if (!strcmp(username, adminInfo[i][0])) {
			acceptUser = 1;
			userIndex = i;
		}
	}

	printf("Password: ");
	//hides password
	int x = 0;
	while(x < STRLENGTH && x >= 0) {
		password[x] = getch();		
		if(password[x] == '\b') {
			x--;
			printf("\b \b");
		} else if(password[x] == '\r') {
			password[x] = '\0';
			break;
		} else {
			printf("*");
			x++;	
		}
	}
	
	if (acceptUser && strcmp(password, adminInfo[userIndex][1]) == 0) 
		return 0;
	else
		return 1;
}


/*
	This function membership for discounts
	returns a value of 0 if the input was valid
	reurns a value of 1 if the input was invalid
*/
int authMember() {
	
	//membership ID: ID Number, Validity (T-Active, F-Inactive)
	char memberID[][2][STRLENGTH] = {
		{"20220908011","INACTIVE"},
		{"20210526834","ACTIVE"},
		{"20201217390","ACTIVE"},
		{"20220329385","INACTIVE"},
		{"20211101347","ACTIVE"}
	
	};
	
	char member[STRLENGTH];
	int run = 1;
	
	while (run) {
		printf("Membership ID (type X to cancel): ");
		scanf("%s", member);

		for (int i = 0; i < 5; i++) {
			if (!strcmp(member, memberID[i][0])) {	
				if(!strcmp(memberID[i][1],"ACTIVE")) {
					printf("###VALID###");
					return 1;
				} else{	
					printf("###INACTIVE###");
				}
			}
			
			if(!strcmp(member, "x"))
				return 0;
		}
		printf("###INVALID###\n");
	}
}

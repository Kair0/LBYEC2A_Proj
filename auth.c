#include "auth.h"

//username, password
char adminInfo[][2][STRLENGTH] = {
	{"adminKAID","3l3ctr0n!cS"},
	{"adminJMGGA","3ngIn3Er1nG"},
	{"adminMG","PR0f35$0r"},
	{"admin", "admin"} //this is temporary
};

//membership ID: ID Number, Validity (T-Active, F-Inactive)
char memberID[][2][STRLENGTH] = {
	{"20220908011","INACTIVE"},
	{"20210526834","ACTIVE"},
	{"20201217390","ACTIVE"},
	{"20220329385","INACTIVE"},
	{"20211101347","ACTIVE"}

};



/*
	This function authenthicates user loging
	returns a value of 0 if the input was valid
	reurnss a value of 1 if the input was invalid
*/
int authenticate() {
	char username[STRLENGTH];
	char password[STRLENGTH];
	
	printf("Username: ");
	scanf("%s", username);
	
	int acceptPassword = 0;
	int userIndex;
	
	for (int i = 0; i < 4; i++) { //change 4 to 3 if "admin" user will be remove
		if (!strcmp(username, adminInfo[i][0])) {
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

int authMember() {
	char member[STRLENGTH];
	int run = 1;
	
	while (run) {
		printf("Membership ID: ");
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
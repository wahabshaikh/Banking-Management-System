#include <stdio.h>
#include <Windows.h>

void create_account();
void display_list();
//void remove_account();
//void search_account();
//void edit_account();
//void deposit();
//void withdraw();

void staff_login()
{
	int pin;
	printf("\nEnter pin: ");
	scanf("%d", &pin);

	if (pin == 1234)
	{
		int choice;

		do
		{
			system("cls");
			printf("\n\t\t\tWELCOME STAFF\n");
			printf("\n 1. Create Account");
			printf("\n 2. Display Customer Details");
			printf("\n 3. Remove Account");
			printf("\n 4. Search for Account");
			printf("\n 5. Edit Account");
			printf("\n 6. Deposit Amount");
			printf("\n 7. Withdraw Amount");
			printf("\n 8. Log Out");

			printf("\n\n Enter your choice: ");
			scanf("%d", &choice);

			switch(choice)
			{
				case 1:
					create_account();
					break;
				case 2:
					display_list();
					break;
				case 3:
					//remove_account();
					break;
				case 4:
					//search_account();
					break;
				case 5:
					//edit_account();
					break;
				case 6:
					//deposit();
					break;
				case 7:
					//withdraw();
					break;
				case 8:
					break;
				default:
					printf("\nInvalid choice. Please try again.\n");
					Sleep(3000);
					break;
			}
		}
		while (choice != 8);
	}
	else
	{
		printf("\nWrong password! Please try again.\n");
		Sleep(3000);
		staff_login();
	}
}

void create_account()
{	
	// Create file pointer and open file in append mode
	FILE *fp = fopen("record.txt", "a");
	if (fp == NULL)
	{
		printf("Error! Cannot create account.\n");
		Sleep(3000);
		return;
	}

	struct ACCOUNT new_ACCOUNT;

	// Input customer details
	system("cls");
	printf("\n\t\t\tENTER CUSTOMER DETAILS\n");
	printf("\nAccount number: ");
	scanf("%llu", &(new_ACCOUNT.ACCOUNT_NUM));
	printf("\nPin: ");
	scanf("%4d", &(new_ACCOUNT.PIN));
	printf("\nName: ");
	fflush(stdin);
	scanf("%[^\n]", new_ACCOUNT.NAME);
	printf("\nAge: ");
	scanf("%d", &(new_ACCOUNT.AGE));
	printf("\nAddress: ");
	fflush(stdin);
	scanf("%[^\n]", new_ACCOUNT.ADDRESS);
	printf("\nInitial Deposit: ");
	scanf("%lf", &(new_ACCOUNT.BALANCE));

	// Timestamp
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);

	// Write the details into the file
	fprintf(fp, "\nTIMESTAMP:- %d-%d-%d %d:%d:%d\nACCOUNT NUMBER:- %llu\nPIN:- %d\nNAME:- %s\nAGE:- %d\nADDRESS:- %s\nBALANCE:- %lf\n", 
str_t.wDay, str_t.wMonth, str_t.wYear, str_t.wHour, str_t.wMinute, str_t.wSecond, new_ACCOUNT.ACCOUNT_NUM, new_ACCOUNT.PIN, new_ACCOUNT.NAME, new_ACCOUNT.AGE, new_ACCOUNT.ADDRESS, new_ACCOUNT.BALANCE);

	// Close the file
	fclose(fp);

	// Print success message
	printf("\nAccount created successfully!\n");
	Sleep(3000);
}

void display_list()
{
	// Create file pointer and open file in read mode
	FILE *fp = fopen("record.txt", "r");
	if (fp == NULL)
	{
		printf("No records found!\n");
		Sleep(3000);
		return;
	}

	// Print the file contents
	system("cls");
	char ch;
	do
	{
		ch = fgetc(fp);
		printf("%c", ch);
	}
	while (ch != EOF);

	// Exit
	int exit;
	do
	{
		printf("\nPress -1 to exit\n");
		scanf("%d", &exit);
	}
	while (exit != -1);

	// Close the file
	fclose(fp);
}


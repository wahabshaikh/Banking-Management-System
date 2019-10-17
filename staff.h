#include <stdio.h>
#include <Windows.h>

void create_account();
void display_list();
void remove_account();
void search_account();
void edit_account();
void deposit();
void withdraw();

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
					remove_account();
					break;
				case 4:
					search_account();
					break;
				case 5:
					edit_account();
					break;
				case 6:
					deposit();
					break;
				case 7:
					withdraw();
					break;
				case 8:
					break;
				default:
					printf("\n Invalid choice. Please try again.\n");
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
		return;
	}
}

void create_account()
{	
	// Allocate memory for new account
	struct ACCOUNT *new_ACCOUNT = (struct ACCOUNT *)malloc(sizeof(struct ACCOUNT));

	// Input customer details
	system("cls");
	printf("\n\t\t\tENTER CUSTOMER DETAILS\n");
	printf("\n Account number: ");
	scanf("%llu", &(new_ACCOUNT -> ACCOUNT_NUM));
	printf("\n Pin: ");
	scanf("%4d",&(new_ACCOUNT -> PIN));
	printf("\n Name: ");
	fflush(stdin);
	scanf("%[^\n]", new_ACCOUNT -> NAME);
	printf("\n Age: ");
	scanf("%d", &(new_ACCOUNT -> AGE));
	printf("\n Address: ");
	fflush(stdin);
	scanf("%[^\n]", new_ACCOUNT -> ADDRESS);
	printf("\n Initial Deposit: ");
	scanf("%lf", &(new_ACCOUNT -> BALANCE));
	GetSystemTime(&(new_ACCOUNT -> str_t));
	new_ACCOUNT -> next = NULL;

	// Add node to linked list
	if (start == NULL)
	{
		start = new_ACCOUNT;
	}
	else
	{
		struct ACCOUNT *ptr = start;
		while (ptr -> next != NULL)
		{
			ptr = ptr -> next;
		}

		ptr -> next = new_ACCOUNT;
	}

	// Print success message
	printf("\n Account created successfully!\n");
	Sleep(3000);

	// Update the file
	ll_to_file();
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

void search_account()
{
	system("cls");

	// Empty linked list
	if (start == NULL)
	{
		printf("No records found!\n");
		Sleep(3000);
		return;
	}

	unsigned long long account_number;
	printf("\nEnter Account Number: ");
	scanf("%llu", &account_number);

	struct ACCOUNT *ptr;
	ptr = start;
	while (ptr -> ACCOUNT_NUM != account_number && ptr != NULL)
	{
		ptr = ptr -> next;
	}

	if (ptr == NULL)
	{
		printf("\nAccount not found! Please try again.\n");
		Sleep(3000);
		return;
	}

	printf("\nTIMESTAMP:- %d-%d-%d %d:%d:%d\nACCOUNT NUMBER:- %llu\nPIN:- %d\nNAME:- %s\nAGE:- %d\nADDRESS:- %s\nBALANCE:- %lf\n", 
ptr -> str_t.wDay, ptr -> str_t.wMonth, ptr -> str_t.wYear, ptr -> str_t.wHour, ptr -> str_t.wMinute, ptr -> str_t.wSecond, ptr -> ACCOUNT_NUM, ptr -> PIN, ptr -> NAME, ptr -> AGE, ptr -> ADDRESS, ptr -> BALANCE);

	int exit;
	do
	{
		printf("\nPress -1 to exit\n");
		scanf("%d", &exit);
	}
	while (exit != -1);
}

void remove_account()
{
	system("cls");

	if (start == NULL)
	{
		printf(" No records found!\n");
		Sleep(3000);
		return;
	}

	unsigned long long account_number;
	int pin;

	printf("\n Enter Account Number: ");
	scanf("%llu", &account_number);
	printf("\n Enter Pin: ");
	scanf("%d", &pin);

	struct ACCOUNT *ptr, *preptr;

	ptr = start;

	// CASE 1: Deleting the first account
	if (ptr -> ACCOUNT_NUM == account_number && ptr -> PIN == pin)
	{
		start = ptr -> next;
		free(ptr);
		printf("\n Account Number: %llu removed successfully!\n", account_number);
		Sleep(3000);
		ll_to_file();
		return;
	}

	else if (ptr -> PIN != pin) 
	{
		printf("\n Invalid pin! Please try again.\n");
		Sleep(3000);
		return;
	}

	// CASE 2: Deleting any other account
	else
	{
		while (ptr -> ACCOUNT_NUM != account_number && ptr != NULL)
		{
			preptr = ptr; 
			ptr = ptr -> next;
		}

		if (ptr == NULL)
		{
			printf("\n Account not found! Please try again.\n");
			Sleep(3000);
			return;
		}

		else if (ptr -> PIN != pin) 
		{
			printf("\n Invalid pin! Please try again.\n");
			Sleep(3000);
			return;
		}

		else
		{
			preptr -> next = ptr -> next;
			free(ptr);
			printf("\n Account Number: %llu removed successfully!\n", account_number);
			Sleep(3000);
			ll_to_file();
		}
	}
}

void edit_account()
{
	system("cls");

	if (start == NULL)
	{
		printf("No records found!\n");
		Sleep(3000);
		return;
	}

	unsigned long long account_number;
	printf("\nEnter Account Number: ");
	scanf("%llu", &account_number);

	struct ACCOUNT *ptr;
	ptr = start;
	while (ptr -> ACCOUNT_NUM != account_number && ptr != NULL)
	{
		ptr = ptr -> next;
	}

	if (ptr == NULL)
	{
		printf("\nAccount not found! Please try again.\n");
		Sleep(3000);
		return;
	}

	printf("\nTIMESTAMP:- %d-%d-%d %d:%d:%d\nACCOUNT NUMBER:- %llu\nPIN:- %d\nNAME:- %s\nAGE:- %d\nADDRESS:- %s\nBALANCE:- %lf\n", 
ptr -> str_t.wDay, ptr -> str_t.wMonth, ptr -> str_t.wYear, ptr -> str_t.wHour, ptr -> str_t.wMinute, ptr -> str_t.wSecond, ptr -> ACCOUNT_NUM, ptr -> PIN, ptr -> NAME, ptr -> AGE, ptr -> ADDRESS, ptr -> BALANCE);

	int option;
	do
	{
		printf("\n What do you wish to edit?\n");
		printf("\n 1. Name");
		printf("\n 2. Age");
		printf("\n 3. Address");  
		printf("\n 4. Pin");
		printf("\n 5. Exit");

		printf("\n\n Enter your choice: ");
		scanf("%d", &option);
		switch(option)
		{
			case 1:
				printf("\n Enter Name: ");
				scanf("%s", ptr -> NAME);
				break;
			case 2:
				printf("\n Enter Age: ");
				scanf("%d", &(ptr -> AGE));
				break;
			case 3:
				printf("\n Enter Address: ");
				scanf("%s", ptr -> ADDRESS);
				break;
			case 4:
				printf("\n Enter Pin: ");
				scanf("%d", &(ptr -> PIN));
			case 5:
				break;
			default:
				printf("\n Invalid choice. Please try again.\n");
				Sleep(3000);
				break;
		}
	}
	while (option != 5);

	printf("\n Account details updated successfully!\n");
	Sleep(3000);

	ll_to_file();
}


void deposit()
{
	system("cls");

	if (start == NULL)
	{
		printf(" No records found!\n");
		Sleep(3000);
		return;
	}

	double amount;
	unsigned long long account_number;

	system("cls");
	printf("\n Enter Account Number: ");
	scanf("%llu", &account_number);

	struct ACCOUNT *ptr;
	ptr = start;
	while (ptr -> ACCOUNT_NUM != account_number && ptr != NULL)
	{
		ptr = ptr -> next;
	}

	if (ptr == NULL)
	{
		printf("\n Account not found! Please try again.\n");
		Sleep(3000);
		return;
	}

	printf("\n Enter amount to deposit: ");
	scanf("%lf", &amount);

	// Update account balance
	ptr -> BALANCE += amount;

	printf("\n\n Amount deposited successfully!");
	printf("\n Updated balance: %lf\n", ptr -> BALANCE);
	Sleep(3000);

	ll_to_file();
}

void withdraw()
{
	system("cls");

	if (start == NULL)
	{
		printf(" No records found!\n");
		Sleep(3000);
		return;
	}

	double amount;
	unsigned long long account_number;

	system("cls");
	printf("\n Enter Account Number: ");
	scanf("%llu", &account_number);

	struct ACCOUNT *ptr;
	ptr = start;
	while (ptr -> ACCOUNT_NUM != account_number && ptr != NULL)
	{
		ptr = ptr -> next;
	}

	if (ptr == NULL)
	{
		printf("\n Account not found! Please try again.\n");
		Sleep(3000);
		return;
	}

	printf("\n Enter amount to withdraw: ");
	scanf("%lf", &amount);

	if (amount > ptr -> BALANCE)
	{
		printf("Insufficient balance! Please try again.\n");
		Sleep(3000);
	}

	else
	{
		// Update account balance
		ptr -> BALANCE -= amount;
	}

	printf("\n\n Amount withdrawn successfully!");
	printf("\n Updated balance: %lf\n", ptr -> BALANCE);
	Sleep(3000);

	ll_to_file();
}
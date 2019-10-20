#include <stdio.h>
#include <Windows.h>

void view_account(struct ACCOUNT *self);
void transact(struct ACCOUNT *self);

void user_login()
{
	if (!start)
	{
		printf("\nNo records found!\n");
		Sleep(3000);
		return;
	}

	unsigned long long account_num;
	int pin;

	// Input login credentials
	printf("\nEnter account number: ");
	scanf("%llu", &account_num);
	printf("\nEnter pin: ");
	scanf("%d", &pin);

	// Find account and validate pin	
	struct ACCOUNT *account;

	account = start;

	while (account -> ACCOUNT_NUM != account_num && account)
	{
		account = account -> next;
	}

	if (!account)
	{
		printf("Account number not found. Please try again.\n");
		Sleep(3000);
		return;
	}

	if (account -> PIN != pin)
	{
		printf("\nWrong password! Please try again.\n");
		Sleep(3000);
		return;
	}

	int choice;

	do
	{
		system("cls");
		printf("\n\t\t\tWELCOME USER\n");
		printf("\n 1. Transact");
		printf("\n 2. View Account Details");
		printf("\n 3. Log Out");

		printf("\n\n Enter your choice: ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				transact(account);
				break;
			case 2:
				view_account(account);
				break;
			case 3:
				break;
			
			default:
				printf("\n Invalid choice. Please try again.\n");
				Sleep(3000);
				break;
		}
	}
	while (choice != 3);
}

void view_account(struct ACCOUNT *self)
{
	system("cls");

	printf("\nTIMESTAMP:- %d-%d-%d %d:%d:%d\nACCOUNT NUMBER:- %llu\nPIN:- %d\nNAME:- %s\nAGE:- %d\nADDRESS:- %s\nBALANCE:- %lf\n", 
self -> str_t.wDay, self -> str_t.wMonth, self -> str_t.wYear, self -> str_t.wHour, self -> str_t.wMinute, self -> str_t.wSecond, self -> ACCOUNT_NUM, self -> PIN, self -> NAME, self -> AGE, self -> ADDRESS, self -> BALANCE);

	int exit;
	do
	{
		printf("\nPress -1 to exit\n");
		scanf("%d", &exit);
	}
	while (exit != -1);
}

void transact(struct ACCOUNT *self)
{
	system("cls");

	unsigned long long account_num;
	printf("\n Enter account number of recipient: ");
	scanf("%d", &account_num);

	// Search for recipient's account
	struct ACCOUNT *recipient = start;
	while (recipient -> ACCOUNT_NUM != account_num && recipient != NULL)
	{
		recipient = recipient -> next;
	}

	if (recipient == NULL)
	{
		printf("\n Account not found! Please try again.\n");
		Sleep(3000);
		return;
	}

	double amount;
	printf("\n Enter amount: ");
	scanf("%lf", &amount);

	if (amount > self -> BALANCE)
	{
		printf("\n Insufficient balance! Please try again.\n");
		Sleep(3000);
		return;
	}

	// Sender's and receiver's balance
	self -> BALANCE -= amount;
	recipient -> BALANCE += amount;

	ll_to_file();
}

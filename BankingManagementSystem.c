#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

// Structure containing account details
struct ACCOUNT
{
	unsigned long long ACCOUNT_NUM;
	int PIN;
	char NAME[30];
	int AGE;
	char ADDRESS[100];
	long double BALANCE;
	struct ACCOUNT *next;
};

struct ACCOUNT *start = NULL;

void staff_login();
void customer_login();

void create_account();
void display_list();
void remove_account();
void search_account(unsigned long long account_num);
void edit_account(unsigned long long account_num);
void deposit(unsigned long long account_num);
void withdraw(unsigned long long account_num);

// MAIN MENU
int main()
{
	int choice;

	do
	{
		system("cls");
		printf("\n\t\t\tWELCOME TO DIGITAL BANK\n");
		printf("\n1. Staff login");
		printf("\n2. Customer login");
		printf("\n3. Exit");

		printf("\n\nEnter your choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
			case 1:
				staff_login();
				break;
			case 2:
				customer_login();
				break;
			case 3:
				break;
			default:
				printf("\nInvalid choice. Please try again.\n");
		}
	}
	while (choice != 3);
}

// Function for staff login
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
			printf("\n 8. Log Out\n");

			printf("\n\n Enter your choice:");
			scanf("%d", &choice);

			unsigned long long account_num;

			if (choice == 4 || choice == 5)
			{
				printf("Enter account number: ");
				scanf("%llu", &account_num);
			}

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
					search_account(account_num);
					break;
				case 5:
					edit_account(account_num);
					break;
				case 6:
					deposit(account_num);
					break;
				case 7:
					withdraw(account_num);
					break;
				case 8:
					break;
				default:
					printf("\nInvalid choice. Please try again.\n");
					break;
			}
		}
		while (choice != 8);
	}
	else
	{
		printf("\nWrong password. Please try again.\n");
		staff_login();
	}
}

// Function for customer login
void customer_login()
{
	struct ACCOUNT *ptr;
	unsigned long long account_num;
	int pin;

	// Input login credentials
	printf("\nEnter account number: ");
	scanf("%llu", &account_num);

	printf("Enter pin: ");
	scanf("%d", &pin);

	// Validate pin
	if (start == NULL)
	{
		printf("No Records.\n");
		Sleep(3000);
		return;
	}
	else
	{
		while (ptr -> ACCOUNT_NUM != account_num && ptr != NULL)
		{
			ptr = ptr -> next;
		}

		if (ptr == NULL)
		{
			printf("Account number not found.\n");
		}
		else
		{
			if (ptr -> PIN != pin)
			{
				printf("Wrong password! Please try again.\n");
				customer_login();
			}
			else
			{
				int choice;
		
				do
				{
					printf("\n\t\t\tWELCOME CUSTOMER\n");
					printf("\n 1. View Account Details");
					printf("\n 2. Deposit");
					printf("\n 3. Withdraw");
					printf("\n 4. Log Out\n");

					printf("\n\n Enter your choice: ");
					scanf("%d", &choice);

					switch(choice)
					{
						case 1:
							search_account(account_num);
							break;
						case 2:
							deposit(account_num);
							break;
						case 3:
							withdraw(account_num);
							break;
						case 4:
							break;
						default:
							printf("\nInvalid choice. Please try again.\n");
							break;
					}
				}
				while (choice != 4);
			}
		}
	}
}

// Function to create a new account
void create_account()
{	
	/*
	// Create file pointer and open file in append mode
	FILE *fp = fopen("record.txt", "a");
	if (fp == NULL)
	{
		printf("Can't open the file.\n");
		return;
	}
	*/

	struct ACCOUNT *new_ACCOUNT, *ptr;

	// Allocate memory for new ACCOUNT
	new_ACCOUNT = (struct ACCOUNT *)malloc(sizeof(struct ACCOUNT));

	// Input customer details
	printf("\nENTER CUSTOMER DETAILS\n\n");
	printf("Account number: ");
	scanf("%llu", new_ACCOUNT -> ACCOUNT_NUM);
	printf("Pin: ");
	scanf("%4d", new_ACCOUNT -> PIN);
	printf("Name: ");
	fflush(stdin);
	scanf("%[^\n]", new_ACCOUNT -> NAME);
	printf("Age: ");
	scanf("%d", new_ACCOUNT -> AGE);
	printf("Address: ");
	fflush(stdin);
	scanf("%[^\n]", new_ACCOUNT -> ADDRESS);
	printf("Initial Deposit: ");
	scanf("%LF", new_ACCOUNT -> BALANCE);

	// Add ACCOUNT to linked list
	new_ACCOUNT -> next = NULL;
	if (start == NULL)
	{
		start = new_ACCOUNT;
	}

	else
	{
		while (ptr -> next != NULL)
			ptr = ptr -> next;
		ptr -> next = new_ACCOUNT;
	}
/*
	// Write the details into the file
	fprintf(fp, "%llu \t %d \t %s \t %d \t %LF \n%s\n", ptr -> ACCOUNT_account_num, 
ptr -> PIN, ptr -> NAME, ptr -> AGE, ptr -> BALANCE, ptr -> ADDRESS);

	// Close the file
	fclose(fp);
*/
}

// Function to display customer list
void display_list()
{
	if (start == NULL)
	{
        printf("No Records.\n");
        return;    
	}
    else
    {
        struct ACCOUNT *ptr = start;
        
        printf("\nCUSTOMER LIST:\n");

        while (ptr != NULL)
        {
        	static int count = 1;

        	system("cls");
        	printf("\nRecord %d:\n", count);
            printf("ACCOUNT NUMBER: %llu\n", ptr -> ACCOUNT_NUM);
            printf("NAME: %s\n", ptr -> NAME);
            printf("PIN: %d\n", ptr -> PIN);
            printf("AGE: %s\n", ptr -> AGE);
            printf("ADDRESS: %s\n", ptr -> ADDRESS);
            printf("BALANCE: %LF\n", ptr -> BALANCE);
            Sleep(3);

            ptr = ptr -> next;
            count++;
        }
    }
}

// Function to remove an account
void remove_account()
{
	int account_num;
    printf("Enter account number to be removed: ");
    scanf("%d", &account_num);

    struct ACCOUNT *ptr, *preptr;

    ptr = start;
    while (ptr -> ACCOUNT_NUM != account_num && ptr != NULL)
    {
        preptr = ptr;
        ptr = ptr -> next;
    }
    
    if (ptr == NULL)
    {
        printf("Account not found!\n");
    }

    else
    {
        preptr -> next = ptr -> next;
        printf("Account %llu removed successfully!", ptr -> ACCOUNT_NUM);
        free(ptr);
    }
}

// Function to search an account
void search_account(unsigned long long account_num)
{
	struct ACCOUNT *ptr;

	if (start == NULL)
	{
		printf("No Records.\n");
		return;
	}
	else
	{
		ptr = start;
		while (ptr -> ACCOUNT_NUM != account_num && ptr != NULL)
		{
			ptr = ptr -> next;
		}
		if (ptr == NULL)
		{
			printf("Record not found.\n");
		}
		else
		{
			printf("ACCOUNT NUMBER: %llu\n", ptr -> ACCOUNT_NUM);
            printf("NAME: %s\n", ptr -> NAME);
            printf("PIN: %d\n", ptr -> PIN);
            printf("AGE: %s\n", ptr -> AGE);
            printf("ADDRESS: %s\n", ptr -> ADDRESS);
            printf("BALANCE: %LF\n", ptr -> BALANCE);
		}
	}
}

// Function to edit an account
void edit_account(unsigned long long account_num)
{
	struct ACCOUNT *ptr;

	if (start == NULL)
	{
		printf("No Records.\n");
		return;
	}
	else
	{
		ptr = start;
		while (ptr -> ACCOUNT_NUM != account_num && ptr != NULL)
		{
			ptr = ptr -> next;
		}

		if (ptr == NULL)
		{
			printf("Record not found.\n");
		}
		else
		{
			printf("ACCOUNT NUMBER: %llu\n", ptr -> ACCOUNT_NUM);
            printf("NAME: %s\n", ptr -> NAME);
            printf("PIN: %d\n", ptr -> PIN);
            printf("AGE: %s\n", ptr -> AGE);
            printf("ADDRESS: %s\n", ptr -> ADDRESS);
            printf("BALANCE: %LF\n", ptr -> BALANCE);

            printf("\nWhat do you wish to edit?\n");
            printf("1. Name\n");
            printf("2. Pin");
            printf("3. Age\n");
            printf("4. Address\n");

            int choice;
            scanf("%d", &choice);

            switch (choice)
            {
            	case 1:
            		printf("Enter name: ");
            		gets(ptr -> NAME);
            		break;
            	case 2:
            		printf("Enter pin: ");
            		scanf("%4d", ptr -> PIN);
            		break;
            	case 3:
            		printf("Enter age: ");
            		scanf("%d", ptr -> AGE);
            		break;
            	case 4:
            		printf("Enter address: ");
            		gets(ptr -> ADDRESS);
            		break;
            	default:
            	printf("Invalid choice.\n");
            	break;
            }
		}
	}	
}

// Function to deposit amount
void deposit(unsigned long long account_num)
{
	struct ACCOUNT *ptr;

	while (ptr -> ACCOUNT_NUM != account_num)
	{
		ptr = ptr -> next;
	}

	long double amount;
	printf("Enter amount to deposit: ");
	scanf("%d", &amount);

	ptr -> BALANCE = ptr -> BALANCE + amount;
	printf("Amount deposited successfully! Current balance: %LF\n", ptr -> BALANCE);
}

// Function to withdraw amount
void withdraw(unsigned long long account_num)
{
struct ACCOUNT *ptr;

	while (ptr -> ACCOUNT_NUM != account_num)
	{
		ptr = ptr -> next;
	}

	long double amount;
	printf("Enter amount to deposit: ");
	scanf("%d", &amount);

	if (ptr -> BALANCE < amount)
	{
		printf("Invalid amount. Please enter an amount less than your current balance.\n");
	}
	else
	{
		ptr -> BALANCE = ptr -> BALANCE - amount;
		printf("Amount withdrawn successfully! Current balance: %LF\n", ptr -> BALANCE);		
	}
}
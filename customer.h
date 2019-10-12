#include <stdio.h>
#include <Windows.h>

void transact();

void customer_login()
{
	unsigned long long account_num;
	int pin;

	// Input login credentials
	printf("\nEnter account number: ");
	scanf("%llu", &account_num);
	printf("\nEnter pin: ");
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
			Sleep(3000);
		}
		else
		{
			if (ptr -> PIN != pin)
			{
				printf("\nWrong password! Please try again.\n");
				customer_login();
			}
			else
			{
				int choice;
		
				do
				{
					printf("\n\t\t\tWELCOME CUSTOMER\n");
					printf("\n 1. Transact");
					printf("\n 2. View Transaction History");
					printf("\n 3. Log Out");

					printf("\n\n Enter your choice: ");
					scanf("%d", &choice);

					switch(choice)
					{
						case 1:
							transact();
							break;
						case 2:
							search_account();
							break;
						case 3:
							break;
						default:
							printf("\nInvalid choice. Please try again.\n");
							Sleep(3000);
							break;
					}
				}
				while (choice != 3);
			}
		}
	}
}
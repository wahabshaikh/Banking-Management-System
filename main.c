#include <stdio.h>
#include <Windows.h>

#include "ACCOUNT.h"
#include "staff.h"

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
				//customer_login();
				break;
			case 3:
				break;
			default:
				printf("\nInvalid choice. Please try again.\n");
				Sleep(3000);
		}
	}
	while (choice != 3);
}


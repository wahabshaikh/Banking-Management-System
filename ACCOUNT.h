#include <stdio.h>
#include <Windows.h>

// Account details
struct ACCOUNT
{
	unsigned long long ACCOUNT_NUM;
	int PIN;
	char NAME[30];
	int AGE;
	char ADDRESS[100];
	double BALANCE;
	// Timestamp
	SYSTEMTIME str_t;
	struct ACCOUNT *next;
};

struct ACCOUNT *start = NULL;

// Read from the file and store it as a linked list
void file_to_ll()
{
	FILE *fp = fopen("record.txt", "r");
	
	if (fp == NULL)
	{
		printf("Error! Cannot open file.\n");
		Sleep(3000);
	}
	else
	{
		int count;
		fscanf(fp, "Number of Records: %d\n", &count);

		int i;
        for (i = 0; i < count; i++)
        {
            struct ACCOUNT *new_node, *ptr;
            new_node = (struct ACCOUNT *)malloc(sizeof(struct ACCOUNT));
            new_node -> next = NULL;

            fscanf(fp, "\nTIMESTAMP:- %d-%d-%d %d:%d:%d\nACCOUNT NUMBER:- %llu\nPIN:- %d\nNAME:- %s\nAGE:- %d\nADDRESS:- %s\nBALANCE:- %lf\n", 
&(new_node -> str_t.wDay), &(new_node -> str_t.wMonth), &(new_node -> str_t.wYear), &(new_node -> str_t.wHour), &(new_node -> str_t.wMinute), &(new_node -> str_t.wSecond), &(new_node -> ACCOUNT_NUM), &(new_node -> PIN), new_node -> NAME, &(new_node -> AGE), new_node -> ADDRESS, &(new_node -> BALANCE));

            if (start == NULL)
            {
                start = new_node;
            }
            else
            {
                ptr = start;
                while (ptr -> next != NULL)
                {
                    ptr = ptr -> next;
                }
                ptr -> next = new_node;
            }
        }
	}
} 

// Function to count the number of nodes in linked list
int counter()
{
    int count = 0;

    struct ACCOUNT *ptr = start;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr -> next;
    }

    return count;
}

// Store linked list contents into file
void ll_to_file()
{
	int count = counter();

	FILE *fp = fopen("record.txt", "w");

	if(fp == NULL)
	{
	    printf("Error! Cannot open file.\n");
	    Sleep(3000);
	}
	else
	{
	    fprintf(fp, "Number of Records: %d\n", count);

	    struct ACCOUNT *ptr = start;
	    while (ptr != NULL)
	    {
			fprintf(fp, "\nTIMESTAMP:- %d-%d-%d %d:%d:%d\nACCOUNT NUMBER:- %llu\nPIN:- %d\nNAME:- %s\nAGE:- %d\nADDRESS:- %s\nBALANCE:- %lf\n", 
ptr -> str_t.wDay, ptr -> str_t.wMonth, ptr -> str_t.wYear, ptr -> str_t.wHour, ptr -> str_t.wMinute, ptr -> str_t.wSecond, ptr -> ACCOUNT_NUM, ptr -> PIN, ptr -> NAME, ptr -> AGE, ptr -> ADDRESS, ptr -> BALANCE);
			ptr = ptr -> next;
	    }
	}

	fclose(fp);
}
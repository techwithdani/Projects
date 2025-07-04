#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void pinGeneration(void)
{
    FILE *fp;

    srand(time(NULL));
    int generatedPin = 1000 + rand() % 9000;

    printf("\nPIN generated successfully\n");
    printf("\nYour generated PIN: %d\n", generatedPin);
    printf("\nRe-run the program and use ATM with this PIN\n\n");

    fp = fopen("pin.txt", "a");
    if (NULL == fp)
    {
        printf("\nCannot open file!");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%d\n", generatedPin);
    fclose(fp);
}

int checkPin(void)
{
    FILE *fp;
    char pin[8];
    char keyPin[8];
    int pinValid = 0;

    printf("\n\nEnter the PIN: \n");
    scanf("%s", keyPin);

    fp = fopen("pin.txt", "r");
    if (NULL == fp)
    {
        printf("\nFile cannot be opened\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(pin, sizeof(pin), fp) != NULL)
    {
        if (strstr(pin, keyPin))
        {
            pinValid = 1;
        }
    }
    fclose(fp);

    return pinValid;
}

void showBalance(int *balance)
{
    printf("\nYour current balance is Rs.%d\n", *balance);
}

void depositMoney(int *balance)
{
    int depositAmount;
    char depositStmt[50];

    printf("\nEnter amount to deposit: ");
    scanf("%d", &depositAmount);

    if (depositAmount > 0)
    {
        *balance += depositAmount;
        printf("\nRs.%d deposited\n", depositAmount);

        snprintf(depositStmt, sizeof(depositStmt), "Rs.%d deposited\n", depositAmount);
    }
    else
    {
        printf("\nInvalid amount entered\n.");
    }
}

void withdrawMoney(int *balance)
{
    int withdrawAmount;
    char withdrawStmt[50];

    printf("\nEnter amount to withdraw: ");
    scanf("%d", &withdrawAmount);

    if (withdrawAmount > 0)
    {
        if (withdrawAmount > *balance)
        {
            printf("\nCannot withdraw. Balance Rs.%d\n", *balance);
        }
        else
        {
            *balance -= withdrawAmount;
            printf("\nRs.%d withdrawn\n", withdrawAmount);

            snprintf(withdrawStmt, sizeof(withdrawStmt), "Rs.%d withdrawn\n", withdrawAmount);
        }
    }
    else
    {
        printf("\nInvalid amount entered\n.");
    }
}

int main(void)
{
    int choice1, choice2;
    int pinValid = 0, balance = 0;

    while (1)
    {
        printf("\n\nATM System\n\n");
        printf("1. Generate PIN\n2. Use ATM\n3. Exit\n");
        printf("\nYour choice: ");
        scanf("%d", &choice1);

        switch (choice1)
        {
        case 1:
            pinGeneration();
            exit(EXIT_SUCCESS);
        case 2:
            pinValid = checkPin();
            if (pinValid)
            {
                printf("\nValid PIN\n");
            }
            else
            {
                printf("\nInvalid PIN. Please generate a PIN if you don't have one.\n");
                exit(EXIT_FAILURE);
            }

            while (pinValid)
            {
                printf("\nATM System Menu\n\n\n");
                printf("1. Check Balance\n2. Deposit\n3. Withdraw\n4. Quit\n\n");

                printf("Enter choice: ");
                scanf("%d", &choice2);

                switch (choice2)
                {
                case 1:
                    showBalance(&balance);
                    break;
                case 2:
                    depositMoney(&balance);
                    break;
                case 3:
                    withdrawMoney(&balance);
                    break;
                case 4:
                    printf("\nThank you for using the ATM\n");
                    exit(EXIT_SUCCESS);
                default:
                    printf("\nInvalid option entered!\n");
                    break;
                }
            }
        case 3:
            exit(EXIT_SUCCESS);
        default:
            printf("\nInvalid choice. Try again.\n");
            break;
        }
    }
    return 0;
}

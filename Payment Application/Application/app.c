#include"app.h"

/*------------------------------------------------------------------------*/
void Menu()
{
	system("COLOR 09");
	printf("\n\n\n\n\n\t\t\t\t\t\t\tpayment\n");
	printf("\t\t\t\t\t\t=======================\n");
	printf("\t\t\t\t\t\t[1] terminal configuration .\n");
	printf("\t\t\t\t\t\t[2] Withdraw money.\n");
	printf("\t\t\t\t\t\t[0] Exit the Program.\n");
	printf("\t\t\t\t\t\t=======================\n");
	printf("\t\t\t\t\t\t  Enter The Choice: ");
}
/*------------------------------------------------------------------------*/
void GoBackOrExit()
{
	getchar();
	char Option;
	printf(" Go back(b)? or Exit(0)?: ");
	scanf("%c", &Option);
	if (Option == '0')
	{
		ExitProject();
	}
	else
	{
		system("cls");
	}
}
/*------------------------------------------------------------------------*/
void ExitProject()
{
	system("cls");
	int i;
	char ThankYou[100] = " ========= Thank You =========\n";
	for (i = 0; i < strlen(ThankYou); i++)
	{
		printf("%c", ThankYou[i]);
		Sleep(30);
	}
	exit(1);
}
/*------------------------------------------------------------------------*/

void userStory(void)
{
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	ST_transaction_t transData;

	float maxAmount = 0;
	/*0- Setting max amount*/
	printf("Set Max Amount of Transactions\n");
	scanf("%f", &maxAmount);
	while(setMaxAmount(&termData, maxAmount))
	{
		printf("Wrong Input\n");
		printf("Set Max Amount of Transactions\n");
		scanf("%f", &maxAmount);
	}
	fflush(stdin);
	
	
		while (1)
		{	
			/*1- Get card holder name*/
			while (getCardHolderName(&cardData))
				printf("Wrong Card Holder Name\n");

			/*2- Get card expiration date*/
			while (getCardExpiryData(&cardData))
				printf("Wrong Expiration Date\n");


			/*3- Get card PAN*/
			while (getCardPAN(&cardData))
				printf("Wrong Primary Account Number\n");

			/*4- Get All card data*/
			strcpy(transData.cardHolderData.cardHolderName, cardData.cardHolderName);
			strcpy(transData.cardHolderData.cardExpirationData, cardData.cardExpirationData);
			strcpy(transData.cardHolderData.primaryAcountNumber, cardData.primaryAcountNumber);

			/*5- Get transaction date*/
			printf("Enter transaction Date in format DD/MM/YYYY\n");
			gets(&termData.transactionDate);
			while (getTransactionDate(&termData))
			{
				printf("Wrong Date, Enter Again\n");
				gets(&termData.transactionDate);
			}

			/*6- is Card Expired?*/
			if (isCardExpired(&cardData, &termData))
			{
				/*7.True- Decline Expired Card*/
				printf("Card is Expired\n");
			}
			else
			{
				/*7.False- Get transaction amount*/
				printf("Enter transaction amount\n");
				scanf("%f", &termData.transAmount);
				while (getTransactionAmount(&termData))
				{
					printf("Invalid amount, enter agian\n");
					scanf("%f", &termData.transAmount);
				}
				/*8- is Exceeded amount?*/
				if (isBelowMaxAmount(&termData))
				{
					/*8.True- Decline amount exceeding limit*/
					printf("Transaction Amount Exceeding Limit\n");
				}
				else
				{

					strcpy(transData.terminalData.transactionDate, termData.transactionDate);
					transData.terminalData.transAmount = termData.transAmount;
					
					recieveTransactionData(&transData);
				}


			}
			printf("\n.\n.\n.\n.");
		}
}

void appStart(void)
{
    ST_cardData_t cardData;
    ST_terminalData_t termData = { .maxTransAmount = 5000.0 };
    ST_transaction_t transData;

    Menu();
    int Option;
    scanf("%d", &Option);
    fflush(stdin);
    switch (Option)
    {
    case 0:
        ExitProject();
        break;
    case 1:
        system("cls");
        system("COLOR 02");
        printf("\n\t\t **** set terminal configuration  ****\n\n");
        float maxAmount = 5000.0;
        printf("Set Max Amount of Transactions\n");
        scanf("%f", &maxAmount);
        while (setMaxAmount(&termData, maxAmount))
        {
            printf("Wrong Input\n");
            printf("Set Max Amount of Transactions\n");
            scanf("%f", &maxAmount);
        }
        printf("\n<<<< %.2f Valid  max Transaction Amount to set >>> \n\n", termData.maxTransAmount);

        GoBackOrExit();
        break;
    case 2:
        system("cls");
        system("COLOR 06");
        /*1- Get card holder name*/
        while (getCardHolderName(&cardData))
            printf("Wrong Card Holder Name\n");

        /*2- Get card expiration date*/
        while (getCardExpiryData(&cardData))
            printf("Wrong Expiration Date\n");


        /*3- Get card PAN*/
        while (getCardPAN(&cardData))
            printf("Wrong Primary Account Number\n");

        /*4- Get All card data*/
        strcpy(transData.cardHolderData.cardHolderName, cardData.cardHolderName);
        strcpy(transData.cardHolderData.cardExpirationData, cardData.cardExpirationData);
        strcpy(transData.cardHolderData.primaryAcountNumber, cardData.primaryAcountNumber);
        /*5- Get transaction date*/
        printf("Enter transaction Date in format DD/MM/YYYY\n");
        gets(&termData.transactionDate);
        while (getTransactionDate(&termData))
        {
            printf("Wrong Date, Enter Again\n");
            gets(&termData.transactionDate);
        }

        /*6- is Card Expired?*/
        if (isCardExpired(&cardData, &termData))
        {
            /*7.True- Decline Expired Card*/
            printf("Card is Expired\n");
        }
        else
        {
            /*7.False- Get transaction amount*/
            printf("Enter transaction amount\n");
            scanf("%f", &termData.transAmount);
            while (getTransactionAmount(&termData))
            {
                printf("Invalid amount, enter agian\n");
                scanf("%f", &termData.transAmount);
            }
            /*8- is Exceeded amount?*/
            if (isBelowMaxAmount(&termData))
            {
                /*8.True- Decline amount exceeding limit*/
                printf("Transaction Amount Exceeding Limit\n");
            }
            else
            {

                strcpy(transData.terminalData.transactionDate, termData.transactionDate);
                transData.terminalData.transAmount = termData.transAmount;

                recieveTransactionData(&transData);
            }
        }
        GoBackOrExit();
        break;
    case 3:
        system("cls");
        system("COLOR F0");
        printf("\n\t\t **** case3  ****\n\n");
        GoBackOrExit();
        break;
    case 4:
        system("cls");
        system("COLOR 06");
        printf("\n\t\t **** case4  ****\n\n");
        GoBackOrExit();
        break;
    case 5:
        system("cls");
        system("COLOR 04");
        printf("\n\t\t **** case5  ****\n\n");
        GoBackOrExit();


        break;
    case 6:
    {
        system("cls");
        system("COLOR 06");
        printf("\n\t\t **** case6  ****\n\n");
        GoBackOrExit();
    }
    break;
    default:
        return 0;
        break;

    }

}
/*------------------------------------------------------------------------*/

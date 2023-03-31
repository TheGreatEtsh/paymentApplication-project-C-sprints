#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include "server.h"
#include "stddef.h"
#include "stdio.h"
#include "string.h"

ST_accountsDB_t accountsDB[DB_SIZE] = { {2000.0,	RUNNING, "1111000011110000"},
										{100000.0,	BLOCKED, "0000111100001111"},
										{100.0,		RUNNING, "1111222211112222"},
										{2500.0,	RUNNING, "2222111122221111"},
										{30000.0,	RUNNING, "2222333322223333"} };



ST_transaction_t transactionData[TD_SIZE] = { {0,0,0,0} };

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	uint8_t PAN[20] = {0};
	uint8_t compare = 0, reference = 0, functionReturn = 0;

	strcpy(PAN, cardData->primaryAcountNumber);
	
	for (; reference < DB_SIZE; reference++)
	{
		compare = strcmp(PAN, accountsDB[reference].primaryAccountNumber);
		if (!compare)
		{
			strcpy(accountRefrence->primaryAccountNumber, accountsDB[reference].primaryAccountNumber);
			accountRefrence->balance = accountsDB[reference].balance;
			accountRefrence->state = accountsDB[reference].state;
			
			break;
		}
		
	}
	
	if (compare)
	{
		functionReturn = ACCOUNT_NOT_FOUND;
		accountRefrence = NULL;
	}
	else
	{
		functionReturn = SERVER_OK;
		
	}

	return functionReturn;

}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	uint8_t accountState = 0, functionReturn = 0;
	accountState = accountRefrence->state;
	if (accountState == RUNNING)
	{
		functionReturn = SERVER_OK;
	}
	else if (accountState == BLOCKED)
	{
		functionReturn = BLOCKED_ACCOUNT;
	}
	else
	{
		/*DO NOTHING*/
	}
	return functionReturn;
}


EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	float transAmount = 0, balance = 0;
	uint8_t checkAmount = 0;
	
	transAmount = termData->transAmount;
	balance = accountRefrence->balance;
	
	if (balance >= transAmount)
	{
		checkAmount = SERVER_OK;
	}
	else
	{
		checkAmount = LOW_BALANCE;
	}

	return checkAmount;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	static uint16_t transactionIndex = 0;
	if (transactionIndex < TD_SIZE)
	{
		transactionData[transactionIndex].transactionSequenceNumber = transactionIndex+1;

		strcpy(transactionData[transactionIndex].terminalData.transactionDate, transData->terminalData.transactionDate);

		strcpy(transactionData[transactionIndex].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);

		strcpy(transactionData[transactionIndex].cardHolderData.primaryAcountNumber, transData->cardHolderData.primaryAcountNumber);

		transactionData[transactionIndex].transState = transData->transState;

		transactionData[transactionIndex].terminalData.transAmount = transData->terminalData.transAmount;

		transactionIndex++;
	}
	else
	{
		/*DO NOTHING*/
	}
	listSavedTransactions();
	return SERVER_OK;
}

void listSavedTransactions(void)
{
	uint8_t transactionIndex = 0;
	printf("TransactionSequence | TransactionDate | CardHolderName | \tPAN\t | TransactionAmount | TransactionState\n");
	while (transactionData[transactionIndex].transactionSequenceNumber)
	{
		printf("%d| %s | %s | %s | %0.1f | ", transactionData[transactionIndex].transactionSequenceNumber
											, transactionData[transactionIndex].terminalData.transactionDate
											, transactionData[transactionIndex].cardHolderData.cardHolderName
											, transactionData[transactionIndex].cardHolderData.primaryAcountNumber
											, transactionData[transactionIndex].terminalData.transAmount);
		
		switch (transactionData[transactionIndex].transState)
		{
		case APPROVED:						printf("APPROVED\n");						break;
		case DECLINED_INSUFFECIENT_FUND:	printf("DECLINED_INSUFFECIENT_FUN\n");		break;
		case DECLINED_STOLEN_CARD:			printf("DECLINED_STOLEN_CARD\n");			break;
		case FRAUD_CARD:					printf("FRAUD_CARD\n");						break;
		case INTERNAL_SERVER_ERROR:			printf("INTERNAL_SERVER_ERROR\n");			break;
		}
		transactionIndex++;
	}
}

EN_transState_t	recieveTransactionData(ST_transaction_t* transData)
{
	
	uint8_t  PAN[20];
	uint8_t accountValidty = 0, amountAvailability = 0, accountState = 0, functionReturn = 0;
	ST_accountsDB_t accReference;

	strcpy(PAN,	transData->cardHolderData.primaryAcountNumber);


	accountValidty = isValidAccount(&transData->cardHolderData, &accReference);
	

	accountState = isBlockedAccount(&accReference);

	amountAvailability = isAmountAvailable(&transData->terminalData, &accReference);	

	if (accountValidty == ACCOUNT_NOT_FOUND)
	{
		functionReturn = FRAUD_CARD;
	}
	else if (accountState == BLOCKED_ACCOUNT)
	{
		functionReturn = DECLINED_STOLEN_CARD;
	}
	else if (amountAvailability == LOW_BALANCE)
	{
		functionReturn = DECLINED_INSUFFECIENT_FUND;
	}
	else
	{
		functionReturn = APPROVED;
		for (uint8_t index = 0; index < DB_SIZE; index++)
		{	 
			if (!strcmp(PAN, accountsDB[index].primaryAccountNumber))
			{
				accountsDB[index].balance -= transData->terminalData.transAmount;
			}

		}
	}
	
	transData->transState = functionReturn;

	saveTransaction(transData);

	return functionReturn;
	
}

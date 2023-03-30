#include "server.h"
#include "stddef.h"
#include "stdio.h"
#include "string.h"

ST_accountsDB_t accountsDB[DB_SIZE] = { {2000.0,	RUNNING, "8989374615436851"},
										{100000.0,	BLOCKED, "5807007076043875"},
										{100.0,		RUNNING, "1233454406049895"},
										{2500.0,	RUNNING, "5773046589566969"},
										{30000.0,	RUNNING, "5402546398124536"} };


ST_transaction_t transactionData[TD_SIZE] = { {0,0,0,0} };

EN_transState_t	recieveTransactionData(ST_transaction_t* transData)
{
	uint32_t sequenceNumber = 0;
	uint8_t cardName[25], PAN[20], expiryDate[6];


	sequenceNumber = transData->transactionSequenceNumber;

	strcpy(expiryDate, transData->cardHolderData.cardExpirationData);
	
	strcpy(PAN, transData->cardHolderData.primaryAcountNumber);
	
	strcpy(cardName, transData->cardHolderData.cardHolderName);
	


}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	uint8_t PAN[20] = {0};
	uint8_t compare = 0, reference = 0, functionReturn = 0;

	accountRefrence = accountsDB;

	strcpy(PAN, cardData->primaryAcountNumber);
	
	for (; reference < DB_SIZE; reference++)
	{
		compare = strcmp(PAN, accountRefrence[reference].primaryAccountNumber);
		if (!compare)
		{
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
		accountRefrence = accountRefrence + reference;
	}

	return functionReturn;

}

EN_serverError_t	isBlockedAccount(ST_accountsDB_t* accountRefrence)
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
	
	if (balance > transAmount)
	{
		checkAmount = SERVER_OK;
	}
	else
	{
		checkAmount = LOW_BALANCE;
	}

	return checkAmount;
}

EN_serverError_t	saveTransaction(ST_transaction_t* transData)
{
	static uint8_t transactionIndex = 0;
	uint8_t i = 0;
	transactionData[transactionIndex].transactionSequenceNumber = transactionIndex+1;
	
	for (i = 0; i < 11; i++)
	{
		transactionData[transactionIndex].terminalData.transactionDate[i] = transData->terminalData.transactionDate[i];
	}
	
	for (i = 0; transData->cardHolderData.cardHolderName[i]; i++)
	{
		transactionData[transactionIndex].cardHolderData.cardHolderName[i] = transData->cardHolderData.cardHolderName[i];
	}
	transactionData[transactionIndex].cardHolderData.cardHolderName[i] = '\0';

	for (i = 0; transactionData[transactionIndex].cardHolderData.primaryAcountNumber[i]; i++)
	{
		transactionData[transactionIndex].cardHolderData.primaryAcountNumber[i] = transData->cardHolderData.primaryAcountNumber[i];
	}
	transactionData[transactionIndex].cardHolderData.primaryAcountNumber[i] = '\0';

	transactionData[transactionIndex].transState = transData->transState;
	transactionData[transactionIndex].terminalData.transAmount = transData->terminalData.transAmount;

	transactionIndex++;
}

void listSavedTransactions(void)
{
	uint8_t transactionIndex = 0;
	printf("TransactionSequence | TransactionDate | CardHolderName | \tPAN\t | TransactionAmount | TransactionState\n");
	while (transactionData[transactionIndex].transactionSequenceNumber)
	{
		printf("%d | %s | %s | %s | %d | ", transactionData[transactionIndex].transactionSequenceNumber
										, transactionData[transactionIndex].terminalData.transactionDate
										, transactionData[transactionIndex].cardHolderData.cardHolderName
										, transactionData[transactionIndex].cardHolderData.primaryAcountNumber
										, transactionData[transactionIndex].terminalData.transAmount);
		
		switch (transactionData[transactionIndex].transState)
		{
		case APPROVED:						printf("APPROVED\n");						break;
		case DECLINED_INSUFFECIENT_FUN:		printf("DECLINED_INSUFFECIENT_FUN\n");		break;
		case DECLINED_STOLEN_CARD:			printf("DECLINED_STOLEN_CARD\n");			break;
		case FRAUD_CARD:					printf("FRAUD_CARD\n");						break;
		case INTERNAL_SERVER_ERROR:			printf("INTERNAL_SERVER_ERROR\n");			break;
		}
	}
}

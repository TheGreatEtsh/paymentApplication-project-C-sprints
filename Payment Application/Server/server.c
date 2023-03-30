#include "server.h"
#include "stddef.h"

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
	
	for (uint8_t i = 0; i < 6; i++)
	{
		expiryDate[i] = transData->cardHolderData->cardExpirationDate[i];
	}
	for (uint8_t i = 0; i < 20; i++)
	{
		PAN[i] = transData->cardHolderData->primaryAccountNumber[i];
	}
	for (uint8_t i = 0; i < strlen(transData->cardHolderData->cardHolderName); i++)
	{
		expiryDate[i] = transData->cardHolderData->cardHolderName[i];
	}


}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	uint8_t PAN[20];
	uint8_t match = 0, reference = 0, functionReturn = 0;

	for ( reference = 0; reference < 20; reference++)
	{
		PAN[reference] = cardData->cardHolderData.primaryAccountNumber[reference];
	}

	reference = 0;
	
	for ( reference = 0; reference < DB_SIZE; reference++)
	{
		match = 0;
		for (uint8_t j = 0; PAN[j]; j++)
		{
			if (PAN[j] == accountRefrence[reference].primaryAccountNumber[j])
			{
				match++;
			}
			if (match == 16)
			{
				break;
			}
		}
		if (match == 16)
		{
			break;
		}
	}
	if (match < 16)
	{
		functionReturn = ACCOUNT_NOT_FOUND;
		accountRefrence = NULL;
	}
	else if (match == 16)
	{
		functionReturn = SERVER_OK;
		accountRefrence = accountRefrence + reference;
	}

	return functionReturn;

}

EN_serverError_t	isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	uint8_t accountState = 0, functionReturn;
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
	transactionData[transactionIndex].transactionSequenceNumber = transactionIndex;
	for (uint8_t i = 0; i < 11; i++)
	{
		transactionData[transactionIndex].terminalData.transactionDate[i] = transData->terminalData.transactionDate[i];
	}
	transactionData[transactionIndex].transState = transData->transState;
	transactionData[transactionIndex].terminalData.transAmount = transData->terminalData.transAmount;
	
	
	transactionIndex++;
}


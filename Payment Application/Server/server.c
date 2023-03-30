#include "server.h"

ST_accountsDB_t accountsDB[255] = { {2000.0,	RUNNING, "8989374615436851"},
									{100000.0,	BLOCKED, "5807007076043875"},
									{100.0,		RUNNING, "1233454406049895"},
									{2500.0,	RUNNING, "5773046589566969"},
									{30000.0,	RUNNING, "5402546398124536"} };


ST_transaction_t trandsactionData[255] = { {0,0,0,0} };

EN_transStat_t		recieveTransactionData(ST_transaction_t* transData)
{
	uint32_t sequenceNumber = 0;
	uint8_t cardName[25], PAN[20], expiryDate[6];
	

	sequenceNumber = transData->transactionSequenceNumber;
	for (uint8_t i = 0; i < 6; i++)
	{
		expiryDate[i] = transData->cardHolderData->cardExpirationDate[i];
	}

}

EN_serverError_t	isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
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

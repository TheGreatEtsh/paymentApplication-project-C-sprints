
#include "serverTest.h"
extern ST_accountsDB_t accountsDB[DB_SIZE];

void	isValidAccountTest(void)
{
	ST_cardData_t cardData;
	ST_accountsDB_t accReference;
	uint8_t accountValidty;

	strcpy(cardData.primaryAcountNumber, "9999888877776666");
	accountValidty = isValidAccount(&cardData, &accReference);

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : isValidAccount\n");
	printf("Test Case 1 :\n");
	printf("Input Data : %s\n",cardData.primaryAcountNumber);
	printf("Expected Result: %d\n", ACCOUNT_NOT_FOUND);
	printf("Acutal Result: %d\n.\n.\n.\n.\n", accountValidty);

	strcpy(cardData.primaryAcountNumber, accountsDB[0].primaryAccountNumber);
	accountValidty = isValidAccount(&cardData, &accReference);
	
	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : isValidAccount\n");
	printf("Test Case 2 :\n");
	printf("Input Data : %s\n",cardData.primaryAcountNumber);
	printf("Expected Result: %d\n", SERVER_OK);
	printf("Acutal Result: %d\n.\n.\n.\n.\n", accountValidty);
}

void	isBlockedAccountTest(void)
{
	uint8_t accountState = 0;
	ST_accountsDB_t accReference;
	
	accReference.state = BLOCKED;
	accountState = isBlockedAccount(&accReference);

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : isBlockedAccount\n");
	printf("Test Case 1 :\n");
	printf("Input Data : %d \n", BLOCKED);
	printf("Expected Result: %d\n", BLOCKED_ACCOUNT);
	printf("Acutal Result: %d\n.\n.\n.\n.\n", accountState);

	accReference.state = RUNNING;
	accountState = isBlockedAccount(&accReference);

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : isBlockedAccount\n");
	printf("Test Case 2 :\n");
	printf("Input Data : %d \n", RUNNING);
	printf("Expected Result: %d\n", SERVER_OK);
	printf("Acutal Result: %d\n.\n.\n.\n.\n", accountState);

}


void	isAmountAvailableTest(void)
{
	uint8_t amountAvailabilty = 0;
	ST_terminalData_t termData;
	ST_accountsDB_t accReference;

	termData.transAmount = 20000;
	accReference.balance = 10000;
	amountAvailabilty = isAmountAvailable(&termData, &accReference);

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : isAmountAvailable\n");
	printf("Test Case 1 :\n");
	printf("Input Data : transAmount = 20000, balance = 10000 \n");
	printf("Expected Result: %d\n", LOW_BALANCE);
	printf("Acutal Result: %d\n.\n.\n.\n.\n", amountAvailabilty);

	termData.transAmount = 10000;
	accReference.balance = 20000;
	amountAvailabilty = isAmountAvailable(&termData, &accReference);

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : isAmountAvailable\n");
	printf("Test Case 2 :\n");
	printf("Input Data : transAmount = 10000, balance = 20000 \n");
	printf("Expected Result: %d\n", SERVER_OK);
	printf("Acutal Result: %d\n.\n.\n.\n.\n", amountAvailabilty);




}

void	saveTransactionTest(void)
{
	ST_transaction_t transData;


	strcpy(transData.terminalData.transactionDate, "10/04/2023");
	strcpy(transData.cardHolderData.cardHolderName, "Ahmed Mohamed Hesham");
	strcpy(transData.cardHolderData.primaryAcountNumber, "9999888877776666");
	transData.transState = APPROVED;
	transData.terminalData.transAmount = 100000;

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : saveTransactionTest\n");
	printf("Test Case 1 :\n");
	printf("Input Data : transaction Date, card holder name, PAN, transtate, transAmount \n");
	printf("Expected Result: transactions Details  \n");
	printf("Acutal Result: \n");
	saveTransaction(&transData);
	printf(".\n.\n.\n.\n");




	strcpy(transData.terminalData.transactionDate, "10/04/2023");
	strcpy(transData.cardHolderData.cardHolderName, "Ahmed Mohamed Hesham");
	strcpy(transData.cardHolderData.primaryAcountNumber, "9999888877776666");
	transData.transState = DECLINED_INSUFFECIENT_FUND;
	transData.terminalData.transAmount = 5000;

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : saveTransactionTest\n");
	printf("Test Case 2 :\n");
	printf("Input Data : transaction Date, card holder name, PAN, transtate, transAmount \n");
	printf("Expected Result: transactions Details + history  \n");
	printf("Acutal Result: \n");
	saveTransaction(&transData);
	printf(".\n.\n.\n.\n");

	strcpy(transData.terminalData.transactionDate, "10/04/2023");
	strcpy(transData.cardHolderData.cardHolderName, "Ahmed Mohamed Hesham");
	strcpy(transData.cardHolderData.primaryAcountNumber, "9999888877776666");
	transData.transState = FRAUD_CARD;
	transData.terminalData.transAmount = 100000;

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : saveTransactionTest\n");
	printf("Test Case 3 :\n");
	printf("Input Data : transaction Date, card holder name, PAN, transtate, transAmount \n");
	printf("Expected Result: transactions Details + history  \n");
	printf("Acutal Result: \n");
	saveTransaction(&transData);
	printf(".\n.\n.\n.\n");

	strcpy(transData.terminalData.transactionDate, "10/04/2023");
	strcpy(transData.cardHolderData.cardHolderName, "Ahmed Mohamed Hesham");
	strcpy(transData.cardHolderData.primaryAcountNumber, "9999888877776666");
	transData.transState = DECLINED_STOLEN_CARD;
	transData.terminalData.transAmount = 200;

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : saveTransactionTest\n");
	printf("Test Case 4 :\n");
	printf("Input Data : transaction Date, card holder name, PAN, transtate, transAmount \n");
	printf("Expected Result: transactions Details + history  \n");
	printf("Acutal Result: \n");
	saveTransaction(&transData);
	printf(".\n.\n.\n.\n");
}

void	listSavedTransactionsTest(void);
void	recieveTransactionDataTest(void);
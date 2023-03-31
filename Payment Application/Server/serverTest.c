
#include "serverTest.h"
extern ST_accountsDB_t accountsDB[DB_SIZE];
extern ST_transaction_t transactionData[TD_SIZE];

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

void	listSavedTransactionsTest(void)
{
	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : listSavedTransactionsTest\n");
	printf("Test Case 1 :\n");
	printf("Input Data : no transactions history \n");
	printf("Expected Result: transactions details without history of transactions\n");
	printf("Acutal Result: \n");
	listSavedTransactions();
	printf(".\n.\n.\n.\n");

	transactionData[0].transactionSequenceNumber = 1;
	strcpy(transactionData[0].terminalData.transactionDate, "10/04/2023");
	strcpy(transactionData[0].cardHolderData.cardHolderName, "Ahmed Mohamed Hesham");
	strcpy(transactionData[0].cardHolderData.primaryAcountNumber, "9999888877776666");
	transactionData[0].transState = DECLINED_STOLEN_CARD;
	transactionData[0].terminalData.transAmount = 200;

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : listSavedTransactionsTest\n");
	printf("Test Case 2 :\n");
	printf("Input Data : adding one transaction \n");
	printf("Expected Result: transactions details with history of one transaction\n");
	printf("Acutal Result: \n");
	listSavedTransactions();
	printf(".\n.\n.\n.\n");

	transactionData[1].transactionSequenceNumber = 2;
	strcpy(transactionData[1].terminalData.transactionDate, "10/04/2023");
	strcpy(transactionData[1].cardHolderData.cardHolderName, "Ahmed Mohamed Hesham");
	strcpy(transactionData[1].cardHolderData.primaryAcountNumber, "9999888877776666");
	transactionData[1].transState = DECLINED_STOLEN_CARD;
	transactionData[1].terminalData.transAmount = 200;

	transactionData[2].transactionSequenceNumber = 3;
	strcpy(transactionData[2].terminalData.transactionDate, "10/04/2023");
	strcpy(transactionData[2].cardHolderData.cardHolderName, "Ahmed Mohamed Hesham");
	strcpy(transactionData[2].cardHolderData.primaryAcountNumber, "9999888877776666");
	transactionData[2].transState = DECLINED_STOLEN_CARD;
	transactionData[2].terminalData.transAmount = 200;
   
	transactionData[3].transactionSequenceNumber = 4;
	strcpy(transactionData[3].terminalData.transactionDate, "10/04/2023");
	strcpy(transactionData[3].cardHolderData.cardHolderName, "Ahmed Mohamed Hesham");
	strcpy(transactionData[3].cardHolderData.primaryAcountNumber, "9999888877776666");
	transactionData[3].transState = DECLINED_STOLEN_CARD;
	transactionData[3].terminalData.transAmount = 200;

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : listSavedTransactionsTest\n");
	printf("Test Case 3 :\n");
	printf("Input Data : adding three more transaction \n");
	printf("Expected Result: transactions details with history of four transaction\n");
	printf("Acutal Result: \n");
	listSavedTransactions();
	printf(".\n.\n.\n.\n");

}
void	recieveTransactionDataTest(void)
{
	ST_transaction_t transData;
	uint8_t recieveReturn = 0;


	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : recieveTransactionTest\n");
	printf("Test Case 1 :\n");
	printf("Input Data : transaction Date, card holder name, wrong PAN, transAmount \n");
	printf("Expected Result: transactions Details + history + FRAUD_CARD  \n");
	printf("Acutal Result: \n");
	strcpy(transData.terminalData.transactionDate, "10/04/2023");
	strcpy(transData.cardHolderData.cardHolderName, "Ahmed Mohamed Hesham");
	strcpy(transData.cardHolderData.primaryAcountNumber, "9999888877776666");
	transData.terminalData.transAmount = 1000;
	recieveReturn = recieveTransactionData(&transData);
	printf(".\n.\n.\n.\n");

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : recieveTransactionTest\n");
	printf("Test Case 2 :\n");
	printf("Input Data : true PAN + last inputs + updates after calling the function\n");
	printf("Expected Result: transactions Details + history + Account balance updated + APPROVED  \n");
	printf("Acutal Result: \n");
	strcpy(transData.cardHolderData.primaryAcountNumber, accountsDB->primaryAccountNumber);
	recieveReturn = recieveTransactionData(&transData);
	printf(".\n.\n.\n.\n");

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : recieveTransactionTest\n");
	printf("Test Case 3 :\n");
	printf("Input Data : same last inputs + updates after calling the function\n");
	printf("Expected Result: transactions Details + history + Account balance updated + APPROVED  \n");
	printf("Acutal Result: \n");
	recieveReturn = recieveTransactionData(&transData);
	printf(".\n.\n.\n.\n");

	printf("Tester Name: Ahmed Mohamed Hesham\n");
	printf("Function Name : recieveTransactionTest\n");
	printf("Test Case 4 :\n");
	printf("Input Data : same last inputs + updates after calling the function\n");
	printf("Expected Result: transactions Details + history + Account balance updated + DECLINED INSUFFICENT FUND \n");
	printf("Acutal Result: \n");
	recieveReturn = recieveTransactionData(&transData);
	printf(".\n.\n.\n.\n");

}
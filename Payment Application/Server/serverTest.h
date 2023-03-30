#ifndef SERVERTEST_H
#define SERVERTEST_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS


#include "server.h"
#include <string.h>

void	recieveTransactionDataTest(void);
void	isValidAccountTest(void);
void	isBlockedAccountTest(void);
void	isAmountAvailableTest(void);
void	saveTransactionTest(void);
void	listSavedTransactionsTest(void);

#endif // !SERVERTEST_H

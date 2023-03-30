#include "string.h"
#include "stdtyps.h"
#include "terminal.h"
//#include "terminal_test.h"
ST_terminalData_t  test_terminal =
{
    .transAmount=1200.0,
    . maxTransAmount=5000.0,
    .transactionDate="25/05/2022"

};
ST_cardData_t test_card ;
void getTransactionDateTest(void)
{

    printf ("Enter Transaction Date DD/MM/YYYY  :  ") ;
    scanf ("%s",test_terminal.transactionDate);
    // printf(" \ndate you have entered %s\n",test_terminal.transactionDate);

    if  (getTransactionDate(&test_terminal)==WRONG_DATE)
    {
        printf ("\n<<<<Wrong format for Transaction Date>>>>\n\n") ;

    }
    else
    {
        printf ("\n<<<<Right Format for Transaction Date >>>> \n\n") ;
    }

}
/////////////////////////////////////////////////////////////////////////////
void isCardExpriedTest(void)
{
    printf ("Enter Expiration Date MM/YY  :  ") ;
    scanf ("%s",test_card.cardExpirationDate);

    if  (isCardExpired(&test_card,&test_terminal)==EXPIRED_CARD)
    {
        printf ("\n<<<<Not Valid Transaction >>>>\n") ;
    }
    else
    {
        printf ("\n<<<<Valid Transaction >>> \n\n") ;
    }
}
/////////////////////////////////////////////////////////////////////////////
void getTransactionAmountTest(void)
{
    printf ("Enter Transaction Amount:  ") ;
    scanf ("%f",&test_terminal.transAmount);

    if  (getTransactionAmount(&test_terminal)==INVALID_AMOUNT)
    {
        printf ("\n<<<<Not Valid Transaction Amount INVALID AMOUNT >>>>\n") ;
    }
    else
    {
        printf ("\n<<<<Valid Transaction Amount >>> \n\n") ;
    }
}
/////////////////////////////////////////////////////////////////////////////
void isBelowMaxAmountTest(void)
{
    printf (" Received Transaction Amount:  ") ;
    printf ("%f\n",test_terminal.transAmount);

    if  (isBelowMaxAmount(&test_terminal)== EXCEED_MAX_AMOUNT )
    {
        printf ("\n<<<<Not Valid Transaction Amount EXCEED MAX AMOUNT  >>>>\n") ;
    }
    else
    {
        printf ("\n<<<<Valid Transaction Amount >>> \n\n") ;
    }
}

/////////////////////////////////////////////////////////////////////////////
void setMaxAmountTest(void)
{
    float max_amount ;
    printf ("Enter max Transaction Amount:  ") ;
    scanf ("%f",&max_amount);
    if( setMaxAmount(&test_terminal,max_amount) == INVALID_AMOUNT )
    {
        printf ("\n<<<<Not Valid Transaction Amount INVALID AMOUNT >>>>\n") ;
    }
    else
    {
        printf ("\n<<<<Valid  max Transaction Amount to set >>> \n\n") ;
    }
}

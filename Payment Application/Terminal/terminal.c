#include "string.h"
#include "stdtyps.h"
#include "terminal.h"
//#include "terminal_test.h"
int32_t Stringlen_H (uint8_t*str)
{
    int32_t i;
    for(i=0; str[i]; i++);

    return i;
}
int32_t stringToInt(uint8_t*str,int32_t*pnum)
{
    int i=0,n=0,flag=0;
    if(str[0]=='-')
    {
        flag=1;
        i=1;
    }
    for(; str[i]; i++)
    {
        if(str[i]>='0'&&str[i]<='9')
            n=n*10+(str[i]-'0');
        else
            return 0;
    }
    if(flag==1)
    {
        n=n*(-1);
    }
    *pnum=n;
    return 1;
}
/////////////////////////////////////////////////////////////////////
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) //dd/mm/yyyy
{
    uint8_t strdd [3],strmm[3],stryyyy[5];
    int32_t dd,mm,yyyy;
    EN_terminalError_t status ;
    // printf("%s\n",termData->transactionDate);
    if ( Stringlen_H (termData->transactionDate) > 10)
    {
        status= WRONG_DATE;

    }
    else if ( Stringlen_H (termData->transactionDate) < 10)
    {
        status= WRONG_DATE;


    }
    else
    {
        if (termData->transactionDate[2]=='/'&&termData->transactionDate[5]=='/')
        {
            strdd[0]= termData->transactionDate[0];
            strdd[1]= termData->transactionDate[1];
            strdd[2]= 0;
            // stringToInt(strdd,&dd);
            dd=atoi(strdd);
            strmm[0]= termData->transactionDate[3];
            strmm[1]= termData->transactionDate[4];
            strmm[2]= 0;
            // stringToInt(strmm,&mm);
            mm=atoi(strmm);
            stryyyy[0]= termData->transactionDate[6];
            stryyyy[1]= termData->transactionDate[7];
            stryyyy[2]= termData->transactionDate[8];
            stryyyy[3]= termData->transactionDate[9];
            stryyyy[4]= 0;
            //stringToInt(stryyyy,&yyyy);
            yyyy=atoi(stryyyy);
            // printf ("\n %d %d %d \n",dd,mm,yyyy);

            if (dd>31||dd<=0||mm>12||mm<0||yyyy<2020||yyyy>2025)
            {
                status= WRONG_DATE;
            }
            else
            {
                status= TERMINAL_OK;

            }
        }
        else
        {
            status= WRONG_DATE;
        }
    }
    return status;
}
/////////////////////////////////////////////////////////////////////
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    uint8_t strmm_t[3],stryy_t[3],strmm_c[3],stryy_c[3];
    int32_t mm_t,yy_t,mm_c,yy_c;
    EN_terminalError_t status ;
  //  printf(" \nReceived Transaction Date  %s\n",termData->transactionDate);
    strmm_t[0]=termData->transactionDate[3]; //m
    strmm_t[1]=termData->transactionDate[4]; //mm
    stryy_t[2]=0;
    mm_t=atoi(strmm_t);
    stryy_t[0]=termData->transactionDate[8]; //y
    stryy_t[1]=termData->transactionDate[9]; //yy
    stryy_t[2]=0;
    yy_t=atoi(stryy_t);
    // printf ("\n %d %d  \n",mm_t,yy_t);
    /////////////////////////////////////////////////////////////////////////////
    //printf(" \nReceivedExpiration date  %s\n",cardData->cardExpirationData);
    /////////////////////////////////////////////////////////////////////////////
    strmm_c[0]=cardData->cardExpirationData[0]; //m
    strmm_c[1]=cardData->cardExpirationData[1]; //mm
    stryy_c[2]=0;
    mm_c=atoi(strmm_c);
    stryy_c[0]=cardData->cardExpirationData[3]; //y
    stryy_c[1]=cardData->cardExpirationData[4]; //yy
    stryy_c[2]=0;
    yy_c=atoi(stryy_c);
    // printf ("\n %d %d  \n",mm_c,yy_c);
    if (yy_c>yy_t )
    {
        status= TERMINAL_OK;
        // printf("HERE0\n");
    }
    else if (yy_c==yy_t)
    {
        if (mm_c>= mm_t)
        {
            status= TERMINAL_OK;
            // printf("HERE1\n");
        }
        else
        {
            status= EXPIRED_CARD;
            // printf("HERE2\n");
        }
    }
    else
    {
        status= EXPIRED_CARD;
        // printf("HERE3\n");
    }
    return status;
}
//*********************************************************************//
/*EN_terminalError_t isCardExpired2(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    uint8_t transactiondate[6];
    int32_t flag;
    EN_terminalError_t status ;
    printf(" \nReceived Transaction Date  %s\n",termData->transactionDate);
    transactiondate[0]=termData->transactionDate[3]; //m
    transactiondate[1]=termData->transactionDate[4]; //mm
    transactiondate[2]=termData->transactionDate[5]; //mm/
    transactiondate[3]=termData->transactionDate[8]; //mm/y
    transactiondate[4]=termData->transactionDate[9]; //mm/yy
    transactiondate[5]=0;                            //mm/yy\n
    printf(" \nTransaction date after rearrange  %s\n",transactiondate);
    printf(" \nReceivedExpiration date  %s\n",cardData->cardExpirationDate);
    flag=strcmp(transactiondate,cardData->cardExpirationDate) ;
    if (flag ==0 )
    {
        status= TERMINAL_OK;
    }
    else
    {
        status= WRONG_DATE;
    }
    return status;
}*/
/////////////////////////////////////////////////////////////////////
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t status ;
    if (termData->transAmount<=0)
    {
        status=INVALID_AMOUNT;
    }
    else
    {
        status= TERMINAL_OK;
    }
    return status;
}
/////////////////////////////////////////////////////////////////////
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t status ;
   // printf ("\nfrom fun : %f",termData->transAmount );
    if (termData->transAmount > termData->maxTransAmount)
    {
        status= EXCEED_MAX_AMOUNT;

    }
    else
    {
        status= TERMINAL_OK;

    }
    return status;
}
/////////////////////////////////////////////////////////////////////
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    EN_terminalError_t status ;
    if (maxAmount<=0)
    {
        status=INVALID_AMOUNT;
    }
    else
    {
        termData->maxTransAmount=maxAmount ;
        status= TERMINAL_OK;
    }
    return status;
}

/////////////////////////////////////////////////////////////////////


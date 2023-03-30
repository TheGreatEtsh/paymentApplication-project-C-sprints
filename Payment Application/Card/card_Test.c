#include"card_Test.h"




void getCardHolderNameTest(void)
{
    ST_cardData_t cardData;
    EN_card_Error_t result;
printf("Name:Momen hassan bayoumy\n");
printf("Function:getCardHolderName\n");
    // Test case 1: Valid cardholder name
    printf("Test case 1: Valid cardholder name\n");
printf("Enter card holder name: momen hassan bayoumy\n");
cardData.cardHolderName[strcspn(cardData.cardHolderName, "\n")] = '\0';
    result = getCardHolderName(&cardData);

    if (result == CARD_OK) {
        printf("Cardholder name: %s\n", cardData.cardHolderName);
    } else {
        printf("Wrong Card Name \n" );
    }
printf("/////////////////////////////////\n");
             ////////////////////////////////////

printf("Name:Momen hassan bayoumy\n");
printf("Function:getCardHolderName\n");
    // Test case 2: inValid cardholder name
    printf("Test case 2: short cardholder name\n");
printf("Enter card holder name: momen \n");
cardData.cardHolderName[strcspn(cardData.cardHolderName, "\n")] = '\0';
    result = getCardHolderName(&cardData);

    if (result == CARD_OK) {
        printf("Cardholder name: %s\n", cardData.cardHolderName);
    } else {
        printf("Wrong Card Name \n" );
    }
    printf("/////////////////////////////////\n");
                   ///////////////////////////////

printf("Name:Momen hassan bayoumy\n");
printf("Function:getCardHolderName\n");
    // Test case 3: Empty cardholder name
    printf("Test case 3: Empty cardholder name\n");
    printf("Enter card holder name:(empty) \n");
cardData.cardHolderName[strcspn(cardData.cardHolderName, "\n")] = '\0';
    result = getCardHolderName(&cardData);

    if (result == CARD_OK) {
        printf("Cardholder name: %s\n", cardData.cardHolderName);
    } else {

        printf("Wrong Card Name \n" );
    }
    printf("/////////////////////////////////\n");

printf("Name:Momen hassan bayoumy\n");
printf("Function:getCardHolderName\n");
    // Test case 3: Empty cardholder name
    printf("Test case 4: long cardholder name\n");
    printf("Enter card holder name: momen hassan bayoumy ali ghareb  \n");
cardData.cardHolderName[strcspn(cardData.cardHolderName, "\n")] = '\0';
    result = getCardHolderName(&cardData);

    if (result == CARD_OK) {
        printf("Cardholder name: %s\n", cardData.cardHolderName);
    } else {
        printf("Wrong Card Name \n" );
    }
}






void getCardExpiryDataTest(void)
{

        ST_cardData_t cardData;
    EN_card_Error_t result;
// Test case 1: Valid expiry date
printf("Name:Momen hassan bayoumy\n");
printf("Function:getCardExpiryData\n");

printf("Test case 1: Valid expiry date\n");
printf("Enter card expiry date (MM/YY): 12/23\n");
result = getCardExpiryData(&cardData);
if (result == CARD_OK) {
    printf("Card expiration date: %s\n", cardData.cardExpirationData);
} else {
    printf("Invalid expiry date\n");
}
printf("/////////////////////////////////\n");

// Test case : Invalid expiry date format

printf("Name:Momen hassan bayoumy\n");
printf("Function:getCardExpiryData\n");
printf("Test case 2: Invalid expiry date format\n");
printf("Enter card expiry date (MM/YY): 1223\n");
result = getCardExpiryData(&cardData);
if (result == WRONG_EXP_DATE) {
    printf("Invalid expiry date\n");
} else {
    printf("Unexpected result\n");
}
printf("/////////////////////////////////\n");
// Test case 3: Invalid month

printf("Name:Momen hassan bayoumy\n");
printf("Function:getCardExpiryData\n");
printf("Test case 3: Invalid month\n");
printf("Enter card expiry date (MM/YY): 00/23\n");
result = getCardExpiryData(&cardData);
if (result == WRONG_EXP_DATE) {
    printf("Invalid expiry date\n");
} else {
    printf("Unexpected result\n");
}
printf("/////////////////////////////////\n");
// Test case 4: Invalid year

printf("Name:Momen hassan bayoumy\n");
printf("Function:getCardExpiryData\n");
printf("Test case 4: Invalid year\n");
printf("Enter card expiry date (MM/YY): 12/100\n");
result = getCardExpiryData(&cardData);
if (result == WRONG_EXP_DATE) {
    printf("Invalid expiry date\n");
} else {
    printf("Unexpected result\n");
}





}
void getCardPANtest(void)
{
    ST_cardData_t cardData;
EN_card_Error_t result;

// Test case 1: Valid PAN

printf("Name:Momen hassan bayoumy\n");
printf("Function:getCardPAN\n");
printf("Test case 1: Valid PAN\n");
printf("Enter primary account number: 1234567890123456\n");
result = getCardPAN(&cardData);
if (result == CARD_OK) {
    printf("Primary account number: %s\n", cardData.primaryAcountNumber);
} else {
    printf("Invalid PAN\n");
}
printf("/////////////////////////////////\n");
// Test case 2: Invalid PAN - contains non-digits
printf("Name:Momen hassan bayoumy\n");
printf("Function:getCardPAN\n");
printf("Test case 2: Invalid PAN - contains non-digits\n");
printf("Enter primary account number: 1234-5678-9012-3456\n");
result = getCardPAN(&cardData);
if (result == CARD_OK) {
    printf("Primary account number: %s\n", cardData.primaryAcountNumber);
} else {
    printf("Invalid PAN\n");
}
printf("/////////////////////////////////\n");
// Test case 3: Invalid PAN - too short
printf("Name:Momen hassan bayoumy\n");
printf("Function:getCardPAN\n");
printf("Test case 3: Invalid PAN - too short\n");
printf("Enter primary account number: 123456789012345\n");
result = getCardPAN(&cardData);
if (result == CARD_OK) {
    printf("Primary account number: %s\n", cardData.primaryAcountNumber);
} else {
    printf("Invalid PAN\n");
}
printf("/////////////////////////////////\n");
// Test case 4: Invalid PAN - too long
printf("Name:Momen hassan bayoumy\n");
printf("Function:getCardPAN\n");
printf("Test case 4: Invalid PAN - too long\n");
printf("Enter primary account number: 1234567890123456789012\n");
result = getCardPAN(&cardData);
if (result == CARD_OK) {
    printf("Primary account number: %s\n", cardData.primaryAcountNumber);
} else {
    printf("Invalid PAN\n");
}
}


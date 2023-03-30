#include"card.h"

EN_card_Error_t getCardHolderName(ST_cardData_t * cardData)
{    // declare a char array to store the input name
    char name[25];
        // prompt the user to enter the card holder's name
    printf("Please enter card holder name: ");
        // read the input using fgets() function
    fgets(name, 25, stdin);
        // remove the newline character from the input
    name[strcspn(name, "\n")] = '\0';
    // check if the input is null or its length is less than 20 or more than 24 characters
    if (name[0] == '\0' || strlen(name) < 20 || strlen(name) > 24) {
        // if the input is invalid, return the WRONG_NAME error
        return WRONG_NAME;
    } else {
        // otherwise, clear the cardHolderName field of the cardData struct using memset() function
        memset(cardData->cardHolderName, 0, sizeof(cardData->cardHolderName));
                // copy the input string to cardHolderName field using strncpy() function
        strncpy(cardData->cardHolderName, name, sizeof(cardData->cardHolderName) - 1);
        // return the CARD_OK error
        return CARD_OK;
    }
}
EN_card_Error_t getCardExpiryData(ST_cardData_t * cardData)
{
    // declare a char array to store the input expiry date
    char expiryData[6];
    char expiryDataCopy[6];
    // prompt the user to enter the card expiry date
    printf("Please enter card expiry date (MM/YY): ");
    // read the input using fgets() function
    gets(expiryData);
    strcpy(expiryDataCopy,expiryData);
    // remove the newline character from the input
    expiryData[strcspn(expiryData, "\n")] = '\0'; // remove the newline character from input
    // check if the input is null or its length is not equal to 5 characters
    if (expiryData[0] == '\0' || strlen(expiryData) != 5) {
        // if the input is invalid, return the WRONG_EXP_DATE error
        return WRONG_EXP_DATE;
    }
    // check if the third character of the input is '/'
    if (expiryData[2] != '/') {
        // if not, return the WRONG_EXP_DATE error

        return WRONG_EXP_DATE;
    }
    // extract the month and year from the input string using strtok() function
    char * monthStr = strtok(expiryData, "/");
    char * yearStr = strtok(NULL, "/");
    // check if either the month or year strings are null
    if (monthStr == NULL || yearStr == NULL) {
        // if so, return the WRONG_EXP_DATE error
        return WRONG_EXP_DATE;
    }
    int month = atoi(monthStr);
    int year = atoi(yearStr);
    if (month < 1 || month > 12 || year < 0 || year > 99) {
        return WRONG_EXP_DATE;
    }
    // otherwise, clear the cardExpirationData field of the cardData struct using memset() function
    memset(cardData->cardExpirationData, 0, sizeof(cardData->cardExpirationData));
    // copy the input string to cardExpirationData using strncpy() function
    strncpy(cardData->cardExpirationData, expiryDataCopy, sizeof(cardData->cardExpirationData) - 1);
    // return the CARD_OK error
    return CARD_OK;
}
EN_card_Error_t getCardPAN(ST_cardData_t * cardData)
{
    // Declares a character array of size 21
    char primaryAcountNumber[21];
    // Prints a message to the console for the user to enter the primary account number
    printf("Please enter primary account number: ");
    // Takes input from the console and stores it in the primaryAcountNumber array
    fgets(primaryAcountNumber, 21, stdin);
    // Removes the newline character from the input string
    primaryAcountNumber[strcspn(primaryAcountNumber, "\n")] = '\0';
    // Checks if the input string is empty or has an invalid length
    if (primaryAcountNumber[0] == '\0' || strlen(primaryAcountNumber) < 16 || strlen(primaryAcountNumber) > 19) {
        // Returns an error code if the input string is invalid
        return WRONG_PAN;
    }
// Loops through each character in the input string
    for (int i = 0; i < strlen(primaryAcountNumber); i++) {
            // Checks if the character is not a digit
        if (primaryAcountNumber[i] < '0' || primaryAcountNumber[i] > '9') {
            // Returns an error code if the input string contains non-digits
            return WRONG_PAN;
        }
    }
// Clears the primary account number field in the struct
    memset(cardData->primaryAcountNumber, 0, sizeof(cardData->primaryAcountNumber));
    // Copies the input string to the primary account number field in the struct, truncating to fit if necessary
    strncpy(cardData->primaryAcountNumber, primaryAcountNumber, sizeof(cardData->primaryAcountNumber) - 1);

// Returns a success code if everything was successful
    return CARD_OK;
}

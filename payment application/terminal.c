#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    uint8_t Date[MAX_DATE_LENGTH]={};
    printf("Enter Transaction Date: ");
    gets(Date);
    fflush(stdin);

    if(termData == NULL){ //Ensure the termData pointer is not NULL,
        return WRONG_DATE;
    }
    /* Ensure the length of the date is exactly 10 characters (DD/MM/YYYY),
     and the date format has slashes in the correct positions. Also check if the month part is valid (01-12).*/
    if(strlen(Date)!=10 || Date[2]!='/' || Date[5]!='/'  || (Date[3]=='1' && Date[4]>'2')){
        return WRONG_DATE;
    }
    else{
             // Copy the valid transaction date to the termData structure
         for(uint32_t i=0;i<strlen(Date);++i){
             termData->transactionDate[i]=Date[i];
         }
         termData->transactionDate[strlen(Date)]='\0'; // Null-terminate
         return TERMINAL_OK; // Return success if the date is valid
    }
}
void getTransactionDateTest(void)
{
    ST_terminalData_t TermDate;
    EN_terminalError_t Test;
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : getTransactionDate \n");
    printf("===========================================\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data:");
    Test = getTransactionDate(&TermDate);
     printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result: %s\n", Test == WRONG_DATE ? "WRONG_DATE" : "TERMINAL_OK");
    printf("===========================================\n");
    printf("Test Case 2:22*10*2005\n");
    printf("Input Data:");
    Test=getTransactionDate(&TermDate);
     printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_DATE? "WRONG_DATE":"TERMINAL_OK");
    printf("===========================================\n");
    printf("Test Case 3:22/8/22 \n");
    printf("Input Data:");
    Test=getTransactionDate(&TermDate);
     printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_DATE? "WRONG_DATE":"TERMINAL_OK");
     printf("===========================================\n");
    printf("Test Case 4:22/08/200444\n");
    printf("Input Data:");
    Test=getTransactionDate(&TermDate);
    printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"WRONG_DATE");
    printf("===========================================\n");
    printf("Test Case 5:22/08/2004\n");
    printf("Input Data:");
    Test=getTransactionDate(&TermDate);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"WRONG_DATE");
}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
     // Check if the pointers are NULL to avoid segmentation faults
    if(cardData == NULL || termData == NULL){
        return EXPIRED_CARD;
    }
     // Compare expiration year with transaction year
    if(cardData->cardExpirationDate[3]<termData->transactionDate[8]
    ||((cardData->cardExpirationDate[3]==termData->transactionDate[8])
    &&(cardData->cardExpirationDate[4]<termData->transactionDate[9]))){
        return EXPIRED_CARD; // Return an error if the expiration year is before the transaction year
     }
      // If the years are the same, compare expiration month with transaction month
            if((cardData->cardExpirationDate[3]==termData->transactionDate[8])
            &&(cardData->cardExpirationDate[4]<termData->transactionDate[9])){
                 // Compare the months
                if(cardData->cardExpirationDate[0]<termData->transactionDate[3]
                ||((cardData->cardExpirationDate[0]==termData->transactionDate[3])
                 &&(cardData->cardExpirationDate[1]<termData->transactionDate[4]))){
                         return EXPIRED_CARD; // Return an error if the expiration month is before the transaction month
            }
            else{
                return TERMINAL_OK;
            }
        }
        else{
            return TERMINAL_OK; // Return success if the card is not expired
        }
}
void isCardExpriedTest(void)
{
    ST_cardData_t CardDate;
    ST_terminalData_t TermDate;
    EN_terminalError_t Test;
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : isCardExpired \n");
    printf("===========================================\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data:");
    getCardExpiryDate(NULL);
    getTransactionDate(NULL);
    Test = isCardExpired(NULL,NULL);
    printf("Expected Result: EXPIRED_CARD\n");
    printf("Actual Result: %s\n", Test == EXPIRED_CARD ? "EXPIRED_CARD" : "TERMINAL_OK");
    printf("===========================================\n");
        printf("Test Case 2:Before\n");
    printf("Input Data:");
    getCardExpiryDate(&CardDate);
    getTransactionDate(&TermDate);
    Test = isCardExpired(&CardDate,&TermDate);
    printf("Expected Result: EXPIRED_CARD\n");
    printf("Actual Result: %s\n", Test == EXPIRED_CARD ? "EXPIRED_CARD" : "TERMINAL_OK");
    printf("===========================================\n");
        printf("Test Case 3:After\n");
    printf("Input Data:");
    getCardExpiryDate(&CardDate);
    getTransactionDate(&TermDate);
    Test = isCardExpired(&CardDate,&TermDate);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", Test == EXPIRED_CARD ? "EXPIRED_CARD" : "TERMINAL_OK");
    printf("===========================================\n");
        printf("Test Case 4:Equal\n");
    printf("Input Data:");
    getCardExpiryDate(&CardDate);
    getTransactionDate(&TermDate);
    Test = isCardExpired(&CardDate,&TermDate);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", Test == EXPIRED_CARD ? "EXPIRED_CARD" : "TERMINAL_OK");

}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    if(termData == NULL){  //Ensure the termData pointer is not NULL,
        return INVALID_AMOUNT;
    }

    float32 Amount=0;
    printf("Enter Transction Amount: ");
    scanf("%f",&Amount);
    // Ensure the amount is greater than 0
    if( Amount <= 0 ){
        return INVALID_AMOUNT;
    }
    else{
        termData->transAmount=Amount; // Store the valid amount in termData
        return TERMINAL_OK; // Return success if the amount is valid
    }
}
void getTransactionAmountTest(void)
{
    ST_terminalData_t TermDate;
    EN_terminalError_t Test;
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : getTransactionAmount \n");
    printf("===========================================\n");
    printf("Test Case 1:0\n");
    printf("Input Data:");
    Test = getTransactionAmount(&TermDate);
     printf("Expected Result: INVALID_AMOUNT\n");
    printf("Actual Result: %s\n", Test == INVALID_AMOUNT ? "INVALID_AMOUNT" : "TERMINAL_OK");
    printf("===========================================\n");
    printf("Test Case 2:-100\n");
    printf("Input Data:");
    Test=getTransactionAmount(&TermDate);
     printf("Expected Result: INVALID_AMOUNT\n");
    printf("Actual Result:%s\n",Test==INVALID_AMOUNT? "INVALID_AMOUNT":"TERMINAL_OK");
    printf("===========================================\n");
    printf("Test Case 3:100\n");
    printf("Input Data:");
    Test=getTransactionAmount(&TermDate);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"INVALID_AMOUNT");
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if(termData == NULL ){ //Ensure the termData pointer is not NULL.
        return EXCEED_MAX_AMOUNT;
    }
    //termData->maxTransAmount=200;
     // Check if the transaction amount exceeds the maximum allowed amount
    if( termData->transAmount > termData->maxTransAmount){
        return EXCEED_MAX_AMOUNT; // Return error if the transaction amount exceeds the max amount
    }
    else{
        return TERMINAL_OK; // Return success if the amount is within the limit
    }
}
void isBelowMaxAmountTest(void)
{
    ST_terminalData_t TermDate;
    EN_terminalError_t Test;
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : isBelowMaxAmount \n");
    printf("===========================================\n");
    printf("Test Case 1:Amount greater than max\n");
    printf("Input Data:");
    getTransactionAmount(&TermDate);
    Test=isBelowMaxAmount(&TermDate);
     printf("Expected Result: EXCEED_MAX_AMOUNT\n");
    printf("Actual Result:%s\n",Test==EXCEED_MAX_AMOUNT? "EXCEED_MAX_AMOUNT":"TERMINAL_OK");
    printf("===========================================\n");
    printf("Test Case 2:Amount equal than max\n");
    printf("Input Data:");
    getTransactionAmount(&TermDate);
    Test=isBelowMaxAmount(&TermDate);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"EXCEED_MAX_AMOUNT");
    printf("===========================================\n");
    printf("Test Case 3:Amount less than max\n");
    printf("Input Data:");
    getTransactionAmount(&TermDate);
    Test=isBelowMaxAmount(&TermDate);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"EXCEED_MAX_AMOUNT");
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float32 maxAmount)
{
    if( termData == NULL){
        return INVALID_MAX_AMOUNT;
    }
    // Check if the provided maxAmount is less than or equal to zero, or if termData is NULL
    if(maxAmount <= 0 ){
        return INVALID_MAX_AMOUNT;
    }
    else{
        // Set the maximum transaction amount in the terminal data structure
        termData->maxTransAmount=maxAmount;
        return TERMINAL_OK; // Return success if the maximum amount is set correctly
    }
}
void setMaxAmountTest(void)
{
    ST_terminalData_t TermDate;
    EN_terminalError_t Test;
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : setMaxAmount \n");
    printf("===========================================\n");
    printf("Test Case 1:Negative\n");
    printf("Input Data:");
    Test=setMaxAmount(&TermDate,-100);
     printf("Expected Result: INVALID_MAX_AMOUNT\n");
    printf("Actual Result:%s\n",Test==INVALID_MAX_AMOUNT? "INVALID_MAX_AMOUNT":"TERMINAL_OK");
    printf("===========================================\n");
    printf("Test Case 2:zero\n");
    printf("Input Data:");
    Test=setMaxAmount(&TermDate,0);
    printf("Expected Result: INVALID_MAX_AMOUNT\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"INVALID_MAX_AMOUNT");
    printf("===========================================\n");
    printf("Test Case 3:positive\n");
    printf("Input Data:");
    Test=setMaxAmount(&TermDate,100);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"INVALID_MAX_AMOUNT");
}

int32_t isLuhnValid(const char *pan) {
    if (pan == NULL) {
        return 0;
    }

    uint32_t OddSum = 0;
    uint32_t EvenSum = 0;
    uint32_t DoubleEven = 0;
    int32_t Length = strlen(pan);

    // Check if the length is within the valid range for credit card numbers
    if (Length < 16 || Length > 19) {
        return 0;
    }
    // Check if each character is a digit (between '0' and '9')
    for (int32_t i = Length - 1; i >= 0; i--) {

        if (pan[i] < '0' || pan[i] > '9') {
            return 0;
        }

        uint32_t digit = pan[i] - '0'; // Convert character to integer digit

        // Check if the digit's position from the right is even or odd
        if ((Length - i) % 2 == 0) {
            DoubleEven = digit * 2;
            if (DoubleEven > 9) {
                DoubleEven -= 9;
            }
            EvenSum += DoubleEven;
        } else {
            OddSum += digit;
        }
    }

    uint32_t check = EvenSum + OddSum; // Calculate the total sum
    return (check % 10 == 0); // Return 1 if the total sum is divisible by 10 (valid number)
}
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData) {
    // Check if the input card data pointer is NULL
    if (cardData == NULL) {
        return INVALID_CARD;
    }
     // Use the Luhn algorithm to validate the Primary Account Number (PAN)
    if (isLuhnValid(cardData->primaryAccountNumber)) {
        return TERMINAL_OK;
    } else {
        return INVALID_CARD;
    }
}
void isValidCardPANTest(void) {
    ST_cardData_t card;
   EN_terminalError_t Test;
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : isValidCardPAN \n");
    printf("===========================================\n");
     printf("Test Case 1:Valid PAN\n");
    printf("Input Data:");
    getCardPAN(&card);
     Test = isValidCardPAN(&card);
   printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==INVALID_CARD? "INVALID_CARD":"TERMINAL_OK");
    printf("===========================================\n");
     printf("Test Case 2:Invalid PAN\n");
    printf("Input Data:");
    getCardPAN(&card);
     Test = isValidCardPAN(&card);
   printf("Expected Result: INVALID_CARD\n");
    printf("Actual Result:%s\n",Test==INVALID_CARD? "INVALID_CARD":"TERMINAL_OK");
}




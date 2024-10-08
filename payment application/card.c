#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "card.h"
EN_cardError_t getCardHolderName (ST_cardData_t *cardData)
{
     // Define a variable to store the cardholder's name
    uint8_t name[MAX_NAME_LENGTH]={};
    printf("Enter Card Holder's Name: ");
    gets(name);
    fflush(stdin); // Clear the standard input buffer to prevent unwanted input

    // Ensure the cardData pointer is not NULL, and the length of the name is between 20 and 24 characters
    if( cardData == NULL || strlen(name)>24 || strlen(name)<20){
        return WRONG_NAME;
    }
    else{
        uint32_t i;
        for(i=0 ; i<strlen(name) ; ++i){
            if(!isalpha(name[i]) && name[i]!=' '){
                return WRONG_NAME;
            }
        }
    }
     // Copy the valid name to the cardData structure
    for (uint32_t i=0;i<strlen(name);++i)
    {
        cardData->cardHolderName[i] = name[i];
    }
    cardData->cardHolderName[strlen(name)] = '\0'; // Null-terminate
    return CARD_OK;
}
void getCardHolderNameTest(void)
{
    ST_cardData_t CardData;
    EN_cardError_t Test;
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : getCardHolderName \n");
    printf("===========================================\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data:");
    Test = getCardHolderName(&CardData);
     printf("Expected Result: WRONG_NAME\n");
    printf("Actual Result: %s\n", Test == WRONG_NAME ? "WRONG_NAME" : "CARD_OK");
    printf("===========================================\n");
    printf("Test Case 2:Ibrahim\n");
    printf("Input Data:");
    Test=getCardHolderName(&CardData);
     printf("Expected Result: WRONG_NAME\n");
    printf("Actual Result:%s\n",Test==WRONG_NAME? "WRONG_NAME":"CARD_OK");
    printf("===========================================\n");
    printf("Test Case 3:Ibrahim mohamed && \n");
    printf("Input Data:");
    Test=getCardHolderName(&CardData);
     printf("Expected Result: WRONG_NAME\n");
    printf("Actual Result:%s\n",Test==WRONG_NAME? "WRONG_NAME":"CARD_OK");
    printf("===========================================\n");
    printf("Test Case 4:Ibrahim Mohamed Elstuhy\n");
    printf("Input Data:");
    Test=getCardHolderName(&CardData);
    printf("Expected Result: CARD_OK\n");
    printf("Actual Result:%s\n",Test==CARD_OK? "CARD_OK":"WRONG_NAME");

}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    uint8_t date[MAX_EXP_DATE_LENGTH]={};
    printf("Enter Card Expiry Date: ");
    gets(date); // Clear the input buffer to prevent unwanted input
    fflush(stdin);
    // Ensure the cardData pointer is not NULL, and the length of the date is exactly 5 characters (MM/YY)
    if( cardData == NULL || strlen(date) != EXP_DATE_FORMAT_LENGTH ){
        return WRONG_EXP_DATE;
    }
    else{
        uint32_t i=0;
        for(i=0 ; i<strlen(date) ; ++i){
            if(date[2] != '/' ||(date[0] =='1' && date[1] > '2')|| date[0] > '1' ){
                return WRONG_EXP_DATE; // Return an error if the format is incorrect
            }
        }
        // Copy the valid expiration date to the cardData structure
        for (uint32_t i=0;i<5;++i){
        cardData->cardExpirationDate[i] = date[i];
    }
    cardData->cardExpirationDate[strlen(date)] = '\0'; // Null-terminate
    }
    return CARD_OK;
}
void getCardExpiryDateTest (void)
{
    ST_cardData_t CardData;
    EN_cardError_t Test;
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : getCardExpiryDate \n");
    printf("===========================================\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data:");
    Test=getCardExpiryDate(&CardData);
    printf("Expected Result: WRONG_EXP_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_EXP_DATE? "WRONG_EXP_DATE":"CARD_OK");
    printf("===========================================\n");
    printf("Test Case 2:05 25\n");
    printf("Input Data:");
    Test=getCardExpiryDate(&CardData);
    printf("Expected Result: WRONG_EXP_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_EXP_DATE? "WRONG_EXP_DATE":"CARD_OK");
     printf("===========================================\n");
    printf("Test Case 3:13/25\n");
    printf("Input Data:");
    Test=getCardExpiryDate(&CardData);
    printf("Expected Result: WRONG_EXP_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_EXP_DATE? "WRONG_EXP_DATE":"CARD_OK");
     printf("===========================================\n");
    printf("Test Case 4:05/25\n");
    printf("Input Data:");
    Test=getCardExpiryDate(&CardData);
    printf("Expected Result: CARD_OK\n");
    printf("Actual Result:%s\n",Test==WRONG_EXP_DATE? "WRONG_EXP_DATE":"CARD_OK");
}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    uint8_t CardPAN[MAX_PAN_LENGTH]={};
        printf("Enter Card Pan: ");
        gets(CardPAN);
        fflush(stdin);// Clear the input buffer to prevent unwanted input

        // Ensure the cardData pointer is not NULL, and the length of the PAN is between 16 and 19 characters
         if( cardData == NULL || strlen(CardPAN)>19 || strlen(CardPAN)<16){
            return WRONG_PAN;
        }
        // Copy the valid PAN to the cardData structure
       for (uint32_t i=0; i<strlen(CardPAN); ++i)
    {
        cardData->primaryAccountNumber[i] = CardPAN[i];
    }
    cardData->primaryAccountNumber[strlen(CardPAN)] = '\0'; // Null-terminate


    return CARD_OK; // Return success if the PAN is valid
}
void getCardPANTest(void)
{
    ST_cardData_t CardData;
    EN_cardError_t Test;
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : getCardPAN \n");
    printf("===========================================\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data:");
    Test=getCardPAN(&CardData);
    printf("Expected Result: WRONG_PAN\n");
    printf("Actual Result:%s\n",Test==WRONG_PAN? "WRONG_PAN":"CARD_OK");
    printf("===========================================\n");
    printf("Test Case 2:123456\n");
    printf("Input Data:");
    Test=getCardPAN(&CardData);
    printf("Expected Result: WRONG_PAN\n");
    printf("Actual Result:%s\n",Test==WRONG_PAN? "WRONG_PAN":"CARD_OK");
     printf("===========================================\n");
    printf("Test Case 3:123456789123456789123456\n");
    printf("Input Data:");
    Test=getCardPAN(&CardData);
    printf("Expected Result: WRONG_PAN\n");
    printf("Actual Result:%s\n",Test==WRONG_PAN? "WRONG_PAN":"CARD_OK");
     printf("===========================================\n");
    printf("Test Case 4:123456789123456789\n");
    printf("Input Data:");
    Test=getCardPAN(&CardData);
    printf("Expected Result: CARD_OK\n");
    printf("Actual Result:%s\n",Test==WRONG_PAN? "WRONG_PAN":"CARD_OK");
}

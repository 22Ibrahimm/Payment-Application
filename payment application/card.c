#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "card.h"
EN_cardError_t getCardHolderName (ST_cardData_t *cardData)
{
    unit8 name[27];
    gets(name);
    if( cardData == NULL || strlen(name)>24 || strlen(name)<20){
        return WRONG_NAME;
    }
    else{
        unit32 cnt;
        for(cnt=0;cnt<strlen(name);++cnt){
            if(!isalpha(name[cnt])&&name[cnt]!=' '){
                return WRONG_NAME;
            }
        }
    }
    for (unit32 i=0;i<strlen(name);++i)
    {
        cardData->cardHolderName[i] = name[i];
    }
    cardData->cardHolderName[strlen(name)] = '\0';
    return CARD_OK;
}
void getCardHolderNameTest(void)
{
    ST_cardData_t CardData;
    EN_cardError_t Test;
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : GetCardHolderName \n");
    printf("===========================================\n");
    printf("Test Case 1:NULL\n");
    printf("Expected Result: WRONG_NAME\n");
    printf("Input Data:");
    Test = getCardHolderName(NULL);
    printf("Actual Result: %s\n", Test == WRONG_NAME ? "WRONG_NAME" : "CARD_OK");
    printf("===========================================\n");
    printf("Test Case 2:Ibrahim\n");
    printf("Expected Result: WRONG_NAME\n");
    printf("Input Data:");
    Test=getCardHolderName(&CardData);
    printf("Actual Result:%s\n",Test==WRONG_NAME? "WRONG_NAME":"CARD_OK");
    printf("===========================================\n");
    printf("Test Case 3:Ibrahim mohamed && \n");
    printf("Expected Result: WRONG_NAME\n");
    printf("Input Data:");
    Test=getCardHolderName(&CardData);
    printf("Actual Result:%s\n",Test==WRONG_NAME? "WRONG_NAME":"CARD_OK");
    printf("Test Case 4:Ibrahim Mohamed Elstuhy\n");
    printf("===========================================\n");
    printf("Expected Result: CARD_OK\n");
    printf("Input Data:");
    Test=getCardHolderName(&CardData);
    printf("Actual Result:%s\n",Test==CARD_OK? "CARD_OK":"WRONG_NAME");

}

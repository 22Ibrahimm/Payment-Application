#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    unit8 Date[15]={};
    gets(Date);
    if(termData == NULL || strlen(Date)!=10 || Date[2]!='/' || Date[5]!='/'  || (Date[3]=='1' && Date[4]>'2')){
        return WRONG_DATE;
    }
    else{
         for(unit32 i=0;i<strlen(Date);++i){
             termData->transactionDate[i]=Date[i];
         }
         termData->transactionDate[strlen(Date)]='\0';
         return TERMINAL_OK;
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
    if(cardData == NULL || termData == NULL){
        return EXPIRED_CARD;
    }
    if(cardData->cardExpirationDate[3]<termData->transactionDate[8]
    ||((cardData->cardExpirationDate[3]==termData->transactionDate[8])
    &&(cardData->cardExpirationDate[4]<termData->transactionDate[9]))){
        return EXPIRED_CARD;
     }
            if((cardData->cardExpirationDate[3]==termData->transactionDate[8])
            &&(cardData->cardExpirationDate[4]<termData->transactionDate[9])){
                if(cardData->cardExpirationDate[0]<termData->transactionDate[3]
                ||((cardData->cardExpirationDate[0]==termData->transactionDate[3])
                 &&(cardData->cardExpirationDate[1]<termData->transactionDate[4]))){
                         return EXPIRED_CARD;
            }
            else{
                return TERMINAL_OK;
            }
        }
        else{
            return TERMINAL_OK;
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
    float32 Amount=0;
    scanf("%f",&Amount);
    if(termData == NULL || Amount <= 0 ){
        return INVALID_AMOUNT;
    }
    else{
        termData->transAmount=Amount;
        return TERMINAL_OK;
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
    termData->maxTransAmount=200;
    if(termData == NULL || termData->transAmount > termData->maxTransAmount){
        return EXCEED_MAX_AMOUNT;
    }
    else{
        return TERMINAL_OK;
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
    if(maxAmount<=0 || termData == NULL){
        return INVALID_MAX_AMOUNT;
    }
    else{
        termData->maxTransAmount=maxAmount;
        return TERMINAL_OK;
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
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
       if(cardData == NULL){
       return INVALID_CARD;
    }
    unit32 OddSum = 0 ;
    unit32 EvenSum = 0 ;
    unit32 DoubleEven=0 ;
    unit32 Length=strlen(cardData->primaryAccountNumber);
    for(unit32 i = 1 ; i < Length ; i+=2){
        OddSum+=cardData->primaryAccountNumber[i]-'0';
    }
     for(unit32 i = 0 ; i < Length ; i+=2){
        DoubleEven = (cardData->primaryAccountNumber[i] - '0') * 2;
        if (DoubleEven > 9) {
            DoubleEven -= 9;
        }
        EvenSum += DoubleEven;
     }
     unit32 check=EvenSum+OddSum;
     if(check % 10 != 0 || check <= 0 ){
        return INVALID_CARD;
     }
     else{
        return  TERMINAL_OK;
     }
}
void isValidCardPANTest(void)
{
    ST_cardData_t CardData;
    EN_terminalError_t Test;
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : isValidCardPAN \n");
    printf("===========================================\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data:");
    getCardPAN(&CardData);
    Test=isValidCardPAN(&CardData);
    printf("Expected Result: INVALID_CARD\n");
    printf("Actual Result:%s\n",Test==INVALID_CARD? "INVALID_CARD":"TERMINAL_OK");
    printf("===========================================\n");
    printf("Test Case 2:Not Luhn Number\n");
    printf("Input Data:");
    getCardPAN(&CardData);
    Test=isValidCardPAN(&CardData);
    printf("Expected Result: INVALID_CARD\n");
    printf("Actual Result:%s\n",Test==INVALID_CARD? "INVALID_CARD":"TERMINAL_OK");
    printf("===========================================\n");
    printf("Test Case 3:Luhn Number\n");
    printf("Input Data:");
    getCardPAN(&CardData);
    Test=isValidCardPAN(&CardData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==INVALID_CARD? "INVALID_CARD":"TERMINAL_OK");

}



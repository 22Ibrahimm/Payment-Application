#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
    ST_terminalData_t TermData;
    EN_terminalError_t Test;
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : getTransactionDate \n");
    printf("===========================================\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data:");
    Test = getTransactionDate(&TermData);
     printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result: %s\n", Test == WRONG_DATE ? "WRONG_DATE" : "TERMINAL_OK");
    printf("===========================================\n");
    printf("Test Case 2:22*10*2005\n");
    printf("Input Data:");
    Test=getTransactionDate(&TermData);
     printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_DATE? "WRONG_DATE":"TERMINAL_OK");
    printf("===========================================\n");
    printf("Test Case 3:22/8/22 \n");
    printf("Input Data:");
    Test=getTransactionDate(&TermData);
     printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_DATE? "WRONG_DATE":"TERMINAL_OK");
     printf("===========================================\n");
    printf("Test Case 4:22/08/200444\n");
    printf("Input Data:");
    Test=getTransactionDate(&TermData);
    printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"WRONG_DATE");
    printf("===========================================\n");
    printf("Test Case 5:22/08/2004\n");
    printf("Input Data:");
    Test=getTransactionDate(&TermData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"WRONG_DATE");
}


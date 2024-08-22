#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "server.h"
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountReference, List *pl) {
    if (cardData == NULL || accountReference == NULL || pl == NULL) {
        return ACCOUNT_NOT_FOUND;
    }

    ListNode *currentNode = pl->head;

    while (currentNode != NULL) {
        if (strcmp(cardData->primaryAccountNumber, ((ST_accountsDB_t*)currentNode->ptr)->primaryAccountNumber) == 0) {
            *accountReference = (ST_accountsDB_t*)currentNode->ptr;
            return SERVER_OK;
        }
        currentNode = currentNode->next;
    }

    *accountReference = NULL;
    return ACCOUNT_NOT_FOUND;
}

void isValidAccountTest(void)
{
    ST_cardData_t CardData;
    EN_serverError_t Result;
    ST_accountsDB_t  *account;
    List l;
    CreateList(&l);


    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : isValidAccount \n");
    printf("===========================================\n");
     printf("Test Case 1:NULL \n");
    printf("Input Data:");
    ReadToFile("file.txt",&l);
    Result=isValidAccount(NULL,&account,&l);
    printf("Expected Result: ACCOUNT_NOT_FOUND\n");
    printf("Actual Result:%s\n",Result==SERVER_OK? "SERVER_OK":"ACCOUNT_NOT_FOUND");
    printf("===========================================\n");
    printf("Test Case 2:Exisiting\n");
    printf("Input Data:");
    ReadToFile("file.txt",&l);
    getCardPAN(&CardData);
    Result=isValidAccount(&CardData,&account,&l);
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result:%s\n",Result==SERVER_OK? "SERVER_OK":"ACCOUNT_NOT_FOUND");
    printf("===========================================\n");
     printf("Test Case 3:UN AVAILABLE \n");
    printf("Input Data:");
    ReadToFile("file.txt",&l);
    getCardPAN(&CardData);
    Result=isValidAccount(&CardData,&account,&l);
    printf("Expected Result: ACCOUNT_NOT_FOUND\n");
    printf("Actual Result:%s\n",Result==SERVER_OK? "SERVER_OK":"ACCOUNT_NOT_FOUND");
    printf("===========================================\n");

}



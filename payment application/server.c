#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "server.h"
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountReference, List *pl) {
    if (cardData == NULL || accountReference == NULL || pl == NULL) {
        return ACCOUNT_NOT_FOUND;
    }

    ListNode *currentNode = pl->head;

    while (currentNode != NULL) {
        if (strcmp(cardData->primaryAccountNumber, ((ST_accountsDB_t*)currentNode->ptr)->primaryAccountNumber) == 0) {
            *accountReference = *((ST_accountsDB_t*)currentNode->ptr);
            return SERVER_OK;
        }
        currentNode = currentNode->next;
    }

    accountReference = NULL;
    return ACCOUNT_NOT_FOUND;
}

void isValidAccountTest(void)
{
    ST_cardData_t CardData;
    EN_serverError_t Result;
    ST_accountsDB_t  account;
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
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference, List *list) {
    if (accountReference == NULL || list == NULL) {
        return BLOCKED_ACCOUNT;
    }

    ListNode *current = list->head;
    while (current != NULL) {
        ST_accountsDB_t *account = (ST_accountsDB_t *)current->ptr;
        if (strcmp(account->primaryAccountNumber, accountReference->primaryAccountNumber) == 0) {
            return account->state == 0 ? SERVER_OK : BLOCKED_ACCOUNT;
        }
        current = current->next;
    }

    return BLOCKED_ACCOUNT;
}

void isBlockedAccountTest(void) {
    ST_accountsDB_t account;
    EN_serverError_t Result;
    List l;
    CreateList(&l);
    ReadToFile("file.txt",&l);
    printf("Tester Name: Ibrahim Mohamed\n");
    printf("Function Name: isBlockedAccount\n");
    printf("===========================================\n");
    printf("Test Case 1: NULL Input\n");
    printf("Input Data: NULL account pointer\n");
    Result = isBlockedAccount(NULL,&l);
    printf("Expected Result: BLOCKED_ACCOUNT\n");
    printf("Actual Result: %s\n", Result == BLOCKED_ACCOUNT ? "BLOCKED_ACCOUNT" : "SERVER_OK");
    printf("===========================================\n");
    printf("Test Case 2: Account is Running\n");
    printf("Input Data: \n");
     ListNode *node = l.head;
    while (node != NULL) {
        ST_accountsDB_t *account = (ST_accountsDB_t *)node->ptr;
        if (account->state == 0) {
            Result = isBlockedAccount(account,&l);
            printf("Expected Result: SERVER_OK\n");
            printf("Actual Result: %s\n", Result == SERVER_OK ? "SERVER_OK" : "BLOCKED_ACCOUNT");
            break;
        }
        node = node->next;
    }
    printf("===========================================\n");
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference, List *pl) {
    if (termData == NULL || accountReference == NULL || pl == NULL) {
        return LOW_BALANCE;
    }
    ListNode *currentNode = pl->head;
    while (currentNode != NULL) {
        ST_accountsDB_t *account = (ST_accountsDB_t*)currentNode->ptr;
        if (strcmp(account->primaryAccountNumber, accountReference->primaryAccountNumber) == 0) {
        return termData->transAmount > account->balance ? LOW_BALANCE : SERVER_OK;
        }
        currentNode = currentNode->next;
    }

    return LOW_BALANCE;
}
void isAmountAvailableTest(void) {
    EN_serverError_t result;
    ST_terminalData_t termData;
    ST_accountsDB_t account;
    List l;

    CreateList(&l);
    ReadToFile("file.txt", &l);

    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : isAmountAvailable \n");
    printf("===========================================\n");

    strcpy(account.primaryAccountNumber, "22876543210987654");

    printf("Test Case 1:More than balance\n");
    printf("Input Data:");
     getTransactionAmount(&termData);
    result = isAmountAvailable(&termData, &account, &l);

    printf("Expected Result: LOW_BALANCE \n");
    printf("Actual Result: %s\n", result == SERVER_OK ? "SERVER_OK" : "LOW_BALANCE");
    printf("===========================================\n");

    printf("===========================================\n");

    strcpy(account.primaryAccountNumber, "22876543210987654");

    printf("Test Case 2:Less than balance\n");
    printf("Input Data:");
     getTransactionAmount(&termData);
    result = isAmountAvailable(&termData, &account, &l);

    printf("Expected Result: SERVER_OK \n");
    printf("Actual Result: %s\n", result == SERVER_OK ? "SERVER_OK" : "LOW_BALANCE");
    printf("===========================================\n");
}

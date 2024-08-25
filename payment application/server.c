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
        if (strcmp(cardData->primaryAccountNumber,((ST_accountsDB_t*)currentNode->ptr)->primaryAccountNumber) == 0) {
            *accountReference = ((ST_accountsDB_t*)currentNode->ptr);
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
    ST_accountsDB_t  account;
    List l;
    CreateList(&l);
    ReadToFile("file.txt",&l);
    printf("Tester Name : Ibrahim Mohamed \n");
    printf("Function Name : isValidAccount \n");
    printf("===========================================\n");
     printf("Test Case 1:NULL \n");
    printf("Input Data:");
    Result=isValidAccount(NULL,&account,&l);
    printf("Expected Result: ACCOUNT_NOT_FOUND\n");
    printf("Actual Result:%s\n",Result==SERVER_OK? "SERVER_OK":"ACCOUNT_NOT_FOUND");
    printf("===========================================\n");
    printf("Test Case 2:Exisiting\n");
    printf("Input Data:");
    getCardPAN(&CardData);
    Result=isValidAccount(&CardData,&account,&l);
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result:%s\n",Result==SERVER_OK? "SERVER_OK":"ACCOUNT_NOT_FOUND");
    printf("===========================================\n");
     printf("Test Case 3:UN AVAILABLE \n");
    printf("Input Data:");
    getCardPAN(&CardData);
    Result=isValidAccount(&CardData,&account,&l);
    printf("Expected Result: ACCOUNT_NOT_FOUND\n");
    printf("Actual Result:%s\n",Result==SERVER_OK? "SERVER_OK":"ACCOUNT_NOT_FOUND");
    printf("===========================================\n");

}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference) {
    if (accountReference == NULL) {
        return ACCOUNT_NOT_FOUND; // Handle case where the account reference is NULL
    }

    if (accountReference->state == BLOCKED) {
        return BLOCKED_ACCOUNT;
    } else {
        return SERVER_OK;
    }
}


void isBlockedAccountTest(void) {
    ST_accountsDB_t *account;
    EN_serverError_t Result;
    List l;
    CreateList(&l);
    ReadToFile("file.txt", &l);

    printf("Tester Name: Ibrahim Mohamed\n");
    printf("Function Name: isBlockedAccount\n");
    printf("===========================================\n");
    printf("Test Case 1: Existing blocked account  \n");
    printf("Input Data: Blocked Account \n");
    ST_cardData_t CardData;
    getCardPAN(&CardData);
    Result = isValidAccount(&CardData, &account, &l);
    if (Result == SERVER_OK) {
        Result = isBlockedAccount(account);
        printf("Expected Result: BLOCKED_ACCOUNT\n");
        printf("Actual Result: %s\n", Result == BLOCKED_ACCOUNT ? "BLOCKED_ACCOUNT" : "SERVER_OK");
    } else {
        printf("Account not found.\n");
    }
    printf("===========================================\n");
    printf("Test Case 2: Existing blocked account \n");
    printf("Input Data: Blocked Account \n");
    getCardPAN(&CardData);
    Result = isValidAccount(&CardData, &account, &l);
    if (Result == SERVER_OK) {
        Result = isBlockedAccount(account);
        printf("Expected Result: BLOCKED_ACCOUNT\n");
        printf("Actual Result: %s\n", Result == BLOCKED_ACCOUNT ? "BLOCKED_ACCOUNT" : "SERVER_OK");
    } else {
        printf("Account not found.\n");
    }
    printf("===========================================\n");
    printf("Test Case 3: Existing unblocked account \n");
    printf("Input Data: Unblocked Account \n");
    getCardPAN(&CardData);

    Result = isValidAccount(&CardData, &account, &l);
    if (Result == SERVER_OK) {
        Result = isBlockedAccount(account);
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: %s\n", Result == BLOCKED_ACCOUNT ? "BLOCKED_ACCOUNT" : "SERVER_OK");
    } else {
        printf("Account not found.\n");
    }
    printf("===========================================\n");
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference) {
    if (termData == NULL || accountReference == NULL ) {
        return LOW_BALANCE;
    }
    if(termData->transAmount > accountReference->balance){
        return LOW_BALANCE;
    }
    else{
        return SERVER_OK;
    }
}
void isAmountAvailableTest(void) {
    EN_serverError_t result;
    ST_terminalData_t termData;
    ST_accountsDB_t *account;
    ST_cardData_t CardData;
    List l;

    CreateList(&l);
    ReadToFile("file.txt", &l);

    printf("Tester Name: Ibrahim Mohamed\n");
    printf("Function Name: isAmountAvailable\n");
    printf("===========================================\n");

    printf("Test Case 1: Amount more than balance\n");
    printf("Input Data:\n");

    getCardPAN(&CardData);
    result = isValidAccount(&CardData, &account, &l);

    if (result == SERVER_OK) {
        termData.transAmount = 600.00;
        printf("Transaction Amount: %.2f\n", termData.transAmount);
        printf("Account Balance: %.2f\n", account->balance);
        result = isAmountAvailable(&termData, account);
        printf("Expected Result: LOW_BALANCE\n");
        printf("Actual Result: %s\n", result == SERVER_OK ? "SERVER_OK" : "LOW_BALANCE");
    } else {
        printf("Account not found.\n");
    }
    printf("===========================================\n");

    printf("Test Case 2: Amount equal to balance\n");
    printf("Input Data:\n");

    getCardPAN(&CardData);
    result = isValidAccount(&CardData, &account, &l);

    if (result == SERVER_OK) {
        termData.transAmount = 500.00;
        printf("Transaction Amount: %.2f\n", termData.transAmount);
        printf("Account Balance: %.2f\n", account->balance);
        result = isAmountAvailable(&termData, account);
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: %s\n", result == SERVER_OK ? "SERVER_OK" : "LOW_BALANCE");
    } else {
        printf("Account not found.\n");
    }
    printf("===========================================\n");


    printf("Test Case 3: Amount less than balance\n");
    printf("Input Data:\n");

    getCardPAN(&CardData);
    result = isValidAccount(&CardData, &account, &l);

    if (result == SERVER_OK) {
        termData.transAmount = 300.00;
        printf("Transaction Amount: %.2f\n", termData.transAmount);
        printf("Account Balance: %.2f\n", account->balance);
        result = isAmountAvailable(&termData, account);
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: %s\n", result == SERVER_OK ? "SERVER_OK" : "LOW_BALANCE");
    } else {
        printf("Account not found.\n");
    }
    printf("===========================================\n");
}
EN_serverError_t saveTransaction(ST_transaction_t *transData) {
    int32_t transaction_count = ReadTransactionsFromFile("transaction.txt", transaction_DB);

    if (transaction_count >= 300) {
        printf("SAVING_FAILED\n");
        return SAVING_FAILED;
    }

    transData->transactionSequenceNumber = transaction_count + 1;

    strcpy(transaction_DB[transaction_count].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
    strcpy(transaction_DB[transaction_count].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);
    strcpy(transaction_DB[transaction_count].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);
    strcpy(transaction_DB[transaction_count].terminalData.transactionDate, transData->terminalData.transactionDate);
    transaction_DB[transaction_count].terminalData.transAmount = transData->terminalData.transAmount;
    transaction_DB[transaction_count].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
    transaction_DB[transaction_count].transState = transData->transState;

    if (SaveTransactionsToFile("transaction.txt", transaction_DB, transaction_count + 1) != 0) {
        printf("SAVING_FAILED\n");
        return SAVING_FAILED;
    }

    printf("SERVER_OK\n");
    return SERVER_OK;
}


void saveTransactionTest(void) {
    ST_transaction_t data;
    strcpy(data.cardHolderData.cardHolderName, "AhmedNgySoliman");
    strcpy(data.cardHolderData.primaryAccountNumber, "1234567890123456");
    strcpy(data.cardHolderData.cardExpirationDate, "12/25");
    strcpy(data.terminalData.transactionDate, "2024/08/25");
    data.terminalData.transAmount = 100.00;
    data.terminalData.maxTransAmount = 500.00;
    data.transState = DECLINED_STOLEN_CARD;

    printf("Tester Name : Ibrahim Mohamed\n");
    printf("Function Name : saveTransaction\n");

    ReadTransactionsFromFile("transaction.txt", transaction_DB);

    printf("Test Case 1: SERVER_OK\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Input Data:\n");

    EN_serverError_t result = saveTransaction(&data);
    printf("Actual Result: %s\n", result == SERVER_OK ? "SERVER_OK" : "SAVING_FAILED");
}



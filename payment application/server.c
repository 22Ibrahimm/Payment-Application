#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "server.h"
#include "file_handling.h"
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountReference) {
    if (cardData == NULL) {
        return ACCOUNT_NOT_FOUND;
    }

    ListNode *currentNode = Account_DB.head;
    *accountReference = NULL;

    while (currentNode) {
        if (strcmp((char *)cardData->primaryAccountNumber, ((ST_accountsDB_t*)currentNode->ptr)->primaryAccountNumber) == 0) {
            *accountReference = (ST_accountsDB_t*)currentNode->ptr;
            return SERVER_OK;
        }
        currentNode = currentNode->next;
    }

    return ACCOUNT_NOT_FOUND;
}


void isValidAccountTest(void)
{
    ST_cardData_t CardData;
    EN_serverError_t Result;
    ST_accountsDB_t *account = NULL;
    CreateList(&Account_DB);
    ReadFromFile();

    printf("Tester Name: Ibrahim Mohamed \n");
    printf("Function Name: isValidAccount \n");
    printf("===========================================\n");

    // Test Case 1: Null card data
    printf("Test Case 1: NULL Card Data\n");
    printf("Input Data: NULL\n");
    Result = isValidAccount(NULL, &account);
    printf("Expected Result: ACCOUNT_NOT_FOUND\n");
    printf("Actual Result: %s\n", Result == SERVER_OK ? "SERVER_OK" : "ACCOUNT_NOT_FOUND");
    printf("===========================================\n");

    // Test Case 2: Existing card data
    printf("Test Case 2: Existing Card Data\n");
    strcpy(CardData.primaryAccountNumber, "1474798140991724");
    printf("Input Data: %s\n", CardData.primaryAccountNumber);
    Result = isValidAccount(&CardData, &account);
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %s\n", Result == SERVER_OK ? "SERVER_OK" : "ACCOUNT_NOT_FOUND");
    printf("===========================================\n");

    // Test Case 3: Non-existing card data
        printf("Test Case 3: Non-existing Card Data\n");
    strcpy(CardData.primaryAccountNumber, "00000000000000000");
    printf("Input Data: %s\n", CardData.primaryAccountNumber);
    Result = isValidAccount(&CardData, &account);
    printf("Expected Result: ACCOUNT_NOT_FOUND\n");
    printf("Actual Result: %s\n", Result == SERVER_OK ? "SERVER_OK" : "ACCOUNT_NOT_FOUND");
    printf("===========================================\n");
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference) {
    if (accountReference == NULL) {
        return ACCOUNT_NOT_FOUND;
    }

    if (accountReference->state == BLOCKED) {
        return BLOCKED_ACCOUNT;
    } else {
        return SERVER_OK;
}
}

void isBlockedAccountTest(void) {
    ST_cardData_t CardData;
    ST_accountsDB_t *account = NULL;
    EN_serverError_t Result;
    List Account_DB;


    CreateList(&Account_DB);
    ReadFromFile();

    printf("Tester Name: Ibrahim Mohamed\n");
    printf("Function Name: isBlockedAccount\n");
    printf("===========================================\n");

    // Test Case 1: Null account reference
    printf("Test Case 1: NULL Account Reference\n");
    printf("Input Data: NULL\n");
    Result = isBlockedAccount(NULL);
    printf("Expected Result: ACCOUNT_NOT_FOUND\n");
    printf("Actual Result: %s\n", Result == ACCOUNT_NOT_FOUND ? "ACCOUNT_NOT_FOUND" : "SERVER_OK");
    printf("===========================================\n");

    // Test Case 2: Existing blocked account
    printf("Test Case 2: Existing Blocked Account\n");
    strcpy(CardData.primaryAccountNumber, "4876950850461244");
    printf("Input Data: %s\n", CardData.primaryAccountNumber);
    Result = isValidAccount(&CardData, &account);
    if (Result == SERVER_OK) {
        Result = isBlockedAccount(account);
        printf("Expected Result: BLOCKED_ACCOUNT\n");
        printf("Actual Result: %s\n", Result == BLOCKED_ACCOUNT ? "BLOCKED_ACCOUNT" : "SERVER_OK");
    } else {
        printf("Expected Result: ACCOUNT_NOT_FOUND\n");
        printf("Actual Result: ACCOUNT_NOT_FOUND\n");
    }
    printf("===========================================\n");

    // Test Case 3: Existing unblocked account
    printf("Test Case 3: Existing Unblocked Account\n");
    strcpy(CardData.primaryAccountNumber, "1474798140991724");
    printf("Input Data: %s\n", CardData.primaryAccountNumber);
    Result = isValidAccount(&CardData, &account);
    if (Result == SERVER_OK) {
        Result = isBlockedAccount(account);
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: %s\n", Result == SERVER_OK ? "SERVER_OK" : "BLOCKED_ACCOUNT");
    } else {
        printf("Expected Result: ACCOUNT_NOT_FOUND\n");
        printf("Actual Result: ACCOUNT_NOT_FOUND\n");
    }
    printf("===========================================\n");

    // Test Case 4: Non-existing account
    printf("Test Case 4: Non-existing Account\n");
    strcpy(CardData.primaryAccountNumber, "00000000000000000");
    printf("Input Data: %s\n", CardData.primaryAccountNumber);
    Result = isValidAccount(&CardData, &account);
    if (Result == SERVER_OK) {
        Result = isBlockedAccount(account);
        printf("Expected Result: ACCOUNT_NOT_FOUND\n");
        printf("Actual Result: %s\n", Result == ACCOUNT_NOT_FOUND ? "ACCOUNT_NOT_FOUND" : "BLOCKED_ACCOUNT");
    } else {
        printf("Expected Result: ACCOUNT_NOT_FOUND\n");
        printf("Actual Result: ACCOUNT_NOT_FOUND\n");
    }
    printf("===========================================\n");
}


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference)
{
    if (termData == NULL || accountReference == NULL ) {
        return ACCOUNT_NOT_FOUND;
    }

    if(termData->transAmount > accountReference->balance){
        return LOW_BALANCE;
    }
    else{
        return SERVER_OK;
    }
}
void isAmountAvailableTest(void) {
    ST_terminalData_t termData;
    ST_accountsDB_t *account = NULL;
    ST_cardData_t CardData;
    EN_serverError_t result;
    List Account_DB;

    CreateList(&Account_DB);
    ReadFromFile();

    printf("Tester Name: Ibrahim Mohamed\n");
    printf("Function Name: isAmountAvailable\n");
    printf("===========================================\n");

    // Test Case 1: Amount more than balance
    printf("Test Case 1: Amount More Than Balance\n");
    printf("Input Data:\n");
    getCardPAN(&CardData);
    result = isValidAccount(&CardData, &account);

    if (result == SERVER_OK) {
        termData.transAmount = 600.00;
        printf("Transaction Amount: %.2f\n", termData.transAmount);
        printf("Account Balance: %.2f\n", account->balance);
        result = isAmountAvailable(&termData, account);
        printf("Expected Result: LOW_BALANCE\n");
        printf("Actual Result: %s\n", result == LOW_BALANCE ? "LOW_BALANCE" : "SERVER_OK");
    } else {
        printf("Account not found.\n");
    }
    printf("===========================================\n");

    // Test Case 2: Amount equal to balance
    printf("Test Case 2: Amount Equal to Balance\n");
    printf("Input Data:\n");
    getCardPAN(&CardData);
    result = isValidAccount(&CardData, &account);

    if (result == SERVER_OK) {
        termData.transAmount = 600.00;
        printf("Transaction Amount: %.2f\n", termData.transAmount);
        printf("Account Balance: %.2f\n", account->balance);
        result = isAmountAvailable(&termData, account);
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: %s\n", result == SERVER_OK ? "SERVER_OK" : "LOW_BALANCE");
    } else {
        printf("Account not found.\n");
    }
    printf("===========================================\n");

    // Test Case 3: Amount less than balance
    printf("Test Case 3: Amount Less Than Balance\n");
    printf("Input Data:\n");
    getCardPAN(&CardData);
    result = isValidAccount(&CardData, &account);

    if (result == SERVER_OK) {
        termData.transAmount = 600.00;
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
     if (transData == NULL){
        return SAVING_FAILED;
     }
 int32_t transaction_count = ReadTransactionsFromFile();

 insertAccount(transaction_count,transData,&Transaction_DB);

 if (SaveTransactionsToFile () != 1){
        return SAVING_FAILED;
 }

    return SERVER_OK;


}

void listSavedTransactions(void)
{
    ListNode *pn = Transaction_DB.head;
    if (pn==NULL)
        printf ("\nThere are no transactions \n");
    char state[30];
    while (pn)
    {
        ST_transaction_t *PtrAccount = (ST_transaction_t *)pn->ptr;

        if      (PtrAccount->transState == APPROVED)                      strcpy (state,"APPROVED");
        else if (PtrAccount->transState == DECLINED_INSUFFECIENT_FUND)    strcpy (state,"DECLINED_INSUFFECIENT_FUND");
        else if (PtrAccount->transState == DECLINED_STOLEN_CARD)          strcpy (state,"DECLINED_STOLEN_CARD");
        else if (PtrAccount->transState == FRAUD_CARD)                    strcpy (state,"FRAUD_CARD");
        else if (PtrAccount->transState == INTERNAL_SERVER_ERROR)         strcpy (state,"INTERNAL_SERVER_ERROR");
        else                                                              strcpy (state,"ERROR");

        printf("\n#####################################\n");
        printf("Transaction Sequence Number: %d\n" ,PtrAccount->transactionSequenceNumber );
        printf("Transaction Date: %s\n"            ,PtrAccount->terminalData.transactionDate);
        printf("Transaction Amount: %.2f\n"        ,PtrAccount->terminalData.transAmount);
        printf("Transaction State: %s\n"           ,state);
        printf("Terminal Max Amount: %.2f\n"       ,PtrAccount->terminalData.maxTransAmount);
        printf("Cardholder Name: %s\n"             ,PtrAccount->cardHolderData.cardHolderName);
        printf("PAN: %s\n"                         ,PtrAccount->cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n"        ,PtrAccount->cardHolderData.cardExpirationDate);
        printf("#####################################\n");

        pn=pn->next;
    }
}

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    if (transData == NULL){
    return INTERNAL_SERVER_ERROR;
    }
     ST_accountsDB_t *PtrAccount=NULL;
    EN_cardError_t Card_State;
    EN_terminalError_t Term_State;

    Card_State = getCardHolderName (&transData->cardHolderData);
    while (Card_State != CARD_OK)
    {
        printf ("Wrong name, ");
        printf("Please try again.\n");
        Card_State = getCardHolderName(&transData->cardHolderData);
    }

    Card_State = getCardPAN (&transData->cardHolderData);
    while (Card_State != CARD_OK)
    {
        printf ("Wrong PAN, ");
        printf("Please try again.\n");
        Card_State = getCardPAN(&transData->cardHolderData);
    }

    Card_State = getCardExpiryDate (&transData->cardHolderData);
    while (Card_State != CARD_OK)
    {
        printf ("Wrong date, ");
        printf("Please try again.\n");
        Card_State = getCardExpiryDate(&transData->cardHolderData);
    }

    Term_State = getTransactionDate(&transData->terminalData);
    while (Term_State != TERMINAL_OK)
    {
        printf(" Wrong date, ");
        printf("Please try again.\n");
        Term_State = getTransactionDate(&transData->terminalData);
    }

    Term_State = setMaxAmount(&transData->terminalData,100.000);
    while (Term_State != TERMINAL_OK)
    {
        printf("Invalid amount, ");
        printf("Please try again.\n");
        Term_State = setMaxAmount(&transData->terminalData,100.00);
    }

    Term_State = getTransactionAmount(&transData->terminalData);
    while (Term_State != TERMINAL_OK)
    {
        printf("Invalid amount, ");
        printf("Please try again.\n");
        Term_State = getTransactionAmount(&transData->terminalData);
    }

    if (isCardExpired(&transData->cardHolderData, &transData->terminalData) != TERMINAL_OK)
    {
        printf("\nCard is expired\n");
        transData->transState = INTERNAL_SERVER_ERROR;
        return INTERNAL_SERVER_ERROR;
    }

    if (isValidCardPAN (&transData->cardHolderData) != TERMINAL_OK)
    {
        printf("\nInvalid PAN\n");
        transData->transState = INTERNAL_SERVER_ERROR;
        return INTERNAL_SERVER_ERROR;
    }

    if (isBelowMaxAmount(&transData->terminalData) != TERMINAL_OK)
    {
        printf("\nAmount Exceeds maximum allowed\n");
        transData->transState = INTERNAL_SERVER_ERROR;
        return INTERNAL_SERVER_ERROR;
    }



    if(isValidAccount(&transData->cardHolderData,&PtrAccount) == ACCOUNT_NOT_FOUND)
    {
        transData->transState = FRAUD_CARD;
        return FRAUD_CARD;
    }

    if(isBlockedAccount(PtrAccount) == BLOCKED_ACCOUNT || isBlockedAccount(PtrAccount) == ACCOUNT_NOT_FOUND)
    {
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD ;
    }

    if(isAmountAvailable(&transData->terminalData,PtrAccount) == LOW_BALANCE || isAmountAvailable(&transData->terminalData,PtrAccount) == ACCOUNT_NOT_FOUND)
    {
        transData->transState = DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }

    PtrAccount->balance -= transData->terminalData.transAmount;

    UpdateFile ();
    transData->transState = APPROVED;
    return APPROVED;
}


#include <stdio.h>
#include <stdlib.h>
#include "file_handling.h"

void  ReadFromFile()
{
    // Open the file in read mode
    FILE *file = fopen("D:\\important\\project\\payment appliction\\Payment-Application\\payment application\\file.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return -1;
    }

    int32_t i=0; // Index to track the number of accounts
    uint8_t state[8]; // Array to store the account state read from the file

      // Loop to read each line from the file until the end of the file
    while (!feof(file))
    {
        // Allocate memory for storing the account data
        ST_accountsDB_t *account = (ST_accountsDB_t *)malloc(sizeof(ST_accountsDB_t));
         if (account == NULL)
        {
            printf("Memory allocation failed\n");
            fclose(file);
            return;
        }
        // Read the account data from the file (balance, account number, and state)
        if (fscanf(file, "%f %s %s", &account->balance, account->primaryAccountNumber, state) != 3)
        {
            free(account);
            break;
        }

        // Check and set the account state
        if (strcmp(state, "RUNNING") == 0)
            account->state = RUNNING;
        else if (strcmp(state, "BLOCKED") == 0)
            account->state = BLOCKED;
        else
        {
            printf("Unknown account state: %s\n", state);
            free(account);
            continue;
        }

        // Insert the account into the database
        insertAccount(i, account, &Account_DB);
        i++; // Increment the index
    }

    fclose(file);
}
void UpdateFile()
{
     // Open the file for writing
    FILE *file=fopen("D:\\important\\project\\payment appliction\\Payment-Application\\payment application\\file.txt","w");

    if (file == NULL)
    {
        printf("Error, File is Not Found\n");
        return;
    }

    char state[8];

    ListNode *pn = Account_DB.head;

    // Iterate through the list of accounts
    while (pn)
    {
        ST_accountsDB_t *PtrAccount = (ST_accountsDB_t *)pn->ptr;

        // Determine the state of the account
        if (PtrAccount->state == RUNNING)       strcpy (state,"RUNNING");
        else if (PtrAccount->state == BLOCKED)  strcpy (state,"BLOCKED");
        else                                    strcpy (state,"ERROR");

        // Write account data to the file
        fprintf(file, "%f %s %s\n", PtrAccount->balance, PtrAccount->primaryAccountNumber, state);
        pn = pn->next;
    }
    fclose(file);
}

int32_t  ReadTransactionsFromFile() {

    // Open the transactions file in read mode
    FILE *file = fopen("D:\\important\\project\\payment appliction\\Payment-Application\\payment application\\transaction.txt", "r");
    if (file == NULL) {
        return -1;
    }

    int32_t count = 0; // Initialize count for the number of transactions read
    uint8_t state[30]; // Temporary variable to store transaction state from file

    // Loop through the file until end-of-file is reached
     while (!feof(file))
    {
        // Allocate memory for a new transaction structure
        ST_transaction_t *transaction=(ST_transaction_t *)malloc(sizeof(ST_transaction_t));
        if (transaction == NULL)
        {
            printf("Memory allocation failed\n");
            fclose(file);
            return -1;
        }
        // Read transaction data from the file
        if (fscanf(file,"%d %s %f %s %f %s %s %49[^\n]\n"
                  ,&transaction->transactionSequenceNumber
                  ,transaction->terminalData.transactionDate
                  ,&transaction->terminalData.transAmount
                  ,state
                  ,&transaction->terminalData.maxTransAmount
                  ,transaction->cardHolderData.cardExpirationDate
                  ,transaction->cardHolderData.primaryAccountNumber
                  ,transaction->cardHolderData.cardHolderName) != 8)
        {
            free(transaction);
            break;
        }
         // Determine the transaction state from the read string
        if (strcmp(state, "APPROVED") == 0) transaction->transState = APPROVED;
        else if (strcmp(state, "DECLINED_INSUFFECIENT_FUND") == 0) transaction->transState = DECLINED_INSUFFECIENT_FUND;
        else if (strcmp(state, "DECLINED_STOLEN_CARD") == 0) transaction->transState = DECLINED_STOLEN_CARD;
        else if (strcmp(state, "FRAUD_CARD") == 0) transaction->transState = FRAUD_CARD;
        else if (strcmp(state, "INTERNAL_SERVER_ERROR") == 0) transaction->transState = INTERNAL_SERVER_ERROR;
        else
        {
            printf("Unknown account state: %s\n", state);
            free(transaction);
            continue;
        }
        // Insert the transaction into the database
        insertAccount(count, transaction, &Transaction_DB);
        count ++; // Increment the count of successfully read transactions

    }
    fclose(file);
    return count;
}


int32_t  SaveTransactionsToFile()
{
    // Open the transactions file in write mode
    FILE *file = fopen("D:\\important\\project\\payment appliction\\Payment-Application\\payment application\\transaction.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int32_t count=0;  // Initialize count for the number of transactions
    uint8_t state[30];  // Temporary variable to store transaction state as a string

    ListNode *pn = Transaction_DB.head; // Start from the head of the transactions list

    // Loop through the transactions list
    while (pn)
    {
         // Get the transaction data from the current node
        ST_transaction_t *PtrAccount = (ST_transaction_t *)pn->ptr;
        PtrAccount->transactionSequenceNumber= ++count; // Update the transaction sequence number

        // Determine the transaction state as a string
        if      (PtrAccount->transState == APPROVED)                      strcpy (state,"APPROVED");
        else if (PtrAccount->transState == DECLINED_INSUFFECIENT_FUND)    strcpy (state,"DECLINED_INSUFFECIENT_FUND");
        else if (PtrAccount->transState == DECLINED_STOLEN_CARD)          strcpy (state,"DECLINED_STOLEN_CARD");
        else if (PtrAccount->transState == FRAUD_CARD)                    strcpy (state,"FRAUD_CARD");
        else if (PtrAccount->transState == INTERNAL_SERVER_ERROR)         strcpy (state,"INTERNAL_SERVER_ERROR");
        else                                                              strcpy (state,"ERROR");

        /* Write the transaction data to the file*/
        fprintf(file,"%d %s %f %s %f %s %s %s\n"
                  ,PtrAccount->transactionSequenceNumber
                  ,PtrAccount->terminalData.transactionDate
                  ,PtrAccount->terminalData.transAmount
                  ,state
                  ,PtrAccount->terminalData.maxTransAmount
                  ,PtrAccount->cardHolderData.cardExpirationDate
                  ,PtrAccount->cardHolderData.primaryAccountNumber
                  ,PtrAccount->cardHolderData.cardHolderName);

            // Move to the next node in the list
        pn = pn->next;
    }
    fclose(file);
    return 1;
}

#include <stdio.h>
#include <stdlib.h>
#include "file_handling.h"

int32_t  ReadToFile(const uint8_t* FileName , List *pl)
{
    FILE *My_file=NULL;
    My_file=fopen("file.txt","r");
    if(My_file==NULL){
        printf("Error opening file!\n");
        return -1;
    }
    ST_accountsDB_t *accountDB;
    uint32_t pos=0;
  while (1) {
        accountDB = (ST_accountsDB_t *)malloc(sizeof(ST_accountsDB_t));
        if (accountDB == NULL) {
            printf("Memory allocation failed.\n");
            fclose(My_file);
            return -1;
        }
        int32_t result = fscanf(My_file, "%f %19s %i", &accountDB->balance, accountDB->primaryAccountNumber, &accountDB->state);
        if (result == EOF) {
            free(accountDB);
            break;
        }
         else if (result !=3) {
            printf("Error reading file data.\n");
            free(accountDB);
            fclose(My_file);
            return -1;
        }
        insertAccount(pos, accountDB, pl);
        pos++;
    }

    fclose(My_file);
    return 1;
}

int32_t ReadTransactionsFromFile(const uint8_t *FileName, ST_transaction_t *transactions) {
    FILE *transaction = fopen((const char *)FileName, "r");
    if (transaction == NULL) {
        printf("Error opening file!\n");
        return -1;
    }

    int32_t transaction_count = 0;
    char transStateStr[30];

    while (fscanf(transaction,
                  "%49s %19s %7s %10s %f %f %29s %u\n",
                  transactions[transaction_count].cardHolderData.cardHolderName,
                  transactions[transaction_count].cardHolderData.primaryAccountNumber,
                  transactions[transaction_count].cardHolderData.cardExpirationDate,
                  transactions[transaction_count].terminalData.transactionDate,
                  &transactions[transaction_count].terminalData.transAmount,
                  &transactions[transaction_count].terminalData.maxTransAmount,
                  transStateStr,
                  &transactions[transaction_count].transactionSequenceNumber) != EOF) {
        transactions[transaction_count].transState = mapStringToTransState(transStateStr);
        transaction_count++;
        if (transaction_count >= 300) break;
    }

    fclose(transaction);
    return transaction_count;
}

EN_transState_t mapStringToTransState(const char *stateStr) {
    if (strcmp(stateStr, "APPROVED") == 0) return APPROVED;
    if (strcmp(stateStr, "DECLINED_INSUFFECIENT_FUND") == 0) return DECLINED_INSUFFECIENT_FUND;
    if (strcmp(stateStr, "DECLINED_STOLEN_CARD") == 0) return DECLINED_STOLEN_CARD;
    if (strcmp(stateStr, "FRAUD_CARD") == 0) return FRAUD_CARD;
    if (strcmp(stateStr, "INTERNAL_SERVER_ERROR") == 0) return INTERNAL_SERVER_ERROR;
    return INTERNAL_SERVER_ERROR;
}
void SaveTransactionsToFile(const uint8_t *FileName, ST_transaction_t *transactions, int32_t count) {
    FILE *transaction = fopen((const char *)FileName, "w");
    if (transaction == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int32_t i = 0; i < count; i++) {
        fprintf(transaction,
                "%s %s %s %s %.2f %.2f %s %u\n",
                transactions[i].cardHolderData.cardHolderName,
                transactions[i].cardHolderData.primaryAccountNumber,
                transactions[i].cardHolderData.cardExpirationDate,
                transactions[i].terminalData.transactionDate,
                transactions[i].terminalData.transAmount,
                transactions[i].terminalData.maxTransAmount,
                mapTransStateToString(transactions[i].transState),
                transactions[i].transactionSequenceNumber);
    }

    fclose(transaction);
}

const char* mapTransStateToString(EN_transState_t transState) {
    switch (transState) {
        case APPROVED: return "APPROVED";
        case DECLINED_INSUFFECIENT_FUND: return "DECLINED_INSUFFECIENT_FUND";
        case DECLINED_STOLEN_CARD: return "DECLINED_STOLEN_CARD";
        case FRAUD_CARD: return "FRAUD_CARD";
        case INTERNAL_SERVER_ERROR: return "INTERNAL_SERVER_ERROR";
        default: return "UNKNOWN_STATE";
    }
}

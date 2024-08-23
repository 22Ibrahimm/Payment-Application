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
    FILE *transaction = NULL;
    transaction = fopen((const char *)FileName, "r");
    if (transaction == NULL) {
        printf("Error opening file!\n");
        return -1;
    }

    uint32_t i = 0;
    while (fscanf(transaction,
                  "%49s %19s %7s %10s %f %f %d %u\n",
                  transactions[i].cardHolderData.cardHolderName,
                  transactions[i].cardHolderData.primaryAccountNumber,
                  transactions[i].cardHolderData.cardExpirationDate,
                  transactions[i].terminalData.transactionDate,
                  &transactions[i].terminalData.transAmount,
                  &transactions[i].terminalData.maxTransAmount,
                  (int32_t *)&transactions[i].transState,
                  &transactions[i].transactionSequenceNumber) != EOF) {
        i++;
        if (i >= 300) break;
    }

    fclose(transaction);
    return i;
}


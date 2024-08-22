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
/*
int32_t readAccountsFromFile(const char *filename, List *pl) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    ST_accountsDB_t *account;
    uint32_t pos = 0;

    while (1) {
        account = (ST_accountsDB_t *)malloc(sizeof(ST_accountsDB_t));
        if (account == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return -1;
        }
        int32_t result = fscanf(file, "%f %19s %i", &account->balance, account->primaryAccountNumber, &account->state);
        if (result == EOF) {
            free(account);
            break;
        }
         else if (result !=3) {
            printf("Error reading file data.\n");
            free(account);
            fclose(file);
            return -1;
        }
        insertAccount(pos, account, pl);
        pos++;
    }

    fclose(file);
    return 1;
}
*/

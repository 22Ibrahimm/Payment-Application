#include <stdio.h>
#include <stdlib.h>
#include "file_handling.h"

void  ReadToFile( const unit8* FileName , List *pl)
{
    FILE *My_file=NULL;
    My_file=fopen("file.txt","r");
    if(My_file==NULL){
        printf("Error opening file!\n");
    }
    unit32 state;
    ST_accountsDB_t accountDB;
    unit32 pos=0;
   while (fscanf(My_file, "%f %20s %i", &accountDB.balance, accountDB.primaryAccountNumber, &state) != EOF) {
        accountDB.state = (EN_accountState_t)state;
        accountDB.primaryAccountNumber[20]='\0';
        insertAccount(pos, accountDB, pl);
        pos++;
    }

    fclose(My_file);
}

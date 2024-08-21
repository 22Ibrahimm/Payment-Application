#include <stdio.h>
#include <stdlib.h>
#include "file_handling.h"

void ReadToFile( const unit8* FileName , ST_accountsDB_t accountDB[])
{
    FILE *My_file=NULL;
    My_file=fopen("file.txt","r");
    if(My_file==NULL){
        printf("Error opening file!\n");
        return;
    }
    unit32 i=0;
    unit32 state;
    while(fscanf(My_file,"%f %s %i \n",&accountDB[i].balance,accountDB[i].primaryAccountNumber,&state)!=EOF)
    {
        accountDB[i].state=(EN_accountState_t)state;
        i++;
    }

    fclose(My_file);
}

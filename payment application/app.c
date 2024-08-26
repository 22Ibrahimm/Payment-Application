#include <stdio.h>
#include <stdlib.h>
#include "app.h"
void appStart(void)
{
    ST_transaction_t trans;
    ST_accountsDB_t *ref;
    List l;
    CreateList(&l);
    ReadToFile("file.txt", &l);
    EN_transState_t transvariable=recieveTransactionData(&trans,&l);

    if(isCardExpired(&trans.cardHolderData,&trans.terminalData)==TERMINAL_OK){
        if (isBelowMaxAmount(&trans.terminalData) == TERMINAL_OK) {
                if(isValidAccount(&trans.cardHolderData,&ref,&l)==SERVER_OK){
                    if (transvariable == APPROVED){
                        if(saveTransaction(&trans)==SERVER_OK){
                            printf("\nTranscation Saved");
                        }
                        else{
                            printf("\nSaving Failed");
                        }
                    }
                    else if (transvariable == DECLINED_STOLEN_CARD)
				{
					printf("\nDECLINED_STOLEN_CARD");
				}
				else if (transvariable == DECLINED_INSUFFECIENT_FUND) {
					printf("\nDECLINED_INSUFFECIENT_FUND");
				}
				else {
				 }
                }

    }
    else if (isBelowMaxAmount(&trans.terminalData) == EXCEED_MAX_AMOUNT) {
			printf("Exceed Max Amount");
		}
}
else if (isCardExpired(&trans.cardHolderData, &trans.terminalData) == EXPIRED_CARD) {
		printf("Expired Card");
	}
}

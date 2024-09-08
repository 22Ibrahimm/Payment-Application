#include <stdio.h>
#include <stdlib.h>
#include "app.h"
void App_Start (void)
{
            int userChoice=1;
            while (userChoice)
            {
            CreateList (&Transaction_DB);
            CreateList (&Account_DB);

                do {
                 printf("\n------- PAYMENT APPLICATION --------\n");
                printf("                                  \n");
                printf("     1. Do a transaction          \n");
                printf("                                  \n");
                printf("     2. Display transactions list \n");
                printf("                                  \n");
                printf("     0. Exit                      \n");

                printf("\nPlease select your choice : ");
                scanf(" %d", &userChoice);
                fflush(stdin);
                if (userChoice == 1)
                {
                    userChoice = 1;

                ReadFromFile ();

                ST_transaction_t *transData = (ST_transaction_t *)malloc(sizeof(ST_transaction_t));
                if (transData == NULL)
                {
                printf("Out Of Memory \n");
                return;
                }

                EN_transState_t Trans_State;

                Trans_State=recieveTransactionData (transData);



                if (Trans_State == INTERNAL_SERVER_ERROR)
                {
                printf("\nTransaction can't be saved\n");
                }
                else if (Trans_State == FRAUD_CARD)
                {
                printf("\nAccount doesn't exist\n");
                }
                else if (Trans_State == DECLINED_INSUFFECIENT_FUND)
                {
                printf("\nAmount isn't available\n");
                }
                else if (Trans_State == DECLINED_STOLEN_CARD)
                {
                printf("\nAccount is blocked\n");
                }
                else if (Trans_State == APPROVED)
                {
                printf("\nTransaction Approved\n");
                }

                EN_serverError_t Server_State = saveTransaction(transData);

                if (Server_State == SAVING_FAILED)
                printf("\nFailed to save transaction data.\n");


                free (transData);

                break;
                }
                else if (userChoice == 2)
                {
                    userChoice = 2;
                    ReadTransactionsFromFile ();
                    listSavedTransactions ();
                    break;
                }
                else if (userChoice == 0)
                {
                    userChoice = 0;
                    break;
                }
                else
                {
                    printf("Invalid input, Please enter '1' or '0'.\n");
                }
            }

        while (1);

        clear_list (&Account_DB);
        clear_list (&Transaction_DB);
    }
}

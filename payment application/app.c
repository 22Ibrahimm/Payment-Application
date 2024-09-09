#include <stdio.h>
#include <stdlib.h>
#include "app.h"
void App_Start (void)
{
            int userChoice=1;

            while (userChoice)   // Loop until the user chooses to exit (userChoice == 0).
            {
            CreateList (&Transaction_DB);    // Initialize the Transaction_DB linked list.
            CreateList (&Account_DB);        // Initialize the Account_DB linked list.

            // Display the menu options to the user.
                do {
            printf("\n=====================================\n");
            printf("|         PAYMENT APPLICATION       |\n");
            printf("=====================================\n");
            printf("|  1. Perform a New Transaction     |\n");
            printf("|-----------------------------------|\n");
            printf("|  2. Display All Transactions      |\n");
            printf("|-----------------------------------|\n");
            printf("|  0. Exit                          |\n");
            printf("=====================================\n");
                printf("\nPlease select your choice: ");
                scanf(" %d", &userChoice);
                fflush(stdin);

                if (userChoice == 1)
                {
                    userChoice = 1;  // Set userChoice to 1 to keep in the loop.

                ReadFromFile ();   // Load account data from the file.


                 // Allocate memory for a new transaction data structure.
                ST_transaction_t *transData = (ST_transaction_t *)malloc(sizeof(ST_transaction_t));

                if (transData == NULL)
                {
                printf("Out Of Memory \n");
                return;
                }

                EN_transState_t Trans_State;


                // Process the transaction and get the transaction state.
                Trans_State=recieveTransactionData (transData);



                // Display messages based on the transaction state.
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

                // Save the transaction to the database.
                EN_serverError_t Server_State = saveTransaction(transData);

                if (Server_State == SAVING_FAILED)
                printf("\nFailed to save transaction data.\n");


                free (transData);

                break;
                }
                else if (userChoice == 2)
                {
                    userChoice = 2;
                    ReadTransactionsFromFile ();   // Load the transactions from the file.
                    listSavedTransactions ();      // Display the saved transactions.
                    break;
                }
                else if (userChoice == 0)   // Option 0: Exit the application.
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

        clear_list (&Account_DB);    // Clear the Account_DB linked list to free memory.
        clear_list (&Transaction_DB);   // Clear the Transaction_DB linked list to free memory.
    }
}

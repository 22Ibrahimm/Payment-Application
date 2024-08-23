#include <stdio.h>
#include <stdlib.h>
#include "platform_types.h"
#include "card.h"
#include "terminal.h"
#include "platform_types.h"
#include "server.h"
#include "list.h"
ST_transaction_t transaction_DB[300];

int main()
{
//getCardHolderNameTest();
//getCardExpiryDateTest();
//getCardPANTest();
//getTransactionDateTest();
//isCardExpriedTest();
//getTransactionAmountTest();
//isBelowMaxAmountTest();
//setMaxAmountTest();
//isValidCardPANTest();
//readAccountsFromFile("file.txt",&l);
//DisplayList(&l, printAccount);
//isBlockedAccountTest();
//isValidAccountTest();
// isAmountAvailableTest();

uint32_t resutlt =ReadTransactionsFromFile("transaction.txt",transaction_DB);
 for (int i = 0; i < resutlt; i++) {
        printf("Card Holder Name: %s\n", transaction_DB[i].cardHolderData.cardHolderName);
        printf("Primary Account Number: %s\n", transaction_DB[i].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n", transaction_DB[i].cardHolderData.cardExpirationDate);
        printf("Transaction Date: %s\n", transaction_DB[i].terminalData.transactionDate);
        printf("Transaction Amount: %.2f\n", transaction_DB[i].terminalData.transAmount);
        printf("Max Transaction Amount: %.2f\n", transaction_DB[i].terminalData.maxTransAmount);
        printf("Transaction State: %d\n", transaction_DB[i].transState);
        printf("Sequence Number: %u\n", transaction_DB[i].transactionSequenceNumber);

    }

    return 0;
}

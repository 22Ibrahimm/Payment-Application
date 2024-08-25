#include <stdio.h>
#include <stdlib.h>
#include "platform_types.h"
#include "card.h"
#include "terminal.h"
#include "platform_types.h"
#include "server.h"
#include "list.h"
/*void PrintAccount(void *data) {
    ST_accountsDB_t *account = (ST_accountsDB_t *)data;
    printf("Balance: %.2f\n", account->balance);
    printf("PAN: %s\n", account->primaryAccountNumber);
    printf("State: %s\n", account->state == 0 ? "RUNNING" : "BLOCKED");
    printf("-------------------------------------------\n");
}*/
/*void PrintTransaction(ST_transaction_t *transaction) {
    printf("Card Holder Name: %s\n", transaction->cardHolderData.cardHolderName);
    printf("Primary Account Number: %s\n", transaction->cardHolderData.primaryAccountNumber);
    printf("Card Expiration Date: %s\n", transaction->cardHolderData.cardExpirationDate);
    printf("Transaction Date: %s\n", transaction->terminalData.transactionDate);
    printf("Transaction Amount: %.2f\n", transaction->terminalData.transAmount);
    printf("Max Transaction Amount: %.2f\n", transaction->terminalData.maxTransAmount);
    printf("Transaction State: %d\n", transaction->transState);
    printf("Transaction Sequence Number: %u\n", transaction->transactionSequenceNumber);
    printf("===========================================\n");
}
void PrintAllTransactions(ST_transaction_t *transactions, int32_t count) {
    for (int32_t i = 0; i < count; i++) {
        PrintTransaction(&transactions[i]);
    }
}*/
int main()
{
//List l;
//CreateList(&l);
//ReadToFile("file.txt", &l);

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
//DisplayList(&l, PrintAccount);
//isValidAccountTest();
//isBlockedAccountTest();
//isAmountAvailableTest();
listSavedTransactions();
//recieveTransactionDataTest();
//saveTransactionTest();
//uint32_t res=ReadTransactionsFromFile("transaction.txt",transaction_DB);
//PrintAllTransactions(transaction_DB,res);
//printf("%i\n",res);
    return 0;
}

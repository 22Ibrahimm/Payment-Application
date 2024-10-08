#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#include "platform_types.h"
#include "card.h"
#include "terminal.h"
#include "list.h"

typedef enum EN_transState_t
{
APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD,
FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
ST_cardData_t cardHolderData;
ST_terminalData_t terminalData;
EN_transState_t transState;
uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_serverError_t
{
SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND,
LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;

typedef enum EN_accountState_t
{
RUNNING,
BLOCKED
}EN_accountState_t;


typedef struct ST_accountsDB_t
{
float32 balance;
EN_accountState_t state;
uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

// List structures for account and transaction databases
List Account_DB;     // Linked list to store account data
List Transaction_DB;  // Linked list to store transaction data

EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountReference);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference) ;
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
 void listSavedTransactions(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);



#endif // SERVER_H_INCLUDED

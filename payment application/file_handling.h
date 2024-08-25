#ifndef FILE_HANDLING_H_INCLUDED
#define FILE_HANDLING_H_INCLUDED
#include "platform_types.h"
#include "server.h"
#include "list.h"

int32_t ReadToFile(const uint8_t* FileName , List *pl);
int32_t ReadTransactionsFromFile(const uint8_t *FileName, ST_transaction_t *transactions);
EN_transState_t mapStringToTransState(const char *stateStr);
void SaveTransactionsToFile(const uint8_t *FileName, ST_transaction_t *transactions, int32_t count);
const char* mapTransStateToString(EN_transState_t transState);
#endif // FILE_HANDLING_H_INCLUDED

#ifndef FILE_HANDLING_H_INCLUDED
#define FILE_HANDLING_H_INCLUDED
#include "platform_types.h"
#include "server.h"
#include "list.h"

int32_t ReadToFile(const uint8_t* FileName , List *pl);
int32_t ReadTransactionsFromFile(const uint8_t *FileName, ST_transaction_t *transactions);


#endif // FILE_HANDLING_H_INCLUDED

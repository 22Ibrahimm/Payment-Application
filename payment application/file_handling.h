#ifndef FILE_HANDLING_H_INCLUDED
#define FILE_HANDLING_H_INCLUDED
#include "platform_types.h"
#include "server.h"
#include "list.h"

void ReadFromFile();
void UpdateFile();
int32_t  ReadTransactionsFromFile();
int32_t  SaveTransactionsToFile();
#endif // FILE_HANDLING_H_INCLUDED

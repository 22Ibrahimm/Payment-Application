#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "platform_types.h"
#include "server.h"

typedef struct ListNode
{
ST_accountsDB_t accountDB;
struct ListNode *next;
}ListNode;

typedef struct List
{
    ListNode *head;
    unit32 size;
}List;

unit32 CreateList(List *pl);
void insertAccount(unit32 pos, ST_accountsDB_t account, List *pl);
unit32 DisplayList(List *pl, void (*pf)(ST_accountsDB_t));
unit32 ListSize(List *pl);


#endif // LIST_H_INCLUDED

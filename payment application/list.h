#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "platform_types.h"
typedef struct ListNode
{
void *ptr;
struct ListNode *next;
}ListNode;

typedef struct List
{
    ListNode *head;
    uint32_t size;
}List;

int32_t CreateList(List *pl);
int32_t insertAccount(uint32_t pos, void *account, List *pl);
int32_t DisplayList(List *pl, void (*pf)(void *));
int32_t ListSize(List *pl);


#endif // LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
unit32 CreateList(List *pl)
{
    if(pl==NULL){
        return -1;
    }
    else{
    pl->head=NULL;
    pl->size=0;
    return 1;
    }
}
void insertAccount(unit32 pos, ST_accountsDB_t account, List *pl)
{
    if(pl==NULL){
        return -1;
    }

    ListNode *p, *q;
    unit32 i;

    p = (ListNode *)malloc(sizeof(ListNode));
    if (p == NULL) {
        return -1;
    }
    p->accountDB = account;
    p->next = NULL;
    if (pos == 0) {
        p->next = pl->head;
        pl->head = p;
    }
     else {
        for (q = pl->head, i = 0; i < pos - 1; i++) {
            q = q->next;
        }
        p->next = q->next;
        q->next = p;
    }
    pl->size++;
    return 1;
}
unit32 DisplayList(List *pl, void (*pf)(ST_accountsDB_t))
{
    if (pl == NULL || pf == NULL) {
        return -1;
    }

    ListNode *p = pl->head;
    if (p == NULL) {
        printf("List is empty\n");
        return -1;
    }

    while (p) {
        (*pf)(p->accountDB);
        p = p->next;
    }

    return 1;
}
unit32 ListSize(List *pl)
{
if(pl==NULL){
    return -1;
}
else{
    return pl->size;
}
}

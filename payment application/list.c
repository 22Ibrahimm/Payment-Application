#include <stdio.h>
#include <stdlib.h>
#include "list.h"
int32_t CreateList(List *pl)
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
int32_t insertAccount(uint32_t pos, void *account , List *pl)
{
    if(pl==NULL){
        return -1;
    }

    ListNode *p, *q;
    uint32_t i;

    p = (ListNode *)malloc(sizeof(ListNode));
    if (p == NULL) {
        return -1;
    }
    p->ptr = account;
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
int32_t DisplayList(List *pl, void (*pf)(void *))
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
        (*pf)(p->ptr);
        p = p->next;
    }

    return 1;
}
int32_t ListSize(List *pl)
{
if(pl==NULL){
    return -1;
}
else{
    return pl->size;
}
}


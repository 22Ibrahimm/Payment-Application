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
int32_t DeleteNode(uint32_t pos, void **pe, List *pl) {
    if (pe == NULL || pl == NULL) {
        return -1;
    }

    if (pl->size == 0) {
        printf("List is empty\n");
        return -1;
    }

    ListNode *p, *q;

    if (pos == 0) {
        *pe = pl->head->ptr;
        p = pl->head->next;
        free(pl->head);
        pl->head = p;
    } else {
        uint32_t i;
        for (q = pl->head, i = 0; i < pos - 1; ++i) {
            q = q->next;
        }
        *pe = q->next->ptr;
        p = q->next->next;
        free(q->next);
        q->next = p;
    }

    pl->size--;
    return 1;
}

int32_t RetrieveList(uint32_t pos, void **pe, List *pl) {
    if (pe == NULL || pl == NULL) {
        return -1;
    }

    if (pl->size == 0) {
        printf("List is empty\n");
        return -1;
    }

    ListNode *p = pl->head;
    uint32_t i;

    for (i = 0; i < pos; ++i) {
        p = p->next;
    }

    *pe = p->ptr;
    return 1;
}
int32_t ReplaceList(uint32_t pos, void *e, List *pl) {
    if (pl == NULL) {
        return -1;
    }

    if (pl->size == 0) {
        printf("List is empty\n");
        return -1;
    }

    ListNode *p = pl->head;
    uint32_t i;

    for (i = 0; i < pos; ++i) {
        p = p->next;
    }

    p->ptr = e;
    return 1;
}
int clear_list (List *pl)
{
    if (pl==NULL)
        return -1;
    ListNode *pn=pl->head;
    while (pl->head)
    {
        pn=pl->head->next;
        free (pl->head);
        pl->head=pn;
    }
    pl->size=0;
    return 1;
}

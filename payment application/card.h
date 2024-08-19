#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
#include "platform_types.h"

typedef struct ST_cardData_t
{
unit8 cardHolderName[25];
unit8 primaryAccountNumber[20];
unit8 cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);
void getCardHolderNameTest(void);
void getCardExpiryDateTest (void);

#endif // CARD_H_INCLUDED

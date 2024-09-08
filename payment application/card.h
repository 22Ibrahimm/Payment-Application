#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
#include "platform_types.h"

#define MAX_NAME_LENGTH 27
#define MAX_EXP_DATE_LENGTH 7
#define EXP_DATE_FORMAT_LENGTH 5
#define MAX_PAN_LENGTH 25

typedef struct ST_cardData_t
{
uint8_t cardHolderName[25];
uint8_t primaryAccountNumber[20];
uint8_t cardExpirationDate[6];
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
void getCardPANTest(void);

#endif // CARD_H_INCLUDED

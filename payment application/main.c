#include <stdio.h>
#include <stdlib.h>
#include "platform_types.h"
#include "card.h"
#include "terminal.h"
#include "platform_types.h"
#include "server.h"
#include "list.h"
int main()
{
    List l;
    CreateList(&l);
//getCardHolderNameTest();
//getCardExpiryDateTest();
//getCardPANTest();
//getTransactionDateTest();
//isCardExpriedTest();
//getTransactionAmountTest();
//isBelowMaxAmountTest();
//setMaxAmountTest();
//isValidCardPANTest();
ReadToFile("file.txt",&l);
    return 0;
}

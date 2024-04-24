#include <stdio.h>
#include "stock.h"

void 
Stock::makeLogAndEntry(){
    printf("Make investment in stock, the amount is %d.\n", getAmount());
}
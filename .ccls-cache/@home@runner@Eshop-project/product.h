#ifndef PRODUCT_H
#define PRODUCT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *ProdPTR;
FILE * ProfitPTR;
struct product {
    char id[50];
    char name[50];
    int quantity;
    int cost;
    int selling_price;
};
#endif // PRODUCT_H
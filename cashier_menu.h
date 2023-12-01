#ifndef CASHIER_MENU_H
#define CASHIER_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "publicdata.h"

float total_profit;
int cashier_view_product();
int cashier_sell_product();

void cashier() {
  int x = 1;
  int choice;
  printf("--------Cashier--------\n");
  while (x > 0) {
    printf("What do you want to do\n");
    printf("1. View Product\n");
    printf("2. Sold Product\n");
    printf("3. Exit\n");
    printf("Enter your choice: \n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      printf("\n");
      cashier_view_product();
      x = 0;
      break;
    case 2:
      printf("\n");
      cashier_sell_product();
      x = 0;
      break;
    case 3:
      x = 0;
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice. Please choose again.\n");
      printf("\n");
    }
  }
}

int cashier_view_product() {
  ProdPTR = fopen("ProductList.csv", "r");

  char List[50];
  while (fgets(List, 50, ProdPTR)) {
    printf("%s", List);
  }

  fclose(ProdPTR);
  printf("\n");
  cashier();
}

int cashier_sell_product() {
    struct product Product;
    char product_id[5];

    printf("Enter the product ID: ");
    scanf("%s", product_id);

    ProdPTR = fopen("ProductList.csv", "r");
    if (ProdPTR == NULL) {
        perror("Error opening file");
      exit(EXIT_FAILURE);
    }

    printf("Id\tName\tQuantity\tCost\tSelling Price\n");
    fscanf(ProdPTR, "%*[^\n]\n");

  

    int found = 0;
    while (fscanf(ProdPTR, "%[^,],%[^,],%d,%d,%d\n", Product.id, Product.name, &Product.quantity, &Product.cost, &Product.selling_price) == 5) {
        if (strcmp(Product.id, product_id) == 0) {
          printf("%s\t%s\t%d\t\t%d\t%d\n", Product.id, Product.name, Product.quantity, Product.cost, Product.selling_price);
            found = 1;
            break;
        }
    }

    // fclose(ProdPTR);

    if (!found) {
        printf("Product with ID %s not found.\n", product_id);
      exit(EXIT_FAILURE);
    }

    printf("Enter the quantity sold: ");
    int sold_quantity;
    scanf("%d", &sold_quantity);

    if (sold_quantity > Product.quantity) {
        printf("Error: Not enough stock available for sale.\n");
      exit(EXIT_FAILURE);
    }

    float total_cost = sold_quantity * Product.cost;
    float total_revenue = sold_quantity * Product.selling_price;
    float profit = total_revenue - total_cost;


    ProfitPTR = fopen("ProfitFile.csv", "a");  // Open in append mode

    if (ProfitPTR == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    total_profit += profit;

    fprintf(ProfitPTR, "%s,%s,%d,%.2f\n", Product.id, Product.name, sold_quantity, profit);
    fprintf(ProfitPTR, "Total profit: %.2f\n", total_profit);
    fclose(ProfitPTR);

    printf("Sale recorded successfully. Profit for this item: %.2f\n", profit);
    printf("Total profit: %.2f\n", total_profit);
    printf("\n");
  
  FILE *TempPTR = fopen("ProductList(Modified).csv", "w");
  if (TempPTR == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  
  fprintf(TempPTR, "Id,Name,Quantity,Cost,Selling,Price");
  while (fscanf(ProdPTR, "%[^,],%[^,],%d,%d,%d\n", Product.id, Product.name, &Product.quantity, &Product.cost, &Product.selling_price) == 5) {
      if (strcmp(Product.id, product_id) == 0) {
        Product.quantity -= sold_quantity;
        fprintf(TempPTR, "%s,%s,%d,%d,%d\n", Product.id, Product.name, Product.quantity, Product.cost, Product.selling_price);
      }else{
        fprintf(TempPTR, "%s,%s,%d,%d,%d\n", Product.id, Product.name, Product.quantity, Product.cost, Product.selling_price);
      }
  }
  
    cashier();
}
#endif // CASHIER_MENU_H
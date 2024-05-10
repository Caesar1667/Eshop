#ifndef CASHIER_MENU_H
#define CASHIER_MENU_H

#include "publicdata.h"
#include "profit.h"
// #include "UpdateInventory.h"
#include "manager_menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




void cashier_view_product();
void cashier_sell_product();
void exit_confirmation();

char ex[1];

void cashier() {
  int x = 1;
  int choice;
  printf("--------Cashier--------\n");
  while (x > 0) {
    printf("What do you want to do\n");
    printf("1. View Product\n");
    printf("2. Sold Product\n");
    printf("3. Revert Changes\n");
    printf("4. Update Inventory\n");
    printf("5. Exit\n");
    printf("Enter your choice: \n");
    scanf("%d", &choice);
    clearBuffer();
    switch (choice) {
    case 1:
      printf("\n");
      cashier_view_product();
      x = 0;
      break;
    case 2:
      printf("\n");
      SaveState(cashier_sell_product, cashier);
      // cashier_sell_product();
      x = 0;
      break;
    case 3:
      printf("\n");
      Revert();
      x = 0;
      break;
    case 4:
      printf("\n");
      UpdateInv(cashier);
      x = 0;
      break;
    case 5:
      printf("\n");
      if(save_state){
        x=0;
        printf("Exiting...");
        break;
      }else{
        exit_confirmation();
      }
        break;
    default:
      printf("Invalid choice. Please choose again.\n");
      printf("\n");
      }
  }
}
  
//This function use to see all the product currently//
void cashier_view_product() {
  ProdPTR = fopen("ProductList.csv", "r"); //open file in read mode.

  char List[50];
  while (fgets(List, 50, ProdPTR)) { //read a line in the  file
    printf("%s", List); //print a line out
  }

  fclose(ProdPTR); //close the file
  printf("\n");
  cashier(); //return to cashier menu
}

void exit_confirmation(){
  printf("You have unsaved changes.\n Are you sure you want to exit? This will discard changes you made. (Y/N) : ");
  scanf("%c", ex);
  clearBuffer();
  if (ex[0] == 'Y' || ex[0] == 'y') {
    printf("Exiting without saving changes...\n");
  }else if(ex[0] == 'N' || ex[0] == 'n'){
    printf("Returning to menu...\n");
    cashier();
  }else{
    printf("Invalid input. Returning to menu...\n");
    cashier();
  }
}

void cashier_sell_product() {
  struct product Product;
  char product_id[5];

  printf("Enter the product ID (Input Q to return): "); //enter the existing product id.
  scanf("%s", product_id);
  clearBuffer();
  if(product_id[0] == 'q' || product_id[0] == 'Q') {
    cashier();
  }

  ProdPTR = fopen("ProductList.csv", "r"); //open original file in read mode
  if (ProdPTR == NULL) { //if can't be open then output error message.
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  printf("Id\tName\tQuantity\tCost\tSelling Price\n");
  fscanf(ProdPTR, "%*[^\n]\n"); //skip the first line by reading it and not doing anything to it.

  int found = 0; //use for finding the product we input in line 93
  while (fscanf(ProdPTR, "%[^,],%[^,],%d,%d,%d\n", Product.id, Product.name, &Product.quantity, &Product.cost, &Product.selling_price) == 5) { //read each line and assign them to appropriate variables.
    if (strcmp(Product.id, product_id) == 0) { //compare product id we input to the file.
      printf("%s\t%s\t%d\t\t%d\t%d\n", Product.id, Product.name, Product.quantity, Product.cost, Product.selling_price); //if found the right product id output the variables.
      found = 1; 
      break;
    }
  }


  if (!found) { //if not found return to input product id (line ;
    printf("Product with ID %s not found.\n", product_id);
    // exit(EXIT_FAILURE);
    cashier_sell_product();
  }

  printf("Enter the quantity sold: "); //input quantity.
  int sold_quantity;
  scanf("%d", &sold_quantity);
  clearBuffer();

  if (sold_quantity > Product.quantity) { //if quantity we're selling is more than the inventory return to the cashier menu.
    printf("Error: Not enough stock available for sale.\n");
    cashier();
  }

  Profit_cal(sold_quantity, Product);

  FILE *TempPTR = fopen("ProductList(Modified).csv", "w"); //open the new file in write mode.
  //use as a temporary file before putting changes to the original file. 
  if (TempPTR == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  
  fprintf(TempPTR, "Id,Name,Quantity,Cost,Selling,Price\n");

  rewind(ProdPTR); //set the original file position to the first line.

  fscanf(ProdPTR, "%*[^\n]\n"); //skip the first line.

  while (fscanf(ProdPTR, "%[^,],%[^,],%d,%d,%d\n", Product.id, Product.name,
                &Product.quantity, &Product.cost,
                &Product.selling_price) == 5) { //read the line and assign to the appropriate variable
    if (strcmp(Product.id, product_id) == 0) { //compare the product id we input.
      Product.quantity -= sold_quantity; //if found the right product id, put change the quantity value.
      fprintf(TempPTR, "%s,%s,%d,%d,%d\n", Product.id, Product.name,
              Product.quantity, Product.cost, Product.selling_price);
    } else { //if not found, (this mean it's not the line we want to change) print the line as normal
      fprintf(TempPTR, "%s,%s,%d,%d,%d\n", Product.id, Product.name,
              Product.quantity, Product.cost, Product.selling_price);
    }
  }
  fclose(TempPTR);
  save_state = 0;
  cashier(); //return the cashier menu.
}
#endif // CASHIER_MENU_H
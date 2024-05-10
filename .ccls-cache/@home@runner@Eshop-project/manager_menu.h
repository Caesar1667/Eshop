#ifndef MANAGER_MENU_H
#define MANAGER_MENU_H

#include "publicdata.h"
#include "UpdateInventory.h"
#include "RevertChanges.h"
#include "SaveStateCheck.h"
#include "Reorder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void manager_view_product();
void manager_view_profit();
void manager_reorder_product();
void manager_remove_product();
void manager_addnew_product();
void manager_UpdateInv();

//This is the manager menu function//
void manager() {
  int x = 1;
  int choice;
  printf("--------Manager--------\n");
  while (x > 0) {
    printf("What do you want to do\n");
    printf("1. View Product\n");
    printf("2. View Profit\n");
    printf("3. Reorder Product\n");
    printf("4. Restock Product\n");
    printf("5. Remove Product\n");
    printf("6. AddNew Product\n");
    printf("7. Update Inventory\n");
    printf("8. Exit\n");
    printf("Enter your choice: \n");
    scanf("%d", &choice);
    clearBuffer();
    switch (choice) {
    case 1:
      printf("\n");
      manager_view_product();
      x = 0;
      break;
    case 2:
      printf("\n");
      manager_view_profit();
      x = 0;
      break;
    case 3:
      printf("\n");
      reorder_product();
      manager();
      x = 0;
      break;
    case 4:
      printf("\n");
      SaveState(restock_product, manager);
      manager();
      x = 0;
      break;
    case 5:
      printf("\n");
      SaveState(manager_remove_product, manager);
      manager_remove_product();
      x = 0;
      break;
    case 6:
      printf("\n");
      SaveState(manager_addnew_product, manager);
      x = 0;
      break;
    case 7:
      printf("\n");
      // manager_UpdateInv();
      UpdateInv(manager);
      x = 0;
      break;
    case 8:
      x = 0;
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice. Please choose again.\n");
      printf("\n");
    }
  }
}

//This function use to remove the product that you didn't want to sell anymore from storage//
void manager_remove_product() {
  FILE *TempPtr;
  char line[100], nameToDelete[50];
  int found = 0;

  ProdPTR = fopen("ProductList.csv", "r");

  if (ProdPTR == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  TempPtr = fopen("ProductList(Modified).csv", "w");

  if (TempPtr == NULL) {
    perror("Error opening file");
    fclose(ProdPTR);
    exit(EXIT_FAILURE);
  }

  printf("Enter the name to delete (Input Q to return): ");
  fgets(nameToDelete, sizeof(nameToDelete), stdin);
  nameToDelete[strcspn(nameToDelete, "\n")] = '\0';
  if(nameToDelete[0] == 'q' || nameToDelete[0] == 'Q') {
    manager();
  }

  while (fgets(line, sizeof(line), ProdPTR) != NULL) {
    if (strstr(line, nameToDelete) == NULL) {
      fputs(line, TempPtr);
    } else {
      found = 1;
    }
  }

  fclose(ProdPTR);
  fclose(TempPtr);

  rename("Temp.csv", "ProductList.csv");

  if (found) {
    printf("Name '%s' deleted successfully.\n", nameToDelete);
  } else {
    printf("Name '%s' not found in the file.\n", nameToDelete);
  }
  printf("\n");
  save_state = 0;
  manager();
}

//This function is use to add new product that want to sell//
void manager_addnew_product() {
  char ProdID[50], ProdName[50];
  int Quantity, Price, Cost;
  printf("Please input a Product ID : ");
  scanf("%s", ProdID);
  clearBuffer();
  if(ProdID[0] == 'q' || ProdID[0] == 'Q') {
    manager();
  }
  printf("Please input a Product Name : ");
  scanf("%s", ProdName);
  clearBuffer();
  printf("Please input quantities : ");
  scanf("%d", &Quantity);
  clearBuffer();
  printf("Please input a cost : ");
  scanf("%d", &Cost);
  clearBuffer();
  printf("Please input a price : ");
  scanf("%d", &Price);
  clearBuffer();
  
  ProdPTR = fopen("ProductList.csv", "r");
  if (ProdPTR == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  
  FILE *TempPTR = fopen("ProductList(Modified).csv", "w");
    if(TempPTR == NULL){
      perror("Error opening file");
      exit(EXIT_FAILURE);
    }
  
  char line[100];
  while(fgets(line, sizeof(line), ProdPTR) != NULL) {
      fputs(line,TempPTR);
  }
  fprintf(TempPTR, "\n%s,%s,%d,%d,%d", ProdID, ProdName, Quantity, Cost, Price);
  fclose(TempPTR);
  fclose(ProdPTR);
  printf("\n");
  save_state = 0;
  manager();
}

//This function use to update the stock, manager need to use this every time before close their shop so today data will be update to present.
//obsolete turned into header file.
void manager_UpdateInv() {
  char choice[1];
  printf("Are you sure you want to update the inventory? (Y/N)");
  scanf("%c", choice);
  switch (choice[0]) {
  case 'Y':
    remove("ProductList.csv");
    rename("ProductList(Modified).csv", "ProductList.csv");
    break;
  case 'y':
    remove("ProductList.csv");
    rename("ProductList(Modified).csv", "ProductList.csv");
    break;
  case 'N':
    break;
  case 'n':
    break;
    default:
    printf("Invalid input please try again.\n");
    manager_UpdateInv();
    break;
  }
  printf("\n");
  manager();
}

//This function use to see all the product currently//
void manager_view_product() {
  ProdPTR = fopen("ProductList.csv", "r");

  char List[50];
  while (fgets(List, 50, ProdPTR)) {
    printf("%s", List);
  }

  fclose(ProdPTR);
  printf("\n");
  manager();
}

void manager_view_profit() {
  FILE *ProfPTR = fopen("ProfitFile.csv", "r");

  char List[50];
  while (fgets(List, 50, ProfPTR)) {
    printf("%s", List);
  }

  fclose(ProfPTR);
  printf("\n");
  manager();
}

void manager_view_reordering(){
  FILE *reorderPTR = fopen("ToReorder.txt", "r");
  char List[50];
  while(fgets(List, sizeof(List), reorderPTR)){
    printf("%s", List);
  }
  fclose(reorderPTR);
  printf("\n");
  manager();
}

#endif // MANAGER_MENU_H
#include <stdio.h>
#include <unistd.h>
#include "publicdata.h"
#include "binary_handling.h"

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void UpdateInv(void (*f)()) {
  char choice[1];
  printf("Are you sure you want to update the inventory? (Y/N) : ");
  scanf("%c", choice);
  clearBuffer();
  switch (choice[0]) {
  case 'Y':
    save_state = 1;
    rename("ProductList.csv", "ProductList_bak.csv");
    rename("ProductList(Modified).csv", "ProductList.csv");
    if(access("ProductList.bin", F_OK) == 0){ //check if the file already exists then change to backup version and create the new version.
      rename("ProductList.bin", "ProductList_bak.bin");
      rename("ProfitFile.bin", "ProfitFile_bak.bin");
      csv_to_binary("ProductList.csv", "ProductList.bin");
      csv_to_binary("ProfitFile.csv", "ProfitFile.bin");
    }else{
      csv_to_binary("ProductList.csv", "ProductList.bin");
      csv_to_binary("ProfitFile.csv", "ProfitFile.bin");
    }
    
    break;
  case 'y':
    save_state = 1;
    rename("ProductList.csv", "ProductList_bak.csv");
    rename("ProductList(Modified).csv", "ProductList.csv");
    
    if(access("ProductList.bin", F_OK) == 0){ //check if the file already exists then change to backup version and create the new version.
      rename("ProductList.bin", "ProductList_bak.bin");
      rename("ProfitFile.bin", "ProfitFile_bak.bin");
      csv_to_binary("ProductList.csv", "ProductList.bin");
      csv_to_binary("ProfitFile.csv", "ProfitFile.bin");
    }else{
      csv_to_binary("ProductList.csv", "ProductList.bin");
      csv_to_binary("ProfitFile.csv", "ProfitFile.bin");
    }
    
    break;
  case 'N':
    break;
  case 'n':
    break;
    default:
    printf("Invalid input please try again.\n");
    UpdateInv(f);
    break;
  }
  f();
  printf("\n");
}


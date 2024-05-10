#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "publicdata.h"

void Revert(){
  char c[1];
  printf("Are you sure you want to revert changes? (Y/N) : ");
  scanf("%c", c);

  switch(c[0]){
    case 'Y':
      save_state = 1;
      remove("ProductList.csv");
      remove("ProfitFile.csv");
      remove("ProductList.bin");
      remove("ProfitFile.bin");
      rename("ProductList_bak.csv","ProductList.csv");
      rename("ProfitFile_bak.csv","ProfitFile.csv");
      rename("ProductList_bak.bin","ProductList.bin");
      rename("ProfitFile_bak.bin","ProfitFile.bin");
      break;
    case 'y':
      save_state = 1;
      remove("ProductList.csv");
      remove("ProfitFile.csv");
      remove("ProductList.bin");
      remove("ProfitFile.bin");
      rename("ProductList_bak.csv","ProductList.csv");
      rename("ProfitFile_bak.csv","ProfitFile.csv");
      rename("ProductList_bak.bin","ProductList.bin");
      rename("ProfitFile_bak.bin","ProfitFile.bin");
      break;
    case 'N':
      break;
    case 'n':
      break;
    default:
      printf("Invalid Input. Please try again.\n");
      break;
    }
  }
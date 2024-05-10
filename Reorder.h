#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "publicdata.h"

  struct product Reor;
  int reorder_threshold = 40;

//This is reoder product function, once the product is less than reorder threshold. The function will reoder the product that less than threshold.
void reorder_product() {
  int new_quantity = reorder_threshold + 10;
  ProdPTR = fopen("ProductList.csv", "r");
  if (ProdPTR == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  fscanf(ProdPTR, "%*[^\n]\n");

  FILE *rePTR = fopen("ToReorder.txt", "w");
  if(rePTR == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  
  while (fscanf(ProdPTR, "%[^,],%[^,],%d,%d,%d\n", Reor.id, Reor.name, &Reor.quantity, &Reor.cost, &Reor.selling_price) == 5) {
    if (Reor.quantity < reorder_threshold) {
      printf("Product ID %s need reordering (Currently : %d). Quantity needed : %d\n", Reor.id, Reor.quantity, new_quantity-Reor.quantity);
      fprintf(rePTR,"Product ID %s need reordering (Currently : %d). Quantity needed : %d\n", Reor.id, Reor.quantity, new_quantity-Reor.quantity);
    }
  }

fclose(ProdPTR);
fclose(rePTR);
  printf("\n");
  save_state = 0;
}

void restock_product(){
  int new_quantity = reorder_threshold + 10;

  FILE *TempPTR = fopen("ProductList(Modified).csv", "w");
  if (TempPTR == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  
  fprintf(TempPTR, "Id,Name,Quantity,Cost,Selling Price\n");

  rewind(ProdPTR); // Reset file pointer to the beginning of the file

  // Skip the first line (header) by reading and discarding it
  fscanf(ProdPTR, "%*[^\n]\n");

  while (fscanf(ProdPTR, "%[^,],%[^,],%d,%d,%d\n", Reor.id, Reor.name, &Reor.quantity, &Reor.cost, &Reor.selling_price) == 5) {
    if(Reor.quantity >= reorder_threshold){
    fprintf(TempPTR, "%s,%s,%d,%d,%d\n", Reor.id, Reor.name, Reor.quantity, Reor.cost, Reor.selling_price);
    }else if(Reor.quantity < reorder_threshold){
      fprintf(TempPTR, "%s,%s,%d,%d,%d\n", Reor.id, Reor.name, new_quantity, Reor.cost, Reor.selling_price);
    }
  }

  fclose(TempPTR);
  remove("ToReorder.txt");
  printf("Restock complete.\n");
  fclose(ProdPTR);
  printf("\n");
  save_state = 0;
}
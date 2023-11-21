#include "Login.h"
#include "view_product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product {
  int id;
  char name[50];
  int quantity;
  float price;
};
FILE *ProdPTR;

void sold_product() {
  // printf("Press Any Key to go back.");
  // getch();
}

void view_product() {
  ProdPTR = fopen("ProductList.csv", "r");

  char List[50];
  while (fgets(List, 50, ProdPTR)) {
    printf("%s", List);
  }

  fclose(ProdPTR);
}

void reorder_product() {
  // Implement function
}

int remove_product() {
  FILE *TempPtr;
  char line[100], nameToDelete[50];
  int found = 0;

  // Open the input file
  ProdPTR = fopen("ProductList.csv", "r");

  if (ProdPTR == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  // Open the output file
  TempPtr = fopen("Temp.csv", "w");

  if (TempPtr == NULL) {
    perror("Error opening file");
    fclose(ProdPTR);
    return EXIT_FAILURE;
  }

  // Get the name to delete
  printf("Enter the name to delete: ");
  fgets(nameToDelete, sizeof(nameToDelete), stdin);
  nameToDelete[strcspn(nameToDelete, "\n")] =
      '\0'; // Remove the newline character

  // Read the file line by line
  while (fgets(line, sizeof(line), ProdPTR) != NULL) {
    // Check if the line contains the specified name
    if (strstr(line, nameToDelete) == NULL) {
      // If not, write the line to the output file
      fputs(line, TempPtr);
    } else {
      found = 1;
    }
  }

  // Close the files
  fclose(ProdPTR);
  fclose(TempPtr);

  // Remove the original file
  remove("ProductList.csv");

  // Rename the output file to the original filename
  rename("Temp.csv", "ProductList.csv");

  if (found) {
    printf("Name '%s' deleted successfully.\n", nameToDelete);
  } else {
    printf("Name '%s' not found in the file.\n", nameToDelete);
  }

  return EXIT_SUCCESS;
}

void add_product() {
  char ProdID[50], ProdName[50];
  int Quantity, Price;
  printf("Please input a Product ID : ");
  scanf("%s", ProdID);
  printf("Please input a Product Name : ");
  scanf("%s", ProdName);
  printf("Please input quantities : ");
  scanf("%d", &Quantity);
  printf("Please input a price : ");
  scanf("%d", &Price);
  ProdPTR = fopen("ProductList.csv", "a");
  fprintf(ProdPTR, "\n%s,%s,%d,%d", ProdID, ProdName, Quantity, Price);
  fclose(ProdPTR);
}

void create_binary_file() {
  // Implement function
}

void write_product_data_to_file(FILE *file, int product_count) {
  // Implement function
}

void read_product_data_from_file(FILE *file, int product_count) {
  // Implement function
}

void binary_file_handling() {
  // Implement function
}

int main() {
  remove_product();
  // managerorcashier();
  return 0;
}
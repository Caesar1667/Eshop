#include "cashier_menu.h"
#include <stdio.h>
#include <string.h>

int cashier() {
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
      cashier_sell_product();
      x = 0;
      break;
    case 2:
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
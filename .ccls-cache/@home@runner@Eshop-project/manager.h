#include <stdio.h>
#include <string.h>
#include "manager_menu.h"

void manager() {
  int x = 1;
  int choice;
  printf("--------Manager--------\n");
  while (x > 0) {
    printf("What do you want to do\n");
    printf("1. View Product\n");
    printf("2. Reorder Product\n");
    printf("3. Remove Product\n");
    printf("4. AddNew Product\n");
    printf("5. Update Inventory\n");
    printf("6. Exit\n");
    printf("Enter your choice: \n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      view_product();
      x = 0;
      break;
    case 2:
      reorder_product();
      x = 0;
      break;
    case 3:
      remove_product();
      x = 0;
      break;
    case 4:
      addnew_product();
      x = 0;
      break;
    case 5:
      UpdateInv();
      x = 0;
      break;
    case 6:
      x = 0;
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice. Please choose again.\n");
      printf("\n");
    }
  }
}
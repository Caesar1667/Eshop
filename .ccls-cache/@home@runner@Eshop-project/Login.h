#include <stdio.h>
#include <string.h>

void cashier() {
  int choice;
  printf("--------Cashier--------\n");
  printf("What do you want to do\n");
  printf("1. View Product\n");
  printf("2. Sold Product\n");
  printf("3. Exit\n");
  printf("Enter your choice: \n");
  scanf("%d", &choice);
  switch (choice) {
  case 1:

    break;
  case 2:

    break;
  case 3:
    printf("Exiting...\n");
    break;
  default:
    printf("Invalid choice. Please choose again.\n");
    printf("\n");
    cashier();
  }
}

void manager() {
  int choice;
  printf("--------Manager--------\n");
  printf("What do you want to do\n");
  printf("1. View Product\n");
  printf("2. Reorder Product\n");
  printf("3. Remove Product\n");
  printf("4. Add Product\n");
  printf("5. Exit\n");
  printf("Enter your choice: \n");
  scanf("%d", &choice);
  switch (choice) {
  case 1:

    break;
  case 2:

    break;
  case 3:

    break;
  case 4:

    break;
  case 5:
    printf("Exiting...\n");
    break;
  default:
    printf("Invalid choice. Please choose again.\n");
    printf("\n");

    manager();
  }
}

void managerlogin() {
  int id, attempts = 3;
  char upassword[50];
  const char *password = "Admin";
  printf("-----ManagerLogin-----\n");
  while (attempts > 0) {
    printf("Please type your Id:\n");
    scanf("%d", &id);

    if (id == 6600) {
      printf("Please type your Password:\n");
      scanf("%s", upassword);
      if (strcmp(upassword, password) == 0) {
        manager();
        return;
      }
    }

    attempts--;
    printf("Invalid credentials. %d attempts remaining.\n", attempts);

    if (attempts == 0) {
      printf("Login failed. Exiting...\n");
      return;
    }
  }
}

void cashierlogin() {
  int id, attempts = 3;
  char upassword[50];
  const char *password = "Worker";
  printf("-----CashierLogin-----\n");
  while (attempts > 0) {
    printf("Please type your Id:\n");
    scanf("%d", &id);

    if (id > 6600) {
      printf("Please type your Password:\n");
      scanf("%s", upassword);
      if (strcmp(upassword, password) == 0) {
        cashier();
        return;
      }
    }

    attempts--;
    printf("Invalid credentials. %d attempts remaining.\n", attempts);

    if (attempts == 0) {
      printf("Login failed. Exiting...\n");
      return;
    }
  }
}

void managerorcashier() {
  int choice;
  printf("-----Welcome-----\n");
  printf("What role do you want to login\n");
  printf("1. Manager\n");
  printf("2. Cashier\n");
  printf("3. Exit\n");
  printf("Enter your choice: \n");
  scanf("%d", &choice);
  switch (choice) {
  case 1:
    managerlogin();
    break;
  case 2:
    cashierlogin();
    break;
  case 3:
    printf("Exiting...\n");
    break;
  default:
    printf("Invalid choice. Please choose again.\n");
    printf("\n");
    managerorcashier();
  }
}

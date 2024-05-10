#include "manager_menu.h"
#include "cashier_menu.h"
#include <stdio.h>
#include <string.h>


//This function use to Login in as manager role, To login you need ID and Password. And you have 3 attempts, once you login successfully you will be in the manager menu//
void managerlogin() {
  int id, attempts = 3;
  char upassword[50];
  const char *password = "Admin";
  printf("-----ManagerLogin-----\n");
  while (attempts > 0) {
    printf("Please type your Id:\n");
    scanf("%d", &id);
    clearBuffer();
    printf("Please type your Password:\n");
    scanf("%s", upassword);
    clearBuffer();
    if (id == 6600) {
      if (strcmp(upassword, password) == 0) {
        printf("Login successful\n\n");
        manager();
        return;
      }
    }

    attempts--;
    printf("Worng id or password,Pls Try again. %d attempts remaining.\n",
           attempts);

    if (attempts == 0) {
      printf("Login failed. Exiting...\n");
      return;
    }
  }
}

//This function use to Login in as cashier role, To login you need ID and Password. And you have 3 attempts, once you login successfully you will be in the cashier menu//
void cashierlogin() {
  int id, attempts = 3;
  char upassword[50];
  const char *password = "Worker";
  printf("-----CashierLogin-----\n");
  while (attempts > 0) {
    printf("Please type your Id:\n");
    scanf("%d", &id);
    clearBuffer();
    printf("Please type your Password:\n");
    scanf("%s", upassword);
    clearBuffer();
    if (id > 6600) {
      if (strcmp(upassword, password) == 0) {
        printf("Login successful\n\n");
        cashier();
        return;
      }
    }

    attempts--;
    printf("Worng id or password,Pls Try again. %d attempts remaining.\n",
           attempts);

    if (attempts == 0) {
      printf("Login failed. Exiting...\n");
      return;
    }
  }
}

//This function is used to let the user choose the login status.//
void managerorcashier() {
  int choice;
  printf("-----Welcome-----\n");
  printf("What role do you want to login\n");
  printf("1. Manager\n");
  printf("2. Cashier\n");
  printf("3. Exit\n");
  printf("Enter your choice: \n");
  scanf("%d", &choice);
  clearBuffer();
  //You can select option by input the number//
  switch (choice) {
  case 1:
    printf("\n");
    managerlogin();
    break;
  case 2:
    printf("\n");
    cashierlogin();
    break;
  case 3:
    printf("Exiting...\n");
    break;
  default:
    printf("Invalid choice. Please choose again.\n");
    printf("\n");
    managerorcashier();
    //If you input isn't in any case you will return in the selection role menu again//
  }
}

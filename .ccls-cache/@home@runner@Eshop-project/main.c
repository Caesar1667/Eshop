#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Login.h"
#include "cashier_menu.h"
#include "manager_menu.h"

int main() {
  managerorcashier();
  /*new changes as follow:
    new functions:
      -Restock
      -Binary file converter
      -Revert Change(Go back to old version)
      -Save State (Check whether the file have been saved or not)
      -Date and Time for the transaction (in ProfitFile)
      -View Profit File
    new changes:
      -Make reorder to tell you how many you need to order for certain products instead of refill the inventory.
      -Update Invetory (Basically saving file function) as a header file, because cashier also need to save changes made to the file as well.
  */

  /*Also please check if scanf() function have clear buffer or not. I already made the function.
    Example, scanf("%s", &name);
             clearBuffer();
  */

  /*Also, formatting the output taking too much time. I'm too lazy for that.
    https://stackoverflow.com/questions/276827/string-padding-in-c
    This link will help you if you want to work on it.
    In cashier_menu.h line:119 && line:125
    printf("%-*s%-*sQuantity\tCost\tSelling Price\n", 8, "ID", 19, "Name"); some reference.
  */

  /**IMPORTANT* If I (Arm) do not wake up in time, you will have to call me via Line, Instagram or Discord, or 0967307426. Please call at least 2 times. Thank you.
  */
  return 0;
}
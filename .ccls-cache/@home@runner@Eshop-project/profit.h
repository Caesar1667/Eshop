#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "publicdata.h"

float total_profit;
struct Profit{
  char Date[50];
  char Time[50];
  char ID[50];
  char Name[50];
  int Quantity;
  int profit;
  int Total_Profit;
};

int Profit_cal(int sold_quantity, struct product Product){
  struct Profit pro;
  float total_cost = sold_quantity * Product.cost;
  float total_revenue = sold_quantity * Product.selling_price;
  float profit = total_revenue - total_cost;

  ProfitPTR = fopen("ProfitFile.csv", "r+");
  if(ProfitPTR == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  char text[1000];
  char *lastLine = NULL;
  char *token;
  
  // fseek(ProfitPTR, 0, SEEK_END);
  while(fgets(text, sizeof(text), ProfitPTR) != NULL){
    lastLine = strdup(text);  
    // sscanf(text, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%lf", &total_profit);
  }

  if(lastLine != NULL){
    token = strtok(lastLine, ",");
    while(token != NULL){
     total_profit = atof(token); //find the current profit made
      token = strtok(NULL, ",");
    }
  }

  
  // fclose(ProfitPTR);

  // printf("%g", total_profit);
  // fseek(ProfitPTR, 0, SEEK_SET);
  total_profit += profit;
  
  struct tm *ptr;
  time_t t;
  t = time(NULL);
  ptr = localtime(&t);
  char time_format[50];

  strftime(time_format,50,"%x,%I:%M:%S:%p", ptr); //time for mat DD/MM/YY, hr:min:sec:am/pm.

  fprintf(ProfitPTR, "\n%s,%s,%s,%d,%.2f,%.2f", time_format, Product.id, Product.name, sold_quantity, profit, total_profit); //write the profit, continued from the last line.
  // fprintf(ProfitPTR, "Total profit: %.2f\n", total_profit);
  fclose(ProfitPTR);

  printf("Sale recorded successfully. Profit for this item: %.2f\n", profit);
  printf("Total profit: %.2f\n", total_profit);
  printf("\n");
}
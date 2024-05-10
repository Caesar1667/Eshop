#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "publicdata.h"

void SaveState(void (*f)(), void (*g)()){
  char l[1];
  if(save_state){
    f();
  }else{
    printf("You have unsaved changes.\n Are you sure you want to continue? This will discard changes you made. (Y/N) : ");
    scanf("%c", l);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    switch(l[0]){
      case 'Y':
        f();
        break;
      case 'y':
        f();
        break;
      case 'N':
        g();
        break;
      case 'n':
        g();
        break;
      default:
        printf("Invalid input. Please Try again\n");
        SaveState(f, g);
        break;
    }
    }
  }
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "dataTypes.h"
#include "files.h"
#include "userInteraction.h"
#include "utils.h"


int iniciar(){
  setlocale(LC_ALL, "Portuguese_Brasil");
  setlocale (LC_CTYPE, "pt_BR.UTF-8");
  menuPrincipal();
  return 0;
}

int main(){
  return iniciar();
}
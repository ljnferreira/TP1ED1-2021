#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "dataTypes.h"
#include "files.h"
#include "utils.h"

int main(){
  setlocale(LC_ALL, "");
  setlocale(LC_CTYPE, ""); // setando o intervalo de char possivel
  char texto[] = "José AndrÉ";
  padronizaString(texto);
  printf("\n\n%s\n\n", texto);
  return 0;
}
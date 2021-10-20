#include <stdlib.h>
#include "memoryManagement.h"

int *alocaVetorInteiros(int tamanho){
  int *vetor = (int*)malloc(sizeof(int)* tamanho);
  return vetor;
}

int *realocaVetorInteiros(int *vetor, int *tamanho, int acrescimo){
  vetor = (int*)malloc(sizeof(int)* (*tamanho + acrescimo));
  *tamanho += acrescimo;
  return vetor;
}
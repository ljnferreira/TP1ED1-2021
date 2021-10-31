#include <stdlib.h>
#include "dataTypes.h"
#include "memoryManagement.h"

int *alocaVetorInteiros(int tamanho){
  int *vetor = (int*)malloc(sizeof(int)* tamanho);
  return vetor;
}

int *realocaVetorInteiros(int *vetor, int *tamanho, int acrescimo){
  vetor = (int*)realloc( vetor,sizeof(int)* (*tamanho + acrescimo));
  *tamanho += acrescimo;
  return vetor;
}

ItemCarrinho *alocaCarrinho(int tamanho){
  ItemCarrinho *carrinho = (ItemCarrinho*)malloc(sizeof(ItemCarrinho)* tamanho);
  return carrinho;
}
ItemCarrinho *aumentaCarrinho(ItemCarrinho *carrinho, int *tamanho){
  carrinho = (ItemCarrinho*)realloc( carrinho,sizeof(ItemCarrinho)* (*tamanho + 1));
  *tamanho += 1;
  return carrinho;
}

ItemCarrinho *diminuiCarrinho(ItemCarrinho *carrinho, int *tamanho){
  ItemCarrinho *aux;
  aux = (ItemCarrinho*)malloc(sizeof(ItemCarrinho)* (*tamanho - 1));
  *tamanho -= 1;
  for(int i = 0; i < *tamanho - 1; i++){
    aux[i] = carrinho[i];
  }
  carrinho = aux;
  return carrinho;
}

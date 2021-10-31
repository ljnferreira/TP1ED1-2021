#ifndef _MEMORY_MANAGEMENT_
#define _MEMORY_MANAGEMENT_

#include "dataTypes.h"
int *alocaVetorInteiros(int tamanho);
int *realocaVetorInteiros(int *vetor, int *tamanho, int acrescimo);


/**
  Aloca um vetor do tipo item carrinho de tamanho definido pelo usuario,
  retornando um ponteiro para o mesmo.
*/
ItemCarrinho *alocaCarrinho(int tamanho);

/**
  Realoca um vetor do tipo item carrinho recebendo o mesmo como parametro, alem de um ponteiro
  do tipo inteiro para que o usuario da função saiba o atual tamanho do vetor.
  Retorna o vetor com os mesmo valores do antigo acrescido de uma posiçao vazia ao final.
*/
ItemCarrinho *aumentaCarrinho(ItemCarrinho *carrinho, int *tamanho);

/**
  Realoca um vetor do tipo item carrinho recebendo o mesmo como parametro, alem de um ponteiro
  do tipo inteiro para que o usuario da função saiba o atual tamanho do vetor.
  Retorna o vetor com os mesmo valores do antigo diminuido em uma posiçao ao final, da qual se perde os dados.
*/
ItemCarrinho *diminuiCarrinho(ItemCarrinho *carrinho, int *tamanho);

#endif
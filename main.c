#include <stdio.h>
#include <string.h>
#include "dataTypes.h"
#include "files.h"

int main(){
  Produto pdt;
  FILE *produtos;
  strcpy(pdt.nome, "remedio2");
  pdt.precoUnitario = 15.50; 
  pdt.quantidadeEstoque = 0;
  printf("Hello World");
  produtos = abrirArquivo("data/Produtos.dat");
  if (produtos){
    for(int i=1; i<=10;i++){
      pdt.id = (unsigned long) i;
      if(gravarRegistroEmArquivo(&pdt, produtos))
        printf("\nGravou!\n");
    }
    
  }

  for(int i=1; i<=10;i++){
    lerRegistroEmArquivo(&pdt, produtos,i);
    printf("\nid: %ld\nnome: %s\npreço unitario: %.2f\n\n",
    pdt.id, pdt.nome, pdt.precoUnitario);    
  }
  fecharArquivo(produtos);
  
  return 0;
}
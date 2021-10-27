#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "dataTypes.h"
#include "files.h"
#include "utils.h"


int iniciar(){
  FILE *clientes;
  Cliente cliente;

  int *clientArray, tamanho = 0;

  char nome[] = "Lucas José do nascimento FErreira";

  clientes = abrirArquivo("data/Clientes.dat");

  setlocale(LC_ALL, "Portuguese_Brasil");
  setlocale (LC_CTYPE, "pt_BR.UTF-8");
  printf("Bem vindo ao programa de Gerenciamento de farmacias!");
  
  for(int i = 0; i < 4; i++){
    cliente.id = getNewIdCliente(clientes);
    strcpy(cliente.nome, "Tais");
    strcpy(cliente.cpf, "12758371669");
    strcpy(cliente.email, "ljnferreira@gmail.com");
    strcpy(cliente.telefone, "(32)99986-1427");

    gravarRegistroFinalArquivo(&cliente, clientes, sizeof(Cliente));
  }

  clientArray = findClientesByName(clientes, "Ta", &tamanho);

  if(tamanho){
    for (int i =0 ; i< tamanho; i++) {
      lerRegistroEmArquivo(&cliente, clientes, clientArray[i]);
      printf("\nposição %d° caso: %d, nome do cliente %s, id: %ld", i + 1, clientArray[i], cliente.nome, cliente.id);
    }
  }

  padronizaString(nome);

  printf("\n\n%s", nome);

  //free(clientArray);

  fecharArquivo(clientes);
  return 0;
}

int main(){
  return iniciar();
}
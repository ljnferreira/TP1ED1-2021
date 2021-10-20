#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "dataTypes.h"
#include "files.h"
#include "utils.h"

int main(){
  setlocale(LC_ALL, "");
  FILE *clientes;
  Cliente cliente;
  char nome;

  
  for (int i = 0; i < 4; i++){
    clientes = abrirArquivo("data/Clientes.dat");
    cliente.id = getNewUniqueId(clientes, sizeof(Cliente));
    strcpy(cliente.nome, "Lucas");
    strcpy(cliente.email, "ljnferreira@gmail.com");
    strcpy(cliente.telefone, "(32)99986-1427");
    strcpy(cliente.cpf, "12758371669");
    gravarRegistroFinalArquivoClientes(&cliente, clientes);
    fecharArquivo(clientes);
  }
  clientes = abrirArquivo("data/Clientes.dat");
  int *resultados;
  resultados = findClientesByName(clientes,"Luc");
  if(resultados){
    printf("O tamanho do vetor é: %ld", sizeof resultados[0]);
  }
  fseek(clientes, 0, SEEK_END);
  printf("Ftell: %ld\t sizeof: %ld\t registros: %ld\n", ftell(clientes), sizeof(Cliente), ftell(clientes)/sizeof(Cliente));
  for(int i = 0; i < ftell(clientes)/sizeof cliente; i++){
    lerRegistroEmArquivo(&cliente, clientes, i);
    printf("Id: %ld \nNome: %s \nEmail: %s\nTelefone: %s\n\n",
            cliente.id, cliente.nome, cliente.email, cliente.telefone);
  }
  
  fecharArquivo(clientes);
  return 0;
}
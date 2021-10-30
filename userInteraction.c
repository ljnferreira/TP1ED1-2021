#include <stdio.h>
#include <stdlib.h>
#include "userInteraction.h"
#include "crud.h"

void crudCliente(){
  int opcao = 0;
  do {
    limparTela();
    bemVindo();
    printf("Escolha uma das opções abaixo: \n");
    printf("1 - Cadastrar Cliente\n");
    printf("2 - Consultar Cliente\n");
    printf("3 - Alterar Cliente\n");
    printf("4 - Listar Clientes\n");
    printf("0 - Sair \n");
    scanf("%d", &opcao);
    if(opcao > 0 && opcao < 5)
    switch (opcao) {
      case 1 :
          cadastrarCliente();
          break;
        case 2:
          consultarCliente();
          break;
        case 3:
          alterarCliente();
          break;
        case 4:
          listarClientes();
          break;
    }

  }while (opcao > 0 && opcao < 5);
  
}
void crudVendedor(){
  int opcao = 0;
  do {
    limparTela();
    printf("Escolha uma das opções abaixo: \n");
    printf("1 - Cadastrar Vendedor\n");
    printf("2 - Consultar Vendedor\n");
    printf("3 - Alterar Vendedor\n");
    printf("4 - Listar Vendedores\n");
    printf("0 - Sair \n");
    scanf("%d", &opcao);
    if(opcao > 0 && opcao < 5)
    switch (opcao) {
      case 1 :
          cadastrarVendedor();
          break;
        case 2:
          consultarVendedor();
          break;
        case 3:
          alterarVendedor();
          break;
        case 4:
          listarVendedores();
          break;
    }

  }while (opcao > 0 && opcao < 5);
  
}
void crudFornecedor(){
  int opcao = 0;
  do {
    limparTela();
    printf("Escolha uma das opções abaixo: \n");
    printf("1 - Cadastrar Fornecedor\n");
    printf("2 - Consultar Fornecedor\n");
    printf("3 - Alterar Fornecedor\n");
    printf("4 - Listar Fornecedores\n");
    printf("0 - Sair \n");
    scanf("%d", &opcao);
    if(opcao > 0 && opcao < 5)
    switch (opcao) {
      case 1 :
          cadastrarFornecedor();
          break;
        case 2:
          consultarFornecedor();
          break;
        case 3:
          alterarFornecedor();
          break;
        case 4:
          listarFornecedores();
          break;
    }

  }while (opcao > 0 && opcao < 5);
  
}

void bemVindo(){
  printf("\t\t================================================================================\n");
  printf("\t\t=    Seja bem Vindo ao programa de gerenciamento da farmacia de Alvinópolis    =\n");
  printf("\t\t================================================================================\n");
}

void menuPrincipal(){
  int opcao = 0;
  limparTela();
  bemVindo();
  do{
    printf("Escolha uma das opções abaixo: \n");
    printf("1 - Gerenciar clientes \n");
    printf("2 - Gerenciar Vendedores \n");
    printf("3 - Gerenciar Fornedores \n");
    printf("4 - Cadastrar Produtos \n");
    printf("5 - Efetuar venda \n");
    printf("6 - Efetuar compra \n");
    printf("7 - Atualizar preço \n");
    printf("8 - Relatórios \n");
    printf("0 - Sair \n");
    scanf("%d", &opcao);
    if (opcao > 0 && opcao < 9){
      switch (opcao) {
        case 1 :
          crudCliente();
          break;
        case 2:
          crudVendedor();
          break;
        case 3:
          crudFornecedor();
          break;
        case 4:
          cadastrarProduto();
          break;
        case 5:
          break;
        case 6:
          break;
        case 7:
          break;
        case 8:
          break;
      }
    }
  }while(opcao > 0 && opcao < 9);
}

void limparTela(){
  system("cls||clear");
}

void pause(){
  if(PAUSE)
    system("read -p \"Pressione enter para sair\" saindo");
  else
    system("pause");
    
}

void creditos(){}
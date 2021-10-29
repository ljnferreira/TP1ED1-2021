#include <stdio.h>
#include <stdlib.h>
#include "crud.h"
#include "dataTypes.h"
#include "userInteraction.h"
#include "utils.h"
#include "files.h"

void cadastrarCliente(){
  FILE *clientes;
  Cliente cliente;
  int opcao = 1;

  clientes = abrirArquivo(CLIENTE);
  if(clientes){
    
    do {
      cliente.id = getNewUniqueId(clientes, sizeof(Cliente));
      do {
        printf("Digite o nome do cliente: ");
        setbuf(stdin, NULL);
        fgets(cliente.nome, 100, stdin);
        setbuf(stdin, NULL);
        padronizaString(cliente.nome);
      }while (!campovazio(cliente.nome));

      do {
        printf("Digite o email do cliente: ");
        setbuf(stdin, NULL);
        fgets(cliente.email, 50, stdin);
        setbuf(stdin, NULL);
        if(!validaEmail(cliente.email)){
          printf("Email inválido!\n\n");
        }
      }while (!campovazio(cliente.email) || !validaEmail(cliente.email));

      do {
        printf("Digite o CPF do cliente: ");
        setbuf(stdin, NULL);
        fgets(cliente.cpf, 12, stdin);
        setbuf(stdin, NULL);
        if(!validaCPF(cliente.cpf)){
          printf("CPF inválido!\n\n");
        }
      }while (!campovazio(cliente.cpf) || !validaCPF(cliente.cpf) ||
              (findClienteByCPF(clientes, cliente.cpf) != -1));

      do {
        printf("Digite o telefone (formato: (xx)xxxxx-xxxx ) do cliente: ");
        setbuf(stdin, NULL);
        fgets(cliente.telefone, 15, stdin);
        setbuf(stdin, NULL);
      }while (!campovazio(cliente.telefone));

      gravarRegistroFinalArquivo(&cliente, clientes, sizeof(Cliente));
      
      printf("Digite 0 para sair ou 1 para cadastrar um novo cliente: ");
      scanf("%d", &opcao);

    }while (opcao != 0);

    fecharArquivo(clientes);

  }else{
    printf("Não foi possível acessar a Base de dados, não sera possivel efetuar cadastro no momento");
  }
}

void consultarCliente(){
  FILE *clientes;
  Cliente cliente;
  int tamanho, posicao, opcao;

  limparTela();
  do {
    printf("Escolha uma opção de acordo com o menu abaixo:\n");
    printf("1 - Consulta por CPF\n");
    printf("2 - Consulta por ID\n");
    printf("3 - Consulta por prefixo do nome\n");
    printf("0 - Sair\n");
    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        printf("Digite o CPF do cliente: ");
        setbuf(stdin, NULL);
        fgets(cliente.cpf, 12, clientes);
        setbuf(stdin, NULL);
        if(validaCPF(cliente.cpf)){
          posicao = findClienteByCPF(clientes, cliente.cpf);
          if(posicao != -1){
            lerRegistroEmArquivo(&cliente, clientes, posicao);
            printf("\nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCPF: %s\n\n",
              cliente.id, cliente.nome, cliente.telefone, cliente.email, cliente.cpf);
          }else{
            printf("CPF não cadastrado!");
          }
        }else{
          printf("CPF Invalido!");
        }
        break;
      case 2:
        printf("Digite o Id do cliente: ");
        scanf("%ld", &cliente.id);
        posicao = findClienteById(clientes, cliente.id);
        if(posicao != -1){
          lerRegistroEmArquivo(&cliente, clientes, posicao);
          printf("\nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCPF: %s\n\n",
            cliente.id, cliente.nome, cliente.telefone, cliente.email, cliente.cpf);
        }else{
          printf("ID não encontrado!");
        }
        break;
      case 3:
        break;
    }
    
  }while ((opcao < 1 || opcao > 3) && opcao != 0);
  

}

void alterarCliente(){}

void listarClientes(){
  FILE *clientes;
  Cliente cliente;

  clientes = abrirArquivo(CLIENTE);

  limparTela();
  printf("Listagem de clientes: \n");

  fseek(clientes, 0, SEEK_SET);
  while (fread(&cliente, sizeof(Cliente), 1, clientes)) {
    printf("\nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCPF: %s\n\n",
              cliente.id, cliente.nome, cliente.telefone, cliente.email, cliente.cpf);
  }
  
  fecharArquivo(clientes);

  pause();

}

void cadastrarVendedor(){
  FILE *vendedores;
  Vendedor vendedor;
  int opcao = 1, cadastrado = 0, invalido = 0;

  vendedores = abrirArquivo(VENDEDOR);
  if(vendedores){
    
    do {
      vendedor.id = getNewUniqueId(vendedores, sizeof(Vendedor));
      do {
        printf("Digite o nome do vendedor: ");
        setbuf(stdin, NULL);
        fgets(vendedor.nome, 100, stdin);
        setbuf(stdin, NULL);
        padronizaString(vendedor.nome);
      }while (!campovazio(vendedor.nome));

      do {
        printf("Digite o email do vendedor: ");
        setbuf(stdin, NULL);
        fgets(vendedor.email, 50, stdin);
        setbuf(stdin, NULL);
        if(!validaEmail(vendedor.email)){
          printf("Email inválido!\n\n");
          invalido = 1;
        }
        if(isEmailCadastradoVendedor(vendedores, vendedor.email)){
          printf("Email já cadastrado para outro vendedor!\n\n");
          cadastrado = 1;

        }
      }while (!campovazio(vendedor.email) || invalido || cadastrado);

      do {
        printf("Digite o CPF do vendedor: ");
        setbuf(stdin, NULL);
        fgets(vendedor.cpf, 12, stdin);
        setbuf(stdin, NULL);
        if(!validaCPF(vendedor.cpf)){
          printf("CPF inválido!\n\n");
        }
      }while (!campovazio(vendedor.cpf) || !validaCPF(vendedor.cpf) || 
              (findVendedorByCPF(vendedores, vendedor.cpf)!= -1));

      do {
        printf("Digite o telefone (formato: (xx)xxxxx-xxxx ) do vendedor: ");
        setbuf(stdin, NULL);
        fgets(vendedor.telefone, 15, stdin);
        setbuf(stdin, NULL);
      }while (!campovazio(vendedor.telefone));

      do {
        printf("Digite a nova senha do vendedor: ");
        setbuf(stdin, NULL);
        fgets(vendedor.password, 20, stdin);
        setbuf(stdin, NULL);
      }while (!campovazio(vendedor.password));

      gravarRegistroFinalArquivo(&vendedor, vendedores, sizeof(Vendedor));
      
      printf("Digite 0 para sair ou 1 para cadastrar um novo vendedor: ");
      scanf("%d", &opcao);

    }while (opcao != 0);

    fecharArquivo(vendedores);

  }else{
    printf("Não foi possível acessar a Base de dados, não sera possivel efetuar cadastro no momento");
  }

}

void alterarVendedor(){}

void consultarVendedor(){}

void listarVendedores(){
  FILE *vendedores;
  Vendedor vendedor;

  vendedores = abrirArquivo(CLIENTE);

  limparTela();
  printf("Listagem de vendedores: \n");

  fseek(vendedores, 0, SEEK_SET);
  while (fread(&vendedor, sizeof(Cliente), 1, vendedores)) {
    printf("\nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCPF: %s\n\n",
              vendedor.id, vendedor.nome, vendedor.telefone, vendedor.email, vendedor.cpf);
  }
  
  fecharArquivo(vendedores);

  pause();
}

void cadastrarFornecedor(){
  FILE *fornecedores;
  Fornecedor fornecedor;
  int opcao = 1, cadastrado = 0, invalido = 0;

  fornecedores = abrirArquivo(FORNECEDOR);
  if(fornecedores){
    
    do {
      fornecedor.id = getNewUniqueId(fornecedores, sizeof(Vendedor));
      do {
        printf("Digite o nome do fornecedor: ");
        setbuf(stdin, NULL);
        fgets(fornecedor.nome, 100, stdin);
        setbuf(stdin, NULL);
        padronizaString(fornecedor.nome);
        cadastrado = isNomeFornecedorCadastrado(fornecedores, fornecedor.nome);
        if(cadastrado){
          printf("\nO nome já foi cadastrado para outro fornecedor!\n\n");
        }
      }while (!campovazio(fornecedor.nome) || cadastrado);
      
      cadastrado = 0;
      
      do {
        printf("Digite o email do fornecedor: ");
        setbuf(stdin, NULL);
        fgets(fornecedor.email, 50, stdin);
        setbuf(stdin, NULL);
        if(!validaEmail(fornecedor.email)){
          printf("Email inválido!\n\n");
          invalido = 1;
        }
        if(isEmailCadastradoVendedor(fornecedores, fornecedor.email)){
          printf("Email já cadastrado para outro fornecedor!\n\n");
          cadastrado = 1;

        }
      }while (!campovazio(fornecedor.email) || invalido || cadastrado);

      cadastrado = 0;
      invalido = 0;
      
      do {
        printf("Digite o CNPJ do fornecedor: ");
        setbuf(stdin, NULL);
        fgets(fornecedor.CNPJ, 15, stdin);
        setbuf(stdin, NULL);
        if(!validaCNPJ(fornecedor.CNPJ)){
          printf("CNPJ inválido!\n\n");
          invalido = 1;
        }
        if(findFornecedorByCNPJ(fornecedores, fornecedor.CNPJ)!= -1){
          printf("CNPJ Já cadastrado para outro Fornecedor!\n\n");
          cadastrado = 1; 
        }

      }while (!campovazio(fornecedor.CNPJ) || invalido || cadastrado);

      do {
        printf("Digite o telefone (formato: (xx)xxxxx-xxxx ) do fornecedor: ");
        setbuf(stdin, NULL);
        fgets(fornecedor.telefone, 15, stdin);
        setbuf(stdin, NULL);
      }while (!campovazio(fornecedor.telefone));

      gravarRegistroFinalArquivo(&fornecedor, fornecedores, sizeof(Fornecedor));
      
      printf("Digite 0 para sair ou 1 para cadastrar um novo fornecedor: ");
      scanf("%d", &opcao);

    }while (opcao != 0);

    fecharArquivo(fornecedores);

  }else{
    printf("Não foi possível acessar a Base de dados, não sera possivel efetuar cadastro no momento");
  }

}

void alterarFornecedor(){}

void consultarFornecedor(){}

void listarFornecedores(){
  FILE *fornecedores;
  Fornecedor fornecedor;

  fornecedores = abrirArquivo(CLIENTE);

  limparTela();
  printf("Listagem de fornecedores: \n");

  fseek(fornecedores, 0, SEEK_SET);
  while (fread(&fornecedor, sizeof(Cliente), 1, fornecedores)) {
    printf("\nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCNPJ: %s\n\n",
              fornecedor.id, fornecedor.nome, fornecedor.telefone, fornecedor.email, fornecedor.CNPJ);
  }
  
  fecharArquivo(fornecedores);

  pause();
}
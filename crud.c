#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud.h"
#include "dataTypes.h"
#include "memoryManagement.h"
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
  int tamanho = 0, *vetor, posicao, opcao;
  unsigned long id;
  char cpf[12], prefixo[100];

  clientes = abrirArquivo(CLIENTE);

  if (clientes) {
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
          fgets(cpf, 12, stdin);
          setbuf(stdin, NULL);
          if(validaCPF(cpf)){
            posicao = findClienteByCPF(clientes, cpf);
          }else{
            printf("CPF Invalido!\n");
          }
          break;
        case 2:
          printf("Digite o Id do cliente: ");
          scanf("%ld", &id);
          posicao = findClienteById(clientes, id);
          break;
        case 3:
          printf("Digite o prefixo do nome do cliente: ");
          setbuf(stdin, NULL);
          fgets(prefixo, 100, stdin);
          setbuf(stdin, NULL);
          retiraEnter(prefixo);
          padronizaString(prefixo);
          vetor = findClientesByName(clientes, prefixo, &tamanho);
          if(tamanho){
            for (int i = 0; i < tamanho; i++) {
              lerRegistroEmArquivo(&cliente, clientes, vetor[i], sizeof(Cliente));
              printf("\nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCPF: %s\n\n",
                    cliente.id, cliente.nome, cliente.telefone, cliente.email, cliente.cpf);
            }
          }
          break;
      }
      if(posicao != -1 && opcao !=3){
        lerRegistroEmArquivo(&cliente, clientes, posicao, sizeof(Cliente));
        printf("\nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCPF: %s\n\n",
          cliente.id, cliente.nome, cliente.telefone, cliente.email, cliente.cpf);
      }
    }while (opcao != 0);

    fecharArquivo(clientes);
  }else{
    printf("\nNão foi possivel acessar a base de dados!\n");
  }
  

}

void alterarCliente(){
  FILE *clientes;
  Cliente cliente;
  unsigned long id;
  int posicao, opcao;

  clientes = abrirArquivo(CLIENTE);
  if (clientes) {
    limparTela();
    printf("\nDigite o ID do cliente que deseja alterar: ");
    scanf("%ld", &id);
    posicao = findClienteById(clientes, id);
    if(posicao != -1){
      lerRegistroEmArquivo(&cliente, clientes, posicao, sizeof(Cliente));
      printf("Deseja alterar o nome de %s? \n1 - Sim 2 - Não: ", cliente.nome);
      scanf("%d", &opcao);
      if(opcao == 1){
        do {
          printf("Digite o novo nome do cliente: ");
          setbuf(stdin, NULL);
          fgets(cliente.nome, 100, stdin);
          setbuf(stdin, NULL);
          padronizaString(cliente.nome);
        }while (!campovazio(cliente.nome));
      }
    printf("Deseja alterar o CPF (%s)? \n1 - Sim 2 - Não: ", cliente.cpf);
    scanf("%d", &opcao);
    if(opcao == 1){
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
    }
    
    printf("Deseja alterar o email (%s)? \n1 - Sim 2 - Não: ", cliente.email);
    scanf("%d", &opcao);
    if(opcao == 1){
      do {
        printf("Digite o novo email do cliente: ");
        setbuf(stdin, NULL);
        fgets(cliente.email, 50, stdin);
        setbuf(stdin, NULL);
        if(!validaEmail(cliente.email)){
          printf("Email inválido!\n\n");
        }
      }while (!campovazio(cliente.email) || !validaEmail(cliente.email));
    }
    
    printf("Deseja alterar o telefone (%s)? \n1 - Sim 2 - Não: ", cliente.telefone);
    scanf("%d", &opcao);
    if(opcao == 1){
      do {
        printf("Digite o novo telefone (formato: (xx)xxxxx-xxxx ) do cliente: ");
        setbuf(stdin, NULL);
        setbuf(stdin, NULL);
        fgets(cliente.telefone, 15, stdin);
        setbuf(stdin, NULL);
      }while (!campovazio(cliente.telefone));
    }

    printf("Novos dados do cliente: \nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCPF: %s\n\n",
          cliente.id, cliente.nome, cliente.telefone, cliente.email, cliente.cpf);

    gravarRegistroEmArquivo(&cliente, clientes, posicao, sizeof(Cliente));

    }else{
      printf("\nRegistro não encontrado!!!\n");
    }
    fecharArquivo(clientes);
  }else{
    printf("\nNão foi possivel acessar a base de dados!\n");
  }
}

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
        setbuf(stdin, NULL);
        fgets(vendedor.telefone, 15, stdin);
        setbuf(stdin, NULL);
      }while (!campovazio(vendedor.telefone));

      do {
        printf("Digite a nova senha do vendedor: ");
        setbuf(stdin, NULL);
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

void alterarVendedor(){
  FILE *vendedores;
  Vendedor vendedor;
  unsigned long id;
  int posicao, opcao;

  vendedores = abrirArquivo(VENDEDOR);
  if (vendedores) {
    limparTela();
    printf("\nDigite o ID do vendedor que deseja alterar: ");
    scanf("%ld", &id);
    posicao = findVendedorById(vendedores, id);
    printf("posicao: %ld", id);
    if(posicao != -1){
      lerRegistroEmArquivo(&vendedor, vendedores, posicao, sizeof(Vendedor));
      printf("Deseja alterar o nome de %s? \n1 - Sim 2 - Não: ", vendedor.nome);
      scanf("%d", &opcao);
      if(opcao == 1){
        do {
          printf("Digite o novo nome do vendedor: ");
          setbuf(stdin, NULL);
          fgets(vendedor.nome, 100, stdin);
          setbuf(stdin, NULL);
          padronizaString(vendedor.nome);
        }while (!campovazio(vendedor.nome));
      }
      printf("Deseja alterar o CPF (%s)? \n1 - Sim 2 - Não: ", vendedor.cpf);
      scanf("%d", &opcao);
      if(opcao == 1){
        do {
          printf("Digite o CPF do vendedor: ");
          setbuf(stdin, NULL);
          fgets(vendedor.cpf, 12, stdin);
          setbuf(stdin, NULL);
          if(!validaCPF(vendedor.cpf)){
            printf("CPF inválido!\n\n");
          }
        }while (!campovazio(vendedor.cpf) || !validaCPF(vendedor.cpf) ||
              (findVendedorByCPF(vendedores, vendedor.cpf) != -1));
      }
      
      printf("Deseja alterar o email (%s)? \n1 - Sim 2 - Não: ", vendedor.email);
      scanf("%d", &opcao);
      if(opcao == 1){
        do {
          printf("Digite o novo email do vendedor: ");
          setbuf(stdin, NULL);
          fgets(vendedor.email, 50, stdin);
          setbuf(stdin, NULL);
          if(!validaEmail(vendedor.email)){
            printf("Email inválido!\n\n");
          }
        }while (!campovazio(vendedor.email) || !validaEmail(vendedor.email));
      }
      
      printf("Deseja alterar o telefone (%s)? \n1 - Sim 2 - Não: ", vendedor.telefone);
      scanf("%d", &opcao);
      if(opcao == 1){
        do {
          printf("Digite o novo telefone (formato: (xx)xxxxx-xxxx ) do vendedor: ");
          setbuf(stdin, NULL);
          setbuf(stdin, NULL);
          fgets(vendedor.telefone, 15, stdin);
          setbuf(stdin, NULL);
        }while (!campovazio(vendedor.telefone));
      }
      printf("Deseja alterar a senha do vendedor? \n1 - Sim 2 - Não: ");
      scanf("%d", &opcao);
      if(opcao == 1){
        do {
          printf("Digite a nova senha do vendedor: ");
          setbuf(stdin, NULL);
          fgets(vendedor.password, 20, stdin);
          setbuf(stdin, NULL);
        }while (!campovazio(vendedor.password));
      }
      printf("Novos dados do vendedor: \nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCPF: %s\n\n",
            vendedor.id, vendedor.nome, vendedor.telefone, vendedor.email, vendedor.cpf);

      gravarRegistroEmArquivo(&vendedor, vendedores, posicao, sizeof(Vendedor));

      fecharArquivo(vendedores);

    }else{
      printf("\nRegistro não encontrado!!!\n");
    }
  }else{
    printf("\nNão foi possivel acessar a base de dados!\n");
  }
}

void consultarVendedor(){
  FILE *vendedores;
  Vendedor vendedor;
  int tamanho = 0, *vetor, posicao, opcao;
  unsigned long id;
  char cpf[12], prefixo[100];

  vendedores = abrirArquivo(VENDEDOR);

  if (vendedores) {
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
          printf("Digite o CPF do vendedor: ");
          setbuf(stdin, NULL);
          fgets(cpf, 12, stdin);
          setbuf(stdin, NULL);
          if(validaCPF(cpf)){
            posicao = findVendedorByCPF(vendedores, cpf);
          }else{
            printf("CPF Invalido!\n");
          }
          break;
        case 2:
          printf("Digite o Id do vendedor: ");
          scanf("%ld", &id);
          posicao = findVendedorById(vendedores, id);
          break;
        case 3:
          printf("Digite o prefixo do nome do vendedor: ");
          setbuf(stdin, NULL);
          fgets(prefixo, 100, stdin);
          setbuf(stdin, NULL);
          retiraEnter(prefixo);
          padronizaString(prefixo);
          vetor = findVendedoresByName(vendedores, prefixo, &tamanho);
          if(tamanho){
            for (int i = 0; i < tamanho; i++) {
              lerRegistroEmArquivo(&vendedor, vendedores, vetor[i], sizeof(Vendedor));
              printf("\nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCPF: %s\n\n",
                    vendedor.id, vendedor.nome, vendedor.telefone, vendedor.email, vendedor.cpf);
            }
          }
          break;
      }
      if(posicao != -1 && opcao !=3){
        lerRegistroEmArquivo(&vendedor, vendedores, posicao, sizeof(Vendedor));
        printf("\nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCPF: %s\n\n",
          vendedor.id, vendedor.nome, vendedor.telefone, vendedor.email, vendedor.cpf);
      }
    }while (opcao != 0);

    fecharArquivo(vendedores);
  }else{
    printf("\nNão foi possivel acessar a base de dados!\n");
  }
  

}

void listarVendedores(){
  FILE *vendedores;
  Vendedor vendedor;

  vendedores = abrirArquivo(VENDEDOR);

  limparTela();
  printf("Listagem de vendedores: \n");

  fseek(vendedores, 0, SEEK_SET);
  while (fread(&vendedor, sizeof(Vendedor), 1, vendedores)) {
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
        retiraEnter(fornecedor.nome);
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

void alterarFornecedor(){
  FILE *fornecedores;
  Fornecedor fornecedor;
  unsigned long id;
  int posicao, opcao;

  fornecedores = abrirArquivo(FORNECEDOR);
  if (fornecedores) {
    limparTela();
    printf("\nDigite o ID do fornecedor que deseja alterar: ");
    scanf("%ld", &id);
    posicao = findFornecedorById(fornecedores, id);
    if(posicao != -1){
      lerRegistroEmArquivo(&fornecedor, fornecedores, posicao, sizeof(fornecedor));
      printf("Deseja alterar o nome de %s? \n1 - Sim 2 - Não: ", fornecedor.nome);
      scanf("%d", &opcao);
      if(opcao == 1){
        do {
          printf("Digite o novo nome do fornecedor: ");
          setbuf(stdin, NULL);
          fgets(fornecedor.nome, 100, stdin);
          setbuf(stdin, NULL);
          retiraEnter(fornecedor.nome);
          padronizaString(fornecedor.nome);
        }while (!campovazio(fornecedor.nome) || 
                isNomeFornecedorCadastrado(fornecedores, fornecedor.nome));
      }
    printf("Deseja alterar o CNPJ (%s)? \n1 - Sim 2 - Não: ", fornecedor.CNPJ);
    scanf("%d", &opcao);
    if(opcao == 1){
      do {
        printf("Digite o CNPJ do fornecedor: ");
        setbuf(stdin, NULL);
        fgets(fornecedor.CNPJ, 12, stdin);
        setbuf(stdin, NULL);
        if(!validaCNPJ(fornecedor.CNPJ)){
          printf("CNPJ inválido!\n\n");
        }
      }while (!campovazio(fornecedor.CNPJ) || !validaCNPJ(fornecedor.CNPJ) ||
            (findFornecedorByCNPJ(fornecedores, fornecedor.CNPJ) != -1));
    }
    
    printf("Deseja alterar o email (%s)? \n1 - Sim 2 - Não: ", fornecedor.email);
    scanf("%d", &opcao);
    if(opcao == 1){
      do {
        printf("Digite o novo email do fornecedor: ");
        setbuf(stdin, NULL);
        fgets(fornecedor.email, 50, stdin);
        setbuf(stdin, NULL);
        if(!validaEmail(fornecedor.email)){
          printf("Email inválido!\n\n");
        }
      }while (!campovazio(fornecedor.email) || !validaEmail(fornecedor.email));
    }
    
    printf("Deseja alterar o telefone (%s)? \n1 - Sim 2 - Não: ", fornecedor.telefone);
    scanf("%d", &opcao);
    if(opcao == 1){
      do {
        printf("Digite o novo telefone (formato: (xx)xxxxx-xxxx ) do fornecedor: ");
        setbuf(stdin, NULL);
        setbuf(stdin, NULL);
        fgets(fornecedor.telefone, 15, stdin);
        setbuf(stdin, NULL);
      }while (!campovazio(fornecedor.telefone));
    }

    printf("Novos dados do fornecedor: \nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCPF: %s\n\n",
          fornecedor.id, fornecedor.nome, fornecedor.telefone, fornecedor.email, fornecedor.CNPJ);

    gravarRegistroEmArquivo(&fornecedor, fornecedores, posicao, sizeof(Fornecedor));

    }else{
      printf("\nRegistro não encontrado!!!\n");
    }
    fecharArquivo(fornecedores);
  }else{
    printf("\nNão foi possivel acessar a base de dados!\n");
  }
}

void consultarFornecedor(){
  FILE *fornecedores;
  Fornecedor fornecedor;
  int tamanho = 0, *vetor, posicao, opcao;
  unsigned long id;
  char cnpj[15], prefixo[100];

  fornecedores = abrirArquivo(FORNECEDOR);

  if (fornecedores) {
    limparTela();
    do {
      printf("Escolha uma opção de acordo com o menu abaixo:\n");
      printf("1 - Consulta por CNPJ\n");
      printf("2 - Consulta por ID\n");
      printf("3 - Consulta por prefixo do nome\n");
      printf("0 - Sair\n");
      scanf("%d", &opcao);

      switch (opcao) {
        case 1:
          printf("Digite o CNPJ do fornecedor: ");
          setbuf(stdin, NULL);
          fgets(cnpj, 15, stdin);
          setbuf(stdin, NULL);
          if(validaCNPJ(cnpj)){
            posicao = findFornecedorByCNPJ(fornecedores, cnpj);
          }else{
            printf("CNPJ Invalido!\n");
          }
          break;
        case 2:
          printf("Digite o Id do fornecedor: ");
          scanf("%ld", &id);
          posicao = findFornecedorById(fornecedores, id);
          break;
        case 3:
          printf("Digite o prefixo do nome do fornecedor: ");
          setbuf(stdin, NULL);
          fgets(prefixo, 100, stdin);
          setbuf(stdin, NULL);
          retiraEnter(prefixo);
          padronizaString(prefixo);
          posicao = findFornecedorByName(fornecedores, prefixo);
          break;
      }
      if(posicao != -1){
        lerRegistroEmArquivo(&fornecedor, fornecedores, posicao, sizeof(Fornecedor));
        printf("\nId: %ld \nNome: %s \nTelefone: %s \nEmail : %s \nCNPJ: %s\n\n",
          fornecedor.id, fornecedor.nome, fornecedor.telefone, fornecedor.email, fornecedor.CNPJ);
      }
    }while (opcao != 0);

    fecharArquivo(fornecedores);
  }else{
    printf("\nNão foi possivel acessar a base de dados!\n");
  }
  

}

void listarFornecedores(){
  FILE *fornecedores;
  Fornecedor fornecedor;

  fornecedores = abrirArquivo(FORNECEDOR);

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

void cadastrarProduto(){
  FILE *produtos;
  Produto produto;
  int opcao;

  produtos  = abrirArquivo(PRODUTO);
  if(produtos){
    do {
      produto.id = getNewUniqueId(produtos, sizeof(Produto));
      produto.quantidadeEstoque = 0;
      do {
        printf("Digite o nome do produto: ");
        setbuf(stdin, NULL);
        fgets(produto.nome, 100, stdin);
        setbuf(stdin, NULL);
        padronizaString(produto.nome);
      }while (!campovazio(produto.nome));

      do{
        printf("Digite o preço unitario do produto: ");
        scanf("%f", &produto.precoUnitario);
      }while(produto.precoUnitario <= 0);

      gravarRegistroFinalArquivo(&produto, produtos, sizeof(Produto));

      printf("Deseja Sair? \n1 - Sim 2 - Não: ");
      scanf("%d", &opcao);
    }while (opcao != 1);

    fecharArquivo(produtos);
  }
}

void listarProdutos(){
  Produto produto;
  FILE *produtos;

  produtos = abrirArquivo(PRODUTO);
  printf("\t|\t Id \t|\t Nome \t|\n");
  while (fread(&produto, sizeof(Produto), 1, produtos)) {
    printf("\t|\t %ld \t|\t %s \t|\n", produto.id, produto.nome);
  }
  fecharArquivo(produtos);
}

void atualizarPreco(){
  FILE *historicoPrecos;
  FILE *produtos;
  Produto produto;
  HistoricoPreco historicoPreco;
  int valorAjuste = 0, opcao, contador = 0;
  float porcentagem = 0;
  unsigned long id;

  historicoPrecos = abrirArquivo(HISTORICO_PRECOS);
  produtos = abrirArquivo(PRODUTO);
  if(historicoPrecos && produtos){

    do{
      printf("Qual o valor (em porcentagem) do ajuste? (valor entre -100 e 100 ");
      scanf("%d", &valorAjuste);
    }while(valorAjuste < -100 && valorAjuste > 100);
    porcentagem = (1 + (float) valorAjuste/100);
    do{
      printf("O ajuste é para apenas um produto ou para todos? \n1 - somente um \n2 -todos \n opção: ");
      scanf("%d", &opcao);
    }while(opcao < 1 || opcao > 2);
    if(opcao ==1){
      printf("\t\t\tListagem de produtos: \n\n");
      printf("|\tNome \t\t|\t id \t|\n");
      fseek(produtos, 0, SEEK_SET);
      while(fread(&produto, sizeof(Produto), 1, produtos)){
        printf("|\t%s \t|\t %ld \t|\n", produto.nome, produto.id);
      }
      fseek(produtos, 0, SEEK_SET);
      printf("\n\n");
      printf("Digite o id do produto: ");
      scanf("%ld",&id);
      fseek(produtos, 0, SEEK_SET);
      while(fread(&produto, sizeof(Produto), 1, produtos)){
        if(produto.id == id){
          produto.precoUnitario = produto.precoUnitario * porcentagem;
          historicoPreco.idProduto = produto.id;
          getSystemDate(historicoPreco.data);
          historicoPreco.valor = produto.precoUnitario;
          gravarRegistroFinalArquivo(&historicoPreco, historicoPrecos, sizeof(HistoricoPreco));
          gravarRegistroEmArquivo(&produto, produtos, contador, sizeof(Produto));
        }
        contador ++;
      }
    }else{
      contador = 0;
      fseek(produtos, 0, SEEK_SET);
      while(fread(&produto, sizeof(Produto), 1, produtos)){
        produto.precoUnitario = produto.precoUnitario * porcentagem; 
        historicoPreco.idProduto = produto.id;
        getSystemDate(historicoPreco.data);
        historicoPreco.valor = produto.precoUnitario;
        gravarRegistroFinalArquivo(&historicoPreco, historicoPrecos, sizeof(HistoricoPreco));
        gravarRegistroEmArquivo(&produto, produtos, contador, sizeof(Produto)); 
        contador ++;
      }
    }

    printf("\t\t\tListagem de produtos com novos preços: \n\n");
    printf("|\t\tNome \t\t|\t id \t| \t preço unitário |\n");
    fseek(produtos, 0, SEEK_SET);
    while(fread(&produto, sizeof(Produto), 1, produtos)){
      printf("|\t%s \t|\t %ld \t|\t %.2f|\n", produto.nome, produto.id, produto.precoUnitario);
    }
    pause();
    fecharArquivo(produtos);
    fecharArquivo(historicoPrecos);
  }
}


void efetuarCompra(){
  FILE *produtos, *fornecedores, *notasCompra, *itensNotaCompra;
  Produto produto;
  Fornecedor fornecedor;
  NotaCompra notaCompra;
  ItemNotaCompra itemNotaCompra;
  ItemCarrinho *carrinho, item;

  produtos = abrirArquivo(PRODUTO); 
  fornecedores = abrirArquivo(FORNECEDOR); 
  notasCompra = abrirArquivo(NOTA_COMPRA);

  int tamanho = 1, contador = 0, opcao, quantidade, posicao;
  unsigned long id;
  float totalNota = 0;
  carrinho = alocaCarrinho(tamanho);
  
  do {
    printf("Para efetuar uma compra escolha o fornecedor de acordo com a tabela abaixo:");
    listarFornecedores();
    printf("Digite o id do fornecedor: ");
    scanf("%ld", &id);
  }while (findFornecedorById(fornecedores, id) == -1);

  notaCompra.idFornecedor = id;
  notaCompra.id = getNewUniqueId(notasCompra, sizeof(NotaCompra));

  getSystemDate(notaCompra.dataCompra);

  do{
    do {
      limparTela();
      listarProdutos();
      printf("Digite o Id do produto que deseja adicionar: ");
      scanf("%ld", &id);
    }while (findProdutoById(produtos, id) == -1);

    do{
      printf("Digite a quantidade (deve ser um valor maior que zero) do produto: ");
      scanf("%d", &quantidade);
    }while(quantidade <= 0);

    do{
      printf("Digite o valor unitario do produto: ");
      scanf("%f", &item.valorUnitario);
    }while(item.valorUnitario <= 0);

    item.quantidade = quantidade;
    item.idProduto = id;
    
    if(contador == tamanho){
      carrinho = aumentaCarrinho(carrinho, &tamanho);
    }

    carrinho[contador] = item;
    contador++;

    printf("Deseja comprar mais um produto? \n1 - Sim 2 - Não");
    scanf("%d", &opcao);
    
  }while(opcao ==1);

  for(int i = 0; i < contador; i++){
    itensNotaCompra = abrirArquivo(ITEM_NOTA_COMPRA);
    
    itemNotaCompra.idNotaCompra = notaCompra.id;
    itemNotaCompra.id = getNewUniqueId(itensNotaCompra, sizeof(ItemNotaCompra));
    itemNotaCompra.quantidade = carrinho[i].quantidade;
    itemNotaCompra.idProduto = carrinho[i].idProduto;
    itemNotaCompra.valorUnitario = carrinho[i].valorUnitario;
    totalNota += itemNotaCompra.valorUnitario * itemNotaCompra.quantidade;

    gravarRegistroFinalArquivo(&itemNotaCompra, itensNotaCompra, sizeof(ItemNotaCompra));

    posicao = findProdutoById(produtos, item.idProduto);
    lerRegistroEmArquivo(&produto, produtos, posicao, sizeof(Produto));
    produto.quantidadeEstoque += carrinho[i].quantidade;
    gravarRegistroEmArquivo(&produto, produtos, posicao, sizeof(Produto));

    fecharArquivo(itensNotaCompra);
  }

  notaCompra.valorTotal = totalNota;
  gravarRegistroFinalArquivo(&notaCompra, notasCompra, sizeof(NotaCompra));
  
  fecharArquivo(produtos);
  fecharArquivo(fornecedores);
  fecharArquivo(notasCompra);
  
}

void efetuarVenda(){
  FILE *produtos, *clientes, *notasFiscais, *itensNotaFiscal;
  Produto produto;
  Cliente cliente;
  NotaFiscal notaFiscal;
  ItemNotaFiscal itemNotaFiscal;
  ItemCarrinho *carrinho, item;

  produtos = abrirArquivo(PRODUTO); 
  clientes = abrirArquivo(CLIENTE); 
  notasFiscais = abrirArquivo(NOTA_FISCAL);

  int tamanho = 1, contador = 0, opcao, quantidade, posicao;
  unsigned long id;
  float totalNota = 0;
  carrinho = alocaCarrinho(tamanho);
  
  do {
    printf("Para efetuar uma venda escolha o Cliente de acordo com a tabela abaixo:");
    listarClientes();
    printf("Digite o id do cliente: ");
    scanf("%ld", &id);
  }while (findClienteById(clientes, id) == -1);

  notaFiscal.idCliente = id;
  notaFiscal.id = getNewUniqueId(notasFiscais, sizeof(NotaFiscal));

  getSystemDate(notaFiscal.dataCompra);

  do{
    do {
      limparTela();
      listarProdutos();
      printf("Digite o Id do produto que deseja adicionar: ");
      scanf("%ld", &id);
    }while (findProdutoById(produtos, id) == -1);

    posicao = findProdutoById(produtos, id);
    lerRegistroEmArquivo(&produto, produtos, posicao, sizeof(Produto));

    do{
      printf("Digite a quantidade (max: %d) do produto: ", produto.quantidadeEstoque);
      scanf("%d", &quantidade);
    }while(quantidade <= 0 || quantidade > produto.quantidadeEstoque);

    item.quantidade = quantidade;
    item.idProduto = id;
    
    if(contador == tamanho){
      carrinho = aumentaCarrinho(carrinho, &tamanho);
    }

    carrinho[contador] = item;
    contador++;

    printf("Deseja comprar mais um produto? \n1 - Sim 2 - Não ");
    scanf("%d", &opcao);
    
  }while(opcao ==1);

  for(int i = 0; i < contador; i++){
    itensNotaFiscal = abrirArquivo(ITEM_NOTA_FISCAL);
    
    posicao = findProdutoById(produtos, item.idProduto);
    lerRegistroEmArquivo(&produto, produtos, posicao, sizeof(Produto));
    produto.quantidadeEstoque -= carrinho[i].quantidade;
    gravarRegistroEmArquivo(&produto, produtos, posicao, sizeof(Produto));

    carrinho[i].valorUnitario = produto.precoUnitario;

    itemNotaFiscal.idNotaFiscal = notaFiscal.id;
    itemNotaFiscal.id = getNewUniqueId(itensNotaFiscal, sizeof(ItemNotaFiscal));
    itemNotaFiscal.quantidade = carrinho[i].quantidade;
    itemNotaFiscal.idProduto = carrinho[i].idProduto;
    itemNotaFiscal.valorVenda = carrinho[i].valorUnitario;
    totalNota += itemNotaFiscal.valorVenda * itemNotaFiscal.quantidade;

    gravarRegistroFinalArquivo(&itemNotaFiscal, itensNotaFiscal, sizeof(itemNotaFiscal));

    fecharArquivo(itensNotaFiscal);
  }

  notaFiscal.valorTotal = totalNota;
  
  gravarRegistroFinalArquivo(&notaFiscal, notasFiscais, sizeof(notaFiscal));
  
  fecharArquivo(produtos);
  fecharArquivo(clientes);
  fecharArquivo(notasFiscais);

  printf("Valor total da compra: %.2f", totalNota);

  pause();
  
}
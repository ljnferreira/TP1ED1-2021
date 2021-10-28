#include <stdio.h>
#include <string.h>
#include "files.h"
#include "dataTypes.h"
#include "memoryManagement.h"

FILE *abrirArquivo(char location[]){
  FILE *file;
  file = fopen(location, "rb+");
  if(!file){
    file = fopen(location, "wb+");
  }
  if (file){
    return file;
  }else{
    return NULL;
  }
  
}
int fecharArquivo(FILE *file){
  fclose(file);
}

int gravarRegistroFinalArquivo(void *data, FILE *file, unsigned long size){
  fseek(file, 0, SEEK_END);
  return fwrite(data, size, 1, file);
}

int gravarRegistroEmArquivo(void *data, FILE *file, int posicao, unsigned long size){
  fseek(file, posicao * size, SEEK_SET);
  return fwrite(data, size, 1, file);
}
void lerRegistroEmArquivo(void *data, FILE *file, int position){
  fseek(file, position * sizeof data, SEEK_SET);
  fread(data, sizeof(data), 1, file);
}

unsigned long getNewUniqueId(FILE *file, unsigned long sizeOfRegister){
  unsigned long int tamanho; 
  fseek(file, 0, SEEK_END);
  tamanho = ftell(file);
  return (tamanho / sizeOfRegister) + 1; 
}

int findClienteById(FILE *file, unsigned long id){
  Cliente cliente;
  int tamanho, posicao = -1;
  fseek(file, 0, SEEK_END);
  tamanho = ftell(file) / sizeof (Cliente);
  for(int i = 0; i < tamanho; i++){
    fread(&cliente, sizeof(Cliente), 1, file);
    if(cliente.id == id){
      posicao = i;
    }
  }
  return posicao;
}
int findClienteByCPF(FILE *file, char *cpf){
  Cliente cliente;
  int tamanho, posicao = -1;
  fseek(file, 0, SEEK_END);
  tamanho = ftell(file) / sizeof (Cliente);
  for(int i = 0; i < tamanho; i++){
    fread(&cliente, sizeof(Cliente), 1, file);
    if(!strcmp(cliente.cpf, cpf)){
      posicao = i;
    }
  }
  return posicao;
}

/**
 * Recebe como parametro o arquivo e o texto a ser procurado, além de um
 * ponteiro para armazenar o tamanho do vetor
 * e retorna um array de inteiros com a posição de cada ocorrencia
 * do texto entre os registros. Após uso do array deve-se usar
 * a função free da biblioteca stdlib para liberar a memoria alocada.
*/
int *findClientesByName(FILE *file, char *name, int *tamanho){
  Cliente cliente;
  int tamanhoArquivo, posicao = -1, tamanhoVetor = 1, qtdRegistros = 0;
  int *vetor = alocaVetorInteiros(tamanhoVetor);
  fseek(file, 0, SEEK_END);
  tamanhoArquivo = ftell(file) / sizeof(Cliente);
  fseek(file, 0, SEEK_SET);
  for(int i = 0; i < tamanhoArquivo; i++){
    fread(&cliente, sizeof(Cliente), 1, file);
    if(strstr(cliente.nome, name)){
      if(qtdRegistros == 0){
        vetor[qtdRegistros] = i;
        qtdRegistros++;
      }else{
        vetor = realocaVetorInteiros(vetor, &tamanhoVetor, 1);
        vetor[qtdRegistros] = i;
        qtdRegistros ++;
      }
    }
  }// percorre todo o arquivo
  *tamanho = qtdRegistros;
  if(qtdRegistros == 0){
    return NULL;
  }else
    return vetor;
}

int findVendedorById(FILE *file, unsigned long id){
  Vendedor vendedor;
  int tamanho, posicao = -1;
  fseek(file, 0, SEEK_END);
  tamanho = ftell(file) / sizeof (Vendedor);
  for(int i = 0; i < tamanho; i++){
    fread(&vendedor, sizeof(Vendedor), 1, file);
    if(vendedor.id == id){
      posicao = i;
    }
  }
  return posicao;
}
int findVendedorByCPF(FILE *file, char *cpf){
  Vendedor vendedor;
  int tamanho, posicao = -1;
  fseek(file, 0, SEEK_END);
  tamanho = ftell(file) / sizeof (Vendedor);
  for(int i = 0; i < tamanho; i++){
    fread(&vendedor, sizeof(Vendedor), 1, file);
    if(!strcmp(vendedor.cpf,cpf)){
      posicao = i;
    }
  }
  return posicao;
}

/**
 * Recebe como parametro o arquivo e o texto a ser procurado, além de um
 * ponteiro para armazenar o tamanho do vetor
 * e retorna um array de inteiros com a posição de cada ocorrencia
 * do texto entre os registros. Após uso do array deve-se usar
 * a função free da biblioteca stdlib para liberar a memoria alocada.
*/
int *findVendedoresByName(FILE *file, char *name, int *tamanho){
  Vendedor vendedor;
  int tamanhoArquivo, posicao = -1, tamanhoVetor = 1, qtdRegistros = 0;
  int *vetor = alocaVetorInteiros(tamanhoVetor);
  fseek(file, 0, SEEK_END);
  tamanhoArquivo = ftell(file) / sizeof(Vendedor);
  fseek(file, 0, SEEK_SET);
  for(int i = 0; i < tamanhoArquivo; i++){
    fread(&vendedor, sizeof(Vendedor), 1, file);
    if(strstr(vendedor.nome, name)){
      if(qtdRegistros == 0){
        vetor[qtdRegistros] = i;
        qtdRegistros++;
      }else{
        vetor = realocaVetorInteiros(vetor, &tamanhoVetor, 1);
        vetor[qtdRegistros] = i;
        qtdRegistros ++;
      }
    }
  }// percorre todo o arquivo
  *tamanho = qtdRegistros;
  if(qtdRegistros == 0){
    return NULL;
  }else
    return vetor;
}

int findFornecedorById(FILE *file, unsigned long id){
  Fornecedor fornecedor;
  int tamanho, posicao = -1;
  fseek(file, 0, SEEK_END);
  tamanho = ftell(file) / sizeof (Fornecedor);
  for(int i = 0; i < tamanho; i++){
    fread(&fornecedor, sizeof(Fornecedor), 1, file);
    if(fornecedor.id == id){
      posicao = i;
    }
  }
  return posicao;
}
int findFornecedorByCNPJ(FILE *file, char *cnpj){
  Fornecedor fornecedor;
  int tamanho, posicao = -1;
  fseek(file, 0, SEEK_END);
  tamanho = ftell(file) / sizeof (Fornecedor);
  for(int i = 0; i < tamanho; i++){
    fread(&fornecedor, sizeof(Fornecedor), 1, file);
    if(!strcmp(fornecedor.CNPJ, cnpj)){
      posicao = i;
    }
  }
  return posicao;
}

/**
 * Recebe como parametro o arquivo e o texto a ser procurado, além de um
 * ponteiro para armazenar o tamanho do vetor
 * e retorna um array de inteiros com a posição de cada ocorrencia
 * do texto entre os registros. Após uso do array deve-se usar
 * a função free da biblioteca stdlib para liberar a memoria alocada.
*/
int *findFornecedoresByName(FILE *file, char *name, int *tamanho){
  Fornecedor fornecedor;
  int tamanhoArquivo, posicao = -1, tamanhoVetor = 1, qtdRegistros = 0;
  int *vetor = alocaVetorInteiros(tamanhoVetor);
  fseek(file, 0, SEEK_END);
  tamanhoArquivo = ftell(file) / sizeof(Fornecedor);
  fseek(file, 0, SEEK_SET);
  for(int i = 0; i < tamanhoArquivo; i++){
    fread(&fornecedor, sizeof(Fornecedor), 1, file);
    if(strstr(fornecedor.nome, name)){
      if(qtdRegistros == 0){
        vetor[qtdRegistros] = i;
        qtdRegistros++;
      }else{
        vetor = realocaVetorInteiros(vetor, &tamanhoVetor, 1);
        vetor[qtdRegistros] = i;
        qtdRegistros ++;
      }
    }
  }// percorre todo o arquivo
  *tamanho = qtdRegistros;
  if(qtdRegistros == 0){
    return NULL;
  }else
    return vetor;
}

int findNotaFiscalById(FILE *file, unsigned long id){
  NotaFiscal notaFiscal;
  int tamanho, posicao = -1;
  fseek(file, 0, SEEK_END);
  tamanho = ftell(file) / sizeof (NotaFiscal);
  for(int i = 0; i < tamanho; i++){
    fread(&notaFiscal, sizeof(NotaFiscal), 1, file);
    if(notaFiscal.id == id){
      posicao = i;
    }
  }
  return posicao;
}
int findNotaCompraById(FILE *file, unsigned long id){
  NotaCompra notaCompra;
  int tamanho, posicao = -1;
  fseek(file, 0, SEEK_END);
  tamanho = ftell(file) / sizeof (NotaCompra);
  for(int i = 0; i < tamanho; i++){
    fread(&notaCompra, sizeof(NotaCompra), 1, file);
    if(notaCompra.id == id){
      posicao = i;
    }
  }
  return posicao;
}

int findItemNotaCompraById(FILE *file, unsigned long id){
  ItemNotaCompra itemNotaCompra;
  int tamanho, posicao = -1;
  fseek(file, 0, SEEK_END);
  tamanho = ftell(file) / sizeof (ItemNotaCompra);
  for(int i = 0; i < tamanho; i++){
    fread(&itemNotaCompra, sizeof(ItemNotaCompra), 1, file);
    if(itemNotaCompra.id == id){
      posicao = i;
    }
  }
  return posicao;
}


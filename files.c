#include <stdio.h>
#include <string.h>
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

int gravarRegistroFinalArquivo(void *data, FILE *file){
  fseek(file, 0, SEEK_END);
  return fwrite(data, sizeof(data), 1, file);
}

int gravarRegistroFinalArquivoClientes(Cliente *cliente, FILE *file){
  fseek(file, 0, SEEK_END);
  return fwrite(cliente, sizeof(Cliente), 1, file);
}

int gravarRegistroEmArquivo(void *data, FILE *file, int posicao){
  fseek(file, posicao * sizeof(data), SEEK_SET);
  return fwrite(data, sizeof(data), 1, file);
}
void lerRegistroEmArquivo(void *data, FILE *file, int position){
  fseek(file, position * sizeof data, SEEK_SET);
  fread(data, sizeof(data), 1, file);
}

unsigned long getNewUniqueId(FILE *file, int sizeOfRegister){
  unsigned long id;
  fseek(file, 0, SEEK_END);
  id = (unsigned long) ftell(file) / sizeOfRegister + 1;
  return id; 
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
 * Recebe como parametro o arquivo e o texto a ser procurado
 * e retorna um array de inteiros com a posição de cada ocorrencia
 * do texto entre os registros. Após uso do array deve-se usar
 * a função free da biblioteca stdlib para liberar a memoria alocada.
*/
int *findClientesByName(FILE *file, char *name){
  Cliente cliente;
  int tamanho, posicao = -1, tamanhoVetor = 1, qtdRegistros = 0;
  int *vetor = alocaVetorInteiros(tamanhoVetor);
  fseek(file, 0, SEEK_END);
  tamanho = ftell(file)/sizeof(Cliente);
  fseek(file, 0, SEEK_SET);
  printf("tamanho do arquivo: %d\n", tamanho);
  for(int i = 0; i < tamanho; i++){
    fread(&cliente, sizeof(Cliente), 1, file);
    printf("Nome do cliente atual: %s\n",cliente.nome);
    if(strstr(cliente.cpf, name)){
      if(qtdRegistros == 0){
        vetor[qtdRegistros] = i;
        qtdRegistros++;
      }else{
        vetor = realocaVetorInteiros(vetor, &tamanhoVetor, 1);
        vetor[qtdRegistros] = i;
      }
    }
  }// percorre todo o arquivo
  printf("Numero de registros encontrados: %d\n", qtdRegistros);
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
int findVendedorByCPF(FILE *file, char *cpf);
int findVendedorByName(FILE *file, char *name);

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
int findFornecedorByCNPJ(FILE *file, char *cnpj);
int findProdutoByName(FILE *file, char *name);

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


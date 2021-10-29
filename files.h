#ifndef _FILES_H_
#define _FILES_H_

#include <stdio.h>
#include "dataTypes.h"

#define CLIENTE "data/Clientes.dat"
#define VENDEDOR "data/Vendedores.dat"
#define FORNECEDOR "data/Fornecedores.dat"

FILE *abrirArquivo(char location[]);
int fecharArquivo(FILE *file);

int gravarRegistroFinalArquivo(void *data, FILE *file, unsigned long size);
int gravarRegistroEmArquivo(void *data, FILE *file, int posicao,unsigned long size);
void lerRegistroEmArquivo(void *data, FILE *file, int position);

unsigned long getNewUniqueId(FILE *file, unsigned long sizeOfRegister);

int findClienteById(FILE *file, unsigned long id);
int findClienteByCPF(FILE *file, char *cpf);
int *findClientesByName(FILE *file, char *name, int *tamanho);

int findVendedorById(FILE *file, unsigned long id);
int findVendedorByCPF(FILE *file, char *cpf);
int *findVendedoresByName(FILE *file, char *name, int *tamanho);
int isEmailCadastradoVendedor(FILE *file, char *email);

int findFornecedorById(FILE *file, unsigned long id);
int findFornecedorByCNPJ(FILE *file, char *cnpj);
int *findFornecedoresByName(FILE *file, char *name, int *tamanho);
int isNomeFornecedorCadastrado(FILE *file, char * nome);

int findNotaFiscalById(FILE *file, unsigned long id);
int findNotaCompraById(FILE *file, unsigned long id);
int findItemNotaCompraById(FILE *file, unsigned long id);

#endif
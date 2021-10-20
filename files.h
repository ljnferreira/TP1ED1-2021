#ifndef _FILES_H_
#define _FILES_H_

#include <stdio.h>
#include "dataTypes.h"

FILE *abrirArquivo(char location[]);
int fecharArquivo(FILE *file);

int gravarRegistroFinalArquivo(void *data, FILE *file);
int gravarRegistroFinalArquivoClientes(Cliente *cliente, FILE *file);
int gravarRegistroEmArquivo(void *data, FILE *file, int posicao);
void lerRegistroEmArquivo(void *data, FILE *file, int position);

unsigned long getNewUniqueId(FILE *file, int sizeOfRegister);

int findClienteById(FILE *file, unsigned long id);
int findClienteByCPF(FILE *file, char *cpf);
int *findClientesByName(FILE *file, char *name);

int findVendedorById(FILE *file, unsigned long id);
int findVendedorByCPF(FILE *file, char *cpf);
int findVendedorByName(FILE *file, char *name);

int findFornecedorById(FILE *file, unsigned long id);
int findFornecedorByCNPJ(FILE *file, char *cnpj);
int findProdutoByName(FILE *file, char *name);

int findNotaFiscalById(FILE *file, unsigned long id);
int findNotaCompraById(FILE *file, unsigned long id);
int findItemNotaCompraById(FILE *file, unsigned long id);

#endif
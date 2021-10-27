#ifndef _FILES_H_
#define _FILES_H_

#include <stdio.h>
#include "dataTypes.h"

FILE *abrirArquivo(char location[]);
int fecharArquivo(FILE *file);

int gravarRegistroFinalArquivo(void *data, FILE *file, unsigned long size);
int gravarRegistroEmArquivo(void *data, FILE *file, int posicao,unsigned long size);
void lerRegistroEmArquivo(void *data, FILE *file, int position);

unsigned long getNewUniqueId(FILE *file, unsigned long sizeOfRegister);
unsigned long getNewIdCliente(FILE *file);

int findClienteById(FILE *file, unsigned long id);
int findClienteByCPF(FILE *file, char *cpf);
int *findClientesByName(FILE *file, char *name, int *tamanho);

int findVendedorById(FILE *file, unsigned long id);
int findVendedorByCPF(FILE *file, char *cpf);
int *findVendedoresByName(FILE *file, char *name, int *tamanho);

int findFornecedorById(FILE *file, unsigned long id);
int findFornecedorByCNPJ(FILE *file, char *cnpj);
int *findFornecedoresByName(FILE *file, char *name, int *tamanho);

int findNotaFiscalById(FILE *file, unsigned long id);
int findNotaCompraById(FILE *file, unsigned long id);
int findItemNotaCompraById(FILE *file, unsigned long id);

#endif
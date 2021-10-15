#include <stdio.h>

FILE *abrirArquivo(char location[]);
int fecharArquivo(FILE *file);

int gravarRegistroFinalArquivo(void *data, FILE *file);
int gravarRegistroEmArquivo(void *data, FILE *file, int posicao);
void lerRegistroEmArquivo(void *data, FILE *file, int position);

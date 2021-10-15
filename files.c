#include <stdio.h>

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

int gravarRegistroEmArquivo(void *data, FILE *file, int posicao){
  fseek(file, posicao * sizeof(data), SEEK_SET);
  return fwrite(data, sizeof(data), 1, file);
}
void lerRegistroEmArquivo(void *data, FILE *file, int position){
  fseek(file, position * sizeof(data), SEEK_SET);
  fread(data, sizeof(data), 1, file);
}


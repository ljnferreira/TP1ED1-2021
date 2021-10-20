#ifndef _UTILS_H_
#define _UTILS_H_

//Funções de validação 
int validaCPF(char *cpf);
int validaCNPJ(char *cnpj);
int validaData(char *data);
int validaEmail(char *email);

void retiraEnter(char *string);

int campovazio(char *nome);

void padronizaString(char *texto);

#endif
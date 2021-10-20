#include <string.h>
#include <ctype.h>

//Funções de validação 

/**
 * Função que verifica se um char é uma letra
*/
int isChar(char c){
  return ((c >= 'a' && c <= 'z')|| (c >= 'A' && c <= 'Z'));
}
  
/**
 * Função que verifica se um char é um numero
*/
int isDigit(const char c){
    return (c >= '0' && c <= '9');
}

int validaCPF(char *cpf){
  int i, j, digito1 = 0, digito2 = 0;
  /*verificando se o tamanho do vetor é diferente de 11, caso
  seja ele retorna 0 invalidando o cpf*/
  if(strlen(cpf) != 11)
      return 0;
  else if(!strcmp(cpf,"00000000000") || !strcmp(cpf,"11111111111") || !strcmp(cpf,"22222222222") ||
          !strcmp(cpf,"33333333333") || !strcmp(cpf,"44444444444") || !strcmp(cpf,"55555555555") ||
          !strcmp(cpf,"66666666666") || !strcmp(cpf,"77777777777") || !strcmp(cpf,"88888888888") ||
          !strcmp(cpf,"99999999999") || !strcmp(cpf,"12345678909") || !strcmp(cpf,"01234567890"))
      return 0; //se o CPF tiver todos os números iguais ou for formado por sequencias ele é inválido.
  else
  {
      // verificando digito 1---------------------------------------------------
      for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) //multiplica os números de 10 a 2 e soma os resultados dentro de digito1
          digito1 += (cpf[i]-48) * j;
      digito1 %= 11;
      if(digito1 < 2)
          digito1 = 0;
      else
          digito1 = 11 - digito1;
      if((cpf[9]-48) != digito1)
          return 0; ///se o digito 1 não for o mesmo que o da validação CPF é inválido
      else
      // verificando digito 2--------------------------------------------------
      {
          for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                  digito2 += (cpf[i]-48) * j;
      digito2 %= 11;
      if(digito2 < 2)
          digito2 = 0;
      else
          digito2 = 11 - digito2;
      if((cpf[10]-48) != digito2)
          return 0; ///se o digito 2 não for o mesmo que o da validação CPF é inválido
      }
  }
  return 1;
}
int validaCNPJ(char *cnpj){
  int mascaraPrimeiroDigito[] = {5 ,4 ,3 ,2 ,9 ,8 ,7 ,6 ,5 ,4 ,3 ,2};
  int mascaraSegundoDigito[] = {6, 5 ,4 ,3 ,2 ,9 ,8 ,7 ,6 ,5 ,4 ,3 ,2};
  int valido = 0, digitoUm, digitoDois, somatorio = 0, cnpjInt[14];
  
  if(strlen(cnpj) !=14){
    return 0;
  }

  if(!strcmp(cnpj, "00000000000000")||
    !strcmp(cnpj, "11111111111111")||
    !strcmp(cnpj, "22222222222222")||
    !strcmp(cnpj, "33333333333333")||
    !strcmp(cnpj, "44444444444444")||
    !strcmp(cnpj, "55555555555555")||
    !strcmp(cnpj, "66666666666666")||
    !strcmp(cnpj, "77777777777777")||
    !strcmp(cnpj, "88888888888888")||
    !strcmp(cnpj, "99999999999999")){
      return 0;
  }

  // percorre o vetor de char convertendo os caracteres pra inteiro e salvando
  // no vetor de inteiros
  for (int i = 0; i < strlen(cnpj); i++){
    if(isDigit(cnpj[i])){
      cnpjInt[i] = (int) cnpj[i]-48; 
    }else{
      return 0;
    }
  }

  //calculando digito 1
  for (int i = 0; i < 12; i++){
    somatorio += cnpjInt[i] * mascaraPrimeiroDigito[i];
  }
  somatorio = somatorio % 11;
  digitoUm = somatorio <= 2 ? somatorio : 11 - somatorio; 
  somatorio = 0;
  //calculando digito 2
  for (int i = 0; i < 13; i++){
    if (i == 12){ // verifica se a posicação a ser acessada é a do digito 1
      somatorio += digitoUm * mascaraSegundoDigito[i];
    }else{
      somatorio += cnpjInt[i] * mascaraSegundoDigito[i];
    }
  }
 
  somatorio = somatorio % 11;
  digitoDois = somatorio <= 2 ? somatorio : 11 - somatorio; 

  if (digitoUm == cnpjInt[12] && digitoDois == cnpjInt[13]){
    valido = 1;
  }
  return valido;
}

int validaData(char *data){
  int dia,mes,ano,n1,n2,n3;
  /* convertendo a data char para int */
  n1=(data[0]-48)*10;
  dia = n1 + (data[1]-48);
  n1=0;
  n1=(data[3]-48)*10;
  mes = n1 + (data[4]-48);
  n1=0;
  n1=(data[6]-48)*1000;
  n2=(data[7]-48)*100;
  n3=(data[8]-48)*10;
  ano = n1 + n2 + n3 +(data[9]-48);
  /*Validando a data*/
  if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1950 && ano <= 2100)){ //verifica se os numeros sao validos{
    if(ano <= 1950 && mes <= 6 && dia <= 20 )
        return 0;
    if ((dia == 29 && mes == 2) && ((ano % 4) == 0)) //verifica se o ano e bissexto
        return 1;

    if (dia <= 28 && mes == 2) //verifica o mes de feveireiro
        return 1;

    if ((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) //verifica os meses de 30 dias
        return 1;

    if ((dia <=31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)) //verifica os meses de 31 dias
        return 1;

    else
        return 0;

  }
  else
      return 0;
}
  
/**
 * Função que verifica se um email é valido
*/
int validaEmail(char *email){
  
  //verifica se o primeiro caractere é uma letra
  if (!isChar(email[0])) {
    return 0;
  }
  //variaveis para armazenar a posição do ponto e da arroba
  int arroba = -1, ponto = -1;

  //Percorre o array para descobrir a posição do ponto e da arroba
  for (int i = 0; i < strlen(email); i++) {
    if (email[i] == '@') {
      arroba = i;
    }
    else if (email[i] == '.') {
      ponto = i;
    }
  }

  // verifica se falta ponto ou arroba
  if (arroba == -1 || ponto == -1)
      return 0;

  // verifica se o ponto esta antes da arroba
  if (arroba > ponto)
      return 0;

  // verifica se o ponto esta presente no final
  return !(ponto >= (strlen(email) - 1));
}
/**
 * Essa função recebe como entrada uma string, removendo
 * o caratere de escape \n de seu final.
*/
void retiraEnter(char *string){
  if(string[strlen(string)-1]=='\n'){
    string[strlen(string)-1] = '\0';
  }
}
/**
 * Essa função recebe como entrada uma string, verificando se
 * a mesma se encontra vazia.
*/
int campovazio(char *nome){
  retiraEnter(nome);
  if(strlen(nome) == 0)
    return 0;
  return 1;
}

/**
 * Essa função recebe como entrada uma string e retira todos os acentos,
 * convertendo tbm as letras minusculas em maiusculas.
*/
void padronizaString(char *texto){
  int tamanho = strlen(texto);
  char caracterAcentuado[] =    "áàãâéèẽêíìĩîóòõôúùũûçÁÀÃÂÉÈẼÊÍÌĨÎÓÒÕÔÚÙÛŨÇ";
  char caracterNaoAcentuado[] = "aaaaeeeeiiiioooouuuucAAAAEEEEIIIIOOOOUUUUC"; 
  for (int i = 0; i < tamanho; i++){
    for (int k = 0; k < strlen(caracterNaoAcentuado); k++){
      if(texto[i] == caracterAcentuado[k+1] || texto[i] == caracterAcentuado[k*2]){ 
        texto[i] = caracterNaoAcentuado[k];
      }
    }
    texto[i] = toupper(texto[i]); //converte em letras maiusculas
  }
  
}

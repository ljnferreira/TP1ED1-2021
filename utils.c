//Funções de validação 
int validaCPF(char *cpf){
  int i, j, digito1 = 0, digito2 = 0;
  /*verificando se o tamanho do vetor é diferente de 11, caso
  seja ele retorna 0 invalidando o cpf*/
  if(strlen(cpf) != 11)
      return 0;
  else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
          (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
          (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
          (strcmp(cpf,"99999999999") == 0))
      return 0; //se o CPF tiver todos os números iguais ele é inválido.
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
int validaCNPJ(char *cnpj);

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

void retiraEnter(char *string){
  if(string[strlen(string)-1]=="\n"){
    string[strlen(string)-1] = "\0";
  }
}

int campovazio(char *nome){
    retiraEnter(nome);
    if(strlen(nome) == 0)
        return 0;
    return 1;
}

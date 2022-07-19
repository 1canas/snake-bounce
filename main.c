#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>

// Usuario acho interessante por como Global pois sera usado em diversas situações.
char usuario[15];

void Memoria();
int Menu();


int main() {
  int sair = 2, jogar = 1, iniciar;
  char creditos;
  bool running;

  running = true;

  printf("\n --------Bem-vindo ao Snake Bounce----------");

  while (running == true){
    iniciar = Menu();

  if(iniciar == jogar){
    memoria(); // AQUI CHAMAMOS A FUNÇÃO QUE NÃO POSSUI PARAMETROS E NEM RETURN, POR ISSO FICOU SO "memoria()"
    running = false;
    }
  else if(iniciar == sair){
    printf("\n Beleza ate mais!");
    running = false;
    }
  else{
    printf("\n Operacao invalida. \nApenas as opcoes (1) ou (2) sao aceitas.");
    continue;
   }
  }

  return 0;
}

 memoria() {
  /*
   Primeiramente quando criamos o MENU INICIAL(main) e o JOGO DA MEMORIA(memoria), fizemos uma "main" para cada um deles, pois não tinhamos tido a aula de modularização para criar funções,
  porém para a entrega do dia 27/06 era necessário implementar funções para melhorar o código, assim pegamos a main do jogo da memoria e criamos uma função para ela, fizemos o
  protótipo antes do MENU(main) e depois fizemos o bloco de código da função nova do jogo da memória e colamos os comandos que estavam na main original do jogo, assim criamos uma função.
   Vimos que para essa função não podia ter retorno nem parametros, pois queremos apenas que execute o jogo quando a condição no MENU for comprida.
  */

  int numeros[5], respostas[5];
  int tempo=0,contador=0, acertos=0;
  char espaco;

  setlocale(LC_ALL, "Portuguese");
  srand(time(NULL));
  /* comando para o que os números sejam
  diferentes a cada acesso*/

  /*Implementar uma Funçao com as informações do jogo a ser jogado contendo os printf's
    funçao infmorçãoMemoria(void)*/

  printf("\n Você tera 5 segundos para decorar os numeros");
  printf("\n Aperte BARRA DE ESPAÇO para começar");
    do{
    espaco = getch();
      }while(espaco!=32);
  for (contador=0;contador<5;contador++){
        numeros[contador] = (rand() % 50)+1;
    }

  tempo=5;

  do{
    system("cls");
    printf("Memorize os numeros abaixo em %d\n\n", tempo);
    tempo--;
    for (contador=0;contador<5;contador++){
            printf ("%d\t", numeros[contador]);
      }
    Sleep(1000);
    }while(tempo>0);
  system("cls");
  printf("\n\nDigite os numeros exibidos.");
    for(contador=0;contador<5;contador++){
      printf("\t%dº numero :", contador+1);
      scanf("%d", &respostas[contador]);
      /* NESSA SITUAÇÃO, CASO O USUÁRIO NÃO COLOQUE UM NÚMERO INTEIRO O JOGO QUEBRA ENTÃO ESTAMOS BUSCANDO COMANDOS OU FUNÇÕES
      PARA UTILIZAR COM UMA ESTRUTURA CONDICIONAL PARA EVITAR QUE O JOGO QUEBRE
      EX:
       if (respostas[contador] not numeric) {
        printf("\n ops, apenas numeros inteiros são aceitos.")
        continue

      }
      */
      if(respostas[contador]==numeros[contador]){
        acertos++;
      }
    } /*Implementar uma funçao para que faça o sistema como um todo tenha um tamanho mais amigável.
A ideia da funçao é adotar os numeros listados e ve se esta de acordo com os acertos descritos.
    acertoMemoria(contador;numeros;respostas)*/
  if(acertos==5){
    printf("\n\nVocê conseguiu seu bonus... Aproveite!!!");
    for(contador=0;contador<5;contador++){
      printf("%d\t", numeros[contador]);
      }
    }
    else {
    printf ("\n\nFica pra próxia camarada =D ");
        for (contador=0;contador<5;contador++){
            printf ("%d\t", numeros[contador]);
    }
  }

  int Menu()
  {
    int opcao;

    printf("\n\n Digite o nome do seu usuario: ");
    scanf("%s", usuario);

    printf("\nOk ");
    printf("%s", usuario);
    printf(". A seguir estao as opcoes: ");

    printf("\n\n (1)Jogar");
    printf("\n (2)Sair");

    printf("\n\nQual voce deseja: ");
    scanf("%d", &opcao);

    return opcao;
  }

}
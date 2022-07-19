//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//
//
//		Authors:
//		Jefferson dos Santos Felix
//		Felipe Ruiz Peixoto
//
//		With this file, you can make programs using the conio.h
//		100% compatible with Windows and Gnu/Linux systems.
//      This header needs the NCURSES library to work (libncurses-dev).
#ifndef __CONIO_H
#define __CONIO_H

#ifndef __CURSES_H
#include <curses.h>
#endif

#ifndef __NCURSES_H
#include <ncurses.h>
#endif

#undef printf
#define printf printw

#undef scanf
#define scanf scanw

#undef getch

#define BLACK         0
#define RED           1
#define GREEN         2
#define BROWN         3
#define BLUE          4
#define MAGENTA       5
#define CYAN          6
#define LIGHTGRAY     7
#define DARKGRAY      8
#define LIGHTRED      9
#define LIGHTGREEN    10
#define YELLOW        11
#define LIGHTBLUE     12
#define LIGHTMAGENTA  13
#define LIGHTCYAN     14
#define WHITE         15

// Commands supported by this file, used for initialize.
void initconio();
int endconio(void);
int clrscr(void);
int clreol(void);
int textcolor(int color);
int textbackground(int color);
int getche(void);
int getch(void);
int wherex(void);
int wherey(void);
int gotoxy(int x, int y);
int newline(void);

short cur_pair, cur_bold;
int initialized = 0;

void initconio()
{
  short f, b, p;
  initscr();
  start_color();
  cbreak();
  noecho();
  p = 1;
  for(f = 0; f < 8; f++)
    for(b = 0; b < 8; b++, p++)
      init_pair(p, f, b);
  cur_pair = 57;
  cur_bold = 0;
  color_set(cur_pair, NULL);
  attroff(A_BOLD);
  initialized = 1;
}

int endconio(void)
{
  if(initialized == 0) initconio();
  echo();
  endwin();
  initialized == 0;
  return 0;
}

int clrscr(void)
{
  if(initialized == 0) initconio();
  bkgdset(COLOR_PAIR(cur_pair));
  if(cur_bold == 0)
    attroff(A_BOLD);
  else
    attron(A_BOLD);
  clear();
  endconio();
  return 0;
}

int clreol(void)
{
  if(initialized == 0) initconio();
  int cur_x, x, y, maxx;
  color_set(cur_pair, NULL);
  getmaxyx(stdscr, y, maxx);
  cur_x = wherex();
  gotoxy(1, wherey());
  for(x = 1; x <= maxx; x++)
    printw(" ");
  gotoxy(cur_x, wherey() - 1);
  endconio();
  return 0;
}

int textcolor(int color)
{
  if(initialized == 0) initconio();
  short x, y, f, b, p = 1;
  pair_content(cur_pair, &f, &b);
  for(x = 0; x < 8; x++)
    for(y = 0; y < 8; y++, p++)
      if((x == (color%8))&&(y == b))
        cur_pair = p;
  color_set(cur_pair, NULL);
  if(color >= 8)
    cur_bold = 1;
  if(cur_bold == 0)
    attroff(A_BOLD);
  else
    attron(A_BOLD);
  endconio();
  return 0;
}

int textbackground(int color)
{
  if(initialized == 0) initconio();
  short x, y, f, b, p = 1;
  pair_content(cur_pair, &f, &b);
  for(x = 0; x < 8; x++)
    for(y = 0; y < 8; y++, p++)
      if((x == f)&&(y == (color%8)))
        cur_pair = p;
  color_set(cur_pair, NULL);
  endconio();
  return 0;
}

int getche(void)
{
  if(initialized == 0) initconio();
  int c;
  echo();
  c = wgetch(stdscr);
  endconio();
  return c;
}

int getch(void)
{
  if(initialized == 0) initconio();
  int c;
  noecho();
  c = wgetch(stdscr);
  endconio();
  return c;
}

int wherex(void)
{
  if(initialized == 0) initconio();
  int x, y;
  getyx(stdscr, y, x);
  endconio();
  return x + 1;
}

int wherey(void)
{
  if(initialized == 0) initconio();
  int x, y;
  getyx(stdscr, y, x);
  endconio();
  return y + 1;
}

int gotoxy(int x, int y)
{
  if(initialized == 0) initconio();
  move(y - 1, x - 1);
  endconio();
  return 0;
}

int newline(void)
{
  if(initialized == 0) initconio();
  gotoxy(1, wherey() + 1);
  endconio();
  return 0;
}

#endif

//		How to use:
//		Copy this file to the folder of your source codes, or to the
//		library directories of your system.
//
//		See in your source code the line: #include <conio.h>, and change it
//		to: #include "conio.h", if this file is in the directory of your
//		source codes.
//		
//		Before start using the functions of the conio.h, be sure you was
//		initialized it, because some commands need it to work. To initialize
//		you can use the commands listed in the line 57-68 of this file.
//		If you start your program with printf() or scanw() for example,
//		will make a segmentation fault.
//
//		If your program is making errors, try to use the initconio(); function
//		on the begin of the program, and endconio(); function to end it, when
//		using this file.
//
//		If it stills making errors, go to the support pages below:
//		http://www.vivaolinux.com.br/script/Conio.h-para-Linux-%28Nova-versao%29

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>

// Usuario acho interessante por como Global pois sera usado em diversas situações.


void Menu();
void Memoria();
void Snake();

int running = 1;
char usuario[15];
// SCOREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE

int main() {
  //char creditos; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  printf("\n --------Bem-vindo ao Snake Bounce----------");
  printf("\n\n Digite o nome do seu usuario: ");
    scanf("%s", usuario);

  while (running == 1){
    Menu();
    }

  return 0;
}

void Menu()
  {
    int opcao, jogar = 1, sair = 2;

    printf("\nOk ");
    printf("%s", usuario);
    printf(". A seguir estao as opcoes: ");

    printf("\n\n (1)Jogar");
    printf("\n (2)Sair");

    printf("\n\nQual voce deseja: ");
    scanf("%d", &opcao);

    if(opcao == jogar){
        Memoria(); // AQUI CHAMAMOS A FUNÇÃO QUE NÃO POSSUI PARAMETROS E NEM RETURN, POR ISSO FICOU SO "Memoria()"
        running = 0;
    }
    else if(opcao == sair){
        printf("\n Beleza ate mais!");
        running = 0;
    }
    else{
        system("clear");
        printf("\n Ops!! Operacao invalida. \nApenas as opcoes (1) ou (2) sao aceitas.");
        sleep(3000); 
        system("clear");
        // SE ESSE ELSE FOR ATIVADO, CASO O USUÁRIO PREENCHA UMA OPÇÃO NÃO RECONHECIDA PELO SISTEMA, VAI APARECER ESSA MENSAGEM NA TELA,
        // ESPERAR 3 SEGUNDOS, LIMPAR A TELA NOVAMENTE E EXECUTAR O MENU DE NOVO.

    }
}

void Snake(){



}

void Memoria() {
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
    system("clear");
    printf("Memorize os numeros abaixo em %d\n\n", tempo);
    tempo--;
    for (contador=0;contador<5;contador++){
            printf ("%d\t", numeros[contador]);
      }
    sleep(1000);
    }while(tempo>0);
  system("clear");
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


}
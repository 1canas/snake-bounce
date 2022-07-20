// libs
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include<locale.h>

// Usuario acho interessante por como Global pois sera usado em diversas situações.

// prototypes
int Memoria(void);
void Menu(void);
void Snake(void);
void RegisterScore(int score);

// globals vars
int running = 1, erro = 0;
char usuario[15];

// file
FILE *fold;


int main(void) {
  //char creditos; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  printf("\n --------Bem-vindo ao Snake Bounce----------");
  printf("\n\n Digite o nome do seu usuario: ");
  scanf("%s", usuario);

  while (running == 1){
    Menu();
    }

  return 0;
}

// utils
void RegisterScore(int score){ // UMA FUNÇÃO PARA CRIAR UM DIRETÓRIO PARA SALVAR OS DADOS DO 
    char c;
	fold = fopen("snkdata.txt", "wr");

    if (fold == NULL){
        printf("ERROR OPENING THE FILE, PLEASE RUN AGAIN...");
        running = 2;
    }
    
    c = getc(fold);
	while (c != EOF) {
		fprintf(fold, "%c", c);
		c = getc(fold);
	}
    fprintf(fold, "\n%s - ", usuario);
    fprintf(fold, "%d\n", score);
    
    fclose(fold);
}

// View events
void Menu(void){
    int opcao, jogar = 1, highscore = 2 ,sair = 3, check = -1;
    char c;

    printf("\nOk  ");
    printf("%s", usuario);
    printf(". A seguir estao as opcoes: ");

    printf("\n\n (1)Jogar");
    printf("\n (2)Highscore");
    printf("\n (3)Sair");

    printf("\n\nQual voce deseja: ");
    check = scanf("%d", &opcao);

	// menu options
    if (check == 1){
        if(opcao == jogar){
        Snake(); // AQUI CHAMAMOS A FUNÇÃO QUE NÃO POSSUI PARAMETROS E NEM RETURN, POR ISSO FICOU SO "Memoria()"
        running = 0;
        }
        else if(opcao == highscore) {
        	fold = fopen("snkdata.txt", "r");
        	
        	if (fold == NULL) {
        		printf("\nError opening the file");
        		exit(0);
			}
			
			c = getc(fold);
			while (c != EOF) {
				printf("%c", c);
				c = getc(fold);
			}
			
			fclose(fold);
		}
        else if(opcao == sair){
        printf("\n Beleza ate mais!");
        running = 0;
        }
        else{
        system("cls");
        printf("\n Ops!! Operacao invalida. \nApenas as opcoes (1) ou (2) sao aceitas.");
        Sleep(3000);
        system("cls");
        }
    }
    else if (check == 0){
        system("cls");
        printf("\n Ops!! Operacao invalida. \nApenas as opcoes (1) ou (2) sao aceitas.");
        Sleep(3000);
        system("cls");
    } // ------------------------------------------------------------------------------------------------------------------------------------
    else{
        printf("SUPER ERROR");
    }
        // SE ESSE ELSE FOR ATIVADO, CASO O USUÁRIO PREENCHA UMA OPÇÃO NÃO RECONHECIDA PELO SISTEMA, VAI APARECER ESSA MENSAGEM NA TELA,
        // ESPERAR 3 SEGUNDOS, LIMPAR A TELA NOVAMENTE E EXECUTAR O MENU DE NOVO.
}

void Snake(void){
     // setup da área
    int area[25][50], view = 32, wall = 219, foodPlace = 206, i, j;
    int snake_x = 10, snake_y = 10, snake = 219;
    int snakesize = 2, trail_x, trail_y;
    int snaketail_x[2000], snaketail_y[2000];
    int control = 0 , food = 0, food_x, food_y;
    int pontos = 0, retornobonus, gameover = 0;
    char key;

    // preencher a tela
    for (i = 0; i < 25; i++) {
        for (j = 0; j < 50; j++) {
            area[i][j] = view;
        }
    }

    // fazer as paredes horizontais
    for (j = 0; j < 50; j++) {
        area[0][j] = wall;
        area[24][j] = wall;
    }

    // fazer as paredes verticais
    for (i = 0; i < 25; i++) {
        area[i][0] = wall;
        area[i][49] = wall;
    }


    // execução do jogo
    while(1) {
        if (kbhit()) { //kbhit
            key = getch();
        }

        snaketail_y[control] = snake_y;
        snaketail_x[control] = snake_x;
        control++ ;

        //gerar o food automaticamente
        if(food == 0 ){
            food_x = 1 + rand() %48;
            food_y = 1 + rand() %23;
            area[food_y][food_x] = foodPlace ;
            food = 1;
        }


        //aumentar o tamanho da snake caso pegue o food
        if(snake_x == food_x && snake_y == food_y){
            food = 0;
            snakesize ++;
            pontos++;

        }
        else{
            trail_x = snaketail_x[control-snakesize];
            trail_y = snaketail_y[control-snakesize];
        }

        // geração da tela
        for (i = 0; i < 25; i++) {
            for (j = 0; j < 50; j++) {
                printf("%c", area[i][j]);
            }
            printf("\n");
        }
            //GAME OVER se encostar na parede
            if(snake_x == 0 || snake_x == 49 || snake_y == 0 || snake_y == 24){
            gameover =1;
            system("cls");
        }

        // posição inicial da cobra
        area[snake_y][snake_x] = snake;


        // movimentação da cobra
            if (key == 97) {//esquerda
                snake_x--;
            }

            if (key == 100) {//direita
                snake_x++;
            }

            if (key == 115) {//baixo
                snake_y++;
            }

            if (key == 119) {//cima
                snake_y--;
            }
            //não ficar rastro enquanto a snake anda
            if(snake_y != trail_y || snake_x != trail_x){
                area[trail_y][trail_x] = view;
            }

        Sleep(30);
        system("cls");
            if(gameover == 1){
            printf(" O jogo acabou, mas ainda tem a chance de duplicar seus pontos... \n\n\n");
            Sleep(3000);
            retornobonus = Memoria();
            if (retornobonus == 1){
                pontos = pontos * 2;
                gameover = 0;
            }
            else{
            	printf("Você perdeu!");
			}

            printf("seus pontos totais sao: %d\n", pontos);
            system ("pause");
            
            RegisterScore(pontos);
            break;
        }
        
	}
	Menu();
}


int Memoria(void) {
  int numeros[5], respostas[5], check = -1;
  int tempo=0,contador=0, acertos=0, retorno = 0;
  char espaco;

  setlocale(LC_ALL, "Portuguese");
  srand(time(NULL));

  printf("\n\n Voce tera 5 segundos para decorar os numeros");
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
        check = scanf("%d", &respostas[contador]);
    // VERIFICAR SE FOI DIGITADO NUMERO PARA NAO QUEBRAR O PROGRAMA

          if(respostas[contador]==numeros[contador]){
            acertos++;
          }
        }

        if(acertos==5){
            printf("\n\nVocê conseguiu seu bonus... Aproveite!!!");
            for(contador=0;contador<5;contador++){
                printf("%d\t", numeros[contador]);
            }
            retorno = 1;
        }
        else {
        printf ("\n\nFica pra próxia camarada =D ");
            for (contador=0;contador<5;contador++){
                printf ("%d\t", numeros[contador]);
            }
            retorno = 2;
        }


    return retorno;
}
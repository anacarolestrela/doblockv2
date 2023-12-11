//gcc -o doblock.exe TabIdentific.c analex.c anasint.c doblock.c Funcaux.c

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Analex.h" 
#include "anasint.h"
#include "Tabidentific.h"
#include "Funcaux.h"

  FILE *fd;
  TOKEN t;

int testaanalex() {
  FILE *fd;
  TOKEN t;
  if ((fd = fopen("expressao.dat", "r")) == NULL) {
    printf("Arquivo de entrada da expressao nao encontrado!");
   return 0;
   }
 

  printf("LINHA %d: ", contLinha);
  while (1) {
    t = AnaLex(fd);
    switch (t.cat) {
    case ID:
      printf(" <ID, %s> ", t.lexema);
      break;
    case SINAIS:
      printf(" <SINAIS, %s>", SinaisTable[t.codigo]);
      break;
    case INTCON:
      printf(" <INTCON, %d> ", t.valInt);
      break;
    case REALCON:
      printf("<REALCON, %f>", t.valReal);
      break;
    case CHARCON:
      printf(" <CHARCON, %c>", t.valChar);
      break;
    case PALAVRAS_RESERVADAS:
      printf(" <PALAVRAS_RESERVADAS, %s>", PRTable[t.codigo]);
      break;
    case STRCON:
      printf(" <STRCON, \"%s\">", t.lexema);
      break;
    case FIM_EXPR:
      printf(" <FIM_EXPR>\n");
      printf("LINHA %d: ", contLinha);
      break;
    case FIM_ARQ:
      printf(" <Fim do arquivo encontrado>\n");
    }

    if (t.cat == FIM_ARQ)
      break;
  }

  fclose(fd);

  return 0;
}

void TestaAnasint() {

  if ((fd = fopen("expressao.dat", "r")) == NULL) {
    printf("Arquivo de entrada da expressao nao encontrado!");
  }
  IniciaTabIdentif();
    if (t.cat == FIM_ARQ) {
        printf("\nFim do arquivo encontrado!\n");
    }

  Prog();

    if (t.cat==FIM_ARQ)
          printf("\nCódigo fonte sintaticamente correto!\n");
      else {
        printf("\n%d\n", t.cat);
        if(t.cat == ID){
          printf("%s\n", t.lexema);
        }else if(t.cat == PALAVRAS_RESERVADAS){
          printf("%s\n", PRTable[t.codigo]);
        }
        erro("\nErro de sintaxe!");
      }
  
    fclose(fd);
   
}

int main(){
  // printf("TESTAGEM ANALISADOR LEXICO\n");
   //testaanalex();
  printf("\nTESTAGEM ANALISADOR SINTAICO\n");
  TestaAnasint();
}

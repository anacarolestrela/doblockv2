//gcc -o doblock.exe doblock.c Analex.c
//gcc -o doblock.exe doblock.c Analex.c anasint.c


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Analex.h" 
#include "anasint.h"
#include "Tabidentific.h"

TOKEN t;
FILE *fd;

int testaanalex() {
  FILE *fd;
  TOKEN tk;
  if ((fd = fopen("expressao.dat", "r")) == NULL) {
    printf("Arquivo de entrada da expressao nao encontrado!");
   return 0;
   }
 

  printf("LINHA %d: ", contLinha);
  while (1) {
    tk = AnaLex(fd);
    switch (tk.cat) {
    case ID:
      printf(" <ID, %s> ", tk.lexema);
      break;
    case SINAIS:
      printf(" <SINAIS, %s>", SinaisTable[tk.codigo]);
      break;
    case INTCON:
      printf(" <INTCON, %d> ", tk.valInt);
      break;
    case REALCON:
      printf("<REALCON, %f>", tk.valReal);
      break;
    case CHARCON:
      printf(" <CHARCON, %c>", tk.valChar);
      break;
    case PALAVRAS_RESERVADAS:
      printf(" <PALAVRAS_RESERVADAS, %s>", PRTable[tk.codigo]);
      break;
    case STRCON:
      printf(" <STRCON, \"%s\">", tk.lexema);
      break;
    case FIM_EXPR:
      printf(" <FIM_EXPR>\n");
      printf("LINHA %d: ", contLinha);
      break;
    case FIM_ARQ:
      printf(" <Fim do arquivo encontrado>\n");
    }

    if (tk.cat == FIM_ARQ)
      break;
  }

  fclose(fd);

  return 0;
}

void TestaAnasint() {


}

int main(){

  testaanalex();

  TestaAnasint();
}
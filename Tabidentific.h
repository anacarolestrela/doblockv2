#ifndef _TAB_IDENTIFIC_
#define _TAB_IDENTIFIC_

#include <stdlib.h>
#include <stdio.h>
#include "analex.h"
#define TAM_MAX_TAB_IDENTIF 200

enum IDENTIF_CAT {VG = 0, VL, BLK, ARG};
enum ESCOPO {GLOBAL = 0, LOCAL};
enum TIPO {t_INT = 0, T_REAL, T_CHAR, T_BOOL};


typedef
  struct 
  {
      char nomeId[TAM_MAX_LEXEMA];
      int ender;
      int catId; 
      int escopo;
      int tipo;
      bool eh_const;
      bool zombie;
      bool ref;
      int parametros;
  } REG_IDENTIF;  

typedef
  struct 
  {
      int tamTab;
      REG_IDENTIF identificador[TAM_MAX_TAB_IDENTIF];
  } TAB_IDENTIF;    

extern TOKEN t;
extern TOKEN lookahead;
extern TAB_IDENTIF tabIdentif;

void IniciaTabIdentif();
int BuscaTabIdentif(char []);
int InsereTabIdentif(char [], int, int, int, bool, bool, bool, int);
//void ex(char []);

#endif
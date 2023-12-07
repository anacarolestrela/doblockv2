#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analex.h"
#include "anasint.h"
#include "Funcaux.h"

char nomeId[TAM_MAX_LEXEMA];
char blockAux[TAM_MAX_LEXEMA];
int catId;
int escopo = GLOBAL;
int tipo;
bool t_const = 0;
bool zombie = 0;
bool ref = 0;
int parametros = 0;
int tam = 0;

//prog ::= {decl_list_var} {decl_block_prot} block_main {block_def}
void Prog()
{
    catId =VG;
    while(t.cat == PALAVRAS_RESERVADAS &&( t.codigo = PR_INT || t.codigo == PR_CHAR || t.codigo == PR_FLOAT ||  
    t.codigo == PR_BOOL || t.codigo == CONST))
    {
      Decl_list_var();
    }
    if(t.cat!= PALAVRAS_RESERVADAS || t.codigo!= BLOCK)
    { 
        //Erro(1);
    }
    t = AnaLex(fd);
    while(t.cat == ID)
    {
        catId = BLK;
        strcpy(nomeId, t.lexema);
        escopo =GLOBAL;
        InsereTabIdentif(nomeId, catId, escopo, tipo, t_const, zombie, ref, parametros);
        strcpy(blockAux, t.lexema);
        t =AnaLex(fd);
        Decl_block_prot();
        if(t.cat != PALAVRAS_RESERVADAS && t.codigo  ==  BLOCK)
        {
         //Erro(2);        
        }
        t = AnaLex(fd);
    }
    escopo = GLOBAL;
    catId = BLOCK;
     //Block_main();
    catId =BLK;
    t =AnaLex(fd);
    while (t.cat ==PALAVRAS_RESERVADAS && t.codigo == BLOCK)
    {
        //Block_def();
    }
}

//decl_list_var ::= [const] tipo decl_var { , decl_var}
void Decl_list_var()
{
    if(t.cat ==PALAVRAS_RESERVADAS && t.codigo == CONST)
    {
        t = AnaLex(fd);
         t_const=1;
    }
    //Tipo();
    t = AnaLex(fd);
    //Decl_var(); 

    while (t.cat  == SINAIS && t.codigo == VIRGULA)
    {
        t = AnaLex(fd);
     //   Decl_var();
    }
}

//decl_block_prot ::= block id [with [&] tipo { [ ] } { , [&] tipo { [ ] } }]
void Decl_block_prot()
{

    if(t.cat ==PALAVRAS_RESERVADAS && t.codigo == WITH)
    {   
        catId =ARG;
        escopo = LOCAL;
        parametros = 1;
        t = AnaLex (fd);
        if(t.cat == SINAIS && t.codigo == ECOMERCIAL)
        {
            t =AnaLex(fd);
            ref = 1;
        }
        //Tipo();
        strcpy(nomeId, "");
        t =AnaLex(fd);
        while (t.cat ==SINAIS && t.codigo == ABRE_COL)
        {
          t= AnaLex(fd);
          if(t.cat !=SINAIS || t.codigo != FECHA_COL)
          {
            //Erro(2);
          }
          t =AnaLex(fd);
        }
        InsereTabIdentif(nomeId, catId, escopo, tipo, t_const, zombie, ref, parametros);
        while (t.cat ==SINAIS && t.codigo ==VIRGULA)
        {   
            parametros ++;
            ref = 0;
            t =AnaLex(fd);
            if(t.cat ==SINAIS && t.codigo == ECOMERCIAL)
            {
                ref =1;
                t =AnaLex(fd);
            }
        
           // Tipo();
            strcpy(nomeId, "");
            t =AnaLex(fd);
            while (t.cat ==SINAIS && t.codigo == ABRE_COL)
            {
            t= AnaLex(fd);
            if(t.cat !=SINAIS || t.codigo != FECHA_COL)
            {
                //Erro(2);
            }
            t =AnaLex(fd);
            }
                  InsereTabIdentif(nomeId, catId, escopo, tipo, t_const, zombie, ref, parametros);
        } 
    }
}

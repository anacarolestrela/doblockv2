#include <stdlib.h>
#include <string.h>
#include "Tabidentific.h"
#include "Funcaux.h"

void IniciaTabIdentif() 
{
    tabIdentif.tamTab = 0;
}

int BuscaTabIdentif(char nomeId[]) 
{
    int i;

    for (i=0; i<tabIdentif.tamTab; i++) 
    {
        if (!(strcmp(nomeId, tabIdentif.identificador[i].nomeId))) 
        return i;
    }
    return -1;
}

int InsereTabIdentif(char nomeId[], int catId, int escopo, int tipo, bool eh_const, bool zombie, bool ref, int parametros) 
{

    int i;
    if (tabIdentif.tamTab == TAM_MAX_TAB_IDENTIF) 
    //erro("Estouro na tabela de identificadores!");
    i = tabIdentif.tamTab;
    strcpy(tabIdentif.identificador[i].nomeId, nomeId);
    tabIdentif.identificador[i].ender = i;
    tabIdentif.identificador[i].catId = catId;
    tabIdentif.identificador[i].escopo = escopo;
    tabIdentif.identificador[i].parametros = parametros;
    tabIdentif.identificador[i].tipo = tipo;

    if(catId == BLK)
    {
     tabIdentif.identificador[i].parametros = parametros;
    }
    else
    {
        tabIdentif.identificador[i].tipo = tipo;

    }
    
    if(catId == VG || catId == VL)
    {
        tabIdentif.identificador[i].eh_const =eh_const;
    }

    if(catId == ARG)
    {
        tabIdentif.identificador[i].zombie = zombie;
        tabIdentif.identificador[i].ref = ref;
    }

    tabIdentif.tamTab++;
    return i;

}
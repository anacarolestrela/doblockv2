#include <stdlib.h>
#include <string.h>
#include "Funcaux.h"
#include "Tabidentific.h"

TAB_IDENTIF tabIdentif;

void IniciaTabIdentif() 
{
    tabIdentif.tamTab = 0;
}


int BuscaTabIdentif(char nomeId[]) {

    int i;

    for (i=0; i<tabIdentif.tamTab; i++) {
        if (!(strcmp(nomeId, tabIdentif.identificador[i].nomeId)))
        { 
            return i;
        }
    }
    return -1;
}
int InsereTabIdentif(char nomeId[], int catId, int escopo, int tipo, bool eh_const, bool zombie, bool ref, int parametros)
{
    return 0;
}
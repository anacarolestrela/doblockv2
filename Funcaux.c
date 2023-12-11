#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Analex.h"
#include "Funcaux.h"
#include "Cores.h"

// void erro(char msg[]) {
//     printf("LINHA %d: %s\n", contLinha, msg);
//     exit(1);
// }



void erro(char msg[])
{    
    printf(_YELLOW_);
    printf("LINHA %d: %s\n", contLinha, msg);
    printf(_STD_);
    exit(1);
}

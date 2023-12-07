#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Analex.h"
#include "Funcaux.h"

// void erro(char msg[]) {
//     printf("LINHA %d: %s\n", contLinha, msg);
//     exit(1);
// }

void Erro(int codigoErro)
{
  printf("ERRO DE SINTAXE NA LINHA %d: \n", contLinha);
   switch (codigoErro) {
        case 1:
            fprintf(stderr, "Erro 1: declaração de variável ou Palavra Reservada block esperados\n");
            break;
        case 2:
            fprintf(stderr, "Erro 2: Fechamento de colchete esperado\n");
            break;
        case 3:
            fprintf(stderr, "Erro 3: Declaracao de Main esperada\n");
            break;
        case 4:
          fprintf(stderr, "Erro 4: Declaracao de endblock esperada\n");
            break;
        case 5:
          fprintf(stderr, "Erro 5: Declaracao de ID esperada\n");
            break;
        case 6:
            fprintf(stderr, "Erro 6: Declaracao de constante inteira ou id esperada\n");
            break;
        case 7:
            fprintf(stderr, "delcaracao de operador relativo esperada");
            break;
        case 8:
            fprintf(stderr, "Erro 8: abre de parentese esperado\n");
            break;
        case 9:
            fprintf(stderr, "Erro 9: fecha de parentese esperado\n");
            break;
        case 10:
            fprintf(stderr, "Erro 10: downto esperado\n");
            break;
        case 11:
            fprintf(stderr, "Erro 11: endwhile esperado\n");
            break;
        case 12:
            fprintf(stderr, "Erro 12: input ou output esperado\n");
            break;
        case 13:
            fprintf(stderr, "Erro 13: endif esperado\n");
            break;
        case 14:
            fprintf(stderr, "Erro 14: comando esperado\n");
            break;         
        case 15:
            fprintf(stderr, "Erro 15: times esperado\n");
            break;  
        case 16:
            fprintf(stderr, "Erro 16: from esperado\n");
            break;               
        default:
            fprintf(stderr, "Erro desconhecido: Código %d.\n", codigoErro);
    }
        exit(EXIT_FAILURE);
}


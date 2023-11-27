#include "Analex.h"

#define TAM_LEXEMA 50
#define TAM_NUM 20

const char BLANK = ' ';
const char NEW_LINE = '\n';
const char TAB = '\t';

void error(char msg[]) {
  printf("%s\n", msg);
  exit(1);
}

int contLinha=1;

int buscaPR(char lexema[]) {
    size_t i;
    for (i = 1; i < sizeof(PRTable) / sizeof(PRTable[0]); i++) {
        if (strcmp(lexema, PRTable[i]) == 0) {
            return i;
        }
    }
    // Se não encontrou, retorne -1 ou trate "main" de maneira especial, se necessário.
    return -1;
}

TOKEN AnaLex(FILE *fd) {
  int estado;
  char lexema[TAM_LEXEMA] = "";
  int tamL = 0;
  char digitos[TAM_NUM] = "";
  int tamD = 0;

  TOKEN t;
  estado = 0;

  while (true) {
    char c = fgetc(fd);
    switch (estado) {

    case 0:
      if (isspace(c))
      {
        estado = 0;
    if (c == NEW_LINE) {
      t.cat = FIM_EXPR;
      estado = 0;
      contLinha++; // incrementa o contador de linha quando encontra '\n'
      return t;
    }
      }
      else if (isalpha(c)) {
        estado = 1;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';
      } else if (isdigit(c)) {
        estado = 2;
        digitos[tamD] = c;
        digitos[++tamD] = '\0';
      } else if (c == '+') {
        estado = 3;
        t.cat = SINAIS;
        t.codigo = ADICAO;
        return t;
      } else if (c == '-') {
        estado = 4;
        t.cat = SINAIS;
        t.codigo = SUBTRACAO;
        return t;
      } else if (c == '*') {
        estado = 5;
        t.cat = SINAIS;
        t.codigo = MULTIPLIC;
        return t;
      } else if (c == '/') {
        estado = 6;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';
      } else if (c == '=') {
        estado = 7;
      } else if (c == '(') {
        estado = 8;
        t.cat = SINAIS;
        t.codigo = ABRE_PAR;
        return t;
      } else if (c == ')') {
        estado = 9;
        t.cat = SINAIS;
        t.codigo = FECHA_PAR;
        return t;
      } else if (c == '[') {
        estado = 10;
        t.cat = SINAIS;
        t.codigo = ABRE_COL;
        return t;
      } else if (c == ']') {
        estado = 11;
        t.cat = SINAIS;
        t.codigo = FECHA_COL;
        return t;
      } else if (c == '{') {
        estado = 12;
        t.cat = SINAIS;
        t.codigo = ABRE_CHAVE;
        return t;
      } else if (c == '}') {
        estado = 13;
        t.cat = SINAIS;
        t.codigo = FECHA_CHAVE;
        return t;
      } else if (c == ',') {
        estado = 14;
        t.cat = SINAIS;
        t.codigo = VIRGULA;
        return t;
      } else if (c == '\'') {
        estado = 15;
      } else if (c == '\"') {
        estado = 16;
      } else if (c == '&') {
        estado = 17;
      } else if (c == '|') {
        estado = 18;
      } else if (c == '<') {
        estado = 19;
      } else if (c == '>') {
        estado = 20;
      } else if (c == '!') {
        estado = 21;

      } else if (c == '_') {
        estado = 22;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';
      } else if (c == EOF) {
        t.cat = FIM_ARQ;
        return t;
      } else {
        error("Caracter invalido na expressao!");
      }
      break;
    case 1:
      if ((isalpha(c) || isdigit(c) || c == '_')) {
        estado = 1;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';
      } else {
        estado = 23;
        ungetc(c, fd);
        int pr_indice = buscaPR(lexema);
        if (pr_indice >= 0) {
          t.cat = PALAVRAS_RESERVADAS;
          t.codigo = pr_indice;

        } else {
          t.cat = ID;
          strcpy(t.lexema, lexema);
        }

        return t;
      }
      break;
    case 2:
      if (isdigit(c)) {
        estado = 2;
        digitos[tamD] = c;
        digitos[++tamD] = '\0';
      } else if (c == '.') {
        estado = 24;
        digitos[tamD] = c;
        digitos[++tamD] = '\0';
      } else {
        estado = 25;
        ungetc(c, fd);
        t.cat = INTCON;
        t.valInt = atoi(digitos);
        return t;
      }
      break;
    case 6:
      if (c == '/') {
        estado = 26;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';

      } else {
        estado = 27;
        t.cat = SINAIS;
        t.codigo = DIVISAO;
        ungetc(c, fd);
        return t;
      }
      break;
    case 7:
      if (c == '=') {
        estado = 28;
        t.cat = SINAIS;
        t.codigo = IGUAL;
        return t;
      } else {
        estado = 29;
        t.cat = SINAIS;
        t.codigo = ATRIB;
        ungetc(c, fd);
        return t;
      }
      break;
    case 15:
      if (c == '\\') {
        estado = 30;
      } else if (c != '\'' && isprint(c)) {
        // Caractere imprimível (exceto '\')
        estado = 31;
        t.cat = CHARCON;
        t.valChar = c;
        return t;
      } else {
        error("Caracter invalido na expressao!");
      }
      break;
    case 16:
      if (c == '\"') {
        estado = 32;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';
        t.cat = STRCON;
        strcpy(t.lexema, lexema);
        return t;
      } else if (isprint(c)) {
        estado = 16;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';
      } else {
        error("Caracter invalido na expressao!");
      }
      break;
    case 17:
      if (c == '&') {
        estado = 33;
        t.cat = SINAIS;
        t.codigo = AND;
        return t;
      } else {
        estado = 34;
        t.cat = SINAIS;
        t.codigo = ECOMERCIAL;
        ungetc(c, fd);
        return t;
      }
      break;
    case 18:
      if (c == '|') {
        estado = 35;
        t.cat = SINAIS;
        t.codigo = OU;
        return t;
      }
      estado = 35;
      t.cat = SINAIS;
      t.codigo = BARA;
      ungetc(c, fd);
      return t;
      break;
    case 19:
      if (c == '=') {
        estado = 36;
        t.cat = SINAIS;
        t.codigo = MAIOR_IG;
        return t;
      } else {
        estado = 37;
        t.cat = SINAIS;
        t.codigo = MAIORQ;
        ungetc(c, fd);
        return t;
      }
      break;
    case 20:
      if (c == '=') {
        estado = 38;
        t.cat = SINAIS;
        t.codigo = MENOR_IG;
        return t;
      } else {
        estado = 39;
        t.cat = SINAIS;
        t.codigo = MENORQ;
        ungetc(c, fd);
        return t;
      }
      break;
    case 21:
      if (c == '=') {
        estado = 40;
        t.cat = SINAIS;
        t.codigo = DIFERENCA;
        return t;
      } else {
        estado = 41;
        t.cat = SINAIS;
        t.codigo = EXCLAMACAO;
        ungetc(c, fd);
        return t;
      }
      break;
    case 22:
      if (isalpha(c)) {
        estado = 1;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';
      } else {
        error("Caracter invalido na expressao!");
      }
      break;

    case 24:
      if (isdigit(c)) {
        estado = 42;
        digitos[tamD] = c;
        digitos[++tamD] = '\0';
      } else {
        error("Caracter invalido na expressao!");
      }
      break;
      /////REVER!!!!!!!!!!!!!!!!!!!!
    case 26:
      if (isprint(c) && c != '\\') {
        estado = 26;
        lexema[tamL] = c;      // anexa o caractere ao lexema
        lexema[++tamL] = '\0'; // Atualiza o término do lexema
      } else if (c == '\\') {
        estado = 49;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';
      }
      break;
    case 30:
      if (c == '0') {
        estado = 43;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';
      } else if (c == 'n') {
        estado = 44;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';
      }

      else {
        error("Caracter invalido na expressao!");
      }
      break;
    case 31:
      if (c == '\'') {
        estado = 45;
        t.cat = CHARCON;
        strcpy(t.lexema, lexema);
        return t;
      } else {
        error("Caracter invalido na expressao!");
      }
      break;
    case 42:
      if (isdigit(c)) {
        estado = 42;
        digitos[tamD] = c;
        digitos[++tamD] = '\0';
      } else {
        estado = 46;
        t.cat = REALCON;
        t.valReal = atof(digitos);
        ungetc(c, fd);
        return t;
      }
      break;
    case 43:
      if (c == '\'') {
        estado = 47;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';
        t.cat = CHARCON;
        t.valChar = '\0';
        return t;
      } else {
        error("Caracter invalido na expressao!");
      }
      break;
    case 44:
      if (c == '\'') {
        estado = 48;
        lexema[tamL] = c;
        lexema[++tamL] = '\0';
        t.cat = CHARCON;
        t.valChar = '\n';
        return t;
      } else {
        error("Caracter invalido na expressao!");
      }
      break;
    case 49:
      if (c == '\n') {
        estado = 0;
        ungetc(c, fd);

      } else {
        estado = 49;
      }
    }
  }
}

// int main() {
//   FILE *fd;
//   TOKEN tk;
//   if ((fd = fopen("expressao.dat", "r")) == NULL) {
//     error("Arquivo de entrada da expressao nao encontrado!");
//   }

//   printf("LINHA %d: ", contLinha);
//   while (1) {
//     tk = AnaLex(fd);
//     switch (tk.cat) {
//     case ID:
//       printf(" <ID, %s> ", tk.lexema);
//       break;
//     case SINAIS:
//       printf(" <SINAIS, %s>", SinaisTable[tk.codigo]);
//       break;
//     case INTCON:
//       printf(" <INTCON, %d> ", tk.valInt);
//       break;
//     case REALCON:
//       printf("<REALCON, %f>", tk.valReal);
//       break;
//     case CHARCON:
//       printf(" <CHARCON, %c>", tk.valChar);
//       break;
//     case PALAVRAS_RESERVADAS:
//       printf(" <PALAVRAS_RESERVADAS, %s>", PRTable[tk.codigo]);
//       break;
//     case STRCON:
//       printf(" <STRCON, \"%s\">", tk.lexema);
//       break;
//     case FIM_EXPR:
//       printf(" <FIM_EXPR>\n");
//       printf("LINHA %d: ", contLinha);
//       break;
//     case FIM_ARQ:
//       printf(" <Fim do arquivo encontrado>\n");
//     }

//     if (tk.cat == FIM_ARQ)
//       break;
//   }

//   fclose(fd);

//   return 0;
// }

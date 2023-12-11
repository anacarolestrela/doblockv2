#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Analex.h"
#include "anasint.h"
#include "Funcaux.h"

TOKEN t;
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

extern const char *const PRTable[];

//prog ::= {decl_list_var} {decl_block_prot} block_main {block_def}
void Prog()
{           
t = AnaLex(fd); 

while (t.cat == PALAVRAS_RESERVADAS && (t.codigo == PR_INT || t.codigo == PR_CHAR || t.codigo == PR_FLOAT ||  
        t.codigo == PR_BOOL || t.codigo == CONST))
{
   // printf("\nentrou no while de palavras reservadas\n");
    //printf(" PALAVRA RESERVADA: %s", PRTable[t.codigo]);

    Decl_list_var();
    //printf("voltou pra declist var");

    // Após chamar Decl_list_var(), é necessário verificar novamente a condição do while
    if (t.cat == FIM_EXPR)
    {
        t = AnaLex(fd);
    }

}

        t = AnaLex(fd);

    if(t.cat!= PALAVRAS_RESERVADAS || t.codigo!= BLOCK)
    { 
        erro("Block esperado");
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
        if(t.cat != PALAVRAS_RESERVADAS && t.codigo  ==  FECHA_COL)
        {
            erro("ERRO 2: Fecha colchete esperado");
        }
        t = AnaLex(fd);
    }
    escopo = GLOBAL;
    catId =BLK;
    Block_main();
    t =AnaLex(fd);
    while (t.cat ==PALAVRAS_RESERVADAS && t.codigo == BLOCK)
    {
        Block_def();
    }
    //printf("chegou ao final de prog");
}

//decl_list_var ::= [const] tipo decl_var { , decl_var}
void Decl_list_var()
{   //printf("\nentrou em decl list var\n");
    if(t.cat ==PALAVRAS_RESERVADAS && t.codigo == CONST)
    {
        //printf("eh const");
         t_const=1;
    }
    Tipo();
     t =AnaLex(fd);
    Decl_var(); 
    t = AnaLex(fd);


    while (t.cat  == SINAIS && t.codigo == VIRGULA)
    {   //tf("entrou no while de mais de uma variavel");
        t = AnaLex(fd);
        Decl_var();
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
        strcpy(nomeId, "");
        t =AnaLex(fd);
        while (t.cat ==SINAIS && t.codigo == ABRE_COL)
        {
          t= AnaLex(fd);
          if(t.cat !=SINAIS || t.codigo != FECHA_COL)
          {
            erro("ERRO 2: Fecha colchete esperado");
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
        
            t =AnaLex(fd);
            while (t.cat ==SINAIS && t.codigo == ABRE_COL)
            {
            t= AnaLex(fd);
            if(t.cat !=SINAIS || t.codigo != FECHA_COL)
            {
                erro("ERRO 2: Fecha colchete esperado");
            }
            t =AnaLex(fd);
            }
                  InsereTabIdentif(nomeId, catId, escopo, tipo, t_const, zombie, ref, parametros);
        } 
    }
}

//block_main ::= block main {decl_list_var} { cmd } endblock
void Block_main()
{
    if(t.cat != PALAVRAS_RESERVADAS || t.codigo != MAIN)
    {
        erro("ERRO 3: Main esperado");
    }
    t = AnaLex(fd);
    while (t.cat == PALAVRAS_RESERVADAS && (t.codigo == CONST || t.codigo == PR_CHAR || t.codigo == PR_INT || t.codigo == PR_FLOAT || t.codigo == PR_BOOL))
    {
        Decl_list_var();
    }
    while (t.cat == ID ||( t.cat ==PALAVRAS_RESERVADAS && (t.codigo == DO|| t.codigo == IF || t.codigo == WHILE || t.codigo == GOBACK || t.codigo == GETINT || t.codigo == GETREAL || t.codigo == GETCHAR || t.codigo == PUTINT || t.codigo == PUTREAL || t.codigo == PUTCHAR)))
    {
        Cmd();
    }
    

    if(t.cat != PALAVRAS_RESERVADAS || t.codigo != ENDBLOCK)
    {
        erro("ERRO 4: Endblock esperado");
    }

}

//decl_var ::= id {[ intcon | idconst ]} [ = (intcon | realcon | charcon | stringcon |
//{ (intcon | realcon | charcon | stringcon) {, (intcon | realcon |charcon | stringcon) } } ) ]
void Decl_var()
{      

    //printf("\nentrou em dcl var");

    //printf("Token: %d ", t.cat );
    if(t.cat != ID)
    {   
        erro("ERRO 5: ID esperado");
    }
    t = AnaLex(fd);
    while (t.cat == SINAIS && t.codigo == ABRE_COL)
    {
    
       t= AnaLex(fd);
       while (t.cat != INTCON )
       {
        erro("ERRO 13: int esperado");
       }
       t =AnaLex(fd);
       if(t.cat !=SINAIS || t.codigo != FECHA_COL)
       {
            erro("ERRO 2: Fecha colchete esperado");
       }
       t= AnaLex(fd);
    }
    if(t.cat == SINAIS && t.codigo == ATRIB)
    {
        //printf("\nentrou em atrib");
        t = AnaLex(fd);
         //printf("\nToken: %d : %d", t.cat,  t.valInt );

        if(t.cat != INTCON && t.cat != REALCON && t.cat != CHARCON && t.cat != STRCON &&( t.cat != SINAIS && t.codigo != ABRE_CHAVE))
        {
            erro("ERRO 14: variavel ou abre chaves esperado");
        }
        if(t.cat == SINAIS && t.codigo == ABRE_CHAVE)
        {
            t = AnaLex(fd);
            if(t.cat != INTCON|| t.cat != REALCON || t.cat != CHARCON || t.cat != STRCON )
            {
                        erro("ERRO 15: Variavel esperada");
            }
            t = AnaLex(fd);
            while (t.cat == SINAIS && t.codigo ==VIRGULA)
            {
                t = AnaLex(fd);

                if(t.cat != INTCON|| t.cat != REALCON || t.cat != CHARCON || t.cat != STRCON )
                    {
                                erro("ERRO 15: Variavel esperada");
                    }
                t = AnaLex(fd);
            }
            if(t.cat != SINAIS && t.codigo != FECHA_CHAVE)
            {
                erro("ERRO 16: Fecha chaves esperado");
            }
        }
    }
}

// tipo ::= char
//         | int
//         | real
//         | bool
void Tipo()
{   
    t = AnaLex (fd);

   // printf("\nentrou em tipo");
    if(t.cat != PALAVRAS_RESERVADAS || !(t.codigo == PR_CHAR || t.codigo == PR_INT || t.codigo == PR_FLOAT || t.codigo == PR_BOOL))
    {
        erro("ERRO 3: Tipo esperado");
    }
    if(t.codigo == PR_CHAR)
    {   
       // printf("\ntipo char");
        tipo = T_CHAR;
    }else if (t.codigo== PR_INT)
    {
        //printf("\ntipo int");
        tipo = t_INT;
    }else if (t.codigo == PR_FLOAT)
    {
        printf("tipo float");
        tipo = T_REAL;
    }
    else if (t.codigo == PR_BOOL)
    {
       // printf("tipo bool");
        tipo= T_BOOL;
    }

}

//block_def ::= block id [with tipo id1{ [intcon1 | idconst1] } { , tipo id2 { [intcon2| idconst2] } }] {decl_list_var} { cmd } endblock
void Block_def()
{   //printf("entrou em block def");
    t=AnaLex(fd);
    if(t.cat != ID)
    {
        erro("ERRO 5: ID esperado");
    }
    t =AnaLex(fd);
    if(t.cat == PALAVRAS_RESERVADAS && t.codigo == WITH)
    {
        t= AnaLex(fd);
        if(t.cat!=ID)
        {
          erro("ERRO 5: ID esperado");
        }

        while (t.cat == SINAIS && t.codigo == ABRE_COL)
        {
            t= AnaLex(fd);
            if(t.cat != INTCON && t.cat != ID)
            {
              erro("ERRO 5: ID esperado");
            }
            t=AnaLex(fd);
            if(t.cat != SINAIS ||  t.codigo != FECHA_COL)
            {
                erro("ERRO 2: Fecha colchete esperado");

            }
            t = AnaLex(fd);   
        }
        while (t.cat==SINAIS && t.codigo == VIRGULA)
        {
            t = AnaLex(fd);
            if(t.cat!=ID)
            {
                erro("ERRO 5: ID esperado");
            }
        }
         while (t.cat == SINAIS && t.codigo == ABRE_COL)
        {
            t= AnaLex(fd);
            if(t.cat != INTCON && t.cat != ID)
            {
                erro("ERRO 5: ID esperado");
            }
            t=AnaLex(fd);
            if(t.cat != SINAIS ||  t.codigo != FECHA_COL)
            {
                erro("ERRO 2: Fecha colchete esperado");

            }
            t = AnaLex(fd);   
        }
    }
}


// cmd ::= do (id1 [with tipo id1 { , tipo id2 }] | cmd ) varying id2 from expr1(to 
//     | downto) expr2
//     | do (id [with tipo id1 { , tipo id2 }] | cmd ) while ( expr )
//     | do (id [with tipo id1 { , tipo id2 }] | cmd ) [for expr times ]
//     | if ( expr ) { cmd }{ elseif ( expr ) { cmd } } [ else { cmd }] endif
//     | while ( expr ) { cmd } endwhile
//     | atrib
//     | goback
//     | getint id
//     |getreal id
//     | getchar id
//     | putint id
//     | putreal id
//    | putchar id
void Cmd()
{
    if(t.cat == PALAVRAS_RESERVADAS && t.codigo == DO )
    {
        t = AnaLex(fd);
        if(t.cat ==ID)
        {
            if(lookahead.cat == SINAIS && (lookahead.codigo == ABRE_COL))
            {
                Cmd();
            }
            else
            {
                t =AnaLex(fd);
                if(t.cat == PALAVRAS_RESERVADAS && t.codigo == WITH)
                {
                    t =AnaLex(fd);
                    if(t.cat != ID)
                    {
                         erro("ERRO 5: ID esperado");
                    }
                    t = AnaLex(fd);
                    if (t.cat == SINAIS && t.codigo == VIRGULA)
                    {
                        t =AnaLex(fd);
                        if(t.cat!=ID)
                        {
                             erro("ERRO 5: ID esperado");
                        }
                        t=AnaLex(fd);
                    }
                }
            }
        }
        else if(t.cat == PALAVRAS_RESERVADAS && (t.codigo == DO || t.codigo == IF || t.codigo == WHILE || t.codigo == GOBACK || t.codigo == GETINT || t.codigo == GETREAL || t.codigo == GETCHAR || t.codigo == PUTINT || t.codigo == PUTREAL || t.codigo == PUTCHAR))
        {
            Cmd();
        }else
        {
            erro("ERRO 14: palavras reservadas do, if,while, goback. OU inputs e outputs dos tipos autorizados");
        }
        if(t.cat ==PALAVRAS_RESERVADAS && t.codigo == VARYING)
        {
            t =AnaLex(fd);
            if(t.cat !=ID)
            {
                 erro("ERRO 5: ID esperado");
            }
            t=AnaLex(fd);
            if (t.cat!= PALAVRAS_RESERVADAS || t.codigo != FROM)
            {
                erro("ERRO 16: From esperado"); //esperando from
            }
            t=AnaLex(fd);
            Expr();
            if (t.cat!=PALAVRAS_RESERVADAS || (t.codigo != TO && t.codigo != DOWNTO))
            {
                erro("ERRO 10: To ou Downto esperados");//esperando to ou downto
            }
            t=AnaLex(fd);
            Expr();
        }else if (t.cat == PALAVRAS_RESERVADAS && t.codigo == WHILE)
        {
            t=AnaLex(fd);
            if(t.cat !=SINAIS || t.codigo!=ABRE_PAR )
            {
                erro("ERRO 8: Abre parentese esperado"); //ESPERANDO ABRE PARENTESES
            }
            t=AnaLex(fd);
            Expr();
            if (t.cat != SINAIS || t.codigo != FECHA_PAR)
            {
                erro("ERRO 9: Fecha parentese esperado"); //ESPERANDO fecha PARENTESES
            }
            t=AnaLex(fd);
        }else if (t.cat ==PALAVRAS_RESERVADAS && t.codigo == FOR)
        {
            t=AnaLex(fd);
            Expr();
            if(t.cat != PALAVRAS_RESERVADAS || t.codigo != TIMES)
            {
                erro("ERRO 15: Times esperado");//esperandp times
            }
            t=AnaLex(fd);
        }
        else if (t.cat ==PALAVRAS_RESERVADAS && t.codigo == IF)
        {
            t=AnaLex(fd);
            if(t.cat != SINAIS || t.codigo != ABRE_PAR)
            {
                erro("ERRO 8: Abre parentese esperado");
            }
            t=AnaLex(fd);
            Expr();
            if (t.cat  !=SINAIS || t.codigo != FECHA_PAR)
            {
                erro("ERRO 9: Fecha parentese esperado");
            }
            t=AnaLex(fd);
            while((t.cat == PALAVRAS_RESERVADAS && (t.codigo == DO || t.codigo == IF || t.codigo == WHILE || t.codigo == GOBACK || t.codigo == GETINT || t.codigo == GETREAL || t.codigo == GETCHAR || t.codigo == PUTINT || t.codigo == PUTREAL || t.codigo == PUTCHAR )) || t.cat == ID)
            {
                Cmd();
            }
        }
        if (t.cat != PALAVRAS_RESERVADAS || t.codigo != ENDIF)
        {
           erro("ERRO 13: Endif esperado"); //esoerando endif
        }
        t=AnaLex(fd);
    }else if (t.cat == PALAVRAS_RESERVADAS && t.codigo != WHILE)
    {
        t=AnaLex(fd);
        if(t.cat != SINAIS || t.codigo != ABRE_PAR)
        {
            erro("ERRO 8: Abre parentese esperado");
        }
        t=AnaLex(fd);
        Expr();

        if(t.cat != SINAIS || t.codigo != FECHA_PAR)
        {
            erro("ERRO 9: Fecha parentese esperado");
        }
        t=AnaLex(fd);
         while((t.cat == PALAVRAS_RESERVADAS && (t.codigo == DO || t.codigo == IF || t.codigo == WHILE || t.codigo == GOBACK || t.codigo == GETINT || t.codigo == GETREAL || t.codigo == GETCHAR || t.codigo == PUTINT || t.codigo == PUTREAL || t.codigo == PUTCHAR )) || t.cat == ID)
        {
            Cmd();
        }
        if(t.cat != PALAVRAS_RESERVADAS || t.codigo != ENDWHILE)
        {
            erro("ERRO 11: Endwhile esperado");//esperando endwhile
        }
        t=AnaLex(fd);
    }
    else if (t.cat!=ID)
    {
        Atrib();
    }else if (t.cat == PALAVRAS_RESERVADAS && t.codigo == GOBACK)
    {
        t=AnaLex(fd);
    }else if (t.cat ==PALAVRAS_RESERVADAS &&( t.codigo == GETINT || t.codigo ==GETREAL || t.codigo == GETCHAR|| t.codigo == PUTINT || t.codigo == PUTREAL||t.codigo == PUTCHAR ))
    {
        if (t.cat != ID)
        {
             erro("ERRO 5: ID esperado");
        }
        t=AnaLex(fd);
        
    }else
    {
        erro("Erro 12: Inputs ou outputs esperados");//esperando inputs ou outputs
    }
}


// atrib ::= id { [ expr ] } = expr
void Atrib()
{
    if(t.cat != ID)
    {
        erro("ERRO 5: ID esperado");
    }
    t = AnaLex(fd);
    while (t.cat == SINAIS && t.codigo == ABRE_COL )
    {
        t = AnaLex(fd);
        Expr();

        if(t.cat != SINAIS || t.codigo != FECHA_COL)
        {
            erro("ERRO 8: Abre parentese esperado");
        }
        t = AnaLex(fd);
    }
    if(t.cat != SINAIS || t.codigo != ATRIB)
    {
        erro("ERRO 9: Fecha parentese esperado"); //ESPERANDO fecha PARENTESES
    }
    Expr();

}

//expr ::= expr_simp [ op_rel expr_simp ]
void Expr()
{
      Expr_simp();

  if(t.cat == SINAIS && (t.codigo == IGUAL || t.codigo == DIFERENCA || t.codigo == MENOR_IG || t.codigo == MAIOR_IG|| t.codigo == MENORQ  || t.codigo == MAIORQ)){
    Op_rel();

    t = AnaLex(fd);
    Expr_simp();
  }

}

// [+ | – ] termo {(+ | – | ||) termo}
void Expr_simp()
{
    if(t.cat == SINAIS &&( t.codigo == ADICAO || t.codigo == SUBTRACAO))
    {
        t = AnaLex(fd);
    }
    Termo();
    while (t.cat == SINAIS && (t.codigo == ADICAO || t.codigo == SUBTRACAO || t.codigo == OU))
    {
        t = AnaLex(fd);
    }
    Termo();
    
}


// termo ::= fator {(* | / | &&) fator}
void Termo()
{
    Fator();
    while (t.cat ==SINAIS && (t.codigo == MULTIPLIC || t.codigo == BARA || t.codigo == AND))
    {
        t= AnaLex(fd);
        Fator();
    }
    

}

//fator ::= id { [ expr ] } | intcon | realcon | charcon |( expr ) | ! fator
void Fator()
{
    if(t.cat == ID)
    {
        t = AnaLex(fd);
        while (t.cat == SINAIS && t.codigo == ABRE_COL)
        {
            t = AnaLex(fd);
            Expr();
            if(t.cat != SINAIS && t.codigo != FECHA_COL)
            {
                erro("ERRO 2: Fecha colchete esperado");
            }
            t = AnaLex(fd);
        } 
    }
    else if (t.cat == INTCON || t.cat == REALCON || t.cat == REALCON || t.cat == CHARCON)
    {
        t = AnaLex(fd);
    }
    else if (t.cat == SINAIS && t.codigo == ABRE_PAR)
    {
        t = AnaLex(fd);
        Expr();
        if(t.cat ==SINAIS && t.codigo!=FECHA_PAR)
        {
            erro("ERRO 9: Fecha parentese esperado"); //ESPERANDO fecha PARENTESES
        }
        t = AnaLex(fd);
    }    
    else if(t.cat == SINAIS && t.codigo == EXCLAMACAO)
    {
        t = AnaLex(fd);
        Fator();

    }
    else
    {
        erro("ERRO 11: Fator incompleto");
    }

}

// op_rel ::= ==
//         | !=
//         | <=
//         | <
//         | >=
//         | >
void Op_rel()
{
    if(t.cat != SINAIS || (t.codigo != IGUAL && t.codigo != DIFERENCA && t.codigo != MENOR_IG && t.codigo != MENORQ && t.codigo != MAIOR_IG && t.codigo != MAIORQ))
    {
        erro("ERRO 7: Operador relacional esperado");
    }    
}

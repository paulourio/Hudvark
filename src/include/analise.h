#ifndef ANALISE_H
#define ANALISE_H

#include "list.h"

/* Análise léxica */
extern void processar(void);
extern void tk_inicializar(void);
extern void free_token(struct token *ptr);

/* Análise sintática */
extern struct bstree *parser_analisar_tokens(list **lista);
extern void parser_inicializar(void);

#endif


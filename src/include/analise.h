#ifndef ANALISE_H
#define ANALISE_H

#include "list.h"
#include "tree.h"

/* analise.h */
extern struct bstree *analisar(void);

/* Análise léxica */
extern void processar(void);
extern void tk_inicializar(void);
extern struct token *nova_token(const int token);
extern void free_token(struct token *ptr);

/* Análise sintática */
extern struct bstree *parser_analisar_tokens(list **lista);
extern void parser_inicializar(void);

/* Análise semântica */
extern void analise_semantica(struct bstree *tree);

static inline void inicializar_analisadores(void)
{
	tk_inicializar();	/* Inicializa o tokenizer (análise léxica). */
	parser_inicializar();	/* Análise sintática */
}

#endif


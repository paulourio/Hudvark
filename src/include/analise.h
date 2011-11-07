#ifndef ANALISE_H
#define ANALISE_H

#include "list.h"
#include "tree.h"

/* analise.c */
extern struct bstree *analisar(void);

/* Análise léxica - tokenizer.c */
extern void processar(void);
extern void tk_inicializar(void);
extern struct token *nova_token(const int token);
extern void free_token(struct token *ptr);

/* Análise sintática - montar_arvore.c */
extern struct bstree *parser_analisar_tokens(list **lista);
extern void parser_inicializar(void);

/* Análise semântica - semantica.c */
extern void analise_semantica(struct bstree *tree);

static inline void inicializar_analisadores(void)
{
	tk_inicializar();	/* Inicializa o tokenizer (análise léxica). */
	parser_inicializar();	/* Análise sintática */
}

#endif


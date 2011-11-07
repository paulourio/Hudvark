#ifndef ASM_X86_64_H
#define ASM_X86_64_H

#ifndef ASM_H
#	error "Não inclua este arquivo diretamente.  Use asm.h"
#endif

#include "token.h"

/* asm_x86_64.c */
extern void asm_gerar_inicio(void);
extern void asm_gerar_final(void);
extern void asm_gerar(const struct token *tk);
extern void asm_set_legivel(const int valor);
extern void asm_tamanho_memoria(const int valor);
extern void asm_gerar_zerar_celula(void);

#endif


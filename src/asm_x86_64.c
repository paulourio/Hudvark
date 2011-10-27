#include <stdio.h>
#include <stdlib.h>
#include <token.h>
#include <gramatica.h>
#include <loopstack.h>
#include <mensagens.h>

/* Variáveis - Inicializadas com "asm_gerar_inicio" */
static struct loopstack *pilha = NULL;
static int contador_loop = 0;

#define endl		fputc('\n', stdout)
#define out(...)	{ fprintf(stdout, __VA_ARGS__); endl; }

static int legivel = 0; /* Gerar código legível para um humano. */
static int tamanho_memoria = 30000;

static const char *_readable_linux_syscall = "$LINUX_SYSCALL";
static const char *_readable_asm_sys_exit = "$SYS_EXIT";
static const char *_readable_asm_sys_write = "$SYS_WRITE";
static const char *_readable_asm_stdout = "$STDOUT";

static const char *_linux_syscall = "$0x80";
static const char *_asm_sys_exit = "$1";
static const char *_asm_sys_write = "$4";
static const char *_asm_stdout = "$1";

#define _asm_get(o)	(legivel?  _readable##o: o)

#define __SYSCALL _asm_get(_linux_syscall)
#define __SYSEXIT _asm_get(_asm_sys_exit)
#define __SYSWRITE _asm_get(_asm_sys_write)
#define __STDOUT _asm_get(_asm_stdout)

#define __MEMORIA	"m"

#define __REG_POSICAO	"%edi"
#define __REG_TEMP	"%eax"

#define OP_ADD	"addl"
#define OP_SUB	"subl"
#define OP_MOV	"movl"
#define OP_LEA	"leal"
#define OP_TEST	"testl"

void asm_gerar_inicio(void)
{
	pilha = loopstack_new();
	contador_loop = 0;

	if (legivel) {
		out(".section .data");
		out("\t.equ SYS_WRITE, 4");
		out("\t.equ SYS_EXIT, 1");
		out("\t.equ STDOUT, 1");
		out("\t.equ LINUX_SYSCALL, 0x80");
	}
	out(".section .bss");
	out("\t.equ len, %d", tamanho_memoria);
	out("\t.lcomm %s, len", __MEMORIA);

	out(".section .text");
	out(".globl _start");
	out("_start:");
	out("\t%s $0, %s", OP_MOV, __REG_POSICAO); /* i = 0 */
}

void asm_gerar_final(void)
{
	const int codigo_saida = 0;

	if (legivel)
		out("\t# exit(%d)", codigo_saida);
	out("\t%s $%d, %%ebx", OP_MOV, codigo_saida);
	out("\t%s %s, %%eax", OP_MOV, __SYSEXIT);
	out("\tint %s", __SYSCALL);
	endl;

	pilha = loopstack_free(pilha);
}

static void asm_alterar_memoria(const int soma, const int valor)
{
	if (legivel)
		out("\t# %s[i] += %d", __MEMORIA, valor);
	out("\t%s %s(,%s,4), %s", OP_MOV, __MEMORIA, __REG_POSICAO, __REG_TEMP);
	out("\t%s $%d, %s", (soma? OP_ADD: OP_SUB), valor, __REG_TEMP);
	out("\t%s %s, %s(,%s,4)", OP_MOV, __REG_TEMP, __MEMORIA, __REG_POSICAO);
}

static void asm_deslocar_memoria(const int soma, const int valor)
{
	if (legivel)
		out("\t# i += %d", valor);
	out("\t%s $%d, %s", (soma?  OP_ADD:  OP_SUB), valor, __REG_POSICAO);
}

static void asm_imprimir(void)
{
	if (legivel)
		out("\t# sys_write(stdout, %s[i], 1)", __MEMORIA);
	out("\t%s %s, %%ebx", OP_MOV, __STDOUT);
	out("\t%s %s(,%s,4), %%ecx", OP_LEA, __MEMORIA, __REG_POSICAO);
	out("\t%s $1, %%edx", OP_MOV);
	out("\t%s %s, %%eax", OP_MOV, __SYSWRITE);
	out("\tint %s", __SYSCALL);
}

static void asm_criar_loop(void)
{
	struct loop_info *info = malloc(sizeof(struct loop_info));

	if (info == NULL) {
		err("Não há memória disponível para montar um loop.");
		exit(1);
	}
	info->id_corpo = contador_loop++;
	info->id_verificacao = contador_loop++;
	loopstack_push(pilha, info);

	out("\tjmp .loop%d", info->id_verificacao);
	out(".loop%d:", info->id_corpo);
}

static void asm_fechar_loop(void)
{
	struct loop_info *info = loopstack_pop(pilha);

	if (info == NULL) {
		err("Erro ao montar o código. Loop-stack vazia.");
		exit(1);
	}
	out(".loop%d:", info->id_verificacao);
	out("\t%s %s(,%s,4), %s", OP_MOV, __MEMORIA, __REG_POSICAO, __REG_TEMP);
	out("\t%s %s, %s", OP_TEST, __REG_TEMP, __REG_TEMP);
	out("\tjne .loop%d", info->id_corpo);

	free(info);
}

void asm_gerar(const struct token *tk)
{
	switch (tk->token) {
	case PROXIMO:
	case ANTERIOR:
		asm_deslocar_memoria(tk->token == PROXIMO, tk->contagem);
		break;
	case INCREMENTO:
	case DECREMENTO:
		asm_alterar_memoria(tk->token == INCREMENTO, tk->contagem);
		break;
	case IMPRESSAO:
		asm_imprimir();
		break;
	case LEITURA:
		err("\nLeitura: não implementado.\n");
		exit(1);
	case LOOP_INICIO:
		asm_criar_loop();
		break;
	case LOOP_FIM:
		asm_fechar_loop();
		break;
	}
}

void asm_set_legivel(const int valor)
{
	legivel = valor?  1:  0;
}

void asm_tamanho_memoria(const int valor)
{
	tamanho_memoria = valor;
}

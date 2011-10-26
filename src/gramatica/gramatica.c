#include <gramatica.h>

struct gramatica gramatica[] = {
	{PROXIMO,	'>', 	"Próximo \">\""},
	{ANTERIOR,	'<', 	"Anterior \"<\""},
	{INCREMENTO,	'+', 	"Incremento \"+\""},
	{DECREMENTO,	'-', 	"Decremento \"-\""},
	{IMPRESSAO,	'.', 	"Impressão \".\""},
	{LEITURA,	',', 	"Leitura \",\""},
	{LOOP_INICIO,	'[', 	"Início de loop \"[\""},
	{LOOP_FIM,	']', 	"Fim de loop \"]\""},
	{SIMBOLO_NAO_ACEITO, '\0', "Desconhecido"}
};

static void verificar_simbolo_extendido(const int simbolo)
{
	switch (simbolo) {
	case '@':
	case '#':
	case '!':
		warn("O símbolo \"%c\" não é implementado no compilador "
		     "clássico de brainfuck.", (char) simbolo);
		break;
	default:
		break;
	}
}

int identificar_simbolo(const int simbolo)
{
	int i = 0;

	for ( ; gramatica[i].token != SIMBOLO_NAO_ACEITO; i++) {
		if (gramatica[i].simbolo == (char) simbolo)
			return gramatica[i].token;
	}
	verificar_simbolo_extendido(simbolo);
	return SIMBOLO_NAO_ACEITO;
}

char *token_para_string(const int token)
{
	int i = 0;

	for ( ; gramatica[i].token != SIMBOLO_NAO_ACEITO; i++) {
		if (gramatica[i].token == (char) token)
			return gramatica[i].to_s;
	}
	return gramatica[i].to_s;
}


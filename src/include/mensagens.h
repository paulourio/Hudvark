#ifndef MENSAGENS_H
#define MENSAGENS_H

#include <stdio.h>

#define DEBUG

#define msg_location fprintf(stderr, "Na função %s (%s:%d)\n", __FUNCTION__, \
			__FILE__, __LINE__)

#define msg(...) msg_location; fprintf(stderr, "\t" __VA_ARGS__)

#define err(...)	msg("Erro: "__VA_ARGS__)
#define warn(...)	msg("Aviso: " __VA_ARGS__)

#ifdef DEBUG
#	define debug(...)	msg("Debug: " __VA_ARGS__)
#else
#	define debug(...)
#endif

#endif

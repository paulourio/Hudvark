/*
 * Definições de macros para o debug do compilador.
 * O nível de debug e definido em config.h, gerado pelo script
 * configure.sh
 */
#ifndef MENSAGENS_H
#define MENSAGENS_H

#include <stdio.h>
#include "config.h"

#define msg_location fprintf(stderr, "Na função %s (%s:%d)\n", __FUNCTION__, \
			__FILE__, __LINE__)

#define msg(...) msg_location; fprintf(stderr, "\t" __VA_ARGS__)

#define err(...)	msg("Erro: "__VA_ARGS__)

#if CONFIG_DEBUG_LEVEL > 1
#	define warn(...)	msg("Aviso: " __VA_ARGS__)
#else
#	define warn(...)
#endif

#if CONFIG_DEBUG_LEVEL > 2
#	define debug(...)	msg("Debug: " __VA_ARGS__)
#else
#	define debug(...)
#endif

#if CONFIG_DEBUG_LEVEL > 3
#	define dump(...)	msg(__VA_ARGS__)
#else
#	define dump(...)
#endif

#endif


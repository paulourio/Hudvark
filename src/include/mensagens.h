/*
 * Definições de macros para o debug do compilador.
 * O nível de debug e definido em config.h, gerado pelo script
 * configure.sh
 */
#ifndef MENSAGENS_H
#define MENSAGENS_H

#include <stdio.h>
#include "config.h"


#define msg_location	fprintf(stderr, "Na função %s (%s:%d) ", __FUNCTION__, \
				__FILE__, __LINE__)

#define __endl	fprintf(stderr, "\n")

#define msg(...)	msg_location; fprintf(stderr, __VA_ARGS__); __endl

#define err(...)	msg("Erro: "__VA_ARGS__)
#define raw_err(...)	fprintf(stderr, __VA_ARGS__)

#if CONFIG_DEBUG_LEVEL > 1
#	define warn(...)	msg("Aviso: " __VA_ARGS__)
#else
#	define warn(...)
#endif

#if CONFIG_DEBUG_LEVEL > 2
#	define debug(...)	msg("Debug: " __VA_ARGS__)
#	define raw_debug(...)	fprintf(stderr, __VA_ARGS__)
#else
#	define debug(...)
#	define raw_debug(...)
#endif

#if CONFIG_DEBUG_LEVEL > 3
#	define dump(...)	msg(__VA_ARGS__)
#else
#	define dump(...)
#endif

#if CONFIG_DEBUG_LEVEL > 4
#	define megadump(...)	msg(__VA_ARGS__)
#else
#	define megadump(...)
#endif

#endif


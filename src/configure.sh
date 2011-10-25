#!/bin/bash

#set -o nounset

function sintaxe
{
	echo "sintaxe: ./configure [--debug nivel]"
	echo "ex: ./bfc --debug 3"
	echo -e "\t--debug\tDefine quanto o compilador deve mostrar durante"
	echo -e "\t\to processo de compilação."
	echo ""
}

DEBUG=0

while [ "$1" != "" ]; do
    case $1 in
	--debug )	shift
			DEBUG=$1
			if [ "$DEBUG" = "" ]; then
				echo -e "Erro: Você deve definir o nível de debug.\n"
				sintaxe
				exit 1
			fi
			if ! [[ "$DEBUG" =~ ^[0-9]+$ ]]; then
				echo -e "Nível de debug deve ser um número.\n"
				exit 1
			fi
			;;
	-h | --help )   sintaxe
			exit
			;;
	* )
			echo "Opção $1 não reconhecida.  Passe --help para ajuda."
			exit 1
			;;
    esac
    shift
done

if [[ $DEBUG -gt 1 ]]; then
	echo "Escrevendo configuração em include/config.h"
fi

echo "#ifndef CONFIG_H" > include/config.h
echo "#define CONFIG_H" >> include/config.h
echo "" >> include/config.h
echo "#define CONFIG_DEBUG_LEVEL $DEBUG" >> include/config.h
echo "" >> include/config.h
echo "#endif" >> include/config.h
echo "" >> include/config.h

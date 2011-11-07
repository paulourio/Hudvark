#!/bin/bash

#set -o nounset

function sintaxe
{
	echo "sintaxe: ./configure [--debug nivel]"
	echo "ex: ./bfc --debug 3"
	echo -e "\t--debug\t\tDefine quanto o compilador deve mostrar durante"
	echo -e "\t\t\to processo de compilação."
	echo -e "\t--nao-otimizar\tNão otimizar o código."
	echo -e "\t--tam-pilha\tTamanho máximo da pilha. Define a profundidade"
	echo -e "\t\t\tmáxima de loops. Padrão: 300"
	echo -e "\t--memoria\tTamanho da memória do programa. Padrão: 30000"
	echo ""
}

DEBUG=0
OTIMIZAR=1
TAMPILHA=300
MEMORIA=30000

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
	--tam-pilha )	shift
			TAMPILHA=$1
			if [ "$TAMPILHA" = "" ]; then
				echo -e "Erro: Você deve definir o tamanho da pilha.\n"
				sintaxe
				exit 1
			fi
			if ! [[ "$TAMPILHA" =~ ^[0-9]+$ ]]; then
				echo -e "Tamanho da pilha deve ser um número.\n"
				exit 1
			fi
			;;			
	--nao-otimizar )
			OTIMIZAR=0
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

echo "/* Arquivo gerado automaticamente       */" > include/config.h
echo "/* Não altere este arquivo manualmente, */" >> include/config.h
echo "/* use o script configure.sh para gerar */" >> include/config.h
echo "/* as configurações desejadas.          */" >> include/config.h
echo "#ifndef CONFIG_H" >> include/config.h
echo "#define CONFIG_H" >> include/config.h
echo "" >> include/config.h
echo -e "#define CONFIG_DEBUG_LEVEL $DEBUG\n" >> include/config.h
echo -e "#define CONFIG_MAX_LOOP_DEPTH $TAMPILHA\n" >> include/config.h
echo -e "#define CONFIG_OTIMIZAR $OTIMIZAR\n" >> include/config.h
echo -e "#define CONFIG_MEMORIA $MEMORIA\n" >> include/config.h
echo "#endif" >> include/config.h
echo "" >> include/config.h

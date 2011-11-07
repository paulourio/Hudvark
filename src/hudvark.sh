#!/bin/bash

# Mostrar ajuda
function sintaxe
{
	echo "sintaxe: ./hudvark entrada.b [-o executavel]"
	echo "ex: ./bfc hello.b -o HelloWorld"
	echo -e "\t-o   Definir o nome do arquivo executável gerado."
	echo -e "\t-s   Apenas compilar, não fazer o link."
	echo -e "\t-v   Mostrar detalhes do que está acontecendo."
	echo -e "\t-vv  Mostrar muitos detalhes do que está acontecendo."
	echo -e "\t-vvv Mais ainda."
	echo -e "\t-V   Mostrar versão atual compilador instalado."
	echo ""
}

# Imprimir um texto em negrito
# echobf "Exemplo"
function echobf {
	echo -e "\033[0;1m$1\033[0m"
}

versao=v1.0
STR_VERSAO="Hudvärk: Compilador brainfuck $versao\nPaulo Roberto Urio (Outubro 2011)"

RM="`which rm` -f"

FONTE=""
OUTPUT=a.out
DEBUG=0
NAO_LINKAR=0

# Imprime uma mensagem de acordo com a 'verbosidade' definida.
function debugbf {
	if [ $1 -gt $DEBUG ]; then
		echobf "$2"
	fi
}

# Imprime uma mensagem de acordo com a 'verbosidade' definida.
function debug {
	if [ "$1" -le "$DEBUG" ]; then
		echo -e "$2\033[0m"
	fi
}

function mensagem {
	debug 1 "\033[31m* \033[32m$1"
}

function passo {
	mensagem "Passo $1\033[37m:\033[35m $2"
}

function erro {
	debug 0 "\033[31m* $1"
}

function checkret {
	ret="$?"
	sync
	if [ "$ret" -ne "0" ]; then
		if [ "$ret" -ne "127" ]; then
			erro "Erro ao compilar (Código $ret)."
			exit -1
		fi
	fi
}

function executar {
	debug 2 "$1"
	/bin/bash -c "$1"
	checkret
}


while [ "$1" != "" ]; do
    case $1 in
	-o )		shift
			OUTPUT=$1
			if [ "$OUTPUT" = "" ]; then
				echo "Você deve definir um arquivo de saída."
				xit 1
			fi
			;;
	-s )
			NAO_LINKAR=1
			;;
	-v )
			DEBUG=1
			;;
	-vv )
			DEBUG=2
			;;
	-vvv )
			DEBUG=3
			;;
	-V | --versao )   
	                echo -e "$STR_VERSAO"
	                exit 0
	                ;;
	-h | --help )   sintaxe
			exit
			;;
	* )	     if [ "$FONTE" != "" ]; then
				echo "Só é possível definir um arquivo fonte."
				exit 1
			fi
			FONTE="$1"
			;;
    esac
    shift
done

debug 1 "$STR_VERSAO"

EXT_OUT=bof
OUT_PRE=bffiltro.$EXT_OUT
OUT_COD=bfcod.s
OBJ_COD=bfcod.o

ANALISADOR=`which dvarkan`
checkret
PROCESSADOR=`which dvarkpp`
checkret

if [[ "$FONTE" = "" ]]; then
	echo -e "Nenhum arquivo-fonte definido.\n"
	sintaxe
	exit 1
fi

passo 1 "Pré-processamento"

executar "dvarkpp < $FONTE > $OUT_PRE"
if [ "$?" != "0" ]; then
	erro "[Hudvärk] Erro ao pré-processar."
	exit 1
fi

passo 2 "Análise léxica"

passo 3 "Análise sintática"

passo 4 "Análise semântica"

passo 5 "Geração de código"

passo 6 "Otimização de código"

executar "dvarkan < $OUT_PRE > $OUT_COD"

if [[ "$NAO_LINKAR" = "1" ]]; then
	executar "$RM bffiltro.bof"
	mensagem "Arquivo assembly: $OUT_COD"
	exit 0
fi

passo 7 "Geração do código final"

as=`which as`
ld=`which ld`
executar "$as --64 --noexecstack -mmnemonic=att $OUT_COD -o $OBJ_COD"
executar "$ld $OBJ_COD -o $OUTPUT"

mensagem "Removendo arquivos auxiliares"

executar "$RM $OUT_PRE $OBJ_COD $OUT_COD"

mensagem "Arquivo gerado: ./$OUTPUT"


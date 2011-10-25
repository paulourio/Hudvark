FONTES=

CC=cc
CFLAGS=-Wall -O2
INCLUDES=-I../include

default: $(PROGRAMA)

$(PROGRAMA): $(FONTES:.c=.o)

all: $(PRORAMA)

clean:
	$(RM) -f $(PROGRAMA) $(FONTES:.c=.o)

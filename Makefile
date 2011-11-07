
default: all

all: hudvark

semotimizar:
	cd src && make semotimizar
	cp src/hudvark .
	cp src/dvarkpp .
	cp src/dvarkan .

hudvark:
	cd src && make
	cp src/hudvark .
	cp src/dvarkpp .
	cp src/dvarkan .

clean:
	cd src && make clean
	$(RM) hudvark dvarkpp dvarkan


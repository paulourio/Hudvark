INSTALL=/usr/bin/install
INSTDIR=/usr/local/bin

default: all

all: hudvark

semotimizar:
	cd src && make semotimizar

hudvark:
	cd src && make

clean:
	cd src && make clean

install: src/hudvark.sh src/dvarkpp src/dvarkan
	$(INSTALL) src/hudvark.sh $(INSTDIR)/hudvark
	$(INSTALL) src/dvarkpp $(INSTDIR)/dvarkpp
	$(INSTALL) src/dvarkan $(INSTDIR)/dvarkan

uninstall:
	$(RM) $(INSTDIR)/hudvark
	$(RM) $(INSTDIR)/dvarkpp
	$(RM) $(INSTDIR)/dvarkan


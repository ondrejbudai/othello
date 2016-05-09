# Makefile
# Authors:
# Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
# Matej Marusak <xmarus06@stud.fit.vutbr.cz>
#
# Hlavní Makefile zodpovědný za sestavení celého programu a generování dokumentace

all:
	$(MAKE) -C src `./findqt.sh`

clean:
	$(MAKE) -C src clean

doxygen:
	doxygen

run: all
	./hra2016

zip: clean
	rm xbudai00-xmarus06.zip 2>/dev/null || true
	zip -r xbudai00-xmarus06.zip Makefile README findqt.sh src img/*{.png,.jpg} Doxyfile

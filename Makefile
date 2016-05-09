
# TODO:
# - Run target
# - Build directory (hard?)

all:
	$(MAKE) -C src `./findqt.sh`

clean:
	$(MAKE) -C src clean

doxygen:
	doxygen

run: all
	./othello

zip: clean
	rm xbudai00-xmarus06.zip 2>/dev/null || true
	zip -r xbudai00-xmarus06.zip Makefile findqt.sh src img/*{.png,.jpg}

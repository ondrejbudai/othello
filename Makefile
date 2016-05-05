
# TODO:
# - Run target
# - Build directory (hard?)

all:
	$(MAKE) -C src `./findqt.sh`

clean:
	$(MAKE) -C src clean

doxygen:
	doxygen

# TODO:
# - Fallback to use pkg_config
# - Run target
# - Build directory (hard?)

all:
	$(MAKE) -C src `./findqt.sh`

clean:
	$(MAKE) -C src clean

# TODO:
# - Fallback to use pkg_config
# - Run target
# - Build directory (hard?)

all:
	$(MAKE) -C src QT_PATH=`./findqt.sh -f` QT_LIB=`./findqt.sh -l` QT_INCLUDE=`./findqt.sh -i`

clean:
	$(MAKE) -C src clean

SOURCES_GUI := main-qt.cc
OBJECTS_GUI := $(SOURCES_GUI:.cc=.o)

SOURCES_CLI := main.cc
OBJECTS_CLI := $(SOURCES_CLI:.cc=.o)

SUBDIRECTORIES := gui logic
LIBS := $(SUBDIRECTORIES:%=lib%.a)
LIBS_GEN := $(SUBDIRECTORIES:%=gen_%)
SUB_CLEAN := $(SUBDIRECTORIES:%=%clean)

GUI_LIBS:= -L$(QT_LIB) -lQt5Widgets -lQt5Gui -lQt5Core -fPIC
GUI_INCLUDES :=	-I$(QT_INC)/QtCore -I$(QT_INC)/QtGui -I$(QT_INC)/QtWidgets -I$(QT_INC) -fPIC

OTHELLO := ../othello
OTHELLO_CLI := ../othello-cli

CXXFLAGS := -std=c++14 -Wall -Wextra -pedantic -g

LD_LIBRARY_PATH += /usr/local/share/Qt-5.5.1/5.5/gcc_64/lib
export LD_LIBRARY_PATH

all: $(LIBS_GEN) $(OTHELLO) $(OTHELLO_CLI)

$(OTHELLO): $(LIBS) $(OBJECTS_GUI)
	$(CXX) -o $@ $^ $(GUI_LIBS) -L. -lgui -llogic

$(OTHELLO_CLI): $(LIBS) $(OBJECTS_CLI)
	$(CXX) -o $@ $^ -L. -llogic

$(LIBS_GEN): gen_%: %
	@$(MAKE) --no-print-directory -C $^ dep

lib%.a: % force
	$(MAKE) -C $<

force:
	@true

$(OBJECTS_GUI): %.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(GUI_INCLUDES) -o $@ $<

$(OBJECTS_CLI): %.o: %.cc
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean: $(SUB_CLEAN)
	rm $(OBJECTS_CLI) $(OBJECTS_GUI) 2>/dev/null || true

$(SUB_CLEAN): %clean: %
	$(MAKE) -C $^ clean
	rm $(OTHELLO) $(OTHELLO_CLI) 2>/dev/null || true

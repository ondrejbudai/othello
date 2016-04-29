SOURCES := BoardGraphics.cc EndScreen.cc HistoryItemGui.cc HistoryPanel.cc InfoPanel.cc MainWindow.cc OthelloGui.cc PlayerSelection.cc StartPanel.cc
UI := EndScreen.ui HistoryItemGui.ui HistoryPanel.ui InfoPanel.ui MainWindow.ui OthelloGui.ui PlayerSelection.ui StartPanel.ui

OBJECTS :=	$(SOURCES:.cc=.o)
HEADERS := $(SOURCES:.cc=.hh)
MOC_FILES := $(HEADERS:%.hh=moc_%.cc)
OBJECTS += $(MOC_FILES:.cc=.o)


UI_HEADERS := $(UI:%.ui=ui_%.h)

GUI_INCLUDES :=	-I$(QT_INC)/QtCore -I$(QT_INC)/QtGui -I$(QT_INC)/QtWidgets -I$(QT_INC) -fPIC

MOC:=$(QT_PATH)/moc
UIC:=$(QT_PATH)/uic


all: $(UI_HEADERS) $(MOC_FILES) ../libgui.a

../libgui.a: $(OBJECTS)
	ar cr $@ $^
	ranlib $@

%.o: %.cc
	$(CXX) -c -std=c++14 $(GUI_INCLUDES) -o $@ $<

$(UI_HEADERS): ui_%.h: %.ui
	$(UIC) -o $@ $<

$(MOC_FILES): moc_%.cc: %.hh
	$(MOC) -o $@ $<

clean:
	rm $(OBJECTS) $(UI_HEADERS) ../libgui.a 2>/dev/null || true
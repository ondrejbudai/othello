SOURCES := AI.cc GameBoard.cc GameLogic.cc GameLogicGomoku.cc MainGame.cc Player.cc commandManager.cc

OBJECTS :=	$(SOURCES:.cc=.o)

all: ../liblogic.a

../liblogic.a: $(OBJECTS)
	ar cr $@ $^
	ranlib $@

%.o: %.cc
	$(CXX) -c -std=c++14 -o $@ $<

clean:
	rm $(OBJECTS) ../liblogic.a 2>/dev/null || true

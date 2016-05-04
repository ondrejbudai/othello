SOURCES := AI.cc GameBoard.cc GameLogic.cc MainGame.cc Player.cc

OBJECTS :=	$(SOURCES:.cc=.o)

all: ../liblogic.a

../liblogic.a: $(OBJECTS)
	ar cr $@ $^
	ranlib $@

%.o: %.cc
	$(CXX) -c -std=c++14 -o $@ $<

dep:
	@$(CXX) -MM -std=c++14 $(SOURCES) >deps

-include deps

clean:
	rm $(OBJECTS) ../liblogic.a deps 2>/dev/null || true

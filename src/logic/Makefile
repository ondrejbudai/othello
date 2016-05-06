SOURCES := AI.cc GameBoard.cc GameLogic.cc MainGame.cc Player.cc CommandManager.cc Command.cc Field.cc

OBJECTS :=	$(SOURCES:.cc=.o)

CXXFLAGS := -std=c++14 -Wall -Wextra -pedantic -g

all: ../liblogic.a

../liblogic.a: $(OBJECTS)
	ar cr $@ $^
	ranlib $@

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) -o $@ $<

dep:
	@$(CXX) -MM -std=c++14 $(SOURCES) >deps

-include deps

clean:
	rm $(OBJECTS) ../liblogic.a deps 2>/dev/null || true

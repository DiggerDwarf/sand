EXE 		= sand

SRC			= $(wildcard src/*.cpp)
OBJ 		= $(subst src, build, $(patsubst %.cpp, %.o, $(SRC)))

DBG 		= 

INCLUDE 	= -Iinclude
LIB 		= -L lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32

all: link
remake: clean all

run:
	$(EXE)

clean:
	erase $(subst build/, build\, $(OBJ))

mkbuild:
	mkdir build



build/%.o: src/%.cpp
	g++ $(INCLUDE) -c src/$*.cpp -o build/$*.o $(DBG)


link: $(OBJ)
	g++ $(OBJ) -o $(EXE) $(LIB) $(DBG)

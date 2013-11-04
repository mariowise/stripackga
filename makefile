#
# Strip Packing Problem
# 	by mariowise

GALIB_INC = /usr/local/include/ga
GALIB_LIB = /usr/local/lib

INC_DIRS = -I $(GALIB_INC) -Isrc
LIB_DIRS = -L $(GALIB_LIB)

CFLAGS = -c -w
LIBS = -lga

main: build/main.o build/stripGenome.o build/piece.o
	@ g++ build/*.o $(LIB_DIRS) $(LIBS) -o bin/strippackingproblem.run
	@ echo "Compilación terminada de forma exitosa"

build/main.o: src/main.cpp
	@ echo "  g++ src/main.cpp"
	@ g++ $(CFLAGS) $(INC_DIRS) src/main.cpp -o build/main.o

build/stripGenome.o: src/stripGenome.cpp
	@ echo "  g++ src/stripGenome.cpp"
	@ g++ $(CFLAGS) $(INC_DIRS) src/stripGenome.cpp -o build/stripGenome.o

build/piece.o: src/piece.cpp
	@ echo "  g++ src/piece.cpp"
	@ g++ $(CFLAGS) $(INC_DIRS) src/piece.cpp -o build/piece.o

clean:
	@ clear
	@ echo "Limpiando.."
	@ rm -rf build/*
	@ rm -rf bin/*

run:
	@ clear
	@ ./bin/strippackingproblem.run

me: clean main run
#
# Strip Packing Problem
# 	by mariowise

GALIB_INC = /usr/local/include/ga
GALIB_LIB = /usr/local/lib

INC_DIRS = -I $(GALIB_INC) -Isrc
LIB_DIRS = -L $(GALIB_LIB)

CFLAGS = -c -w
LIBS = -lga

main: build/main.o build/stripGenome.o build/piece.o build/pmx.o build/phenotype.o
	@ g++ build/*.o $(LIB_DIRS) $(LIBS) -o bin/stripp.run
	@ echo "Compilación terminada de forma exitosa"

build/main.o: src/main.cpp
	@ echo "  g++ src/main.cpp"
	@ g++ $(CFLAGS) $(INC_DIRS) src/main.cpp -o build/main.o

build/stripGenome.o: src/stripGenome.cpp
	@ echo "  g++ src/stripGenome.cpp"
	@ g++ $(CFLAGS) $(INC_DIRS) src/stripGenome.cpp -o build/stripGenome.o

build/phenotype.o: src/phenotype.cpp
	@ echo "  g++ src/phenotype.cpp"
	@ g++ $(CFLAGS) $(INC_DIRS) src/phenotype.cpp -o build/phenotype.o

build/piece.o: src/piece.cpp
	@ echo "  g++ src/piece.cpp"
	@ g++ $(CFLAGS) $(INC_DIRS) src/piece.cpp -o build/piece.o

build/pmx.o: src/pmx.cpp
	@ echo "  g++ src/pmx.cpp"
	@ g++ $(CFLAGS) $(INC_DIRS) src/pmx.cpp -o build/pmx.o

testRide:
	@ clear
	@ ./bin/stripp.run inst/A1.txt
	@ ./bin/stripp.run inst/B1.txt
	@ ./bin/stripp.run inst/B2.txt
	@ ./bin/stripp.run inst/B3.txt
	@ ./bin/stripp.run inst/B4.txt
	@ ./bin/stripp.run inst/B5.txt
	@ ./bin/stripp.run inst/B6.txt
	@ ./bin/stripp.run inst/B7.txt
	@ ./bin/stripp.run inst/B8.txt
	@ ./bin/stripp.run inst/B9.txt
	@ ./bin/stripp.run inst/B10.txt
	@ ./bin/stripp.run inst/C1.1.txt
	@ ./bin/stripp.run inst/C1.2.txt
	@ ./bin/stripp.run inst/C1.3.txt

clean:
	@ clear
	@ echo "Limpiando.."
	@ rm -rf build/*
	@ rm -rf bin/*

run:
	@ clear
	@ ./bin/stripp.run

me: clean main run
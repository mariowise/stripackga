#include <ga/GAGenome.h>
#include <ga/GASimpleGA.h>
#include <ga/std_stream.h>
#include <ga/ga.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

#include <stripGenome.h>
#include <piece.h>
#include <vector>

extern vector<piece> * pieces;

extern int pieceTotal;

extern int widthTotal;

using namespace std;

int main(int argc, char * argv[]) {
	
	srand(time(NULL));

	cout << "Comenzando ejecución del 'strip packing problem'." << endl;

	readInput("inst/A1.txt");

	// Instanciación
	stripGenome genome;
	genome.stripInitializer((GAGenome &) genome);
	GASimpleGA ga(genome);
	
	// Configuración
	ga.populationSize(10-1);
	ga.nGenerations(500);
	ga.pMutation(0.03);
	ga.pCrossover(0.9);

	// Lanzamiento
	ga.evolve();
	
	return EXIT_SUCCESS;
}
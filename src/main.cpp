#include <ga/GAGenome.h>
#include <ga/GASimpleGA.h>
#include <ga/std_stream.h>
#include <ga/ga.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include <stripGenome.h>
#include <piece.h>
#include <phenotype.h>

extern vector<piece> * pieces;

extern int pieceTotal;

extern int widthTotal;


using namespace std;

int main(int argc, char * argv[]) {
	
	srand(time(NULL));

	if(argc == 1) {
		cout << "inst/A1.txt\t" << endl;
		readInput("inst/A1.txt");
	} else {
		cout << argv[1] << "\t";
		readInput(argv[1]);
	}

	// Instanciación
	stripGenome genome;
	genome.stripInitializer(genome);
	GASimpleGA ga(genome);
	
	// Configuración
	ga.populationSize(49); // Ojo que este número debe ser par o presenta comportamiento extraño
	ga.nGenerations(500);
	ga.pMutation(0.03);
	ga.pCrossover(0.90);

	// Lanzamiento
	ga.evolve();

	stripGenome & bestIndividual = (stripGenome &) ga.statistics().bestIndividual();

	// cout << " " << bestIndividual << " = " << bestIndividual.getHeight() << endl;
	cout << " " << bestIndividual.getHeight() << endl;

	return EXIT_SUCCESS;
}
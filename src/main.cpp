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

	cout << "Peso GAGenome:" << sizeof(char) << endl;	
	cout << "Peso stripGenome:" << sizeof(int) << endl;	

	// Instanciación
	stripGenome genome;
	genome.stripInitializer(genome);
	GASimpleGA ga(genome);
	
	// Configuración
	ga.populationSize(10);
	ga.nGenerations(2);
	ga.pMutation(0.03);
	ga.pCrossover(0.95);

	// Lanzamiento
	ga.evolve();

	cout << "-----------------------------------------------------------" << endl;
	cout << "El mejor individuo es " << ga.statistics().bestIndividual() << endl;
	cout << "-----------------------------------------------------------" << endl;

	return EXIT_SUCCESS;
}
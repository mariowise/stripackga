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

extern float myMaxEver;

extern int * myBestGenome;

using namespace std;

void testUnit() {

	// readInput("inst/A1.txt");

	// phenotype fenoma(widthTotal);

	// fenoma.push(&pieces->at(1 -1));
	// fenoma.push(&pieces->at(2 -1));
	// fenoma.push(&pieces->at(3 -1));
	// fenoma.push(&pieces->at(4 -1));
	// fenoma.push(&pieces->at(5 -1));
	// fenoma.push(&pieces->at(6 -1));

	// cout << "Altura: " << fenoma.height << endl;


	readInput("inst/C1.1.txt");

	// [13, 12, 16, 7, 4, 11, 9, 5, 1, 15, 14, 6, 3, 10, 8, 2] = 16
	// [11, 10, 3, 13, 12, 7, 1, 2, 14, 15, 16, 8, 4, 5, 9, 6] = 16
	phenotype fenomaTest(widthTotal);

	fenomaTest.push(&pieces->at(11 -1));
	fenomaTest.push(&pieces->at(10 -1));
	fenomaTest.push(&pieces->at(3 -1));
	fenomaTest.push(&pieces->at(13 -1));
	fenomaTest.push(&pieces->at(12 -1));
	fenomaTest.push(&pieces->at(7 -1));
	fenomaTest.push(&pieces->at(1 -1));
	fenomaTest.push(&pieces->at(2 -1));
	fenomaTest.push(&pieces->at(14 -1));
	fenomaTest.push(&pieces->at(15 -1));
	fenomaTest.push(&pieces->at(16 -1));
	fenomaTest.push(&pieces->at(8 -1));
	fenomaTest.push(&pieces->at(4 -1));
	fenomaTest.push(&pieces->at(5 -1));
	fenomaTest.push(&pieces->at(9 -1));
	fenomaTest.push(&pieces->at(6 -1));

	cout << "Altura: " << fenomaTest.height << endl;

	exit(0);
}

int main(int argc, char * argv[]) {
	
	srand(time(NULL));

	// testUnit();

	if(argc == 1) {
		cout << "inst/A1.txt" << endl;
		readInput("inst/A1.txt");
	} else {
		cout << argv[1];
		readInput(argv[1]);
	}

	// Artesanía
	myMaxEver = 0.0f;
	myBestGenome = (int *) malloc(sizeof(int) * pieceTotal);

	// Instanciación
	stripGenome genome;
	genome.stripInitializer(genome);
	GASimpleGA ga(genome);
	
	// Configuración
	ga.populationSize(75);
	ga.nGenerations(1000);
	ga.pMutation(0.03);
	ga.pCrossover(0.90);

	// Lanzamiento
	ga.evolve();

	// cout << "-----------------------------------------------------------" << endl;
	// cout << "El peor individuo alcanzó fitness = " << ga.statistics().minEver() << endl;
	// cout << "El mejor individuo alcanzó fitness = " << ga.statistics().maxEver() << endl;
	// cout << "El mejor individuo es = \t\t" << ga.population().best() << " = fitness " << ga.statistics().maxEver() << endl;
	// cout << "El verdadero mejor individuo es = \t[";
	
	stripGenome & bestIndividual = (stripGenome &) ga.statistics().bestIndividual();

	// cout << " " << bestIndividual << " = " << bestIndividual.getHeight() << endl;
	cout << " " << bestIndividual.getHeight() << endl;

	// cout << "[";
	// for(int i = 0; i < pieceTotal; i++) {
	// 	cout << myBestGenome[i];
	// 	if(i != pieceTotal-1)
	// 		cout << ", ";
	// }
	// cout << "]" << " = fitness " << myMaxEver << endl;

	
	// GAPopulation lastPop = ga.population();

	// ga.flushScores();

	// cout << "La población final es: " << endl << lastPop;
	// cout << "-----------------------------------------------------------" << endl;

	return EXIT_SUCCESS;
}
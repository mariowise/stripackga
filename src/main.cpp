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

	// cout << "  Construyendo contenedor de fenotipo" << endl;
	// phenotype fenoma(widthTotal);

	// cout << "  Ingresando piezas" << endl;
	
	// fenoma.write(cout); cout << endl;
	
	// fenoma.push(&pieces->at(1-1));
	// fenoma.push(&pieces->at(5-1));
	// fenoma.push(&pieces->at(6-1));
	// fenoma.push(&pieces->at(4-1));
	// fenoma.push(&pieces->at(2-1));
	// fenoma.push(&pieces->at(3-1));

	// cout << "  Individuo con fitness = " << fenoma.fitness() << endl << endl;

	// int i;
	// for(i = 0; i < pieces->size(); i++) {
	// 	fenoma.push(&pieces->at(i));
	// }

	
	stripGenome genome;
	GASimpleGA ga(genome);
	
	// Configuración
	ga.populationSize(10);
	ga.nGenerations(500);
	ga.pMutation(0.03);
	ga.pCrossover(0.9);

	// Lanzamiento
	ga.evolve();
	
	return EXIT_SUCCESS;
}
#include <ga/GAGenome.h>
#include <ga/GASimpleGA.h>
#include <ga/std_stream.h>
#include <ga/ga.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include <stripGenome.h>
#include <piece.h>
#include <phenotype.h>

extern vector<piece> * pieces;

extern int pieceTotal;

extern int widthTotal;

extern ofstream * outputFile;


using namespace std;

void run(char * path) {

	double elapsedTime;
	clock_t begin, end;
	int i = 0;

	// ofstream solutions("solutions.csv", std::ios::app);
	// ofstream times("times.csv", std::ios::app);
	// outputFile = new ofstream("output.txt");


	for(i = 0; i < 1; i++) {
		begin = clock();
			readInput(path);

			// Instancia
			stripGenome genome;
			genome.stripInitializer(genome);
			GASimpleGA ga(genome);

			// Configuración
			ga.populationSize(50);
			ga.nGenerations(700);
			ga.pCrossover(0.45);
			ga.pMutation(0.05);

			// Lanzamiento
			ga.evolve();

		end = clock();

		// Solution recovery
		stripGenome & bestIndividual = (stripGenome &) ga.statistics().bestIndividual();
		elapsedTime = double(end - begin) / CLOCKS_PER_SEC;

		// solutions << bestIndividual.getHeight() << ";";
		// times << elapsedTime << ";";

		cout << "Mejor= " << bestIndividual.getHeight() << "\t" << elapsedTime << " seg." << endl;
	}

	// solutions << endl;
	// times << endl;

	// solutions.close();
	// times.close();
	// outputFile->close();

}

int main(int argc, char * argv[]) {
	
	srand(time(NULL));

	if(argc != 1) {
		run(argv[1]);
		// cout << "done " << argv[1] << endl;
	} else {
		cout << "* Error: argv[1] was empty" << endl;
		exit(1);
	}

	return EXIT_SUCCESS;
}
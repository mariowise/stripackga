#include <ga/GAGenome.h>
#include <ga/GASimpleGA.h>
#include <ga/std_stream.h>
#include <ga/ga.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

#include <stripGenome.h>

void stripGenome::stripInitializer(GAGenome & genoma) {
	stripGenome & newGenoma = (stripGenome &) genoma;
	newGenoma.stripCodexSize = 5;
	int i, pos;
	int * positions = (int *) malloc(sizeof(int) * newGenoma.stripCodexSize);
	for(i = 0; i < newGenoma.stripCodexSize; i++)
		positions[i] = -1;
	for(i = 0; i < newGenoma.stripCodexSize; i++) {
		pos = rand() % newGenoma.stripCodexSize; // Generar una posición aleatoria
		if(positions[pos] == -1) // Si la posición esta desocupada?
			positions[pos] = i; // Se asigna el número
		else {
			pos = (pos + 1) % newGenoma.stripCodexSize;	// A partir del número i
			while(positions[pos] != -1) // Busco la siguiente posición vacía
				pos = (pos + 1) % newGenoma.stripCodexSize;
			positions[pos] = i;	// Se asigna en la posición
		}
	}
	newGenoma.stripCodex = positions;
	// newGenoma.write(cout);
}

float stripGenome::stripEvaluator(GAGenome & genoma) {
	// stripGenome & theGenoma = (stripGenome &) genoma;
	// cout << "  Evaluando tipo de largo " << theGenoma.stripCodexSize << endl;
	// theGenoma.write(cout);
}

int stripGenome::stripCrossover(const GAGenome& father, const GAGenome& mother, GAGenome* brother, GAGenome* sister) {

}

int stripGenome::stripMutator(GAGenome & genoma, float pmut) {

}
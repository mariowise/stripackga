#include <ga/GAGenome.h>
#include <ga/GASimpleGA.h>
#include <ga/std_stream.h>
#include <ga/ga.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

#include <stripGenome.h>
#include <piece.h>

extern vector<piece> * pieces;

extern int pieceTotal;

extern int widthTotal;

void stripGenome::stripInitializer(GAGenome & genoma) {
	stripGenome & newGenoma = (stripGenome &) genoma;
	newGenoma.stripCodexSize = pieceTotal;
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
	// Mostrar por pantalla los individuos
	newGenoma.write(cout); cout << endl;	
}

float stripGenome::stripEvaluator(GAGenome & genoma) {
	stripGenome & newGenoma = (stripGenome &) genoma;
	if(newGenoma.stripCodexSize != pieceTotal) return 0.0f;
	
	newGenoma.write(cout);

	phenotype fenoma(widthTotal);
	int i; 
	for(i = 0; i < pieces->size(); i++)
		fenoma.push(&pieces->at(newGenoma.stripCodex[i]));
	float fitness = fenoma.fitness(); // 
	
	cout << " => fitness " << (1/fitness) << endl;

	return (1/fitness); // Recordar que el fitness mas grande es el mejor
}

int stripGenome::stripCrossover(const GAGenome& father, const GAGenome& mother, GAGenome* brother, GAGenome* sister) {

}

int stripGenome::stripMutator(GAGenome & genoma, float pmut) {

}
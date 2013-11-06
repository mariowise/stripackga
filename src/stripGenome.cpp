#include <ga/GAGenome.h>
#include <ga/GASimpleGA.h>
#include <ga/std_stream.h>
#include <ga/ga.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

#include <stripGenome.h>
#include <piece.h>
#include <pmx.h>

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
	cout << newGenoma << endl;	
}

float stripGenome::stripEvaluator(GAGenome & genoma) {
	stripGenome & newGenoma = (stripGenome &) genoma;
	if(newGenoma.stripCodexSize != pieceTotal) return 0.0f;
	
	cout << "Eval " << newGenoma;

	phenotype fenoma(widthTotal);
	int i; 
	for(i = 0; i < pieces->size(); i++)
		fenoma.push(&pieces->at(newGenoma.stripCodex[i]));
	float fitness = fenoma.fitness(); // 
	
	cout << " => fitness " << (1/fitness) << endl;

	return (1/fitness); // Recordar que el fitness mas grande es el mejor
}

int stripGenome::stripCrossover(const GAGenome& father, const GAGenome& mother, GAGenome* brother, GAGenome* sister) {
	stripGenome & lfather = (stripGenome &) father;
	stripGenome & lmother = (stripGenome &) mother;
	
	if(lfather.stripCodexSize != pieceTotal || lmother.stripCodexSize != pieceTotal) return 0;
	
	cout << "stripCrossover!" << endl;

	// Construcción del cruzamiento
	pmxCrossover daCross(pieceTotal, lfather.stripCodex, lmother.stripCodex);
	daCross.cross();

	int n = 0;

	if(brother) {
		stripGenome & lbrother = (stripGenome &) brother[0];
		lbrother.stripCodexSize = pieceTotal;
		// lbrother.stripCodex = daCross.son1;
		lbrother.stripCodex = (int *) malloc(sizeof(int) * pieceTotal);
		for(int i = 0; i < pieceTotal; i++)
			lbrother.stripCodex[i] = lfather.stripCodex[i];
		lbrother._evaluated = gaFalse;
		n++;
	}

	if(sister) {
		stripGenome & lsister = (stripGenome &) sister[0];
		lsister.stripCodexSize = pieceTotal;
		// lsister.stripCodex = daCross.son2;
		lsister.stripCodex = (int *) malloc(sizeof(int) * pieceTotal);
		for(int i = 0; i < pieceTotal; i++)
			lsister.stripCodex[i] =	lmother.stripCodex[i];
		lsister._evaluated = gaFalse;
		n++;
	}



	cout << "Saliendo de la función stripCrossover return " << n << endl;
	
	return n;
}

int stripGenome::stripMutator(GAGenome & genoma, float pmut) {
	float flipCoin = (rand() % 1000000) / 1000000.0f;
	if(flipCoin > pmut) // Si no corresponde generar un mutante salimos
		return 0; 

	stripGenome & newGenoma = (stripGenome &) genoma;
	if(newGenoma.stripCodexSize != pieceTotal) return 0;

	// Busca una posición aleatoria donde realizar un swap
	// (swap: intercambiarlo con le vecino de a la derecha)
	int rp = rand() % (pieceTotal-1); 
		
	// Swap
	int aux = newGenoma.stripCodex[rp];
	newGenoma.stripCodex[rp] = newGenoma.stripCodex[rp+1];
	newGenoma.stripCodex[rp+1] = aux;

	return 2; // Retorno el número de genes que cambiaron
}
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <common.h>
#include <piece.h>
#include <phenotype.h>

extern vector<piece> * pieces;

extern int pieceTotal;

extern int widthTotal;

void phenotype::push(piece * newPiece) {
	// Siendo que lowest contiene el stripe mas bajo
	while(expand(lowest, *newPiece) != 0); // Se repite siempre que sea distinto de 0
	
	refreshHeights();
	// newPiece->write(cout); cout << " => \t";
	// write(cout); cout << " lower=" << lowest << " altura=" << height << endl << endl; // cout << " (stripe.size=" << stripes.size() << ", lowest=" << lowest << ")" << endl;
}

void phenotype::write(ostream & stream) {
	int i;
	for(i = 0; i < stripes.size(); i++)
		stream << "(" << stripes.at(i).width << ", " << stripes.at(i).height << ") ";
}

int phenotype::expand(int pos, piece ns) {
	// pos es la posición del vector de stripes a partir de la cual
	// ns es el nuevo stripe
	piece * s = &stripes.at(pos);

	if(ns.width == s->width) { // Si la pieza cabe justo
		// Entonces el stripe se mantiene y cambia su altura
		s->height += ns.height;
		combine();
		refreshHeights();
		return 0;
	}
	else if(ns.width < s->width) { // Si la pieza es menor al stripe
		// Entonces se deben generar 2 stripes
		// Al stripe que había, se le descuenta el ancho y mantiene su altura
		s->width -= ns.width;

		// El nuevo stripe se inserta en la posición pos según el iterador .begin()
		stripes.insert(stripes.begin() + pos, piece(ns.width, s->height + ns.height));
		combine();
		refreshHeights();
		return 0;
	}
	else if(ns.width > s->width) { // En este caso como el stripe candidato tiene muy poco ancho, entonces deberá inflarse
		swell(pos);
		refreshHeights();
		return -1; // No se ha podido expandir, fue necesario inflar
	}
	else { cout << "* Error fatal: Something went really wrong" << endl; exit(0); }
}

int phenotype::swell(int pos) {
	// Pos es el índice del elemento chico que hay que inflar
	// Es necesario elegir a cual de los stripe vecinos se hinchará
	int minNeighbor;
	
	if(pos == 0) // Si se trata del primer elemento
		minNeighbor = 1; // El vecino candidato esta a la derecha
	else if(pos == stripes.size()-1) // Si se trata del último elemento
		minNeighbor = pos-1; // El vecino candidato esta a la izquierda
	else if(stripes.at(pos-1).height <= stripes.at(pos+1).height) // Si el de la izquierda es menor que el de la derecha
		minNeighbor = pos-1;
	else if(stripes.at(pos-1).height > stripes.at(pos+1).height) // Si el de la derecha es menor que el de la izquierda
		minNeighbor = pos+1;
	else { cout << "* Error fatal: swell gone hell" << endl; exit(0); }
	
	// Se combina este stripe con el strip del vecino
	stripes.at(minNeighbor).width += stripes.at(pos).width;

	// Se elimina el stripe que se acaba de combinar
	stripes.erase(stripes.begin() + pos);

	// Devuelve la posición del nuevo stripe cuestión
	return ((minNeighbor < pos) ? minNeighbor : pos);
}

void phenotype::combine() {
	// Genera una pérdida de contexto respecto de los índices
	int i, aux = 0;
	piece * x, * xn;
	for(i = 0; i < stripes.size()-1; i++) {
		x = &stripes.at(i);
		xn= &stripes.at(i+1);
		if(x->height == xn->height) { // Si ambos tienen el mismo alto
			// Entonces hay que combinarlos, sumando sus anchos y dejando uno solo
			x->width += xn->width;
			stripes.erase(stripes.begin()+i+1);
			i--; // Accion de redo para el for
		}
	}
	refreshHeights(); // Actualiza el puntero al mínimo
}

void phenotype::refreshHeights() {
	refreshMinHeight();
	refreshMaxHeight();
}

void phenotype::refreshMaxHeight() {
	int i, max = 0;
	for(i = 0; i < stripes.size(); i++) {
		if(stripes.at(i).height > max)
			max = stripes.at(i).height;
	}
	height = max;
}

void phenotype::refreshMinHeight() {
	// cout << "\tBuscando menor de "; write(cout);
	int i, pmin = 0, min = stripes.at(0).height;
	for(i = 1; i < stripes.size(); i++) {
		if(stripes.at(i).height <= min) {
			pmin = i;
			min = stripes.at(i).height;
		}
	}
	lowest = pmin;
	// cout << " resultando ser " << lowest << endl;
}

float phenotype::fitness() {
	// Es obvio que el fitness será la variable 'height', 
	// pero para añadirle algo mas interesante, se la sumará 
	// el factor de área que queda disponible para nuevas 
	// piezas por debajo de height (Que oscila entre (float) [0, 1])
	// [Se supone que este porcentaje debe ser lo mas bajo posible]
	int i, area = 0, fullArea = widthTotal * height;
	for(i = 0; i < stripes.size(); i++)
		area += stripes.at(i).width * stripes.at(i).height;
	return (float) ((float) height + ( 1.0f - (float) area / (float) fullArea ));
}

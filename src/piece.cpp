#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <piece.h>
#include <common.h>

extern vector<piece> * pieces;

extern int pieceTotal;

extern int widthTotal;

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

vector<string> * split(string s, char delim) {
	vector<string> * response = new vector<string>();
	replaceAll(s, "\t", " ");
	replaceAll(s, "\r", "");
	replaceAll(s, "\n", "\n");
	stringstream ss(s);
	string item;
	while(getline(ss, item, delim)) {
		response->push_back(item);
		// cout << item << "(" << item.length() << ")" <<  endl;
	}
	return response;
}

void readInput(char * target) {
	string line;
	ifstream fd (target);
	int row = 0, x, y;
	vector<string> * aux;
	pieces = new vector<piece>();

	// Primera fila
	getline(fd, line);
	aux = split(line, ' ');
	pieceTotal = atoi(aux->at(0).c_str());
	widthTotal = atoi(aux->at(1).c_str());
	free(aux);
	
	while(getline(fd,line)) {
		aux = split(line, ' ');
		if(aux->size() != 3) break;
		x = atoi(aux->at(1).c_str());
		y = atoi(aux->at(2).c_str());
		pieces->push_back(*new piece(row, x, y));
		free(aux);
		row++;
	}
	fd.close();
	
	// for(row = 0; row < pieces->size(); row++) {
	// 	cout << "piece(" << pieces->at(row).id << ", " << pieces->at(row).width << ", " << pieces->at(row).height << ")" << endl;
	// }
}


// Piece
void piece::write(ostream & stream) {
	stream << "(" << width << ", " << height << ") ";
}


// Phenotype
void phenotype::push(piece * newPiece) {
	// Siendo que lowest contiene el stripe mas bajo
	while(expand(lowest, *newPiece) != 0); // Se repite siempre que sea distinto de 0
	
	newPiece->write(cout); cout << " = ";
	write(cout); cout << " [" << stripes.size() << "]" << endl;
}

void phenotype::write(ostream & stream) {
	int i;
	for(i = 0; i < stripes.size(); i++)
		stream << "(" << stripes.at(i).width << ", " << stripes.at(i).height << ") ";
}

int phenotype::expand(int pos, piece ns) {
	// cout << "  Expandiendo posicion " << pos << " con valor ";
	// stripes.at(pos).write(cout); cout << endl;
	
	// pos es la posición del vector de stripes a partir de la cual
	// ns es el nuevo stripe
	piece * s = &stripes.at(pos);
	if(ns.width == s->width) { // Si la pieza cabe justo
		// Entonces el stripe se mantiene y cambia su altura
		s->height += ns.height;
	}
	if(ns.width < s->width) { // Si la pieza es menor al stripe
		// Entonces se deben generar 2 stripes
		// Al stripe que había, se le descuenta el ancho y mantiene su altura
		s->width -= ns.width;

		// El nuevo stripe se inserta en la posición pos según el iterador .begin()
		stripes.insert(stripes.begin() + pos, piece(ns.width, s->height + ns.height));
		cout << "  Elemento insertado con nuevo largo " << stripes.size() << " ";
		write(cout); cout << endl;
	}
	if(ns.width > s->width) { // En este caso como el stripe candidato tiene muy poco ancho, entonces deberá inflarse
		swell(pos);
		return -1; // No se ha podido expandir, fue necesario inflar
	}
	return 0; // Retorna cero si es que se ha podido expandir exitosamente
}

void phenotype::swell(int pos) {
	// Pos es el índice del elemento chico que hay que inflar
	// Es necesario elegir a cual de los stripe vecinos se hinchará
	int minNeighbor;
	if(pos == 0 || pos == stripes.size()-1) { // Si se trata de las condiciones de borde
		// Entonces solo hay un vecino candidato (el de al lado)
		if(pos == 0)
			minNeighbor = 1;
		if(pos == stripes.size()-1)
			minNeighbor = pos-1;
	} else {
		// Hay que decidir cual de los dos es el menor
		if(stripes.at(pos-1).height <= stripes.at(pos+1).height)
			minNeighbor = pos-1;
		else 
			minNeighbor = pos+1;
	}
	// Se hincha
	stripes.at(pos).height = stripes.at(minNeighbor).height;
	// Se combina en un solo stripe
	combine();
}

void phenotype::combine() {
	// Genera una pérdida de contexto respecto de los índices
	int i, aux = 0;
	piece x, xn;
	for(i = 0; i < stripes.size()-1; i++) {
		x = stripes.at(i);
		xn= stripes.at(i+1);
		if(x.height == xn.height) { // Si ambos tienen el mismo alto
			// Entonces hay que combinarlos, sumando sus anchos y dejando uno solo
			x.width += xn.width;
			stripes.erase(stripes.begin()+i+1);
			i--; // Accion de redo para el for
		}
	}
	refreshMinHeight(); // Actualiza el puntero al mínimo
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
	int i, pmin = 0, min = stripes.at(0).height;
	for(i = 1; i < stripes.size(); i++) {
		if(stripes.at(i).height < min)
			pmin = i;
	}
	lowest = pmin;
}

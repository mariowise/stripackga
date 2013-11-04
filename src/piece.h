#ifndef PIECE_H_
#define PIECE_H_

#include <vector>

using namespace std;

class piece {
	public:
		int id;			// Identificador de la pieza
		int width;		// Ancho de la pieza
		int height;		// Alto de la pieza
		int anchor[2];	// Punto de ancla (Esquina South-West)

		piece(int i, int w, int h) {
			id = i;
			width = w;
			height = h;			
		}
};

void readInput(char *);

#endif
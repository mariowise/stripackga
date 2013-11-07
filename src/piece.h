#ifndef PIECE_H_
#define PIECE_H_

#include <vector>

using namespace std;

class piece {
	public:
		int id;			// Identificador de la pieza
		int width;		// Ancho de la pieza
		int height;		// Alto de la pieza

		piece() {

		}

		piece(int w, int h) {
			width = w;
			height = h;
		}

		piece(int i, int w, int h) {
			id = i;
			width = w;
			height = h;
		}

		piece & operator=(const piece & orig) {
			id = orig.id;
			width = orig.width;
			height = orig.height;
		}

		void write(ostream &);
};

void readInput(char *);

#endif
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

class phenotype {
	public:
		int height; // Fitness
		vector<piece> stripes;
		vector<int> genoma;

		phenotype(int width) {
			stripes.push_back(piece(width, 0));
			lowest = 0; // El mas bajo será el único
		}

		void push(piece *);
		void write(ostream &);

	private:
		int lowest; // El índice del stripe mas bajo

		int expand(int, piece);
		void swell(int);
		void combine();
		void refreshHeights();
		void refreshMaxHeight();
		void refreshMinHeight();
};

void readInput(char *);

#endif
#ifndef PHENOTYPE_H_
#define PHENOTYPE_H_

using namespace std;

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
		float fitness();

	private:
		int lowest; // El índice del stripe mas bajo

		int expand(int, piece);
		int swell(int);
		void combine();
		void refreshHeights();
		void refreshMaxHeight();
		void refreshMinHeight();
};

#endif
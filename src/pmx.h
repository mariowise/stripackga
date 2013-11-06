#ifndef PMX_H_
#define PMX_H_

using namespace std;

class pmxCrossover {
	public:
		int length;
		int * son1;
		int * son2;

	private:
		int * parent1;
		int * parent2;
		int cuti; // Inicio del corte
		int cutj; // Final del corte
		vector<int> section1;
		vector<int> section2;
		vector<int> remains1;
		vector<int> remains2;

	public:
		pmxCrossover(int len, int * pa, int * ma) {
			length = len;
			parent1 = pa;
			parent2 = ma;
			
			// Cota anterior y posterior
			cuti = rand() % (length-1);
			cutj = cuti + rand() % (length -cuti);

			cout << "pmxCrossover {" << cuti << ", " << cutj << "} of " << length << endl; 
			cout << "- pa: ";
			write(pa);
			cout << "- ma: ";
			write(ma);
			
			// Init para listado de faltantes
			for(int i = 0; i < length; i++) {
				remains1.push_back(i);
				remains2.push_back(i);
			}
			
			// Espacio para los hijos
			son1 = (int *) malloc(sizeof(int) * length);
			son2 = (int *) malloc(sizeof(int) * length);
			for(int i = 0; i < length; i++) {
				son1[i] = -1;
				son2[i] = -1;
			}

			// Init para los hijos
			for(int i = cuti; i <= cutj; i++) {
				son1[i] = parent2[i];
				section1.push_back(son1[i]);
				remains1.erase(remains1.begin() + vectorFind(remains1, son1[i]));

				son2[i] = parent1[i];
				section2.push_back(son2[i]);
				remains2.erase(remains2.begin() + vectorFind(remains2, son2[i]));
			}

			// cout << "- son1: "; write(son1);
			// cout << "- son1 remains: "; write(remains1);

			// cout << "- son2: "; write(son2);
			// cout << "- son2 remains: "; write(remains2);

			cout << "- Constructor flag" << endl;	
		}
		
		~pmxCrossover() {}

		void cross();

		void write(int *);

		void write(vector<int> &);

	private:
		int vectorFind(vector<int> &, int);

};

#endif
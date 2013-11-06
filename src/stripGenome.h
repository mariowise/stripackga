#ifndef STRIPGENOME_H_
#define STRIPGENOME_H_

using namespace std;

class stripGenome : public GAGenome {

	public:
		int * stripCodex;
		int stripCodexSize;

		GADefineIdentity("stripGenome", 201);
		static void stripInitializer(GAGenome &);
		static float stripEvaluator(GAGenome &);
		static int stripCrossover(const GAGenome&, const GAGenome&, GAGenome*, GAGenome*);
		static int stripMutator(GAGenome &, float);

		// Constructores
		stripGenome() {
			initializer(stripInitializer);
			evaluator(stripEvaluator);
			crossover(stripCrossover);
			mutator(stripMutator);
		}
		
		stripGenome(const stripGenome & orig) {
			copy(orig);
		}

		virtual ~stripGenome() {
			
		}

		// Operadores
		stripGenome & operator=(const GAGenome & orig) {
			copy(orig);
			return *this;
		}

		// Métodos
		virtual void copy(const GAGenome & orig) {
			GAGenome::copy(orig);
			stripGenome & theOrig = (stripGenome &) orig; // Cast
			
			// Copy
			stripCodexSize = theOrig.stripCodexSize;
			stripCodex = (int *) malloc(sizeof(int) * stripCodexSize);
			for(int i = 0; i < stripCodexSize; i++)
				stripCodex[i] = theOrig.stripCodex[i];
		}
		
		virtual GAGenome * clone(GAGenome::CloneMethod) const {
			return new stripGenome(*this);
		}

		virtual int write(ostream & stream) const {
			int i;
			stream << "[";
			for(i = 0; i < stripCodexSize; i++) {
				stream << stripCodex[i];
				if(i != (stripCodexSize - 1))
					stream << ", ";
			}
			stream << "]";
		}
};

#endif
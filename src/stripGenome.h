#ifndef STRIPGENOME_H_
#define STRIPGENOME_H_

using namespace std;

class stripGenome : public GAGenome {

	public:
		int * stripCodex;
		int stripCodexSize;

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

		stripGenome(int size) {
			initializer(stripInitializer);
			evaluator(stripEvaluator);
			crossover(stripCrossover);
			mutator(stripMutator);
		}

		stripGenome(const stripGenome & orig) {
			copy(orig);
		}

		// Operadores
		stripGenome & operator=(const GAGenome & orig) {
			copy(orig);
			return *this;
		}

		// Métodos
		virtual void copy(const GAGenome & orig) {
			GAGenome::copy(orig);
			stripGenome & newGenome = (stripGenome &) orig;
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
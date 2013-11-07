
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <vector>
#include <pmx.h>

int pmxCrossover::vectorFind(vector<int> & vector, int elem) {
	for(int i = 0; i < vector.size(); i++)
		if(vector.at(i) == elem)
			return i;
	return -1;
}

void pmxCrossover::cross() {
	
	// cout << "- Comenzando cross" << endl;

	for(int i = 0; i < length; i++) {
		if(i < cuti || i > cutj) { // Si esta fuera de la sección
			if(vectorFind(section1, parent1[i]) == -1) { // Si no esta en la sección
				son1[i] = parent1[i];
				remains1.erase(remains1.begin() + vectorFind(remains1, son1[i]));
			} else
				son1[i] = -1; // Se marca como vacío
						
			if(vectorFind(section2, parent2[i]) == -1) { // Si no esta en la sección
				son2[i] = parent2[i];
				remains2.erase(remains2.begin() + vectorFind(remains2, son2[i]));
			} else 
				son2[i] = -1; // Se marca como vacío
		}
	}

	// En este momento tenemos espacios vacíos y una lista de remains
	for(int i = 0; i < length; i++) {
		if(son1[i] == -1) {
			son1[i] = remains1.back();
			remains1.pop_back();
		}

		if(son2[i] == -1) {
			son2[i] = remains2.back();
			remains2.pop_back();
		}
	}

	// cout << "- son1: ";
	// write(son1);
	// cout << "- son2: ";
	// write(son2);
}

void pmxCrossover::write(int * list) {
	cout << "[";
	for(int i = 0; i < length; i++) {
		cout << list[i];
		if(i != length-1)
			cout << ", ";
	}
	cout << "]" << endl;
}

void pmxCrossover::write(vector<int> & list) {
	int len = list.size();
	cout << "[";	
	for(int i = 0; i < len; i++) {
		cout << list.at(i);
		if(i != len)
			cout << ", ";
	}
	cout << "]" << endl;
}
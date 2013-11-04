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

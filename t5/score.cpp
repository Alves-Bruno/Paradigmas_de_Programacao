/*
 * score.cpp
 *
 *  Created on: 3 de mai de 2017
 *      Author: bruno
 */

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>


class Jogadores {
	std::string name;
	std::string atividade;
	int pontos;
public:
	Jogadores(std::string name, std::string atividade, int pontos) {
		this->name = name;
		this->atividade = atividade;
		this->pontos = pontos;
	}
	std::string getName() {
		return name;
	}
	int getPontos() {
		return pontos;
	}

	std::string getAtividade() {
		return atividade;
	}

	bool operator<(Jogadores& p) {

		return this->pontos > p.pontos;

	}

};


class Total {

	std::string nome;
	int pontos;

public:
	Total(std::string name, int pontos) {
		nome = name;
		this->pontos = pontos;
	}

	std::string getName() {
		return nome;
	}
	int getPontos() {
		return pontos;
	}
	void setPontos(int p) {
		this->pontos += p;
	}

};


// comparador de Persons pelo nome
bool alfabetica(Total& p1, Total& p2) {
	return p1.getName() < p2.getName();
}

bool pontuacao(Total& p1, Total& p2) {
	return p1.getPontos() > p2.getPontos();
}

//bool ordena(Jogadores& p1, Jogadores& p2) {
//	return p1.getPontos() > p2.getPontos();
//}

int main() {

	std::ifstream data("score.csv");

	std::string line;
	std::string cell[3];
	std::vector<Jogadores> v;
	std::vector<Total> total;

	while (std::getline(data, line)) {
		std::stringstream linestream(line);
		std::getline(linestream, cell[0], ',');
		std::getline(linestream, cell[1], ',');
		std::getline(linestream, cell[2], ',');
		v.push_back(Jogadores(cell[0], cell[1] ,std::stoi(cell[2])));
	}

	std::vector<Jogadores>::iterator it;

	std::sort(v.begin(), v.end());
	std::cout << "Ordena pontucao, todos os atributos:\n";
	for (it = v.begin(); it != v.end(); it++){
		std::cout << it->getName() << ", " << it->getAtividade() << ", " << it->getPontos() << std::endl;
	}

	// Add elementos na lista, se já existir o nome na lista -> add pontos.
	bool push = true;
	for (it = v.begin(); it != v.end(); it++){

		push = true;
		for (auto i = total.begin(); i != total.end(); i++){

			if(i->getName() == it->getName()){
				i->setPontos(it->getPontos());
				push = false;
			}
		}

		if(push == true){
			total.push_back(Total(it->getName(), it->getPontos()));
		}


	}

	// ordena com funcao cmpPerson definida fora da classe
	std::sort(total.begin(), total.end(), alfabetica);
	std::cout << "\nOrdena ordem alfabetica, nome e total de pontos:\n";
	for (auto i = total.begin(); i != total.end(); i++){
		std::cout<< i->getName() << ", " << i->getPontos() << std::endl;
	}

	std::sort(total.begin(), total.end(), pontuacao);
	std::cout << "\nOrdena pontuacao, nome e total de pontos:\n";
	for (auto i = total.begin(); i != total.end(); i++){
		std::cout<< i->getName() << ", " << i->getPontos() << std::endl;
	}


}





/*
 * biscoitos.cpp
 *
 *  Created on: 10 de mai de 2017
 *      Author: bruno
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <random>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

# define PI 3.141592


float random_floats(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

class Contabilidade {

private:

	int Pequenos;
	int Medios;
	int Grandes;
	float Valor_Total;

public:

	Contabilidade(){
		Pequenos = Medios = Grandes = 0;
		Valor_Total = 0.00;
	}

	void Pequenos_add(void){
		Pequenos += 1;
	}
	void Medios_add(void){
		Medios += 1;
	}
	void Grandes_add(void){
		Grandes += 1;
	}

	void Total_add(float valor){
		Valor_Total += valor;
	}

	int Get_Pequenos(void){
		return Pequenos;
	}
	int Get_Medios(void){
		return Medios;
	}
	int Get_Grandes(void){
		return Grandes;
	}

	float Get_ValorTotal(void){
		return Valor_Total;
	}
};


class Biscoito {

protected:

	float Valor;
	float Tamanho; //Representa a area do Biscoito
	std::string Tipo;


public:


	void Calcula_preco(Contabilidade* cont){
		if(this->Tamanho <= 33){
			cont->Pequenos_add();
			Valor = 3.50;
			cont->Total_add(Valor);
//			std::cout << "PEQUENO" << std::endl  << std::endl;

		}else if(this->Tamanho > 33 && this->Tamanho <= 66){
			cont->Medios_add();
			Valor = 6.00;
			cont->Total_add(Valor);
//			std::cout << "MEDIO" << std::endl << std::endl;

		}else if(this->Tamanho > 66){
			cont->Grandes_add();
			Valor = 9.00;
			cont->Total_add(Valor);
//			std::cout << "GRANDE" << std::endl << std::endl;
		}
	}

	float getValor( void ){
		return Valor;
	}
	float getTam( void ){
		return Tamanho;
	}

	std::string getTipo(void){
		return Tipo;
	}

	bool operator<(Biscoito& p) {

		return this->Tamanho > p.Tamanho;
	}
};

class Triangulo : public Biscoito{

private:

	float h;
	float base;

public:

	Triangulo(Contabilidade* cont){

		h = random_floats(1.00, 15.00);
		base = random_floats(5.00, 14.00);
		Tipo = "Triangulo";
		Tamanho = this->CalcArea();
//		std::cout << "Triangulo(" << h << ", " << base << "). A = " << Tamanho << std::endl;
		this->Calcula_preco(cont);

	}

	Triangulo(float h, float b){

		this->h = h;
		base = b;
		Tamanho = this->CalcArea();
	}

	float CalcArea(){
		return (base*h)/2;
	}


};

class Circulo : public Biscoito{

private:

	float raio;

public:

	Circulo(Contabilidade* cont){

		raio = random_floats(1.00, 5.50);
		Tipo = "Circulo";
		Tamanho = this->CalcArea();
//		std::cout << "Circulo(" << raio << "). A = " << Tamanho << std::endl;
		this->Calcula_preco(cont);

	}

	float CalcArea(){
		return PI * raio * raio;
	}


};

class Retangulo : public Biscoito{

private:

	float h;
	float base;

public:

	Retangulo(Contabilidade* cont){

		h = random_floats(1.00, 10.00);
		base = random_floats(3.00, 10.00);
		Tipo = "Retangulo";
		Tamanho = this->CalcArea();
//		std::cout << "Retangulo(" << h << ", " << base << "). A = " << Tamanho << std::endl;
		this->Calcula_preco(cont);

	}

	Retangulo(float h, float b){

		this->h = h;
		base = b;
		Tamanho = this->CalcArea();
	}

	float CalcArea(){
		return (base*h);
	}


};


Biscoito Random_biscoito(Contabilidade *cont){

	Biscoito retorno;
	int forma = rand() % 3;
	switch(forma){
	case 0:
		retorno = Triangulo(cont);
		break;
	case 1:
		retorno = Circulo(cont);
		break;
	case 2:
		retorno = Retangulo(cont);
		break;
	}

	return retorno;
}


int main(int argc, char **argv) {

	srand(time(0));

	if(argc < 2){
		std::cout << "Por favor, passe o numero de biscoitos que devem ser produzidos como 1º argumento." << std::endl;
		exit(0);
	}

	int entrada = atoi(argv[1]);

	Contabilidade* contabilidade = new Contabilidade;
	std::vector<Biscoito> Cookies;
	std::vector<Biscoito>::iterator it;



	for(auto i = 0; i < entrada; i++){
		Cookies.push_back(Random_biscoito(contabilidade));
	}

	// ordena com operador '<' definido na classe
	std::sort(Cookies.begin(), Cookies.end());

	std::cout << std::endl;
	std::cout << "Tamanho dos Bisoitos:" << std::endl << std::endl;
	for (it = Cookies.begin(); it != Cookies.end(); it++)
	      std::cout<< "\tBiscoito:" << it->getTipo() << " = " << it->getTam() << std::endl;



//	auto teste = Random_biscoito(contabilidade);
//	std::cout << teste->getTam();


	std::cout << std::endl;
	std::cout << "TOTAL:\n" << "\t Pequenos: " << contabilidade->Get_Pequenos() << ", Valor: R$" << std::fixed << std::setprecision(2)
			<< contabilidade->Get_Pequenos() * 3.50 << std::endl;
	std::cout << "\t Medios: " << contabilidade->Get_Medios()<< ", Valor: R$" << std::fixed << std::setprecision(2)
			<< contabilidade->Get_Medios() * 6.00 << std::endl;
	std::cout << "\t Grandes: " << contabilidade->Get_Grandes() << ", Valor: R$" << std::fixed << std::setprecision(2)
			<< contabilidade->Get_Grandes() * 9.00 << std::endl;
	std::cout << "\t TOTAL ARRECADADO: R$" << std::fixed << std::setprecision(2) << contabilidade->Get_ValorTotal() << std::endl;

	return 0;
}













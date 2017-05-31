#include <string>
#include <stdexcept>
#include <FL/fl_ask.H>
#include "window.h"
#include <algorithm>
#include <random>

class Sortear : public UserInterface {

	std::vector<int> vec_guests;
	bool fill_vector;
	int actual_guest;
	int total_guests;

public:

	Sortear() {
		btSortear->callback((Fl_Callback*) btSortearAction, (void*)(this));
		btReset->callback((Fl_Callback*) btResetAction, (void*)(this));

	}

	void show() {
		// Mostra janela
		w->show();
		fill_vector = true;
		actual_guest = 0;
		total_guests = 0;
	}

	void vector_fill(int guests){

		if(fill_vector == true){

			for(int i = 1; i <= guests; i++){
				vec_guests.push_back(i);
			}
			std::random_shuffle(vec_guests.begin(), vec_guests.end());
			total_guests = guests;
			fill_vector = false;

		}
	}

	std::string vector_pop(void){

		int value = vec_guests.back();
		vec_guests.pop_back();
		return std::to_string(value);


	}

	void Reset(void){
		fill_vector = true;
		vec_guests.clear();
		total_guests = 0;
		actual_guest = 0;
	}

	// Funcao callback chamada quando pressionado botao 'Sortear'.
	static void btSortearAction(Fl_Widget* btn, void* userdata) {
		Sortear* gui = static_cast<Sortear*>(userdata);

		// Completa o vetor com os valores validos
		try{
			gui->vector_fill(std::stoi(gui->numGuests_in->value()));
		} catch (std::invalid_argument&) {
			fl_alert("Por favor, insira um valor.");
			return;
		}

		if(gui->actual_guest < gui->total_guests){

			try{

				gui->actual_guest++;
				// Retira um elemento do vector (SORTEIA)
				std::string value = gui->vector_pop();

				gui->boxResult->copy_label(value.data());
				std::string char_guests = std::to_string(gui->actual_guest);
				std::string str_xganhador = char_guests + "º Ganhador:";
				gui->xGanhador->copy_label(str_xganhador.data());
				std::string browser = char_guests + "º Ganhador -> " + value;
				gui->line_browser->add(browser.data(), 0);


			} catch (std::invalid_argument&) {
				fl_alert("Valor inválido. Por favor, insira um número inteiro.");
			} catch (std::out_of_range&) {
				fl_alert("Valor inválido. Por favor, insira um menor valor.");
			}
		} else fl_alert("Todos os números já foram sorteados, clique em RESET.");
	}



	//   Funcao callback chamada quando pressionado botao 'Reset'
	static void btResetAction(Fl_Widget* btn, void* userdata) {
		Sortear* gui = static_cast<Sortear*>(userdata);
		gui->numGuests_in->value("");
		gui->boxResult->copy_label("");
		gui->xGanhador->copy_label("                           ");
		gui->line_browser->clear();
		gui->Reset();
	}

};

int main() {
	Sortear gui;
	gui.show();
	srand(time(NULL));


	return Fl::run();
}



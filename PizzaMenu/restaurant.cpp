#include "restaurant.h"


void Restaurant::load_data() {

	//open the .txt files

	this->m.load_pizza();
}

void Restaurant::view_menu(){
	this->m.display_menu();
}

void Restaurant::add_a_pizza(Pizza &p){
	this->m.add_p(p);
}


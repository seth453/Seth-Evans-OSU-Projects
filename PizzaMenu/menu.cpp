#include "menu.h"
#include <iostream>

Menu::Menu() {
	//initialize variables
	this->num_pizza = 0;
	this->pizza_arr = NULL;
}


Menu::~Menu() {
	//destructor to free the memory
	if (this->pizza_arr != NULL){
		delete [] this->pizza_arr;
		this->pizza_arr = NULL;
	}
}

void Menu::load_pizza(){
	//hard-code values here
	
	//for your assignment, you might want to pass in
	// an fstream obj to populate
	this->num_pizza = 2;
	this->pizza_arr = new Pizza[this->num_pizza];

	//load data for each pizza object
	for (int i = 0; i < this->num_pizza; ++i)
	{
		this->pizza_arr[i].load_a_single_pizza();
	}

}

void Menu::display_menu(){
	cout << "Num of pizza: " << this->num_pizza << endl;
	for (int i = 0; i < this->num_pizza; ++i)
	{
		this->pizza_arr[i].display_a_single_pizza();
	}
	
}


//add p into our pizza_arr
void Menu::add_p(Pizza& p){
	
	//allocate a temp pizza arr with size: num_pizza + 1;
	Pizza* temp = new Pizza [this->num_pizza + 1];

	//get all pizza from pizza_arr into new temp pizza arr
	for (int i = 0; i < this->num_pizza; ++i)
	{
		temp[i] = this->pizza_arr[i];
	}

	//add p into temp pizza arr, index: num_pizza
	temp[this->num_pizza] = p;

	//free the current pizza_arr
	delete [] this->pizza_arr;

	//assign pizza_arr to temp
	this->pizza_arr = temp;

	//increment num_pizza
	++this->num_pizza;


}
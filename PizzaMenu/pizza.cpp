#include "pizza.h"

using namespace std;

Pizza::Pizza() {
	//hard-code values here
	this->name = "ppp";
	this->price = 100;
}

void Pizza::load_a_single_pizza(){
	//hard-code values here
	
	//for your assignment, you might want to pass in
	// an fstream obj to populate the pizza
	this->name = "Some_Pizza";
	this->price = 5.5;
}

void Pizza::display_a_single_pizza() {
	cout << "-------------------" << endl;
	cout << "Name: " << this->name << endl;
	cout << "Price: " << this->price << endl;
	cout << "-------------------" << endl;
}
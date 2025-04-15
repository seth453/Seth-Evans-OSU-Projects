#ifndef PIZZA_H
#define PIZZA_H 

#include <string>
#include <iostream>

using namespace std;

class Pizza
{
private:
	string name;
	float price;
public:
	Pizza(); //constructor 
	void load_a_single_pizza();

	void display_a_single_pizza();
	
};
#endif
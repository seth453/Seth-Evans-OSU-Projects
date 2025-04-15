#ifndef RESTAURANT_H
#define RESTAURANT_H 

#include "menu.h"
#include <string>

using namespace std;


class Restaurant
{
private:
	Menu m;
	string address;
public:
	void load_data();

	void view_menu();

	void add_a_pizza(Pizza& );
	
};
#endif
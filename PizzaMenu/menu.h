#ifndef MENU_H
#define MENU_H 

#include "pizza.h"

class Menu
{
private:
    Pizza* pizza_arr;
    int num_pizza;
public:
	Menu();
	~Menu();

	void load_pizza(); 

	void display_menu();

	//add p into our pizza_arr
	void add_p(Pizza& p);
	
};
#endif
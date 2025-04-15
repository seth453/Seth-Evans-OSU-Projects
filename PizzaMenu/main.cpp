#include <iostream>

#include "restaurant.h"
#include "pizza.h"

using namespace std;

int main()
{
	Pizza p;
	Restaurant r;
	r.load_data();

	r.view_menu();

	r.add_a_pizza(p);

	r.view_menu();



	return 0;
}
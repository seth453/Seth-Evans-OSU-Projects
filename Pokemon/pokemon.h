#ifndef STUDENT_DB_H
#define STUDENT_DB_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
	        
/*student struct with object data types*/
struct Pokemon {
	int poke_level;
	string name;
	string type;
	int num_moves;
	string* moves;
}; 

struct Pokedex {
   string trainer;
   int trainer_level;
   int num_pokemon;
   Pokemon* db;
};


/*Declare fucntion arguments*/
Pokemon* create_pokemons(int numPoke);
void populate_pokedex_data(Pokemon * db, int numPoke, ifstream & inFile);
void delete_info(Pokemon & db);
void populate_pokedex_data(Pokemon* db, int numPoke, ofstream& outFile, int trainer_level);
void search_by_type(Pokemon* db, int numPoke);
#endif


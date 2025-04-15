#include "pokemon.h"
#include <iostream>
#include <string>
#include <fstream>
        
	 
using namespace std;
	    
/*Creates dynamically allocated array based on int number of students from the input file, returns array */
		 
Pokedex* create_pokemons(int numStudents) {
Pokedex* db = new Pokedex[numPoke];
return db;
}
			 
/*Inputs the file data using ifstream inFile and reads through to store alloacted array of student info passed in*/
			   
void populate_pokedex_data(Pokedex* db, int numPoke, ifstream& inFile) {
	for(int i = 0; i < numPoke; i++) {
		inFile >> db[i].poke_level >> db[i].name >> db[i].type >> db[i].num_moves >> db[i].moves;
	}
 }
/*Deletes all dynamic memory created in the program.*/
void delete_info(Pokedex*& db) {
	delete[] db;
	db = NULL;
 }
		
/*Loops through file for number of students to detect a string that matches last name, if found, prints all info. Inputs Last name string from user, outputs student info.*/
					    
void search_by_last(Pokedex* db, int numPoke){ 
   string name;
   cout << "Enter the name of Pokemon: " << endl;
   cin >> name;
   bool found = false; 
   for (int i = 0; i < numPoke; i++) {
	if (db[i].name.compare(name) == 0) {
	  cout << "Level: " << db[i].poke_level << endl;
          cout << "Name: " << db[i].name << endl;
	  cout << "Type: " << db[i].type << endl;
	  cout << "Number of abilities: " << db[i].num_moves << endl;
          cout << "Abilities : " << db[i].moves << endl;
	  found = true;     
	}
   }
	if (!found) {
    		cout << "No Pokemon found. " << endl; 
	}
}
/*Searches by type*/ 

void search_by_type(Pokedex* db, int numPoke) {
string type;
cout << "Enter the type of Pokemon: " << endl;
cin >> type;
bool found = false;
for (int i = 0; i < numPoke; i++) {
      if (db[i].type.compare(type) == 0) {
		cout << "Level: " << db[i].poke_level << endl;
                cout << "Name: " << db[i].name << endl;
		cout << "Type: " << db[i].type << endl;
		cout << "Number of abilities: " << db[i].num_moves << endl;
	        cout << "Abilities : " << db[i].moves << endl;
		found = true;
       }
}
       if(!found) {
       cout << "No Pokemon found." << endl; 
       } 
}

/*Function prints honor roll students. Inputs user choice of search option, then outputs students with GPA > 3.5*/
								     
void populate_info(Pokedex* db, int numPoke, ofstream& outFile, int trainer_level) {
        cout << "Note: You may only upgrade a Pokemon as high as your level. " << endl;
	cout << "Enter the name of the Pokemon you would like to upgrade: " << endl;
        string name;
	cin >> name;
	for (int i = 0; i < numPoke; i++){
		if (db[i].poke_level <= level) {
		/*cout << "ID: " << db[i].id << endl;
		cout << "First: " << db[i].firstName << endl;
		cout << "Last: " << db[i].lastName << endl;
		cout << "Major: " << db[i].major << endl;
		cout << "GPA: " << db[i].gpa << endl;
		}*/
		outFile << "Level: " << db[i].poke_level << endl;
	        outFile << "Name: " << db[i].name << endl;
		outFile << "Type: " << db[i].type << endl;
		outFile << "Number of abilities: " << db[i].num_moves << endl;
		outFile << "Abilities: " << db[i].moves << endl;
		} 
          }
		outFile.close();
}



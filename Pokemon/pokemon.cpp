/*1.Using fstream library check if file exists using ifstream
  2. Reprompt until valid file name given
  3. Open file and read infyo
  */
        
#include <iostream>
#include <fstream>
#include <string>
#include "pokemon.h"
	        
using namespace std;
		  
int main() {
		      
ifstream inFile;
string filename;
int numStudents;
string trainer;
int trainer_level;
			    
cout << "Enter your name: ";
cin >> trainer;
cout << "Enter your level: ";
cin >> trainer_level;
cout << "Enter input file name: ";
cin >> filename;
				  
 /*Checks if file opens succesfully*/
inFile.open(filename.c_str());
				   
while(!inFile.good()) {
	cout << "Error: File doesnt exist" << endl;
	return 0;
}
				    
inFile >> numStudents;
Pokemon *Pokedex = create_pokemons(numPoke);
populate_pokedex_data(Pokedex, numPoke, inFile);
inFile.close();
				        
int choice;
string name;
					  
cout << "Search by name? (1) Search by type? (2) Update/Evolve a Pokemon? (3) or Quit (4)? " << endl;
cin >> choice;
ofstream outFile("output.txt");
					     
switch(choice) {
	case 1:
		search_by_last(Pokedex, numPoke);
		break;
	case 2:
		search_by_type(Pokedex, numPoke/*, outFile, level*/);
		break; 
	case 3:
		print_honor_roll_students(Pokedex, numPoke, outFile, trainer_level);
		/*upgrade_pokemon(); */
		/*Print list*/ 
		//cout << "Which pokemon would you like to upgrade?" << endl;
		break;
	case 4:
		return 0;
		default:
		cout << "Invalid choice. " << endl;
	break;
}
outFile.close();
delete_info(Pokedex& db);
return 0;
}


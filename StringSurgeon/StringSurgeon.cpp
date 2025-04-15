#include <iostream> 
#include <string> 
#include <cstring> 
#include <stdio.h> 
#include <stlib.h> 

using namespace std; 

void inputLine(char* &, int, char*); 
void beginProg(char* &, int); 
void vowelsConso(char* &); 
void lettSwap(char* &); 
void revString(char*); 
bool palinDro(char*); 
void wordFreq(char*); 
char flipperCase(char); 
void delSpace(char*, char* &); 
int wordQuan(char*, string); 
char convertLow(char); 

int main() { 

int length = 1024; 
char *mainInput = new char[length]; 

beginProg(mainInput, length - 1); 

delete []mainInput; 

return 0; 
} 

void beginProg(char* &input, int length) { 

char message[] = "Type 'exit' to quit the program. Type any other string to begin:  " << endl; 
inputLine(input, length, message); 

	if(strstr(input, "exit")) { 
		cout << "Exiting program..." << endl; 
		exit(0); 
	} 

cout << "Your string is: " << input << endl; 
int choice; 
cout << "What would you like to analyze of your string? Vowels vs. Consonants (1) , Letter Swap (2), Flip String (3), Palindrome detector (4), or Word frequency (5) ?:  " << endl; 
cin >> choice; 
cout << "You have chose to analyze "; 
switch(option){ 
	case 1: 
		cout << "Vowels vs. Consonants: " << endl; 
		vowelsConso(input);
		break; 
	case 2: 
		cout << "Letter Swap. " << endl; 
		lettSwap(input); 
		cout << "Your new string is:  " << endl; 
	case 3: 
		revString(input); 
		cout << "Your original string:  " << input << endl; 
		break; 
	case 4: 
		if(palinDro(input)){ 
			cout << "Your input is a palindrome. " << endl; 
		} 
		else { 
			cout << "Your input is not a palindrome. " << endl; 
		} 
		break; 
	case 5: 
		wordFreq(input); 
		break; 
		default: 
		beginProg(input, length); 
		break; 
	      } 
cin.clear(); 
beginProg(input, length); 
} 

char covertLow(char c){ 
	if(c >= 'A' && c <= 'Z') 
		return c + 32; 
	return c; 
	} 
void wordFreq(char* input) { 
	int N; 

	cout << "How many words do you want to search for?:  " << endl; 
	cin >> N; 
	string* wordArray = new string[N]; 

	for(int i = 0; i < N; i++) { 
		cin.ignore(); 
		string word; 
		cout << "Enter a word: " << endl; 
		cin >> word; 
		wordArray[i] = word; 
} 

for(int i = 0; i < N; i++){ 
	int instances = 0; 
	int letterIndex = 0; 

	for(int = 0; i < strlen(original); i++){ 
		if(original[i] == wordtofind[letterIndex] ){ 
		letterIndex++; 
		} 
			else{ 
			letterIndex = 0; 
			} 
	if(letterIndex == wordtofind.length()){ 
		instances++; 
		letterIndex = 0; 
		} 
	}
	return instances; 
} 

bool palinDro(char* string) { 
	char* cleanstring; 
	cleanstring = new char[strlen(string)];
	delSpace(string, cleanstring); 
	int x = strlen(cleanstring) - 1; 

	for( int i = 0; x >= i; i++) { 
		if (cleanstring[x] !=cleanstring[i] ){ 
			delete []cleanstring; 
			return false; 
		} 
		x--; 
	} 
	delete []cleanstring; 
	return true; 
} 

void delSpace(char* string, char* &stringnew){ 
	for(int i = 0; string[i] !- '\0'; i++) { 
	if (string[i] > 64 && string[i] < 91) { 
		string[i] = flipperCase(string[i] ); 
	} 
	if(string[i] > 96 && string[i] < 123) 
	strncat(stringnew, &string[i], 1); 
	} 
} 

void inputLine(char* &charArray, int length, char* message) { 
	cin.clear(); 

	cout << message; cin.getline(charArray, length); 

	if(cin.fail()) { 
		cin.ignore(length, '\n'); 
		cin.clear(); 
		inputLine(charArray, length, message); 
	} 

	cin.clear(); 
	cin.ignore(); 
} 














	



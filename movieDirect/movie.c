#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <dirent.h> 
#include <sys/stat.h> 
#include <time.h> 
#include <errno.h> 

#define MAX_LINE_LENGTH 100 


void ProcessFile(const char* fileName); //Process a specified file
char* LargestCSV(); //A function to retrieve largest file
char* SmallestCSV(); //A function to retrieve smallest file 
char* SpecifyFile(); //A function to enable user to search file by name
void MainMenu(); //A function to display user options
void FileMenu(); //A function to display file options
int compareFilesize(const struct dirent **a, const struct dirent **b); //A function to asses largest csv file in directory
void Directory(char* directoryName, char movies[][MAX_LINE_LENGTH], int movieCount); //A function that intializes directory and populates with files

int main () { 
	int choice; 
	do { 
		MainMenu(); //Display main menu
		scanf("%d", &choice); //Get user choice

		switch(choice) { //User options functionality, will call upon functions to operate
		case 1: 
			FileMenu(); //User wants to see file choices
			int FileChoice; 
			scanf("%d", &FileChoice); //Get user choice

			char* selectFile = NULL; 
			if(FileChoice == 1) { 
				selectFile = LargestCSV();
			} else if (FileChoice == 2) { 
				selectFile = SmallestCSV(); 
			} else if (FileChoice == 3) { 
				selectFile = SpecifyFile();
			} else { 
				printf("Invalid input choice. Enter an integer 1-3.\n");
				break;
			}
			if(selectFile != NULL) { 
				ProcessFile(selectFile); //Process the slectyed file 
				free(selectFile); //Free memeory
			}
			break;

	    case 2: 
		printf("Exiting the program.\n"); //User wants to end program
		exit(0); 
		break; 

		default: 
		printf("Invalid choice. Please try again.\n"); //User enters a integer thats not accepted. We dont have to worry about other data type error handling
		}
	} while(1);
	return 0;
}

char* LargestCSV() { 
	struct dirent **namelist; 
	int n = scandir(".", &namelist, NULL, compareFilesize); //Scan current directory
	if (n < 0) { 
		perror("scandir"); //If scan fails, error
		return NULL;
	}

	for (int i = 0; i < n; ++i) //Iterate through list of files
	 {
	 	if (strncmp(namelist[i]->d_name, "movies_", 7) == 0 && strstr(namelist[i]->d_name,".csv")) //Search for proper file names
	 	{
	 		char* LargestCSV = strdup(namelist[i]->d_name); //duplicate file name- Exploration: strings ex
	 		printf("Now processing the chosen file named: %s\n", LargestCSV);
	 		free(namelist[i]); 
	 		free(namelist);
	 		return LargestCSV; // return largest file
	 	}
	 	free(namelist[i]);
	}
	free(namelist); 
	printf("No file found\n"); 
	return NULL; 
}

char* SmallestCSV() { 
	struct dirent **namelist; 
	int n = scandir(".", &namelist, NULL, compareFilesize); 
	if (n < 0) { 
		perror("scandir"); 
		return NULL;
	}

	for (int i = n - 1; i >= 0; --i) //Iterate through list of files
	 {
	 	if (strncmp(namelist[i]->d_name, "movies_", 7) == 0 && strstr(namelist[i]->d_name,".csv")) //Search for proper file names
	 	{
	 		char* SmallestCSV = strdup(namelist[i]->d_name); //duplicate file name
	 		printf("Now processing the chosen file named: %s\n", SmallestCSV); 
	 		free(namelist[i]);
	 		free(namelist); 
	 		return SmallestCSV; // return smallest file
	 	}
	 	free(namelist[i]);
	}
	free(namelist); 
	printf("No file found\n"); 
	return NULL; 
}

char* SpecifyFile() { 
	char fileName[100]; 
	printf("Enter the complete file name with the extension\n"); 
	scanf("%s", fileName); //read specified file name
	FILE *file = fopen(fileName, "r"); //try to open file
	if (file == NULL)
	{
		printf("The file %s was nout found. Try again\n", fileName);
		return NULL; //file doesnt exist
	}
	fclose(file); 
	return strdup(fileName); //Return file name if exists
}

void MainMenu() 
{ 
	//Show user the options
    printf("\n1. Select file to process\n"); 
	printf("2. Exit program\n"); 
	printf("Enter a choice 1 - 2:\n"); 
	}

void FileMenu() 
{  
	//Show user the options
	printf("\nWhich file do you want to process?\n"); 
	printf("Enter 1 to pick the largest file\n"); 
	printf("Enter 2 to pick the smallest file\n"); 
	printf("Enter 3 to specify a file\n"); 
	printf("Enter a choice 1 - 3:\n"); 
} 

int compareFilesize(const struct dirent **a, const struct dirent **b) { 
	struct stat A, B; 
	stat((*a)->d_name, &A); //get file stats for a file a
	stat((*b)->d_name, &B); //get file stats for a file b
	return (A.st_size > B.st_size) ? -1 : (A.st_size < B.st_size) ? 1 : 0; //Compare file sizes
}

//Make directory and write movies to year files
void Directory(char* directoryName, char movies[][MAX_LINE_LENGTH], int movieCount) { 
	
	mode_t oldMask = umask(027); //set umask (rw-r-----) for file permissions, converted from 640 octal mode; Exploration: Permissions ex

	for (int i = 0; i < movieCount; ++i)
	{
		char title[100], year[4]; 
		sscanf(movies[i], "%[^,],%[^,]", title, year); //Get title and year from each line
		char filePath[100]; 
		sprintf(filePath, "%s/%s.txt", directoryName, year); //Create file path based on year

		FILE *yearFile = fopen(filePath, "a"); //Open the year file in append mode
		if (yearFile) { 
			fprintf(yearFile, "%s\n", title); //write movie title to year file
			fclose(yearFile);
		} else { 
			printf("Error writing to file %s: %s\n", filePath, strerror(errno));
		}
	}
	umask(oldMask);
}
//process selected file
void ProcessFile(const char* fileName) { 
	FILE *file = fopen(fileName, "r"); 
	if (!file)
	{
		printf("Error opening file: %s\n", fileName); //file cant be opened
		return;
	}

	char line[MAX_LINE_LENGTH]; 
	char movies[100][MAX_LINE_LENGTH]; 
	int movieCount = 0; 
	fgets(line, MAX_LINE_LENGTH, file); //skip header line
	while (fgets(line, MAX_LINE_LENGTH, file)) { 
		strcpy(movies[movieCount++], line); //store each movie line
	}
	fclose(file);

//Make random numbered directory name
	srand(time(0)); 
	int randomNum = rand() % 100000; 
	char directoryName[100]; 
	sprintf(directoryName, "evansset.movies.%d", randomNum); //make random name with ONID

//Octal code for owner has r,w,x and group has r,x. permissions to directory
	if(mkdir(directoryName, 0750) == 0) {  //octal code for (rwxr-x---) for file permissions;
		printf("Created directory with name: %s\n", directoryName); 
	} else { 
		printf("Error creating directory: %s\n", strerror(errno)); 
		return; 
	}
//Process movies and write to directory
	Directory(directoryName, movies, movieCount);
}
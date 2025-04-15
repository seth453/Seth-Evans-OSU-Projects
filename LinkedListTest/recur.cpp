#include <iostream>
using namespace std;

//print (num_spaces) white spaces
void print_spaces(int num_spaces) {
    for (int i = 0; i < num_spaces; i++) {
        cout << " ";
    }
}

//print stars, with white spaces in between
void print_stars(int num_stars) {
    for (int i = 0; i < num_stars; i++) {
        if (i == 0 || i == num_stars - 1) {
            cout << "*";
        } else {
            cout << " ";
        }
    }
    cout << endl;
}

/*********************************************************************
** Function: patternHelper()
** Description:  helper function to assist in new variable for row manipulation, as well as recursive calls to n & col
** Parameters: number of rows to print, column of white spaces, a specific row 
** Pre-Conditions: Odd number of int rows, any number of white space
** Post-Conditions: A diamond of user specified size on positioning
*********************************************************************/
void patternHelper(int n, int col, int row) {
    if(row > n) { 
        return;
    } 

    print_spaces(col + 1); 
    print_spaces(n - row);
    print_stars(2 * row - 3);  

    //recursively calledcle
    patternHelper(n, col, row + 1);

    print_spaces(col); 
    print_spaces(n - row);
    print_stars(2 * row - 1);  

} 

//Calls helper function
void pattern(int n, int col) { 
    patternHelper(n, col, 0);
}

int main() {
    int n, col;
    cout << "Enter the number of rows (odd number): ";
    cin >> n; 
    cout << "Enter the leading white spaces: ";
    cin >> col;

    pattern(n, col); 

    return 0;
}
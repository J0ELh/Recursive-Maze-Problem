#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <ctype.h>

//reads in file of name specified by user and fills 2D vector with its characters
//returns number of rows and cols (indirectly) that represent the rows and columns of the 2D vector
//returns 2D vector filled with characters from file
std::vector<std::vector<char>> readFile(int & rows, int & cols){
    std::cout << "Enter filename: ";
    std::string filename = "";
    std::cin >> filename;
    std::cout << std::endl;
    std::ifstream fileInput;
    fileInput.open(filename);
    //gets input of the file with the name specified by user
    
    char character;
    int row = 0;
    int col = 0;
    fileInput >> rows;
    fileInput >> cols;
    //set the number of rows and cols based on the first two numbers in the file
    std::vector<std::vector<char>> grid(rows);
    for (int i = 0; i < rows; i++){
        grid[i] = std::vector<char>(cols);
    }
    //creates 2D vector of size rows * cols
    while (!fileInput.eof()){//CHECK WHY I NEED THE IF ROW !+ ROWS STATEMENT
        fileInput >> character;
        //read character from file
        if (row != rows){
            grid[row][col] = character;
            //if in bounds assign the character to the 2D vector at index [row][col]
        }
        col++;
        if (col == cols){
            //start a new row in the array once all colums of previous row are filled
            col = 0;
            row++;
        }

    }
    fileInput.close();
    return grid;
} 


//recurisvely finds a path through the 2D array that matches with the word given by the user. starts from first matching letter
//find path and marks it in the "blank" array
//does not choose a path with letters it has used before
//grid is the 2D vector of characters
//row is the row to search within
//col is the column to search within
//word is the word or substring which is searched for in the array
//gridBlank is the blank array filled with '-' that is filled in with the path of the word if applicable
//returns true if path is found and falls if no path is found
bool findPath(std::vector<std::vector<char>> & grid, int row, int col, std::string word, std::vector<std::vector<char>> & gridBlank ){
    if (word.length() == 1){
        gridBlank[row][col] = '*';
        //if the last letter has been found, mark it with a '*' in the gridBlank 2D vector and return true
        return true;
    }
    if (row-1 != -1 && grid[row-1][col] == word[1] && findPath(grid, row -1, col, word.substr(1), gridBlank)&& gridBlank[row][col] == '-' ){//UP
        gridBlank[row][col] = '^';
        //mark gridBlank with the up symbol and return true if the upper field is in bound, matches the searched letter, has not been used before, and the rest of the path works out
        return true; 
    }
    if (col+1 != (int)grid[row].size() && grid[row][col+1] == word[1] && findPath(grid, row, col +1, word.substr(1), gridBlank) && gridBlank[row][col] == '-' ){//RIGHT
        gridBlank[row][col] = '>';
        //mark gridBlank with the right symbol and return true if the right field is in bound, matches the searched letter, has not been used before, and the rest of the path works out
        return true; 
    }
    if (row+1 !=  (int)grid.size() && grid[row+1][col] == word[1] && findPath(grid, row +1, col, word.substr(1), gridBlank) && gridBlank[row][col] == '-'){//DOWN
        gridBlank[row][col] = 'V';
        //mark gridBlank with the down symbol and return true if the lower field is in bound, matches the searched letter, has not been used before, and the rest of the path works out
        return true; 
    }
    if (col-1 != -1 && grid[row][col-1] == word[1] && findPath(grid, row, col -1, word.substr(1), gridBlank)&& gridBlank[row][col] == '-' ){//LEFT
        gridBlank[row][col] = '<';
        //mark gridBlank with the left symbol and return true if the left field is in bound, matches the searched letter, has not been used before, and the rest of the path works out
        return true; 
    }
    return false;
    //if no path is found return false
}

//prints a given 2D vector in the right format
//grid is the 2D vector to be printed
//rows is the number of rows of the vector
//cols is the number of columns of the vector
//no return
void printVector(std::vector<std::vector<char>> & grid, int & rows, int & cols){
    for (int i = 0; i < rows; i++){
        //for each row
        for (int j = 0; j < cols; j++){
            //for each column
            std::cout << grid[i][j] << " ";
            //print vector at index i and j
        }
        std::cout << std::endl;
    }
}

//checks every index of the vector for if a path exists
//grid is the 2D vector to check for the starting letter
//rows is the number of rows of the vector
//cols is the number of columns of the vector
//word is the word to search for
//gridBlank is the vector filled with '-'
//returns true if path is found
bool pathExists(std::vector<std::vector<char>> grid, int rows, int cols, std::string word, std::vector<std::vector<char>> gridBlank){
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++){
            if (grid[row][col] == word[0]){
                if (findPath(grid, row, col, word, gridBlank)){
                    printVector(gridBlank, rows, cols);
                    return true;
                }
            }
        }
    }
    return false;
}

//sets up the searching process by getting the word to search for, making it all uppercase, and making a blank 2D vector to match the grid vector and filling it with '-'
//grid is the 2D vector to search the word within
//rows is the number of rows of the vectors
//cols is the number of columns of the vectors
//returns true if a path has been found
bool searchWord(std::vector<std::vector<char>> grid, int rows, int cols){
    std::string word;
    std::cout << "Insert word to search: ";
    std::cin >> word;
    for (int i = 0; i <  (int)word.length(); i++){
        word[i] = toupper(word[i]);
    }
    //gets an input from user and turns it all to uppercase
    
    std::cout << std::endl;
    std::vector<std::vector<char>> gridBlank(rows);
    for (int i = 0; i < rows; i++){
        gridBlank[i] = std::vector<char>(cols);
    }
    for (int i = 0; i < (int)gridBlank.size(); i++){
        for (int j = 0; j < (int)gridBlank[0].size(); j++){
            gridBlank[i][j] = '-';
        }
    }
    //makes a blank 2D vector to match the grid vector and filling it with '-'
    
    return pathExists(grid, rows, cols, word, gridBlank);
    
}


//main method
int main(){
    int rows, cols;
    //rows and cols to be assigned in readFile() function
    std::vector<std::vector<char>> grid = readFile(rows, cols);
    printVector(grid, rows, cols);
    //prints 2D vector
    bool isPath = searchWord(grid, rows, cols);
    //isPath is true if a path has been found
    if (!isPath){
        std::cout << "No path found." << std::endl;
    }
    return 0;
}
#include <iostream>
#include "sudoku.h"


int main(){
    std::srand(time(0));
    sudoku::Sudoku s(16,sudoku::Complexity::very_easy);
    s.generate_grill();
    //s.readFile("sudoku.txt");
    std::cout << s.grille() << std::endl;
    s.solve();
    std::cout << s.grille() << std::endl;
    //s.writeFile("solution.txt");
    return 0;
}
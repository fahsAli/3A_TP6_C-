#pragma once
#ifndef SUDOKU_HEADER
#define SUDOKU_HEADER
#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <ctype.h>
#include <chrono>


namespace sudoku{
    enum class Complexity{
        expert,
        hard,
        medium,
        easy,
        very_easy
    };
    
    class Sudoku{
        public:
            Sudoku(int size=9,Complexity comp=Complexity::hard);
            int size() const;
            std::vector <int> grille() const;
            int itNumber() const;

            void grille(std::vector <int> grid);

            bool test_line(int value,int x,int y);
            bool test_column(int value,int x,int y);
            bool test_block(int value,int x,int y);

            void generate_grill();
            bool solution_generator();
            bool foundEmptyCase(int& x,int& y);

            void solve();
            void readFile(std::string fileName);
            void writeFile(std::string fileName);
        private:
            int _size;
            std::vector <int> _grille;
            Complexity _complexity;
            int _IT_NUMBER = 0;
    };
    int countLines(std::string fname);
    std::string display_number(int num);
    void shift_line(int shift,std::vector <int>& vec);
    std::vector <int> generate_line(int size);
    int getIntFromLine(std::string str,int position);
}
std::ostream& operator<< (std::ostream &os,std::vector <int> vec);

#endif
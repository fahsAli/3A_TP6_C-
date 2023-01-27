#include "sudoku.h"

sudoku::Sudoku::Sudoku(int size,sudoku::Complexity comp){
    _size = size;
    _complexity = comp;
    _grille.resize(_size*_size);
    for(int i=0;i<_grille.size();i++){
        _grille.at(i)=0;
    }
}

int sudoku::Sudoku::size() const{
    return _size;
}

std::vector <int> sudoku::Sudoku::grille() const{
    return _grille;
}

void sudoku::Sudoku::grille(std::vector <int> grid){
    _grille = grid;
}

int sudoku::Sudoku::itNumber() const{
    return _IT_NUMBER;
}

std::string sudoku::display_number(int num){
    std::string str=" ";
    if(num==0){
        str = str + " ";
    }else{
        str = str + "\033[1;92;49m" + std::to_string(num) +"\033[0m";
    }
    str = str + "  ";
    if(str.length()>18){
        str.pop_back();
    }
    return str;
}

bool sudoku::Sudoku::test_column(int value,int x,int y){
    if((value > _size)||(value < 1)||(_grille.at(_size*y+x)!=0)){
        return false;
    }
    for(int i=0;i<_size;i++){
        if(value == _grille.at(_size*i+x)){
            return false;
        }
    }
    return true;
}

bool sudoku::Sudoku::test_line(int value,int x,int y){
    if((value > _size)||(value < 1)||(_grille.at(_size*y+x)!=0)){
        return false;
    }
    for(int i=0;i<_size;i++){
        if(value == _grille.at(_size*y+i)){
            return false;
        }
    }
    return true;
}

bool sudoku::Sudoku::test_block(int value,int x,int y){
    int size=int(std::sqrt(_size));
    if((value > _size)||(value < 1)||(_grille.at(_size*y+x)!=0)){
        return false;
    }
    x = x - x%size;
    y = y - y%size;
    for(int i=y;i<(y+int(std::sqrt(_size)));i++){ 
        for(int j=0;j<size;j++){
            if(_grille.at(_size*i+x+j)==value){
                return false;
            }
        }
    }
    return true;
}

void sudoku::shift_line(int shift,std::vector <int>& vec){
    int stock=0;
    for(int i=0;i<shift;i++){
        stock = vec.front();
        vec.erase(vec.begin(),(vec.begin()+1));
        vec.push_back(stock);
    }
}


std::vector <int> sudoku::generate_line(int size){
    int pos=0,cpt=0;
    std::vector <int> vec;
    vec.resize(size);
    for(int i=0;i<vec.size();i++){
        vec.at(i)=0;
    }
    for(int i=0;i<size;i++){
        pos = std::rand()%size;
        while(vec.at(pos)!=0){
            pos = std::rand()%size;
        }
        vec.at(pos)=(i+1);
    }
    return vec;
}


void sudoku::Sudoku::generate_grill(){
    int num=0,cpt=1,pos=0;
    if(_complexity==sudoku::Complexity::expert){
        num=int(0.25*_size*_size)+rand()%6;
    }else if(_complexity==sudoku::Complexity::hard){
        num=int(0.31*_size*_size)+rand()%6;
    }else if(_complexity==sudoku::Complexity::medium){
        num=int(0.38*_size*_size)+rand()%6;
    }else if(_complexity==sudoku::Complexity::easy){
        num=int(0.435*_size*_size)+rand()%6;
    }else{
        num=int(0.5*_size*_size)+rand()%6;
    }
    std::cout << "num : " << num << std::endl;
    std::vector <int> line = sudoku::generate_line(_size);
    for(int i=0;i<_size;i++){
        for(int j=0;j<_size*_size;j++){
            _grille.at(j)=line.at(j%_size);
            if((j+1)%_size==0){
                if(cpt%int(std::sqrt(_size))==0){
                    sudoku::shift_line(1,line);
                }else{
                    sudoku::shift_line(int(std::sqrt(_size)),line);
                }
                cpt++;
            }
        }
    }

    for(int i=0;i<(_size*_size-num);i++){
        pos = std::rand()%(_size*_size);
        while(_grille.at(pos) == 0){
            pos = std::rand()%(_size*_size);
        }
        _grille.at(pos)=0;
    }
}

//solve par ligne lineaire
// bool sudoku::Sudoku::foundEmptyCase(int& x,int& y){
//     for(int i=0;i<_size*_size;i++){
//         if(_grille.at(i)==0){
//             y = i/_size;
//             x = i-y*_size;
//             return true;
//         }
//     }
//     return false;
// }



// solve ligne par ligne //
bool sudoku::Sudoku::foundEmptyCase(int& x,int& y){ 
    for(y=0;y<_size;y++){
        for(x=0;x<_size;x++){
            if(_grille.at(_size*y+x)==0){
                return true;
            }
        }
    }
    return false;
}

//solve colonne par colonne //
// bool sudoku::Sudoku::foundEmptyCase(int& x,int& y){ 
//     for(x=0;x<_size;x++){
//         for(y=0;y<_size;y++){
//             if(_grille.at(_size*y+x)==0){
//                 return true;
//             }
//         }
//     }
//     return false;
// }


bool sudoku::Sudoku::solution_generator(){
    _IT_NUMBER++;
    int x=0,y=0;
    if(!this->foundEmptyCase(x,y)){
        return true;
    }

    for(int i=1;i<=_size;i++){
        if((this->test_block(i,x,y))&&(this->test_column(i,x,y))&&(this->test_line(i,x,y))){
            _grille.at(_size*y+x)=i;
            if(this->solution_generator()){
                return true;
            }
            _grille.at(_size*y+x)=0;
        }
    }
    return false;
}

void sudoku::Sudoku::solve(){
    auto started = std::chrono::high_resolution_clock::now();
    this->solution_generator();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << "execution time in sec : " << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count()*0.001 << std::endl;
    std::cout << "iteration number : " << this->itNumber() << std::endl;
}

std::ostream& operator<< (std::ostream &os,std::vector <int> vec){
    std::string str="";
    int line=1;
    for(int i=0;i<int(std::sqrt(vec.size()));i++){
        str = str + "\033[1;94;49m------\033[0m";
    }
    str = str + "\033[1;94;49m-\033[0m"+"\n";
    for(int i=0;i<vec.size();i++){
        if(i%int(std::sqrt(std::sqrt(vec.size())))==0){
            str = str + "\033[1;94;49m| \033[0m" + sudoku::display_number(vec.at(i));
        }else{
            str = str + "\033[1;31;49m| \033[0m" + sudoku::display_number(vec.at(i));
        }
        if(i%int((std::sqrt(vec.size()))) == int((std::sqrt(vec.size()))-1)){
            str = str + "\033[1;94;49m|\033[0m" + "\n";
            if(line%int(std::sqrt(std::sqrt(vec.size())))==0){
                for(int i=0;i<int(std::sqrt(vec.size()));i++){
                    str = str + "\033[1;94;49m------\033[0m";
                }
                str = str + "\033[1;94;49m-\033[0m"+"\n";
            }else{
                for(int j=0;j<int(std::sqrt(vec.size()));j++){
                    if(j%int(std::sqrt(std::sqrt(vec.size())))==0){
                        str = str + "\033[1;94;49m-\033[0m";
                    }else{
                        str = str + "\033[1;31;49m-\033[0m";
                    }
                    str = str + "\033[1;31;49m-----\033[0m";
                }
                str = str + "\033[1;94;49m-\033[0m" + "\n";
            }
            line++;
        }
    }       
    os << str;
    return os;
}

int sudoku::countLines(std::string fname){
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(fname);
    while (std::getline(myfile, line)){
        ++number_of_lines;
    }
    return number_of_lines;
}

int sudoku::getIntFromLine(std::string str,int position){
    bool done = 0;
    int start=0,cpt=0,num=0;
    for(int i=0;i<str.length();i++){
        if(!std::isalnum(str[i])){
            start++;
        }else if(start == position){
            start = i;
            break;
        }
    }
    for(int i=start;i<str.length();i++){
        if(std::isalnum(str[i])){
            num *= 10;
            num += (str[i]-'0');
        }else{
            break;
        }   
    }
    return num;
}

void sudoku::Sudoku::readFile(std::string fileName){
    _size = countLines(fileName);
    int index=0,nline=1;
    std::fstream file;
    std::string line="";
    file.open(fileName,std::ios::in);
    if(file.is_open()){
        while(std::getline(file,line)){
            for(int pos=0;pos<_size;pos++){
                _grille.at(index)=getIntFromLine(line,pos);
                index++;
            }
        }
    }else{
        std::cout << "error file is not open to read" << std::endl;
    }
    file.close();
}

void sudoku::Sudoku::writeFile(std::string filename){
    std::fstream file;
    file.open(filename, std::ios::out);
    if(file.is_open()){
        for(int i=0;i<_grille.size();i++){
            file << _grille.at(i) << " ";
            if(((i+1)%_size==0)&&(i!=_size*_size-1)){
                file << "\n";
            }
        }
    }else{
        std::cout << "error file is not open to write" << std::endl;
    }
    file.close();
}
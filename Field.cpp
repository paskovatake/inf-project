#include <iostream>
#include <vector>
#include "Field.h"
using namespace std;
std::ostream& operator << (std::ostream &ostr, const Field &f)
{
	std::vector<std::vector<int>> field = f.get_field();
    std::string s = "";
    for (int i = 0; i < f.get_size(); i++){
        s+="----";
    }
	for (int i = 0; i < f.get_size(); i++){
        for (int j = 0; j < f.get_size(); j++){
            if (j != 0) 
                ostr << '|';
            if (field[i][j] == 1){
                ostr << " x ";
            } 
            if (field[i][j] == 2) {
                ostr << " o ";
            }
            if (field[i][j] == 0){
                ostr << "   ";
            }             }
        if ( i != f.get_size() - 1 )

            ostr << endl << s << endl;
        else
            ostr << endl;
	}
	return ostr;
}

int Field::get_size() const{
    return this->size;
}

std::vector< std::vector<int> > Field::get_field() const {
	return field;
}

bool Field::check_pos(int x, int y) const{
    if (x < 0 || x >= this->get_size())
        return false;
    if (y < 0 || y >= this->get_size())
        return false;
    if (field[y][x] != TTT_EMPTY)
        return false;
    return true;
}

bool Field::make_move(int who, int x, int y){
	if (check_pos(x, y)){
    	field[y][x] = who;
    	return true;
    }
    return false;
}

int Field::check_win() const{
	std::vector<std::vector<int>> f = get_field();
    int horizontal = 0;
    int horizontal_flag = 0;
    int vertical_flag = 0;
    int vertical = 0;
    int size = this->get_size();
    for (int i = 0; i < size; i++){
        horizontal = f[i][0];
        vertical = f[0][i];
        for(int j = 0; j < size; j++){
            if (f[i][j] != horizontal)
                horizontal_flag = 1;
            if (f[j][i] != vertical)
                vertical_flag = 1;
        }
        if (horizontal_flag == 0)
            return horizontal;
        if (vertical_flag == 0)
            return vertical;
        vertical_flag = 0;
        horizontal_flag = 0;
    }
    int diag1_flag = 0;
    int diag2_flag = 0;
    int diag2 = f[0][size - 1];
    int diag1 = f[0][0];
    for(int i = 0; i < size; i++){
        if (diag1 != f[i][i])
            diag1_flag = 1;
        if (diag2 != f[i][size - 1 - i])
            diag2_flag = 1;
    }
    if (diag1_flag == 0)
        return diag1;
    if (diag2_flag == 0)
        return diag2;

    return 0;
}


bool Field::is_playable() const{
    if (check_win()) 
    	return false;

	std::vector<std::vector<int>> f = get_field();
    for (int i = 0; i < this->get_size(); i++)
        for (int j = 0; j < this->get_size(); j++)
            if (f[i][j] == TTT_EMPTY)
                return true;

    return false;
}

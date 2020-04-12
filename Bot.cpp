#include "Bot.h"
#include <vector>

void User::make_move (Field & f){
    std::cout << "YOUR TURN (x y): ";

    int x = -1, y = -1;
    int bad_input_flag = 0;
    while (true){
        std::cin >> x >> y;
        if (f.make_move(this->get_figure(), x, y )){
            break;
        } else {
            std::cout << "INVALID INPUT!!";
            break;
        }
    }
}

// TODO расширить поле
bool Bot::interrupt_enemy (Field &f) 
{
    int enemy = (this->get_figure() == TTT_CIRCLE) ? TTT_CROSS : TTT_CIRCLE;

    std::vector<std::vector<int>> field = f.get_field();
    int size = f.get_size();
    // for use of binary operations initialise as 11 in binary form
    int hor_num_of_circles = 0;
    int hor_num_of_cross = 0;
    int horizontal = 0;
    int vert_num_of_circles = 0;
    int vert_num_of_cross = 0;
    int vertical = 0;
    int enemy_line = 0;
    int player_line = 0;
    int x = -1;
    int y = -1;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if (field[i][j] != TTT_EMPTY){
                horizontal = horizontal | field[i][j];
                if (field[i][j] == TTT_CIRCLE)
                    hor_num_of_circles++;
                if (field[i][j] == TTT_CROSS)
                    hor_num_of_cross++;
            }
            if (field[j][i] != TTT_EMPTY){
                vertical = vertical | field[j][i];
                if (field[j][i] == TTT_CIRCLE)
                    vert_num_of_circles++;
                if (field[j][i] == TTT_CROSS)
                    vert_num_of_cross++;
            }
        }
        if (horizontal == this->get_figure() && ((this->get_figure() == TTT_CIRCLE) ? hor_num_of_circles == size - 1 : hor_num_of_cross == size - 1)){
            for (int j = 0; j < size; j++){
                if (field[i][j] == TTT_EMPTY){
                    x = j;
                    y = i;
                }
            }
            f.make_move(this->get_figure(), x, y);
            return true;
        }
        if (horizontal == enemy && ((enemy == TTT_CIRCLE) ? hor_num_of_circles == size - 1 : hor_num_of_cross == size - 1)){
            for (int j = 0; j < size; j++){
                if (field[i][j] == TTT_EMPTY){
                    x = j;
                    y = i;
                }
            }
            f.make_move(this->get_figure(), x, y);
            return true;
        }
        if (vertical == this->get_figure() && ((this->get_figure() == TTT_CIRCLE) ? vert_num_of_circles == size - 1 : vert_num_of_cross == size - 1)){
            for (int j = 0; j < size; j++){
                if (field[j][i] == TTT_EMPTY){
                    x = i;
                    y = j;
                }
            }
            f.make_move(this->get_figure(), x, y);
            return true;
        }
        if (vertical == enemy && ((enemy == TTT_CIRCLE) ? vert_num_of_circles == size - 1 : vert_num_of_cross == size - 1)){
            for (int j = 0; j < size; j++){
                if (field[j][i] == TTT_EMPTY){
                    x = i;
                    y = j;
                }
            }
            f.make_move(this->get_figure(), x, y);
            return true;
        }
        horizontal = 0;
        vertical= 0;
        vert_num_of_cross = 0;
        hor_num_of_cross = 0;
        vert_num_of_circles = 0;
        hor_num_of_cross = 0;
    }
    int diag1_circles = 0;
    int diag2_circles = 0;
    int diag1_cross = 0;
    int diag2_cross = 0;
    int diag1 = 0;
    int diag2 = 0;
    for(int i = 0; i < size; i++){
        if (field[i][size - i - 1] != TTT_EMPTY){
            diag1 = diag1 | field[i][size - i - 1];
            if (field[i][size - i - 1] == TTT_CIRCLE)
                diag1_circles++;
            if (field[i][size - i - 1] == TTT_CROSS)
                diag1_cross++;
        }
        if (field[i][i] != TTT_EMPTY){
            diag2 = diag2 | field[i][i];
            if (field[i][i] == TTT_CIRCLE)
                diag2_circles++;
            if (field[i][i] == TTT_CROSS)
                diag2_cross++;
        }
    }
    if (diag1 == this->get_figure() && ((this->get_figure() == TTT_CIRCLE) ? diag1_circles == size - 1 : diag1_cross == size - 1)){
        for (int i = 0; i < size; i++){
            if (field[i][size - i - 1] == TTT_EMPTY){
                x = i;
            }
        }
        f.make_move(this->get_figure(), size - x - 1, x);
        return true;
    }
    if (diag1 == enemy && ((enemy == TTT_CIRCLE) ? diag1_circles == size - 1 : diag1_cross == size - 1)){
        for (int i = 0; i < size; i++){
            if (field[i][size - i - 1] == TTT_EMPTY){
                x = i;
            }
        }
        f.make_move(this->get_figure(), size - x - 1, x);
        return true;
    }
    if (diag2 == this->get_figure() && ((this->get_figure() == TTT_CIRCLE) ? diag2_circles == size - 1 : diag2_cross == size - 1)){
        for (int i = 0; i < size; i++){
            if (field[i][i] == TTT_EMPTY){
                x = i;
            }
        }
        f.make_move(this->get_figure(), x, x);
        return true;
    }
    if (diag2 == enemy && ((enemy == TTT_CIRCLE) ? diag2_circles == size - 1 : diag2_cross == size - 1)){
        for (int i = 0; i < size; i++){
            if (field[i][i] == TTT_EMPTY){
                x = i;
            }
        }
        f.make_move(this->get_figure(), x, x);
        return true;
    }
    return false;
}

void Bot::random_move (Field &f)
{
    int x = -1, y = -1;
    while (!f.make_move (this->get_figure(), x, y)){
        // std::cout << "rand";
        x = rand () % f.get_size();
        y = rand () % f.get_size();
    }
}

void Bot::make_move (Field & f)
{
    std::cout << "BOT MAKING A MOVE..." << endl;
    
    if (!this->interrupt_enemy(f))
        this->random_move(f);
}

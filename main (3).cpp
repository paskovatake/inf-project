#include <iostream>
#include <fstream>
using namespace std;
#include "Field.h"
#include "Bot.h"
#include "MNTS.h"
#include "mingw.thread.h"

Tree * selection(Field& field);
Tree * expanding(Field& field, Tree * bestnode);

int main ()
{
    int size;
    std::cout << "Enter the field size ";
    std::cin >> size;
    Field field(size);

    User player1 = User(TTT_CROSS);
    MNTS player2 = MNTS(TTT_CIRCLE, size);
    int current = 1;
    int x = -1, y = -1;
    while (field.is_playable())
    {
        std::cout << field;
        std::cout << current;
        if(current == 1){
            std::cout << "Player " << player1.get_figure() << " turn: ";
            player1.make_move(field);
            // while (!field.make_move (player1.get_figure(), x, y)){
            //     // std::cout << "rand";
            //     x = rand () % field.get_size();
            //     y = rand () % field.get_size();
            // }
        } 
        if (current == 2) {
            std::cout << "Player " << player2.get_figure() << " turn: ";
            player2.search(field);
        }
        if (current == 1){
            current = 2;
        } else {
            current = 1;
        }
    }

    std::cout << field;
    std::ofstream out;
    out.open("results.txt",  std::ios_base::app);
    if (!out.is_open()){
        std::cout << "invalid file";
        exit(0);
    }
    std::string s = std::to_string(field.check_win());
    out << s << "\n";
    std::cout << "Winner is Player " << field.check_win() << endl;

    return 0;
}
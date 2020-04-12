#pragma once

#include <cstdlib>
using namespace std;

#include "Field.h"

class Player
{
private:
    int figure;
public:
    Player(int fig): figure(fig){}
    void set_figure (int fig){
        this->figure = fig;
    }
    int get_figure () const{
        return this->figure;
    }
    // void make_move(Field& f);
};

class User : public Player
{
public:
    using Player::Player;
    void make_move (Field & f);
};

class Bot : public Player
{
private:
    bool interrupt_enemy (Field &f); 
    void random_move (Field &f);

public:
    using Player::Player;
    void make_move (Field & f);
};

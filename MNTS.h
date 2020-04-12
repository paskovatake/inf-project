#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include "Bot.h"
#include "Field.h"
#include "mingw.thread.h"

class Tree{
public:
    int player = 0;
    // last made move coordinates
    int last_move_x = -1;
    int last_move_y = -1;
    // number of wins
    int w = 0;
    // number of simulations
    int n = 0;
    Tree * parent = nullptr;
    std::vector < Tree * >  Nodes;
};

class MNTS : public Player
{
private:
    Field previous_step;

    void latest_step (Field & f, int & x, int & y )
    {
        std::vector<std::vector<int>> field = f.get_field();
        std::vector<std::vector<int>> prev_field = this->previous_step.get_field();
        int s = f.get_size();
        for (int i = 0; i < s; i++)
            for (int j = 0; j < s; j++)
                if ( field[i][j] != prev_field[i][j] ){
                    x = j;
                    y = i;
                }
        this->previous_step = Field(field, s);
    }

    Tree * tree;
    Tree * current;
    void add_node(Field& field);
    Tree * selection(Field& field);
    Tree * expanding(Field& field, Tree * bestnode);
    void simulation(Field& field, Tree * newnode);
    void backpropagation(Field& field, Tree * newnode);


public:
    MNTS (int fig, int s): Player(fig), previous_step(Field(s))
    {
        this->tree = new Tree;
        this->current = this->tree;
        // this->previous_step = Field(s);
    }

    void s_b(Field& field, Tree * newnode)
    {
        simulation(field, newnode);
        backpropagation(field, newnode);
    }

    void search(Field& field){
        cout << "MONTE-CARLO BOT MAKING MOVE..." << endl;
        add_node(field);
        Tree * bestnode = selection(field);
        Tree * newnode = expanding(field, bestnode);

        thread th1(&MNTS::s_b, this, ref(field), newnode);
        thread th2(&MNTS::s_b, this, ref(field), newnode);
        thread th3(&MNTS::s_b, this, ref(field), newnode);
        thread th4(&MNTS::s_b, this, ref(field), newnode);
        th1.join();
        th2.join();
        th3.join();
        th4.join();
        this->current = newnode;
        field.make_move(this->get_figure(), this->current->last_move_x, this->current->last_move_y);
    }

    void Reset (){
        this->current = this->tree;
        this->previous_step = Field(this->previous_step.get_size());
    }
};

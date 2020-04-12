#include "MNTS.h"

void MNTS::add_node(Field& field){
	bool exist = false;

	int enemyx = -1, enemyy = -1;
	this->latest_step(field, enemyx, enemyy);

	for (Tree * node : this->current->Nodes){
	    if (node->last_move_x == enemyx && node->last_move_y == enemyy){
	        exist = true;
	        this->current = node;
	    }
	}

	if ( !exist ){
	    Tree * enemymove = new Tree;
	    enemymove->parent = this->current;
	    enemymove->last_move_x = enemyx;
	    enemymove->last_move_y = enemyy;
	    enemymove->player = (this->get_figure() == TTT_CROSS) ? TTT_CIRCLE : TTT_CROSS;
	    this->current->Nodes.push_back(enemymove);
	    this->current = enemymove;
	}
}

Tree * MNTS::selection(Field& field){
	// 1. selection
	// select node with more wins.
	Tree * bestnode = this->current;

	// TODO сделать классом нормальным
	for ( Tree * node : this->current->Nodes )
	{
	    if ( ((double) node->w / node->n) > ((double) bestnode->w / bestnode->n) )
	        bestnode = node;
	}
	return bestnode;
}

Tree * MNTS::expanding(Field& field, Tree * bestnode){
	// 2. expanding
	// create new node.
	Tree * newnode = new Tree;
	newnode->parent = bestnode;
	newnode->player = this->get_figure();
	this->current->Nodes.push_back(newnode);
	return newnode;
}

void MNTS::simulation(Field& field, Tree * newnode){
	// 3. simulation
	// simulate game.
	Field tmp_field(field);

	Bot bot1((this->get_figure() == TTT_CROSS) ? TTT_CIRCLE : TTT_CROSS);
	Bot bot2(this->get_figure());
	Bot * bot1_ptr = &bot1;
	Bot * bot2_ptr = &bot2;

	Bot * current = bot2_ptr;

	while (tmp_field.is_playable())
	{
	    current->make_move (tmp_field);

	    if ( newnode->last_move_x == -1 && newnode->last_move_y == -1 )
	        this->latest_step(tmp_field, newnode->last_move_x, newnode->last_move_y);

	    if (current == bot1_ptr)
	        current = bot2_ptr;
	    else
	        current = bot1_ptr;
	}
	// delete bot1;
	// delete bot2;
}

void MNTS::backpropagation(Field& field, Tree * newnode){
	// 4. backpropagation.

	int winner = field.check_win();

	Tree * currentnode = newnode;
	while ( currentnode != nullptr )
	{
	    currentnode->n++;

	    if ( currentnode->player == winner )
	        currentnode->w++;

	    currentnode = currentnode->parent;
	}
}

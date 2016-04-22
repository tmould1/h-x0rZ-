#include "Card.h"



Card::Card()
{
}

Card::Card(int myNumber){
	id = myNumber;
}


Card::~Card()
{
}


int Card::GetID(){
	return id;
}

#include "Card.h"

Card::Card( int _count ){
		count = _count;
		in_deck = true;
	}

int  Card::get_count() {
		return count;
	}
void Card::set_in_deck( bool _in_deck ){
		in_deck = _in_deck;
	}
bool Card::get_in_deck(){
		return in_deck;
	}
int Card::get_nominal(){
		return count<52?count/4:60;
	}
int Card::get_suit(){
		return count<52?count%4:4;
	}

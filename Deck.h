#ifndef __DECK
#define __DECK
#include "Card.h"
#include <stdlib.h>
#include <time.h>

class Deck{
	Card* deck[54];
public:
	Deck();
	void mix();
	Card* give_a_card();
};
#endif
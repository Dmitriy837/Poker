class Deck{
	Card* deck[54];
public:
	Deck(){
		for(int i=0;i<54;++i){
			deck[i] = new Card(i);
			deck[i]->set_in_deck(true);
		}
	}
	void mix(){
		for(int i=0; i<54; ++i){
			deck[i]->set_in_deck(true);
		}
	}
	Card* give_a_card(){
		int ran=0;
		do{
			ran = rand()%54;
		}while(deck[ran]->get_in_deck() == 0);
		deck[ran]->set_in_deck(false);
		return deck[ran];
	}
};

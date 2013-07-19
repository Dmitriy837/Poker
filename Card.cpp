/*Карты в колоде располагаются по четыре, одинакового номинала разных мастей.
Джокер имеет номинал 13, масть 4, нормальные карты - номинал 0 - 12, масть 0 -3.*/

class Card{
	int count;
	bool in_deck;
public:	
//**************************************************************************************************
//Конструктор, геттеры, сеттеры:
//**************************************************************************************************
	Card( int _count ){
		count = _count;
		in_deck = true;
	}
	inline int get_count(){
		return count;
	}
	void set_in_deck( bool _in_deck ){
		in_deck = _in_deck;
	}
	inline bool get_in_deck(){
		return in_deck;
	}
	inline int get_nominal(){
		return count<52?count/4:60;
	}
	inline int get_suit(){
		return count<52?count%4:4;
	}
};
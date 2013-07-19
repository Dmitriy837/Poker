#ifndef __HPlayer
#define __HPlayer
#include "Player.h"
#include "Graphical_game.h"
#include <iostream>
using namespace std;
class Human_player:public Player, public Graphical_game{
public:
//**************************************************************************************************
//Человеческий игрок выбирает какие карты он хочет менять:
//**************************************************************************************************
	void make_a_choise();
//**************************************************************************************************
//Человеческий игрок решает, хочет ли он инициировать поднятие ставок:
//**************************************************************************************************
	int init_up_stakes(const int i,bool& in_game,const int combo,const int count_players,int& stakes);
//**************************************************************************************************
//Человеческий игрок решает, согласен ли он поднимать ставки:
//**************************************************************************************************
	void agree_up_stakes(const int i,bool& in_game,const int combo,const int count_players,int& stakes,int& last_in_game);
	bool next_round();
	void init_balances(int* balances);
	void init_cards(int* cards);
	void init_count_players(int count_players);
	void init_player(int player,int count);	
};
#endif
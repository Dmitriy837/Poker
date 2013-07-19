#include "Game.h"


Game::Game(int _count_players){
	count_players = _count_players;
	_players = new Player*[count_players];
	_players[0] = new Human_player();
	for(int i = 1; i<count_players; ++i){
	_players[i] = new Cpu_player();	
	};
	round = new Round(_count_players,_players);
};
//**************************************************************************************************
//Запускаем раунд за раундом пока у всех есть деньги:
//**************************************************************************************************
void Game::Run(){
	int c=1;
	do{
		int i = 0;
		round->begin(my_deck);
		round->finish();
		i = 0;
		while(i<count_players){
			_players[i]->get_ready();
			++i;
		};
		my_deck.mix();
	}while(dynamic_cast<Human_player*>(_players[0])->next_round());
};

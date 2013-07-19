#include "Human_player.h"

//**************************************************************************************************
//Человеческий игрок выбирает какие карты он хочет менять:
//**************************************************************************************************
void Human_player::make_a_choise(){
	cout<<"make..."<<endl;
	bool* tmp = NULL;
	tmp = graphical_make_a_choise();
	for(int i=0;i<5;++i)if(tmp&&tmp[i])set_to_change(i);
	if(tmp)delete [] tmp;
};
//**************************************************************************************************
//Человеческий игрок решает, хочет ли он инициировать поднятие ставок:
//**************************************************************************************************
int Human_player::init_up_stakes(const int i,bool& in_game,const int combo,const int count_players,int& stakes){
	cout<<"Init..."<<endl;
	if(!in_game)return 0;
	if(graphical_init_up_stakes(stakes)){
		stakes+=STAKES_STEP;
		set_money(get_money()-STAKES_STEP);
		return 1;
	};
};
//**************************************************************************************************
//Человеческий игрок решает, согласен ли он поднимать ставки:
//**************************************************************************************************
void Human_player::agree_up_stakes(const int i,bool& in_game,const int combo,const int count_players,int& stakes,int& last_in_game){
	cout<<"agree..."<<endl;
	if(!in_game)return;
	graphical_agree_up_stakes(in_game,stakes);
	if(in_game){
		stakes+=STAKES_STEP;
		set_money(get_money()-STAKES_STEP);
	}
	else last_in_game--;
};
bool Human_player::next_round(){
	cout<<"next..."<<endl;
	return graphical_next_round();
};
void Human_player::init_balances(int* balances){
	graphical_init_balances(balances);
};
void Human_player::init_cards(int* cards){
	graphical_init_cards(cards);
};
void Human_player::init_count_players(int count_players){
	graphical_init_count_players(count_players);
};
void Human_player::init_player(int player,int count){
	cout<<"init_st..."<<player<<endl;
	graphical_init_player(player,count);
};

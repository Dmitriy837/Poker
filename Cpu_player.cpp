#include "Cpu_player.h"

//**************************************************************************************************
//Компьютерный игрок решает, хочет ли он инициировать поднятие ставок:
//**************************************************************************************************
int Cpu_player::init_up_stakes(const int i,bool& in_game,const int combo,const int count_players,int& stakes){
	if(!in_game)return 0;
	cout<<"*******************"<<endl;
	bool i_will = ((combo*STAKES_STEP+START_STAKES)*count_players-stakes>0);
	if(i_will){
		cout<<"player"<<i<<" initiates up stakes"<<endl;
		stakes+=STAKES_STEP;
		set_money(get_money()-STAKES_STEP);
	}
	else cout<<"player"<<i<<" wants not to up stakes"<<endl;
	return i_will*STAKES_STEP;
};
//**************************************************************************************************
//Компьютерный игрок решает, согласен ли он на поднятие ставок:
//**************************************************************************************************
void Cpu_player::agree_up_stakes(const int i,bool& in_game,const int combo,const int count_players,int& stakes,int& last_in_game){
	if(!in_game)return;
	in_game = (((combo*STAKES_STEP+START_STAKES)*count_players-stakes>0)||rand()%2);
	if(!in_game){
		last_in_game--;
		cout<<"player"<<i<<" is pass((("<<endl;
	}
	else{
		cout<<"player"<<i<<" agree to up stakes"<<endl;
		stakes+=STAKES_STEP;
		set_money(get_money()-STAKES_STEP);
	}
};
//**************************************************************************************************
//Перегружаем виртуальную функцию проверки на флеш, это лучше сделать, т.к.
//для человеческого игрока важно лишь распознать собранный флеш,
//а компьютеру нужно просчитать еще и какие карты скорее в него войдут.
//**************************************************************************************************
bool Cpu_player::is_flush(){
	int suits[5]={0};
//Считаем количество карт каждой масти:
	for(int i=0;i<5;++i)if((get_on_hands()[i])->get_suit()!=4)suits[(get_on_hands()[i])->get_suit()]++;
//Избежим собирания масти "джокер"
	suits[4]=0;
//Решаем, карт какой масти больше остальных:
	int fin_suit = find_max(suits,4);
//В комбинацию идут карты выбранной масти и, разумеется, джокеры:
	for(int i=0;i<5;++i)
		{
		if((get_on_hands()[i])->get_suit()==4){set_in_combo(i);suits[fin_suit]++;}
		if((get_on_hands()[i])->get_suit()==fin_suit)set_in_combo(i);
		}
	return (suits[fin_suit]==5);
};
//**************************************************************************************************
//Отмечаем для замены все, что не входит в собираемую комбинацию:
//**************************************************************************************************
void Cpu_player::choose_cards_to_change(){
	for(int i=0;i<5;++i)if(!get_in_combo(i))set_to_change(i);
};
//**************************************************************************************************
//Выбираем собираемую комбинацию:
//**************************************************************************************************
void Cpu_player::make_a_choise(){
	int in_combo_now[5];
	//Если одна из перечисленных комбинаций уже собрана, на том и закончим
	if(is_clear_four_of_a_kind()){choose_cards_to_change();return;}
	in_combo_now[0]=count_in_combo();
	if(is_clear_full_house()){choose_cards_to_change();return;}
	in_combo_now[1]=count_in_combo();
	if(is_clear_flush()){choose_cards_to_change();return;}
	in_combo_now[2]=count_in_combo();
	if(is_clear_straight()){choose_cards_to_change();return;}
	in_combo_now[3]=count_in_combo();
	if(is_clear_three_of_a_kind()){choose_cards_to_change();return;}
	in_combo_now[4]=count_in_combo();
	if(is_clear_two_pairs()){choose_cards_to_change();return;}
	clear_combo();
	//Если собрана чистая пара, остановимся на ней, если же в ней есть джокер, возможны лучшие варианты:
	if(check_for_jokers()==-1&&is_clear_pair()){choose_cards_to_change();return;}
	if(in_combo_now[0]>in_combo_now[1]){is_clear_four_of_a_kind();choose_cards_to_change();return;}
	if(in_combo_now[1]>in_combo_now[2]){is_clear_full_house();choose_cards_to_change();return;}
	if((in_combo_now[2]>=in_combo_now[3])&&(in_combo_now[2]>2)){is_clear_flush();choose_cards_to_change();return;}
	if((in_combo_now[3]>in_combo_now[4])&&(in_combo_now[3]>2)){is_clear_straight();choose_cards_to_change();return;}
	else 	{is_clear_three_of_a_kind();choose_cards_to_change();return;}
};
//**************************************************************************************************

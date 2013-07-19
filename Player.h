#ifndef __PLAYER
#define __PLAYER
#include "Card.h"
#include "Deck.h"
#include <stdio.h>
#include <iostream>

//Денег на руках у игрока в начале игры
#define START_MONEY 3000

class Player{
	int money;
	Card* on_hands[5];
	bool to_change[5];
	bool in_combo[5];
public:
	Player();
//**************************************************************************************************
//Геттеры и сеттеры:
//**************************************************************************************************
	Card** get_on_hands();
	int get_money();
	void set_money(int _money);
	bool* get_to_change();
	void set_to_change(int count);
	void set_in_combo(int count);
	bool get_in_combo(int i);
//**************************************************************************************************
//Берем карты в начале раунда
//**************************************************************************************************
	void take_cards(Deck& _Deck);
//**************************************************************************************************
//Меняем не понравившиеся карты:
//**************************************************************************************************
	void change_cards( Deck& _Deck );
//**************************************************************************************************
//В начале раунда приводим мысли в порядок:
//**************************************************************************************************
	void get_ready();
	void clear_combo();
//Возвращаем индексы:
	int find_min(int *mas,int n);
	int find_max(int *mas,int n);
//Сколько карт входят в комбинацию:
	int count_in_combo();
//Возвращаем индекс не воходящего в комбинацию джокера:
	int check_for_jokers();
//Возвращаем индекс старшей по номиналу карты,не входящей в комбинацию:
	int get_max_nominal();
//**************************************************************************************************
// Проверяем что мы собрали:
//**************************************************************************************************
	//ПАРА
	bool is_pair();
	//ДВЕ ПАРЫ
	bool is_two_pairs();
	//ТРИ
	bool is_three_of_a_kind();
	//СТРИТ
	bool is_straight();
	//ФЛЭШ
	virtual bool is_flush();
	//ФУЛ ХАУС
	bool is_full_house();
	//КАРЭ
	bool is_four_of_a_kind();
//**************************************************************************************************
//Чистые проверки очищают массив карт,собранных в комбинациях:
//**************************************************************************************************
	bool is_clear_four_of_a_kind();
	bool is_clear_full_house();
	bool is_clear_three_of_a_kind();
	bool is_clear_two_pairs();
	bool is_clear_pair();
	bool is_clear_straight();
	bool is_clear_flush();
//**************************************************************************************************
//Раздумываем, что мы собираем:
//**************************************************************************************************
	virtual void make_a_choise()=0;
	virtual int init_up_stakes(const int i,bool& in_game,const int combo,const int count_players,int& stakes)=0;
	virtual void agree_up_stakes(const int i,bool& in_game,const int combo,const int count_players,int& stakes,int& last_in_game)=0;
	int highest_in_combo();
};
#endif
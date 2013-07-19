#include "Player.h"
int comp(const void* n1,const void* n2){return (*(int*)n1-*(int*)n2);};

Player::Player(){
	money = START_MONEY;
	for(int i=0;i<5;++i){
		on_hands[i] = NULL;
		to_change[i]=0;
		in_combo[i]=0;
	}
};
//**************************************************************************************************
//Геттеры, сеттеры
//**************************************************************************************************
Card** Player::get_on_hands(){
	return on_hands;
};
int Player::get_money(){
	return money;
};
void Player::set_money(int _money){
	money = _money;
};
bool* Player::get_to_change(){
	return to_change;
};
void Player::set_to_change(int count){
	to_change[count] = 1;
};
void Player::set_in_combo(int count){
	in_combo[count] = 1;
};
bool Player::get_in_combo(int i){
	return in_combo[i];
};
//**************************************************************************************************

void Player::take_cards(Deck& _Deck){
	for(int i=0; i<5; ++i)on_hands[i] = _Deck.give_a_card();
};
void Player::change_cards( Deck& _Deck ){
	std::cout<<std::endl;
	for(int i=0; i<5; ++i)if(to_change[i])on_hands[i] = _Deck.give_a_card();
};
void Player::get_ready(){
	for(int i=0;i<5;++i){
		on_hands[i] = NULL;
		to_change[i]=0;
		in_combo[i]=0;
	}
};
void Player::clear_combo(){
	for(int i=0;i<5;++i)in_combo[i]=0;
};
int Player::find_min(int *mas,int n){
	int min_ind = 0;
	for(int i=1;i<n;++i)if(mas[i]<mas[min_ind])min_ind=i;
	return min_ind;
};
int Player::find_max(int *mas,int n){
	int max_ind = 0;
	for(int i=1;i<n;++i)if(mas[i]>mas[max_ind])max_ind=i;
	return max_ind;
};

int Player::count_in_combo(){
	int res=0;
	for(int i=0;i<5;++i)if(get_in_combo(i))res++;
	return res;
};

int Player::check_for_jokers(){
	for(int i=0;i<5;++i)if(!in_combo[i])if(on_hands[i]->get_nominal()==60)return i;
	return -1;
};

int Player::get_max_nominal(){
	int j=0, tmp_nominal;
	while((on_hands[j]->get_suit()==4) || in_combo[j])j++;
	int max_nominal_ind = j;
	int max_nominal = on_hands[j]->get_nominal();
	for(int i=0;i<5;++i){
		if(in_combo[i])continue;
		tmp_nominal = on_hands[i]->get_nominal();
		if(tmp_nominal==60)continue;
		if(tmp_nominal>max_nominal){max_nominal_ind = i;max_nominal = tmp_nominal;}
	}
	return max_nominal_ind;
};
//**************************************************************************************************
//Проверяем комбинации:
//**************************************************************************************************
bool Player::is_pair(){
	int tmp;
	for(int i=0;i<5;++i){
	if((in_combo[i])||(on_hands[i]->get_nominal()==60))continue;
	tmp = on_hands[i]->get_nominal();
		for(int j=i+1;j<5;++j){
			if(in_combo[j])continue;
			if(tmp == on_hands[j]->get_nominal()){
				in_combo[i] = in_combo[j] = 1;
				return true;
				}
			}
	}
	int jok = check_for_jokers();
	if( (jok !=-1) && (!in_combo[jok])){
		int max = get_max_nominal();
		set_in_combo(jok);
		set_in_combo(max);
		return true;
	};
	return false;
};
bool Player::is_two_pairs(){
	return is_pair()&&is_pair();
};
bool Player::is_three_of_a_kind(){
	if(!is_pair())return false;
	int tmp;
	for(int i=0;i<5;++i)if(in_combo[i]&&((on_hands[i]->get_nominal())!=60)){tmp=on_hands[i]->get_nominal();break;}
	for(int i=0;i<5;++i)
		if(!in_combo[i]){
			if(on_hands[i]->get_nominal()==tmp){
			in_combo[i] = 1;
			return true;
			}
		}
	int jok = check_for_jokers();
	if( (jok !=-1) && (!in_combo[jok])){
		set_in_combo(jok);
	return true;
	};
	return false;
};

bool Player::is_straight(){
	int tmp_nom[5];//тут просто номиналы карт на руках
	for(int i=0;i<5;++i)tmp_nom[i] = ((get_on_hands()[i])->get_nominal());
	qsort(tmp_nom,5,sizeof(int),comp);//теперь отсортированные!

//Сколько карт идут в стрит...
	int str1=0,str2=0,str3=0;
	//...начиная с первой...
	for(int i=0;i<5;++i)
		for(int j=0;j<5;++j)if((tmp_nom[j]-tmp_nom[0])==i){str1++;break;}
	//..второй...
	for(int i=0;i<5;++i)
		for(int j=0;j<5;++j)if((tmp_nom[j]-tmp_nom[1])==i){str2++;break;}
	//...третей:
	for(int i=0;i<5;++i)
		for(int j=0;j<5;++j)if(tmp_nom[j]-tmp_nom[2]==i){str3++;break;}
	
//Какой из этих стритов предпочтительнее собирать:
	int min_in_combo;//номинал младшей в стрите карты
	if(str1>str2){
		if(str1>str3)min_in_combo = tmp_nom[0];
		else min_in_combo = tmp_nom[2];
		}
	else if(str2>str3)min_in_combo = tmp_nom[1];
		else min_in_combo = tmp_nom[2];
//Отмечаем входящие в комбинацию карты:
	for(int i=0;i<5;++i)
		for(int j=0;j<5;++j)if(((get_on_hands()[j])->get_nominal()-min_in_combo)==i){set_in_combo(j);break;}
//Обнаруженных джокеров просто добавляем в комбинацию:
	int jok = check_for_jokers();
	while(jok!=-1){
		set_in_combo(jok);
		jok = check_for_jokers();
	}
//Особый случай, когда возможен стрит, начинающийся с туза:
	if(min_in_combo<3){
		for(int i=0;i<5;++i)
	//Если при этом в комбинацию входит 4, то оптимизировать нечего
			if((get_on_hands()[i])->get_nominal()>=4)return count_in_combo()==5;
	//Иначе туз может помочь
		for(int i=0;i<5;++i)
			if((get_on_hands()[i])->get_nominal()==12){set_in_combo(i);break;}
	}
//Так был ли стрит:
	return count_in_combo()==5;
};


bool Player::is_flush(){
	int j=0;
	while(on_hands[j]->get_suit()==4)j++;
	int tmp_suit = on_hands[j]->get_suit();
	for(int i=0;i<5;++i)	if((tmp_suit!=on_hands[i]->get_suit())&&(on_hands[i]->get_suit()!=4))return false;
				else set_in_combo(i);
	return true;
};
bool Player::is_full_house(){
	if(is_pair()&&is_three_of_a_kind())return true;
	clear_combo();
	return (is_three_of_a_kind()&&is_pair());
};
bool Player::is_four_of_a_kind(){
	//Нет трех - нет каре!
	if(!is_three_of_a_kind())return false;
	int tmp;
		//ищем карту, входящую в тройку, не джокер, и запоминаем ее номинал
	for(int i=0;i<5;++i)if((in_combo[i])&&(on_hands[i]->get_nominal()!=60)){tmp=on_hands[i]->get_nominal();break;}
		//если среди не входящих в тройку есть джокер или совпадающая по номиналу карта - у нас каре!
	for(int i=0;i<5;++i)if(!in_combo[i]&&((tmp==on_hands[i]->get_nominal())||(on_hands[i]->get_nominal()==60))){set_in_combo(i);return true;}
	return false;
};
//**************************************************************************************************
//Чистые проверки очищают массив карт,собранных в комбинациях:
//**************************************************************************************************
bool Player::is_clear_four_of_a_kind()	{clear_combo();return is_four_of_a_kind();};
bool Player::is_clear_full_house()	{clear_combo();return is_full_house();};
bool Player::is_clear_three_of_a_kind()	{clear_combo();return is_three_of_a_kind();};
bool Player::is_clear_two_pairs()	{clear_combo();return is_two_pairs();};
bool Player::is_clear_pair()		{clear_combo();return is_pair();};
bool Player::is_clear_straight()	{clear_combo();return is_straight();};
bool Player::is_clear_flush()		{clear_combo();return is_flush();};
//**************************************************************************************************
int Player::highest_in_combo(){
	int highest=-1;
	for(int i=0;i<5;++i)
		if(get_in_combo(i)&&(on_hands[i]->get_nominal()>highest)&&(on_hands[i]->get_nominal()!=60))highest = on_hands[i]->get_nominal();
	return highest;
}


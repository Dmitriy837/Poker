	int comp(const void* n1,const void* n2){return (*(int*)n1-*(int*)n2);};


class Player{
	int money;
	Card* on_hands[5];
	bool to_change[5];
	bool in_combo[5];
public:
	Player(){
		money = START_MONEY;
		for(int i=0;i<5;++i){
			on_hands[i] = NULL;
			to_change[i]=0;
			in_combo[i]=0;
		}
	};
//**************************************************************************************************
//Геттеры и сеттеры:
//**************************************************************************************************
	Card** get_on_hands(){
		return on_hands;
	};
//just for debugging
//	void set_on_hands(int ind,int card,Deck& my){
//		on_hands[ind] = my.get_card(card);
//	}
//
	int get_money(){
		return money;
	};
	void set_money(int _money){
		money = _money;
	};
//	COMBO get_combo(){
//		return current_combo;
//	};
//	void set_combo(COMBO gathered){
//		current_combo = gathered;
//	};
	bool* get_to_change(){
		return to_change;
	};
	void set_to_change(int count){
		to_change[count] = 1;
	};
	void set_in_combo(int count){
		in_combo[count] = 1;
	};
	bool get_in_combo(int i){
		return in_combo[i];
	};
//**************************************************************************************************
//Берем карты в начале раунда
//**************************************************************************************************
	void take_cards(Deck& _Deck){
		for(int i=0; i<5; ++i)on_hands[i] = _Deck.give_a_card();
	};
//**************************************************************************************************
//Меняем не понравившиеся карты:
//**************************************************************************************************
	void change_cards( Deck& _Deck ){
//		cout<<endl<<"to change:";
//		for(int i=0; i<5; ++i)cout<<to_change[i];
		cout<<endl;
		for(int i=0; i<5; ++i)if(to_change[i])on_hands[i] = _Deck.give_a_card();
	};
//**************************************************************************************************
//Преимущественно отладочная функция открытия карт:
//**************************************************************************************************
	virtual void open_cards(){
		for(int i=0; i<5; ++i)get_on_hands()[i]->show();
		cout<<"****************************"<<endl;
//		for(int i=0; i<5; ++i)if(on_hands[i])on_hands[i]->show();
	};
//**************************************************************************************************
//В начале раунда приводим мысли в порядок:
//**************************************************************************************************
	void get_ready(){
		for(int i=0;i<5;++i){
			on_hands[i] = NULL;
			to_change[i]=0;
			in_combo[i]=0;
		}
	};
	void clear_combo(){
		for(int i=0;i<5;++i)in_combo[i]=0;
	};
//Возвращаем индексы:
	int find_min(int *mas,int n){
		int min_ind = 0;
		for(int i=1;i<n;++i)if(mas[i]<mas[min_ind])min_ind=i;
		return min_ind;
};
	int find_max(int *mas,int n){
		int max_ind = 0;
		for(int i=1;i<n;++i)if(mas[i]>mas[max_ind])max_ind=i;
		return max_ind;
};
//Сколько карт входят в комбинацию:
	int count_in_combo(){
		int res=0;
		for(int i=0;i<5;++i)if(get_in_combo(i))res++;
		return res;
	};
//Возвращаем индекс не воходящего в комбинацию джокера:
	int check_for_jokers(){
		for(int i=0;i<5;++i)if(!in_combo[i])if(on_hands[i]->get_nominal()==60)return i;
		return -1;
	};
//Возвращаем индекс старшей по номиналу карты,не входящей в комбинацию:
	int get_max_nominal(){
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
// Проверяем что мы собрали:
//**************************************************************************************************
	//ПАРА
	bool is_pair(){
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
	//ДВЕ ПАРЫ
	bool is_two_pairs(){
	return is_pair()&&is_pair();
	};
	//ТРИ
	bool is_three_of_a_kind(){
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

	//СТРИТ
bool is_straight(){
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
	//
	//следующая строчка, по-моему, лишняя:
	//	if(tmp_nom[4]==12&&tmp_nom[0]==0)str1++;
//		cout<<"str1:"<<str1<<" str2:"<<str2<<" str3:"<<str3<<endl;

//Какой из этих стритов предпочтительнее собирать:
		int min_in_combo;//номинал младшей в стрите карты
		if(str1>str2){
			if(str1>str3)min_in_combo = tmp_nom[0];
			else min_in_combo = tmp_nom[2];
			}
		else if(str2>str3)min_in_combo = tmp_nom[1];
			else min_in_combo = tmp_nom[2];
//		cout<<"straight might begin with:"<<min_in_combo<<endl;
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
/*
А вот эта версия из рук вон плоха
	virtual bool is_straight(){
		int tmp_nom[5];//тут просто номиналы карт на руках
		for(int i=0;i<5;++i)tmp_nom[i] = ((get_on_hands()[i])->get_nominal());
		qsort(tmp_nom,5,sizeof(int),comp);//теперь отсортированные!
		for(int i=0;i<5;++i)if((tmp_nom[i+1]-tmp_nom[i]!=1)&&(tmp_nom[i+1]!=60))return false;
		return true;
};*/
	//ФЛЭШ
	virtual bool is_flush(){
		int j=0;
		while(on_hands[j]->get_suit()==4)j++;
		int tmp_suit = on_hands[j]->get_suit();
		for(int i=0;i<5;++i)	if((tmp_suit!=on_hands[i]->get_suit())&&(on_hands[i]->get_suit()!=4))return false;
					else set_in_combo(i);
		return true;
	};
	//ФУЛ ХАУС
	bool is_full_house(){
		if(is_pair()&&is_three_of_a_kind())return true;
		clear_combo();
		return (is_three_of_a_kind()&&is_pair());
/*		if(!is_three_of_a_kind())return false;
		int nic1=-1,nic2;
		for(int i=0;i<5;++i)if(!in_combo[i]){	if(nic1==-1)nic1=i;
							else nic2=i;};
		if((on_hands[nic1]->get_nominal())==(on_hands[nic2]->get_nominal())){
			in_combo[nic1]=1;
			in_combo[nic2]=1;
			return true;
		}
		return false;*/
/*		if(!is_two_pairs())return false;
		int nom,index;
		for(int i=0;i<5;++i)if(!in_combo[i]){nom=on_hands[i]->get_nominal();index = i;break;}
		for(int i=0;i<5;++i)if((i!=index)&&(nom==on_hands[i]->get_nominal())){in_combo[i]=1;return true;}
		return false;*/
	};
	//КАРЭ
	bool is_four_of_a_kind(){
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
	bool is_clear_four_of_a_kind()	{clear_combo();return is_four_of_a_kind();};
	bool is_clear_full_house()	{clear_combo();return is_full_house();};
	bool is_clear_three_of_a_kind()	{clear_combo();return is_three_of_a_kind();};
	bool is_clear_two_pairs()	{clear_combo();return is_two_pairs();};
	bool is_clear_pair()		{clear_combo();return is_pair();};
	bool is_clear_straight()	{clear_combo();return is_straight();};
	bool is_clear_flush()		{clear_combo();return is_flush();};
//**************************************************************************************************
//Раздумываем, что мы собираем:
//**************************************************************************************************
	virtual void make_a_choise()=0;
	virtual int init_up_stakes(const int i,bool& in_game,const int combo,const int count_players,int& stakes)=0;
	virtual void agree_up_stakes(const int i,bool& in_game,const int combo,const int count_players,int& stakes,int& last_in_game)=0;
//**************************************************************************************************
//Исключительно для отладки:
//**************************************************************************************************
//	void print_in_combo(){
//		for(int i=0;i<5;++i)(in_combo[i]?cout<<1:cout<<0);
//		cout<<endl;
//	}
//
	int highest_in_combo(){
		int highest=-1;
		for(int i=0;i<5;++i)
			if(get_in_combo(i)&&(on_hands[i]->get_nominal()>highest)&&(on_hands[i]->get_nominal()!=60))highest = on_hands[i]->get_nominal();
		return highest;
	}
};

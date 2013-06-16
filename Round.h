class Round{
	int count_players;
		//количество игроков
	Player** _players;
		//указатель на массив игроков
	struct res_combo{
		COMBO _combo;
		int highest_nominal;
	};
		res_combo* res;
		//какие игроки собрали комбинации
		//и каков старший номинал карты из 
		//комбинации на случай ничьи
	int in_game;
		//сколько игроков еще не спасовали
	bool* player_in_game;
		//не спасовал ли конкретный игрок
	int start_player;
		//с кого начинаем ходить по кругу
	int stakes;
		//текущая ставка
	int* balances;
	int* cards;
public:
	Round(int count, Player** __players){
		count_players = count;
		_players = __players;
		stakes = 0;
		balances = new int[count_players];
		cards = new int[COUNT_PLAYERS*5];
		res = new res_combo[count_players];
		player_in_game = new bool[count_players];
		int i = 0;
		while(i < count_players){
			player_in_game[i] = 1;			
			++i;
		}
		in_game = count_players;
		start_player = 0;
	};
//**************************************************************************************************
//Ищем победителей, отдаем им, то, что они заслужили:
//**************************************************************************************************
	void finish(){
//Эта функция явно трубует доработки
//мне откровенно кажется, что для результата
//следует создать отдельный класс, чтобы
//удобнее и точнее было определять победителя раунда

	//Смотрим на собранные комбинации:
		int* combos = new int[count_players];
		int i=0;
		while(i<count_players){
			if(player_in_game[i])
			combos[i] = res[i]._combo;
			else
			combos[i] = -1;
			++i;
		};
	//Считаем количество победителей
		int	count_winners=0,
			win_combo = combos[0],
			win_nom = res[0].highest_nominal;
		i=0;
		cout<<endl;
		while(i<count_players){
	//для отладки посмотрим заодно, кто что собрал:
			cout<<"N"<<i<<"gathered:"<<combos[i]<<endl;
			if((combos[i]>win_combo)||((combos[i] == win_combo)&&(res[i].highest_nominal > win_nom))){
				count_winners = 1;
				win_combo = combos[i];
				win_nom = res[i].highest_nominal;
			}
			else if((combos[i] == win_combo)&&(res[i].highest_nominal == win_nom))
			{++count_winners;}	
			++i;
		};
	//Делим выигрыш:
		i=0;
		while(i<count_players){
			if((combos[i] == win_combo)&&(res[i].highest_nominal == win_nom)){
			_players[i]->set_money(_players[i]->get_money() + stakes/count_winners);
			cout<<endl;
			cout<<"COMBO: "<<win_combo<<endl;
			cout<<"NOMINAL: "<<win_nom<<endl;
			cout<<"PRISE: "<<stakes<<endl;
			cout<<"COUNT_WINNERS: "<<count_winners<<endl;
			start_player = i;
			balances[i] = _players[i]->get_money();
			dynamic_cast<Human_player*>(_players[0])->init_player(i,count_winners);
			}
			for(int j = 0; j<5; ++j){
				cards[j + 5*i] = (_players[i]->get_on_hands())[j]->get_count();
			}
			++i;
		};
		dynamic_cast<Human_player*>(_players[0])->init_balances(balances);
		dynamic_cast<Human_player*>(_players[0])->init_cards(cards);
		delete combos;
		stakes = 0;
		i=0;
		while(i<count_players){
			player_in_game[i]=1;
			++i;
		};
	}
//**************************************************************************************************
//Все готовы, игра началась...
//**************************************************************************************************
	void begin(Deck& MyDeck){
	dynamic_cast<Human_player*>(_players[0])->init_count_players(count_players);
	dynamic_cast<Human_player*>(_players[0])->init_player(-1,1);
		int i = 0;
	//Скидываемся на ставку, получаем карты:
		while(i < count_players){
			_players[i]->take_cards(MyDeck);
			_players[i]->set_money(_players[i]->get_money()-START_STAKES);
			stakes+=START_STAKES;
			balances[i] = _players[i]->get_money();
			++i;
		}		
		for(int j = 0; j<5; ++j){
			cards[j] = (_players[0]->get_on_hands())[j]->get_count();
		}
	dynamic_cast<Human_player*>(_players[0])->init_cards(cards);
	dynamic_cast<Human_player*>(_players[0])->init_balances(balances);
	//отладки ради, посмотрим у кого что:
		open_cards();
		i = 0;
	//выбираем какие карты меняем:
		while(i < count_players){
			_players[i]->make_a_choise();
			++i;
		}
		i = 0;
	//меняем:
		while(i < count_players){
			_players[i]->change_cards(MyDeck);
			++i;
		}
		i = 0;
		for(int j = 0; j<5; ++j){
			cards[j] = (_players[0]->get_on_hands())[j]->get_count();
		}
		dynamic_cast<Human_player*>(_players[0])->init_cards(cards);

	//отчитываемся, у кого что:
		while(i < count_players){
			res[i] = fill_res_combo(_players[i]); 
			++i;
		}
		i = start_player;
	//покажем дяде разработчику, что вышло:
		open_cards();
	//спрашиваем, кто повышает ставки:
		while(i < count_players + start_player){
			if(init_up_stakes(i%count_players)){
				int j = i + 1;
				balances[i%count_players] = _players[i%count_players]->get_money();
				dynamic_cast<Human_player*>(_players[0])->init_balances(balances);
				dynamic_cast<Human_player*>(_players[0])->init_player(i%count_players,1);
		//если кто-то ставки повысил,
		//опрашиваем, кто поддержит:
				while(j < count_players + i ){
					agree_up_stakes(j%count_players);
					balances[j%count_players] = _players[j%count_players]->get_money();
					dynamic_cast<Human_player*>(_players[0])->init_balances(balances);
					++j;
				}
			}
			++i;
		}
	//для отладки посмотрим по каждому, комбинацию и старшую карту в комбинации:
		i = 0;
		while(i < count_players){
			char *str = new char[20];
			switch(res[i]._combo){
			case 8:strcpy(str,"Straight flush");break;
			case 7:strcpy(str,"Four of a kind");break;
			case 6:strcpy(str,"Full house");break;
			case 5:strcpy(str,"Flush");break;
			case 4:strcpy(str,"Straight");break;
			case 3:strcpy(str,"Three of a kind");break;
			case 2:strcpy(str,"Two pairs");break;
			case 1:strcpy(str,"Pair");break;
			case 0:strcpy(str,"None");break;
			default: strcpy(str,"Shit happends");
			}
			cout<<"_________________________________"<<endl;
			cout<<"bal"<<i<<_players[i]->get_money()<<endl;
			++i;
		}
//*************************************************
//*Красочная отладочная информация*****************
//*************************************************
/*
cout<<"_____________________"<<endl;
cout<<"Four:"<<_players[0]->is_clear_four_of_a_kind();
cout<<"\t";
cout<<"\t";
_players[0]->print_in_combo();
cout<<"Full house:"<<_players[0]->is_clear_full_house();
cout<<"\t";
_players[0]->print_in_combo();
cout<<"Flush:"<<_players[0]->is_clear_flush();
cout<<"\t";
cout<<"\t";
_players[0]->print_in_combo();
cout<<"Straight:"<<_players[0]->is_clear_straight();
cout<<"\t";
_players[0]->print_in_combo();
cout<<"Three:"<<_players[0]->is_clear_three_of_a_kind();
cout<<"\t";
cout<<"\t";
_players[0]->print_in_combo();
cout<<"Two pairs:"<<_players[0]->is_clear_two_pairs();
cout<<"\t";
_players[0]->print_in_combo();
cout<<"Pair:"<<_players[0]->is_clear_pair();
cout<<"\t";
cout<<"\t";
_players[0]->print_in_combo();*/
//*****************************************************
	};
//**************************************************************************************************
//Искренне надеюсь, что консольная версия демонстрации карт останется отладочной:
//**************************************************************************************************
	void open_cards(){
		int i = 0;
		while(i < count_players){
			_players[i]->open_cards();
			++i;
		}
	};
//**************************************************************************************************
//Сбор результатов по игроку:
//**************************************************************************************************
	res_combo fill_res_combo(Player*& pl){
		res_combo b;
		if((pl->is_clear_flush())&&(pl->is_clear_straight())){
			b._combo=STRAIGHT_FLUSH;
			b.highest_nominal = pl->highest_in_combo();
			return b;
		}
		if(pl->is_clear_four_of_a_kind()){
			b._combo=FOUR_OF_A_KIND;
			b.highest_nominal = pl->highest_in_combo();
			return b;
		}
		if(pl->is_clear_full_house()){
			b._combo=FULL_HOUSE;
			b.highest_nominal = pl->highest_in_combo();
			return b;
		}
		if(pl->is_clear_flush()){
			b._combo=FLUSH;
			b.highest_nominal = pl->highest_in_combo();
			return b;
		}
		if(pl->is_clear_straight()){
			b._combo=STRAIGHT;
			b.highest_nominal = pl->highest_in_combo();
			return b;
		}
		if(pl->is_clear_three_of_a_kind()){
			b._combo=THREE_OF_A_KIND;
			b.highest_nominal = pl->highest_in_combo();
			return b;
		}
		if(pl->is_clear_two_pairs()){
			b._combo=TWO_PAIRS;
			b.highest_nominal = pl->highest_in_combo();
			return b;
		}
		if(pl->is_clear_pair()){
			b._combo=PAIR;
			b.highest_nominal = pl->highest_in_combo();
			return b;
		}
		b._combo=NONE;
		int nom[5];
		for(int i=0;i<5;++i){
			nom[i]=(pl->get_on_hands()[i])->get_nominal();
			if(nom[i]==60)nom[i]=-1;
		}
		int n = pl->find_max(nom,5);
		b.highest_nominal = nom[n];
		return b;
	};
//**************************************************************************************************
//Хотим ли повышать ставку, если да, то насколько:
//**************************************************************************************************
	int init_up_stakes(int i){
		return _players[i]->init_up_stakes(i,player_in_game[i],res[i]._combo,count_players,stakes);
	};
//**************************************************************************************************
//Если кто-то до нас повысил ставку, решаем, поддержать или пасовать:
//**************************************************************************************************
	void agree_up_stakes(int i){
		_players[i]->agree_up_stakes(i,player_in_game[i],res[i]._combo,count_players,stakes,in_game);
	/*	if(!player_in_game[i])return;
		player_in_game[i] = (((res[i]._combo*STAKES_STEP+START_STAKES)*count_players-stakes>0)||rand()%2);
		if(!player_in_game[i]){
			in_game--;
			cout<<"player"<<i<<" is pass((("<<endl;
		}
		else{
			cout<<"player"<<i<<" agree to up stakes"<<endl;
			stakes+=STAKES_STEP;
			_players[i]->set_money(_players[i]->get_money()-STAKES_STEP);
		}*/
	};
};
//**************************************************************************************************

#include <SFML/System/Unicode.hpp>
class Graphical_game{
//Указатель на окошко, картинка стола на фоне, кнопочки
sf::RenderWindow *App;
sf::Sprite sfon;
sf::Image fon;
sf::Image butt_yes;
sf::Sprite sbutt_yes;
sf::Image butt_no;
sf::Sprite sbutt_no;
sf::Image butt_change;
sf::Sprite sbutt_change;
sf::Image butt_raise;
sf::Sprite sbutt_raise;
sf::Image butt_pass;
sf::Sprite sbutt_pass;

//карты разных мастей,по 13 каждой
sf::Sprite sjoker;
sf::Image joker;

sf::Sprite sdiamonds[13];
sf::Image diamonds[13];

sf::Sprite sclubs[13];
sf::Image clubs[13];

sf::Sprite shearts[13];
sf::Image hearts[13];

sf::Sprite sspades[13];
sf::Image spades[13];
//рубaшки карт
sf::Sprite sshirt;
sf::Image shirt;

sf::Sprite *sopen;

sf::Font my_font;
//кое-какие переменные из игры, собственно те, которые влияют на общую картинку
int stakes;
int cards[COUNT_PLAYERS*5];
int balances[COUNT_PLAYERS];
bool choosen[5];
int count_players;
int player[5];//будем использовать эту пременную, чтобы знать кто победил в предыдущем раунде или кто поднял ставку
public:

Graphical_game(){
for(int i = 0; i<5; ++i)player[i] = -1;
stakes = START_STAKES*COUNT_PLAYERS;
App = new sf::RenderWindow(sf::VideoMode(802,520,32),"SFML Graphics");
fon.LoadFromFile("Generals/table.png");
sfon.SetCenter(0,0);
sfon.SetX(0.0f);
sfon.SetY(0.0f);
sfon.SetImage(fon);

butt_yes.LoadFromFile("Generals/yes.png");
sbutt_yes.SetImage(butt_yes);
sbutt_yes.SetX(315.f);
sbutt_yes.SetY(250.f);

butt_no.LoadFromFile("Generals/no.png");
sbutt_no.SetImage(butt_no);
sbutt_no.SetX(405.f);
sbutt_no.SetY(250.f);

butt_change.LoadFromFile("Generals/change.png");
sbutt_change.SetImage(butt_change);
sbutt_change.SetX(340.f);
sbutt_change.SetY(250.f);

butt_raise.LoadFromFile("Generals/ratebutt.png");
sbutt_raise.SetImage(butt_raise);
sbutt_raise.SetX(315.f);
sbutt_raise.SetY(250.f);

butt_pass.LoadFromFile("Generals/buttpas.png");
sbutt_pass.SetImage(butt_pass);
sbutt_pass.SetX(405.f);
sbutt_pass.SetY(250.f);

joker.LoadFromFile("Generals/Joker.png");
sjoker.SetImage(joker);

spades[0].LoadFromFile("spades/spades_2.png");
spades[1].LoadFromFile("spades/spades_3.png");
spades[2].LoadFromFile("spades/spades_4.png");
spades[3].LoadFromFile("spades/spades_5.png");
spades[4].LoadFromFile("spades/spades_6.png");
spades[5].LoadFromFile("spades/spades_7.png");
spades[6].LoadFromFile("spades/spades_8.png");
spades[7].LoadFromFile("spades/spades_9.png");
spades[8].LoadFromFile("spades/spades_10.png");
spades[9].LoadFromFile("spades/spades_J.png");
spades[10].LoadFromFile("spades/spades_Q.png");
spades[11].LoadFromFile("spades/spades_K.png");
spades[12].LoadFromFile("spades/spades_A.png");

hearts[0].LoadFromFile("hearts/hearts_2.png");
hearts[1].LoadFromFile("hearts/hearts_3.png");
hearts[2].LoadFromFile("hearts/hearts_4.png");
hearts[3].LoadFromFile("hearts/hearts_5.png");
hearts[4].LoadFromFile("hearts/hearts_6.png");
hearts[5].LoadFromFile("hearts/hearts_7.png");
hearts[6].LoadFromFile("hearts/hearts_8.png");
hearts[7].LoadFromFile("hearts/hearts_9.png");
hearts[8].LoadFromFile("hearts/hearts_10.png");
hearts[9].LoadFromFile("hearts/hearts_J.png");
hearts[10].LoadFromFile("hearts/hearts_Q.png");
hearts[11].LoadFromFile("hearts/hearts_K.png");
hearts[12].LoadFromFile("hearts/hearts_A.png");

diamonds[0].LoadFromFile("diamonds/diamonds_2.png");
diamonds[1].LoadFromFile("diamonds/diamonds_3.png");
diamonds[2].LoadFromFile("diamonds/diamonds_4.png");
diamonds[3].LoadFromFile("diamonds/diamonds_5.png");
diamonds[4].LoadFromFile("diamonds/diamonds_6.png");
diamonds[5].LoadFromFile("diamonds/diamonds_7.png");
diamonds[6].LoadFromFile("diamonds/diamonds_8.png");
diamonds[7].LoadFromFile("diamonds/diamonds_9.png");
diamonds[8].LoadFromFile("diamonds/diamonds_10.png");
diamonds[9].LoadFromFile("diamonds/diamonds_J.png");
diamonds[10].LoadFromFile("diamonds/diamonds_Q.png");
diamonds[11].LoadFromFile("diamonds/diamonds_K.png");
diamonds[12].LoadFromFile("diamonds/diamonds_A.png");

clubs[0].LoadFromFile("clubs/clubs_2.png");
clubs[1].LoadFromFile("clubs/clubs_3.png");
clubs[2].LoadFromFile("clubs/clubs_4.png");
clubs[3].LoadFromFile("clubs/clubs_5.png");
clubs[4].LoadFromFile("clubs/clubs_6.png");
clubs[5].LoadFromFile("clubs/clubs_7.png");
clubs[6].LoadFromFile("clubs/clubs_8.png");
clubs[7].LoadFromFile("clubs/clubs_9.png");
clubs[8].LoadFromFile("clubs/clubs_10.png");
clubs[9].LoadFromFile("clubs/clubs_J.png");
clubs[10].LoadFromFile("clubs/clubs_Q.png");
clubs[11].LoadFromFile("clubs/clubs_K.png");
clubs[12].LoadFromFile("clubs/clubs_A.png");


for(int i=0;i<13;++i){
sspades[i].SetImage(spades[i]);
shearts[i].SetImage(hearts[i]);
sdiamonds[i].SetImage(diamonds[i]);
sclubs[i].SetImage(clubs[i]);
}

shirt.LoadFromFile("Generals/back.png");
sshirt.SetImage(shirt);

for(int i = 0; i<5; ++i)choosen[i] = 0;
cout<<"constr..."<<endl;
};

//**************************************************************
//Инициализация переменных игры, влияющих на рисуемую картинку
//**************************************************************
void graphical_init_cards(int * _cards){
	for(int i = 0;i<COUNT_PLAYERS*5;++i)
	cards[i] = _cards[i];
};
void graphical_init_balances(int* _balances){
//	memcpy(balances,_balances,COUNT_PLAYERS*sizeof(int));
	for(int i = 0;i<COUNT_PLAYERS;++i)
		balances[i] = _balances[i];
};
void graphical_init_count_players(int _count_players){
	count_players = _count_players;
};
void graphical_init_player(int _player,int count){
	if(count == 1)for(int i = 1; i<5; ++i)player[i] = -1;
	player[count-1] = _player;
};
bool is_player(int num){
	int i = 0;
	while(player[i]!=-1){
		if(player[i] == num)return true;
		++i;
	}
	return false;
};
//**************************************************************
//Отрисовка элементов интерфейса
//**************************************************************
//фон
void draw_table(){
	App->Clear(sf::Color(0,200,0));
	App->Draw(sfon);
};
//баланс игроков
void print_balance(bool wclr){
char bal[10];
sprintf(bal,"%d",balances[0]);
sf::String _balance(bal, sf::Font::GetDefaultFont(), 30.f);
	is_player(0)&&wclr?_balance.SetColor(sf::Color(128, 0, 0)):_balance.SetColor(sf::Color(0, 128, 128));
	_balance.SetPosition(340.f, 460.f);
	_balance.SetSize(50.f);
	App->Draw(_balance);

sprintf(bal,"%d",balances[1]);
	_balance.SetText(bal);
	is_player(1)&&wclr?_balance.SetColor(sf::Color(128, 0, 0)):_balance.SetColor(sf::Color(0, 128, 128));
	_balance.SetPosition(100.f, 140.f);
	App->Draw(_balance);

sprintf(bal,"%d",balances[2]);
	_balance.SetText(bal);
	is_player(2)&&wclr?_balance.SetColor(sf::Color(128, 0, 0)):_balance.SetColor(sf::Color(0, 128, 128));
	_balance.SetPosition(340.f, 10.f);
	App->Draw(_balance);

sprintf(bal,"%d",balances[3]);
	_balance.SetText(bal);
	is_player(3)&&wclr?_balance.SetColor(sf::Color(128, 0, 0)):_balance.SetColor(sf::Color(0, 128, 128));
	_balance.SetPosition(580.f, 140.f);
	App->Draw(_balance);

}
//текущая ставка
void print_stakes(){
char st[6];
sprintf(st,"%d",stakes);
sf::String _stakes(st, sf::Font::GetDefaultFont(), 30.f);
	_stakes.SetColor(sf::Color(0, 128, 128));
	_stakes.SetPosition(340.f, 170.f);
	_stakes.SetSize(50.f);
	App->Draw(_stakes);
};

//**************************************************************
//карты..
//**************************************************************
//...игрока рубашками
void draw_usr_shirts(){
	sshirt.SetY(450.0f);
	for(int i=0;i<5;++i){
		sshirt.SetX(260+i*55);
		App->Draw(sshirt);
	}
//	sshirt.Resize(2,2);
};
//..игрока открытые
void draw_usr_open(){
	for(int i=0;i<5;++i){
		if(cards[i]<52)
			switch(cards[i]%4){
				case 0:sopen = &sspades[cards[i]/4];break;
				case 1:sopen = &sdiamonds[cards[i]/4];break;
				case 2:sopen = &shearts[cards[i]/4];break;
				case 3:sopen = &sclubs[cards[i]/4];break;
			}
		else sopen = &sjoker;
		sopen->SetY(360.0f-choosen[i]*30);
		sopen->SetX(260+i*55);
		App->Draw(*sopen);
	}
};
//..соперников рубашками
void draw_other_shirts(){
	sshirt.SetY(70.0f);
	for(int i=0;i<5;++i){
		sshirt.SetX(260+i*55);
		App->Draw(sshirt);
	}
	sshirt.SetY(220.0f);
	for(int i=0;i<5;++i){
		sshirt.SetX(10+i*55);
		App->Draw(sshirt);
	}
	sshirt.SetY(220.0f);
	for(int i=0;i<5;++i){
		sshirt.SetX(500+i*55);
		App->Draw(sshirt);
	}
};
//соперников открытые
void draw_other_open(){
	for(int i=5;i<10;++i){
		if(cards[i]<52)
			switch(cards[i]%4){
				case 0:sopen = &sspades[cards[i]/4];break;
				case 1:sopen = &sdiamonds[cards[i]/4];break;
				case 2:sopen = &shearts[cards[i]/4];break;
				case 3:sopen = &sclubs[cards[i]/4];break;
			}
		else sopen = &sjoker;
		sopen->SetY(200.0f);
		sopen->SetX(10+(i%5)*55);
		App->Draw(*sopen);
	}
	for(int i=10;i<15;++i){
		if(cards[i]<52)
			switch(cards[i]%4){
				case 0:sopen = &sspades[cards[i]/4];break;
				case 1:sopen = &sdiamonds[cards[i]/4];break;
				case 2:sopen = &shearts[cards[i]/4];break;
				case 3:sopen = &sclubs[cards[i]/4];break;
			}
		else sopen = &sjoker;
		sopen->SetY(70.0f);
		sopen->SetX(260+(i%5)*55);
		App->Draw(*sopen);
	}
	for(int i=15;i<20;++i){
		if(cards[i]<52)
			switch(cards[i]%4){
				case 0:sopen = &sspades[cards[i]/4];break;
				case 1:sopen = &sdiamonds[cards[i]/4];break;
				case 2:sopen = &shearts[cards[i]/4];break;
				case 3:sopen = &sclubs[cards[i]/4];break;
			}
		else sopen = &sjoker;
		sopen->SetY(200.0f);
		sopen->SetX(500+(i%5)*55);
		App->Draw(*sopen);
	}
};
//**************************************************************
//рисуем кнопочки
//**************************************************************
void draw_change(){
	App->Draw(sbutt_change);
}
void draw_yes_no_init(){
	App->Draw(sbutt_yes);
	App->Draw(sbutt_no);
	char massege[40];
	sprintf(massege,"Do you want to raise the stakes?");
	sf::String _massege(massege, sf::Font::GetDefaultFont(), 30.f);
	_massege.SetColor(sf::Color(0, 128, 128));
	_massege.SetPosition(270.f, 310.f);
	_massege.SetSize(20.f);
	App->Draw(_massege);
}
void draw_yes_no_agree(){
	App->Draw(sbutt_raise);
	App->Draw(sbutt_pass);
	char massege[80];
	cout<<"yes_no_agree..."<<player[0]<<endl;
	switch(player[0]){
		case 1:sprintf(massege,"Left player wants to raise the stakes, are you in?");break;
		case 2:sprintf(massege,"Top player wants to raise the stakes, are you in?");break;
		case 3:sprintf(massege,"Right player wants to raise the stakes, are you in?");break;
	};
	sf::String _massege(massege, sf::Font::GetDefaultFont(), 30.f);
	_massege.SetColor(sf::Color(0, 128, 128));
	_massege.SetPosition(210.f, 310.f);
	_massege.SetSize(20.f);
	App->Draw(_massege);
}
void draw_yes_no_next(){
	App->Draw(sbutt_yes);
	App->Draw(sbutt_no);
	char massege[40];
	sprintf(massege,"One more time?");
	sf::String _massege(massege, sf::Font::GetDefaultFont(), 30.f);
	_massege.SetColor(sf::Color(0, 128, 128));
	_massege.SetPosition(335.f, 310.f);
	_massege.SetSize(20.f);
	App->Draw(_massege);
}
//**************************************************************
//методы, требующие ввода
//**************************************************************
//в конце раунда, продолжать ли игру
bool graphical_next_round(){
	while(App->IsOpened()){
		sf::Event Event;
		while(App->GetEvent(Event)){
			if(Event.Type == sf::Event::Closed)
			App->Close();
			if(Event.Type == sf::Event::MouseButtonPressed&&(Event.MouseButton.X>315&&Event.MouseButton.X<399&&Event.MouseButton.Y>250&&Event.MouseButton.Y<309))return true;
			if(Event.Type == sf::Event::MouseButtonPressed&&(Event.MouseButton.X>405&&Event.MouseButton.X<489&&Event.MouseButton.Y>250&&Event.MouseButton.Y<309))return false;
		}
		draw_table();
		print_balance(1);
		draw_yes_no_next();
		draw_usr_open();
		draw_other_open();
		App->Display();
	}
};
//Выбор карт, которые необходимо поменять
bool* graphical_make_a_choise(){
	stakes = START_STAKES * COUNT_PLAYERS ;
	while(App->IsOpened()){
		sf::Event Event;
		while(App->GetEvent(Event)){

			if(Event.Type == sf::Event::Closed)
			App->Close();
			if(Event.Type == sf::Event::MouseButtonPressed)
			{

				if(Event.MouseButton.Y>360&&Event.MouseButton.Y<465&&Event.MouseButton.X>260&&Event.MouseButton.X<535)
				{
					choosen[(Event.MouseButton.X-260)/55] = 1-choosen[(Event.MouseButton.X-260)/55];
				}
				if(Event.MouseButton.X>340&&Event.MouseButton.X<429&Event.MouseButton.Y>250&&Event.MouseButton.Y<304)
				{
				bool* tmp = new bool[5];
				memcpy(tmp,choosen,5*sizeof(bool));
				for(int i=0;i<5;++i)choosen[i]=0;
			//don't worry, Human_player::make_a_choise() will free this memory
				return tmp;
				};
			}
/*			if(Event.Type == sf::Event::MouseMoved){
				char coord[6];
				sprintf(coord,"%d,%d",Event.MouseMove.Y,Event.MouseMove.X);
				sf::String _coord(coord, sf::Font::GetDefaultFont(), 30.f);
				_coord.SetColor(sf::Color(0, 128, 128));
				_coord.SetPosition(0.f, 0.f);
				_coord.SetSize(50.f);
				App->Draw(_coord);
				App->Display();
			}
*/
		}
		draw_table();
		print_stakes();
		print_balance(0);
		draw_change();
		draw_usr_open();
		draw_other_shirts();
		App->Display();
	}
};
//Хочет ли игрок инициировать поднятие ставок
bool graphical_init_up_stakes(int& _stakes){
	stakes = _stakes;
	while(App->IsOpened()){
		sf::Event Event;
		while(App->GetEvent(Event)){
			if(Event.Type == sf::Event::Closed)
			App->Close();
			if(Event.Type == sf::Event::MouseButtonPressed&&(Event.MouseButton.X>315&&Event.MouseButton.X<399&&Event.MouseButton.Y>250&&Event.MouseButton.Y<309))return true;
			if(Event.Type == sf::Event::MouseButtonPressed&&(Event.MouseButton.X>405&&Event.MouseButton.X<489&&Event.MouseButton.Y>250&&Event.MouseButton.Y<309))return false;
		}
		draw_table();
		print_stakes();
		print_balance(0);
		draw_yes_no_init();
		draw_usr_open();
		draw_other_shirts();
		App->Display();
	};
};
//кто-то из соперников поднял ставки, поддержит ли игрок
void graphical_agree_up_stakes(bool& in_game, int& _stakes){
	stakes = _stakes;
	while(App->IsOpened()){
		sf::Event Event;
		while(App->GetEvent(Event)){
			if(Event.Type == sf::Event::Closed)App->Close();
			if(Event.Type == sf::Event::MouseButtonPressed&&(Event.MouseButton.X>315&&Event.MouseButton.X<399&&Event.MouseButton.Y>250&&Event.MouseButton.Y<334))return;
			if(Event.Type == sf::Event::MouseButtonPressed&&(Event.MouseButton.X>405&&Event.MouseButton.X<489&&Event.MouseButton.Y>250&&Event.MouseButton.Y<309)){in_game = 0;return;}
		}
		draw_table();
		print_stakes();
		print_balance(0);
		draw_yes_no_agree();
		draw_usr_open();
		draw_other_shirts();
		App->Display();
	};
};

};

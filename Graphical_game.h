#ifndef __GGame
#define __GGame
#include <string.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Unicode.hpp>
#include <iostream>
#include <string.h>
using namespace std;
//Количество игроков
#define COUNT_PLAYERS 4
//Минимальная ставка с игрока
#define START_STAKES 100
//Минимальный шаг для повышения ставки
#define STAKES_STEP 50
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

Graphical_game();
//**************************************************************
//Инициализация переменных игры, влияющих на рисуемую картинку
//**************************************************************
void graphical_init_cards(int * _cards);
void graphical_init_balances(int* _balances);
void graphical_init_count_players(int _count_players);
void graphical_init_player(int _player,int count);
bool is_player(int num);
//**************************************************************
//Отрисовка элементов интерфейса
//**************************************************************
//фон
void draw_table();
//баланс игроков
void print_balance(bool wclr);
//текущая ставка
void print_stakes();

//**************************************************************
//карты..
//**************************************************************
//...игрока рубашками
void draw_usr_shirts();
//..игрока открытые
void draw_usr_open();
//..соперников рубашками
void draw_other_shirts();
//соперников открытые
void draw_other_open();
//**************************************************************
//рисуем кнопочки
//**************************************************************
void draw_change();
void draw_yes_no_init();
void draw_yes_no_agree();
void draw_yes_no_next();
//**************************************************************
//методы, требующие ввода
//**************************************************************
//в конце раунда, продолжать ли игру
bool graphical_next_round();
//Выбор карт, которые необходимо поменять
bool* graphical_make_a_choise();
//Хочет ли игрок инициировать поднятие ставок
bool graphical_init_up_stakes(int& _stakes);
//кто-то из соперников поднял ставки, поддержит ли игрок
void graphical_agree_up_stakes(bool& in_game, int& _stakes);
};
#endif
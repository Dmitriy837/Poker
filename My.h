#include <iostream>
using namespace std;
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
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
//Количество игроков
#define COUNT_PLAYERS 4
//Денег на руках у игрока в начале игры
#define START_MONEY 3000
//Минимальная ставка с игрока
#define START_STAKES 100
//Минимальный шаг для повышения ставки
#define STAKES_STEP 50
enum COMBO{NONE, PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH};

#include "Graphical_game.h"
#include "Card.h"
#include "Deck.h"

#include "Player.h"
#include "Cpu_player.h"
#include "Human_player.h"
#include "Round.h"
#include "Game.h"


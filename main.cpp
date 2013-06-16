#include "My.h"
int main( int argc, char **argv ){
srand(time(NULL));
Game my_game(COUNT_PLAYERS);
my_game.Run();
return 0;
}

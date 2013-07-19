CC=gcc
CPPFLAGS=-lstdc++ -lsfml-graphics -lsfml-window -lsfml-system
SHELL=/bin/bash

GPoker:Card.o Deck.o Player.o Human_player.o Graphical_game.o Cpu_player.o Round.o Game.o
	$(CC) main.cpp Card.o Deck.o Player.o Human_player.o Graphical_game.o Cpu_player.o Round.o Game.o -o $@ $(CPPFLAGS) 
	(rm Card.o)
	(rm Deck.o)
	(rm Player.o)
	(rm Human_player.o)
	(rm Cpu_player.o)
	(rm Round.o)
	(rm Game.o)
Card.o:
	$(CC) Card.cpp -c $(CPPFLAGS)
Deck.o:
	$(CC) Deck.cpp -c $(CPPFLAGS)
Player.o:
	$(CC) Player.cpp -c $(CPPFLAGS)
Human_player.o:
	$(CC) Human_player.cpp -c $(CPPFLAGS)
Graphical_game.o:
	$(CC) Graphical_game.cpp -c $(CPPFLAGS)
Cpu_player.o:
	$(CC) Cpu_player.cpp -c $(CPPFLAGS)
Round.o:
	$(CC) Round.cpp -c $(CPPFLAGS)
Game.o:
	$(CC) Game.cpp -c $(CPPFLAGS)
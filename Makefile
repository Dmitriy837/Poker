CC=gcc
CPPFLAGS=-lstdc++ -lsfml-graphics -lsfml-window -lsfml-system
SHELL=/bin/bash

GPoker:Card.o Deck.o Player.o Human_player.o
	$(CC) main.cpp Card.o Deck.o Player.o Human_player.o -o $@ $(CPPFLAGS) 
	(rm Card.o)
	(rm Deck.o)
	(rm Player.o)
	(rm Human_player.o)
Card.o:
	$(CC) Card.cpp -c $(CPPFLAGS)
Deck.o:
	$(CC) Deck.cpp -c $(CPPFLAGS)
Player.o:
	$(CC) Player.cpp -c $(CPPFLAGS)
Human_player.o:
	$(CC) Human_player.cpp -c $(CPPFLAGS)

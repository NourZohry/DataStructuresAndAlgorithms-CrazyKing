#include <string>
#include "LinkedList.h"
#include "Card.h"
#pragma once
#include <iostream>
using namespace std;
using std::string;
class Player //Adds a new player
{
	string name;
	LinkedList<Card> PlayerCards;
	int score;



public:
	Player();
	void setName(string n);
	string getName() const;
	void AddToPlayerCards(Card c);
	void PrintCards();
	int HandContainsValue(int val);
	int HandContainsSuit(int suit);
	void DeleteCard(int index);
	Card GetCard(int index);
	bool NoCards();
	void DeleteAllCards();
	int ScoreTally();
	void addToScore(int s);
	int getScore() const;
	int getCardCount() const;
	int MostCommonSuit();
	


	
};



#pragma once
#include <iostream>
#include "Game.h"
using namespace std;

int main()
{
	//I used 1, 2, 3, 4 to represent the 4 suits. [Number|Suit]

	//I tried to print ascii:

	// cout << "♥";
	// char b = '\u0444';
	//cout << b;
	//cout << "Hello, ♥ or \u2665!\n";
	//cout << "♥";
	//wcout << L"♥";
	//wchar_t f = 1060;
	//wcout << f << endl;


	Game *PGame = new Game;
	PGame->startGame();
	
	return 0;
}
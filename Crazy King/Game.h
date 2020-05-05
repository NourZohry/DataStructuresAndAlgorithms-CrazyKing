#include <conio.h> //for getch to get any key to continue 
#include "Stack.h"
#include "Card.h"
#include "Player.h"

#pragma once

class Game //Responsible for game playing, scoring, and program interface.
{
	int NumberOfPlayers;
	Player* PlayerList;
	Stack<Card> DRWpile;
	Stack<Card> DSCpile;
	int TimesDRWRanOut;
	int RoundWinnerIndex;
	//Stack<Card*> DRWpile;
	//Stack<Card*> DSCpile;
	bool TurnOrder;
	int CurrentPlayer;

	bool SkipTurn;
	bool SkipTurnDrawTwo;

public:
	Game();
	void startGame();
	void InputPlayers();
	void FillDRW();
	void Shuffle(Stack<Card>& DRW); //Doesn't work yet
	int StackSize(Stack<Card> s);
	void DealCards();
	void PrintLayout();
	void PlayerAction(int p, int val, int suit);
	bool PlayCardIfPossible(int p, int val, int suit);
	bool CheckWinner(int p);
	int ScoreOfAllOtherPlayers();

	void AceReverseOrder();
	void JackSkipTurn(); //need king exception
	void QueenSkipTurnDrawTwo();

	void ChangeToNextPlayer();
	void KingCardEffect();

	void PrintSuitAfterPlaying(Card playcard);

};


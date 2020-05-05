#include <iostream>     // std::cout
#include <algorithm>    // std::shuffle


#include <random>
#include "Game.h"
//#include "Card.h"
using namespace std;
#pragma once


Game::Game()
{
	NumberOfPlayers = 0;
	TimesDRWRanOut = 0;
	RoundWinnerIndex = 0;
	TurnOrder = 0; //not reversed
	CurrentPlayer = 0;
	SkipTurn = 0;
	SkipTurnDrawTwo = 0;
}

void Game::startGame()
{
	
	InputPlayers();
	while (1)
	{
		FillDRW();
		DealCards();
		PrintLayout();
	
		//At each round, the first player to play is the winner of the last round. If this is the first
		//round ever, a random player is picked to start the game
		/*Each round continues until a player wins or until DRWpile runs out of cards 5 times.*/
		/* ROUNDWinner score in a round is the total sum of all cards points from other players*/
		/*GAME Winner: is the player who achieves total score of 500 first.*/
		CurrentPlayer = RoundWinnerIndex;
		while (1)
		{

		
			cout << "TURN of: " << PlayerList[CurrentPlayer].getName();
			cout << "\nACTION: " << PlayerList[CurrentPlayer].getName();
			PlayerAction(CurrentPlayer, DSCpile.peek().getValue() , DSCpile.peek().getSuit());
			if (CheckWinner(CurrentPlayer))
			{
				RoundWinnerIndex = CurrentPlayer;
				PlayerList[CurrentPlayer].addToScore(ScoreOfAllOtherPlayers());
				cout << endl << PlayerList[CurrentPlayer].getName() << " has won this round! \n\n";
				if (PlayerList[CurrentPlayer].getScore() >= 500)
				{
					cout << PlayerList[CurrentPlayer].getName() << " has won the game! Congratulations and thank you for playing!";
					_getch();
					return;
				}
				break;
			}

			if (DRWpile.isEmpty())
			{
				FillDRW();
				TimesDRWRanOut++;
				if (TimesDRWRanOut == 5)
				{
					cout << "\n The draw pile ran out of cards 5 times so a new round will now start!\n";

					int p = NumberOfPlayers - 1; //assume last player
					//Check who has the lowest number of cards
					for (int i = 0; i < NumberOfPlayers - 1; i++)
					{
						if (PlayerList[i].getCardCount() < PlayerList[i + 1].getCardCount())
							RoundWinnerIndex = i;
					}


					break;
				}

			}

			cout << "\nPress any key to continue.\n";
			_getch();


			PrintLayout();

			if (!CheckWinner(CurrentPlayer))
			{
				//change to next player
				ChangeToNextPlayer();
			}

		}
			
	}
}

void Game::ChangeToNextPlayer()
{
	if (!TurnOrder) //normal order
	{
		CurrentPlayer++;
		if (CurrentPlayer == NumberOfPlayers)
		{
			CurrentPlayer = 0;
		}
		else if (CurrentPlayer == NumberOfPlayers + 1)
		{
			CurrentPlayer = 1;
		}
	}

	else if (TurnOrder) //reversed order
	{
		CurrentPlayer--;
		if (CurrentPlayer == -1)
		{
			CurrentPlayer = NumberOfPlayers - 1;
		}
		else if (CurrentPlayer == -2)
		{
			CurrentPlayer = NumberOfPlayers - 2;
		}
	}
}

bool Game::CheckWinner(int p)
{
	if (PlayerList[p].NoCards())
	{
		return 1;
	}
	return 0;
}

bool Game::PlayCardIfPossible(int p, int val, int suit)
{
	int valcheck = PlayerList[p].HandContainsValue(val);
	int suitcheck = PlayerList[p].HandContainsSuit(suit);
	if (valcheck != -1)
	{
		Card playcard = PlayerList[p].GetCard(valcheck);
		DSCpile.push(playcard);
		PlayerList[p].DeleteCard(valcheck);

		PrintSuitAfterPlaying(playcard);

		return 1;
	}
	else if (suitcheck != -1)
	{
		Card playcard = PlayerList[p].GetCard(suitcheck);
		DSCpile.push(playcard);
		PlayerList[p].DeleteCard(suitcheck);

		PrintSuitAfterPlaying(playcard);

		return 1;
	}
	else if(PlayerList[p].HandContainsValue(13) != -1) //has king
	{
		int valcheck = PlayerList[p].HandContainsValue(13);
		Card playcard = PlayerList[p].GetCard(valcheck);
		DSCpile.push(playcard);
		PlayerList[p].DeleteCard(valcheck);

		PrintSuitAfterPlaying(playcard);

		return 1;
	}
	
	else
		return 0;
}

int Game::ScoreOfAllOtherPlayers()
{
	int score = 0;
	for (int i = 0; i < NumberOfPlayers; i++)
	{
		if (i != RoundWinnerIndex)
			score += PlayerList[i].ScoreTally();
	}
	return score;
}

void Game::PlayerAction(int p, int val, int suit)
{
	if (SkipTurn)
	{
		if (PlayerList[p].HandContainsValue(13) != -1) //has king
		{
			cout << " will play their KING";
			int valcheck = PlayerList[p].HandContainsValue(13); //get index of king
			Card playcard = PlayerList[p].GetCard(valcheck);
			DSCpile.push(playcard);
			PlayerList[p].DeleteCard(valcheck);
			return;
		}
		else 
		{
			cout << " will SKIP their turn.";
			SkipTurn = 0;
			return;
		}
	}
	if (SkipTurnDrawTwo)
	{
		if (PlayerList[p].HandContainsValue(13) != -1) //has king
		{
			cout << " will play their KING";
			int valcheck = PlayerList[p].HandContainsValue(13); //get index of king
			Card playcard = PlayerList[p].GetCard(valcheck);
			DSCpile.push(playcard);
			PlayerList[p].DeleteCard(valcheck);
			return;
		}
		else {
			cout << " will SKIP and DRAW two cards.";
			SkipTurnDrawTwo = 0;

			Card topcard = DRWpile.peek();
			DRWpile.pop();
			PlayerList[p].AddToPlayerCards(topcard);

			if (DRWpile.isEmpty())
			{
				FillDRW();
			}

			topcard = DRWpile.peek();
			DRWpile.pop();
			PlayerList[p].AddToPlayerCards(topcard);
			return;
		}
	}	


	bool played = PlayCardIfPossible(p, val, suit);
	if (played) return;

	//else: doesn't have a card to play

	/* Draw a card from DRW-pile and play if matching.
- Otherwise, draw another card from DRW-pile and play if matching.
- Otherwise, player loses his turn. (PASS)*/

	Card topcard = DRWpile.peek();
	DRWpile.pop();
	PlayerList[p].AddToPlayerCards(topcard);
	played = PlayCardIfPossible(p, val, suit);
	if (played)
	{
		cout << " after DRAWing it from the DRW-pile!";
		return;
	}

	if (DRWpile.isEmpty())
		FillDRW();

	topcard = DRWpile.peek();
	DRWpile.pop();
	PlayerList[p].AddToPlayerCards(topcard);
	played = PlayCardIfPossible(p, val, suit);
	if (played)
	{
		cout << " after DRAWing it as the SECOND card from the DRW-pile!";
		return;
	}

	//else: passes, loses their turn

	cout << " DRAWs two cards from the DRW-pile and loses their turn :(";


}

void Game::InputPlayers()
{
	int n = 0;
	cout << "Enter the number of players: ";
	cin >> n;
	while (n != 2 && n != 3 && n != 4 && n != 5)
	{
		cout << "\nInvalid input! Enter valid number of players: ";
		cin >> n;
	}
	NumberOfPlayers = n;
	PlayerList = new Player[NumberOfPlayers];


	string name;
	for (int i = 0; i < n; i++)
	{
		cout << "\nPlayer " << i + 1 << " name: ";
		cin >> name;
		PlayerList[i].setName(name);
	}

	RoundWinnerIndex = rand() % (NumberOfPlayers);
}

void Game::FillDRW()
{
	while (!DRWpile.isEmpty())
	{
		DRWpile.pop();
	}
	Card drawcards[52]; //Fills DRWpile with 52 cards
	int j = 0;
	int k = 1;
	for (int i = 0; i < 52; i++)
	{
		j++;
		if (j == 14)
		{
			j = 1;
			k++;
		}
		drawcards[i].setValue(j);
		drawcards[i].setSuit(k);
		DRWpile.push(drawcards[i]);
	}

	Shuffle(DRWpile);
}

void Game::DealCards()
{
	for (int i = 0; i < NumberOfPlayers; i++)
	{
		PlayerList[i].DeleteAllCards();
	}

	Card x;
	for (int i = 0; i < NumberOfPlayers; i++)
	{
		for (int j = 0; j < 7; j++)
		{
		x = DRWpile.peek();
		DRWpile.pop();
		PlayerList[i].AddToPlayerCards(x);
		}
	}
	x = DRWpile.peek();
	DRWpile.pop();
	DSCpile.push(x);	
}
	

void Game::PrintLayout()
{
	Card x;
	x = DSCpile.peek();
	cout << "\nDRW-pile  [Cards " << StackSize(DRWpile) << "] [" << TimesDRWRanOut << "] \n\n";
	cout << "DSC-pile  [Cards " << StackSize(DSCpile) << "]  ";
	if (x.getValue() == 1)
		cout << "[" << "A" << "|" << x.getSuit() << "]";
	else if (x.getValue() == 11)
		cout << "[" << "J" << "|" << x.getSuit() << "]";
	else if (x.getValue() == 12)
		cout << "[" << "Q" << "|" << x.getSuit() << "]";
	else if (x.getValue() == 13)
		cout << "[" << "K" << "|" << x.getSuit() << "]";
	else
		cout << "[" << x.getValue() << "|" << x.getSuit() << "]";
	cout << "\n=====================================================================\n";

	for (int i = 0; i < NumberOfPlayers; i++)
	{
		PlayerList[i].PrintCards();
	}
}


void Game::Shuffle(Stack<Card> &DRW)
{
	int n;
	Card* ArrayDRW = DRW.toArray(n);

	random_shuffle(&ArrayDRW[0], &ArrayDRW[n]);

	for (int i = 0; i < 52; i++)
	{
		DRW.pop();
	}
	for (int i = 0; i < 52; i++)
	{
		DRW.push(ArrayDRW[i]);
	}

}

int Game::StackSize(Stack<Card> s)
{
	int count = 0;
	while (!s.isEmpty())
	{
		s.pop();
		count++;
	}
	return count;
}

void Game::AceReverseOrder()
{
	TurnOrder = !TurnOrder;
}

void Game::PrintSuitAfterPlaying(Card playcard)
{
	cout << " will PLAY [";
	if (playcard.getValue() == 11)
	{
		JackSkipTurn();
		cout << "J";
	}
	else if (playcard.getValue() == 12)
	{
		QueenSkipTurnDrawTwo();
		cout << "Q";
	}
	else if (playcard.getValue() == 13)
	{
		KingCardEffect();
		cout << "K";
	}
	else if (playcard.getValue() == 1)
	{
		AceReverseOrder();
		cout << "A";
	}
	else
		cout << playcard.getValue();

	cout << "|" << playcard.getSuit() << "]";
}

void Game::JackSkipTurn()
{
	SkipTurn = true;
}


void Game::QueenSkipTurnDrawTwo()
{
	SkipTurnDrawTwo = true;
}

void Game::KingCardEffect()
{
	int newSuit = PlayerList[CurrentPlayer].MostCommonSuit();

	Card x = DSCpile.peek();
	DSCpile.pop();
	x.setSuit(newSuit);
	DSCpile.push(x);
}
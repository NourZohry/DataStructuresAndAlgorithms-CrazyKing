#include "Player.h"

Player::Player()
{
	score = 0;
}

void Player::setName(string n)
{
	name = n;
}
string Player::getName() const
{
	return name;
}


void Player::AddToPlayerCards(Card c)
{
	PlayerCards.InsertEnd(c);
}

void Player::PrintCards()
{

	int n;
	const Card* PCArray = PlayerCards.toArray(n);

	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (PCArray[i].getValue() == 1 || PCArray[i].getValue() == 11 || PCArray[i].getValue() == 12)
			sum += 10;

		else if (PCArray[i].getValue() == 13)
			sum += 30;

		else
			sum += PCArray[i].getValue();
	}

	cout << name << "\t" << "[Score=" << score << "]\t" << "[" << n << " Cards]" << "\t [Cards Sum = " << sum << "]\n\n";

	
	int x;
	for (int i = 0; i < n; i++)
	{
		x = PCArray[i].getValue();
		if (x == 1)
			cout << "[" << "A" << "|" << PCArray[i].getSuit() << "]";
		else if (x == 11)
			cout << "[" << "J" << "|" << PCArray[i].getSuit() << "]";
		else if (x == 12)
			cout << "[" << "Q" << "|" << PCArray[i].getSuit() << "]";
		else if (x == 13)
			cout << "[" << "K" << "|" << PCArray[i].getSuit() << "]";
		else
		cout << "[" << PCArray[i].getValue() << "|" << PCArray[i].getSuit() << "]";

		
	}
	cout << "\n=====================================================================\n";

}

int Player::HandContainsValue(int val)
{
	//Card x;
	//x.setValue(val);
	////return PlayerCards.search(val);
	//PlayerCards.search(x);
	//return 0;
	int n;
	const Card* PCArray = PlayerCards.toArray(n);
	for (int i = 0; i < n; i++)
	{
		if (PCArray[i].getValue() == val)
			return i;
	}
	return -1;
}

int Player::HandContainsSuit(int suit)
{
	//Card x;
	//x.setValue(val);
	////return PlayerCards.search(val);
	//PlayerCards.search(x);
	//return 0;
	int n;
	const Card* PCArray = PlayerCards.toArray(n);
	for (int i = 0; i < n; i++)
	{
		if (PCArray[i].getSuit() == suit)
			return i;
	}
	return -1;
}

void Player::DeleteCard(int index)
{
	PlayerCards.DeleteIndex(index);
}

Card Player::GetCard(int index)
{
	return PlayerCards.ReturnIndex(index);
}

bool Player::NoCards()
{
	return PlayerCards.IsEmpty();
}

void Player::DeleteAllCards()
{
	PlayerCards.DeleteAll();
}

int Player::ScoreTally()
{
	int sum=0;
	int n;
	const Card* PCArray = PlayerCards.toArray(n);
	for (int i = 0; i < n; i++)
	{
		if (PCArray[i].getValue() == 1 || PCArray[i].getValue() == 11 || PCArray[i].getValue() == 12)
			sum += 10;

		else if (PCArray[i].getValue() == 13)
			sum += 30;

		else
			sum += PCArray[i].getValue();
	}
	return sum;
}

void Player::addToScore(int s)
{
	score += s;
}

int Player::getScore() const
{
	return score;
}

int Player::getCardCount() const
{
	int n;
	const Card* PCArray = PlayerCards.toArray(n);
	return n;
}

int Player::MostCommonSuit()
{
	int n;
	const Card* PCArray = PlayerCards.toArray(n);
	//int count1 = 0;
	//int count2 = 0;
	//int count3 = 0;
	//int count4 = 0;
	int count[4] = { 0 };

	for (int i = 0; i < n; i++)
	{
		if (PCArray[i].getSuit() == 1)
			count[0]++;
		if (PCArray[i].getSuit() == 2)
			count[1]++;
		if (PCArray[i].getSuit() == 3)
			count[2]++;
		if (PCArray[i].getSuit() == 4)
			count[3]++;
	}

	int max = 0;
	for (int i = 0; i < 4; i++)
	{
		if (count[i] > max)
			max = i;
	}
	return max + 1;

}
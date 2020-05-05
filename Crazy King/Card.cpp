#include "Card.h"


void Card::setFaceup(bool f)
{
	Faceup = f;
}

void Card::setValue(int v)
{
	value = v;
}
void Card::setSuit(int s)
{
	suit = s;
}

int Card::getValue() const
{
	return value;
}
int Card::getSuit() const
{
	return suit;
}

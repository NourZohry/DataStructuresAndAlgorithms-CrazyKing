#pragma once
class Card
{
	bool Faceup = 0;
	int value;
	int suit;                    ///////////////////try character instead of string maybe //spade, club, hearts, diamonds

public:

	void setFaceup(bool f);
	void setValue(int v);
	void setSuit(int s);

	int getValue() const;
	int getSuit() const;

};


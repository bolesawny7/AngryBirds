#include "Pig.h"


void Pig::initPigs1(Sprite Pig[])
{
	//1 *score scale /5*
	Pig[0].setPosition(1232, 522);
	Pig[0].setTextureRect(IntRect(786, 569, 80, 85));
	Pig[0].setScale(0.8, 0.8);
	//2
	Pig[1].setPosition(1482, 635);
	Pig[1].setTextureRect(IntRect(786, 569, 80, 85));
	Pig[1].setScale(0.8, 0.8);
	//3
	Pig[2].setPosition(1629, 398);
	Pig[2].setTextureRect(IntRect(786, 569, 80, 85));
	Pig[2].setScale(0.8, 0.8);
}

void Pig::initPigs2(Sprite Pig2[])
{

	//1
	Pig2[0].setPosition(1310, 422);
	Pig2[0].setTextureRect(IntRect(786, 569, 80, 85));
	Pig2[0].setScale(0.8, 0.8);
	//2
	Pig2[1].setPosition(1390, 480);
	Pig2[1].setTextureRect(IntRect(770, 482, 96, 88));
	Pig2[1].setScale(0.8, 0.8);
	//3
	Pig2[2].setPosition(1507, 387);
	Pig2[2].setTextureRect(IntRect(786, 569, 80, 85));
	Pig2[2].setScale(0.8, 0.8);
}

void Pig::initPigs3(Sprite Pig3[])
{

	//1 *score scale /5*
	Pig3[0].setPosition(1110, 387);
	Pig3[0].setTextureRect(IntRect(786, 569, 80, 85));
	Pig3[0].setScale(0.8, 0.8);
	//2
	Pig3[1].setPosition(1360, 387);
	Pig3[1].setTextureRect(IntRect(786, 569, 80, 85));
	Pig3[1].setScale(0.8, 0.8);
	//3
	Pig3[2].setPosition(1643, 330);
	Pig3[2].setTextureRect(IntRect(40, 2, 128, 155));
	Pig3[2].setScale(0.8, 0.8);
}

Pig::Pig()
{
}

Pig::~Pig()
{
}
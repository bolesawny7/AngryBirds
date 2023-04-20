#include "Levels.h"


void Levels::initLevel1(Sprite Wood[])
{
	//1
	Wood[0].setPosition(1200, 585);
	Wood[0].setTextureRect(IntRect(253, 358, 83, 20));
	Wood[0].setScale(1.5, 1);
	Wood[0].setRotation(0);


	//2


	Wood[1].setPosition(1450, 698);
	Wood[1].setTextureRect(IntRect(253, 358, 83, 20));
	Wood[1].setScale(1.5, 1);
	Wood[1].setRotation(0);



	//3

	Wood[2].setPosition(1600, 461);
	Wood[2].setTextureRect(IntRect(253, 358, 83, 20));
	Wood[2].setScale(1.5, 1);
	Wood[2].setRotation(0);
}

void Levels::initLevel2(Sprite Wood2[])
{
	//1
	Wood2[0].setPosition(1300, 485);
	Wood2[0].setTextureRect(IntRect(253, 358, 83, 20));
	Wood2[0].setScale(1, 1);
	Wood2[0].setRotation(0);
	//2
	Wood2[1].setPosition(1390, 550);
	Wood2[1].setTextureRect(IntRect(253, 358, 83, 20));
	Wood2[1].setScale(1, 1);
	Wood2[1].setRotation(0);
	//3
	Wood2[2].setPosition(1500, 450);
	Wood2[2].setTextureRect(IntRect(253, 358, 83, 20));
	Wood2[2].setScale(1, 1);
	Wood2[2].setRotation(0);
}

void Levels::initLevel3(Sprite Wood3[])
{
	//1

	Wood3[0].setPosition(1100, 450);
	Wood3[0].setTextureRect(IntRect(253, 358, 83, 20));
	Wood3[0].setScale(1, 1);
	Wood3[0].setRotation(0);

	//2

	Wood3[1].setPosition(1350, 450);
	Wood3[1].setTextureRect(IntRect(252, 358, 83, 22));
	Wood3[1].setScale(1, 1);
	Wood3[1].setRotation(0);

	//3

	Wood3[2].setPosition(1500, 450);
	Wood3[2].setScale(0.3, 0.09);
	Wood3[2].setRotation(0);

	//triangle
	Wood3[3].setPosition(1440, 243);
	Wood3[3].setScale(0.07, 0.07);
	Wood3[3].setRotation(0);

	Wood3[4].setPosition(1945, 243);
	Wood3[4].setScale(-0.07, 0.07);
	Wood3[4].setRotation(0);

}


Levels::Levels()
{
}

Levels::~Levels()
{
}

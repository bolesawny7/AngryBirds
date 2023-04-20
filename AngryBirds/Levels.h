#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Wood.h"
using namespace sf;

class Levels
{
public:
	void initLevel1(Sprite Wood[]);
	void initLevel2(Sprite Wood2[]);
	void initLevel3(Sprite Wood3[]);
	Levels();
	~Levels();
};


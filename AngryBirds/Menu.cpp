#include "Menu.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Menu::Menu(float width, float height)
{
	font.loadFromFile("../assets/fonts/angrybirds.ttf");

	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color{ 255,204,0 });

	//Play Option
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(90);
	mainMenu[0].setPosition(Vector2f(800, height / 4));
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color{ 255,204,0 });

	//Instructions
	mainMenu[1].setString("Instructions");
	mainMenu[1].setCharacterSize(90);
	mainMenu[1].setPosition(Vector2f(800, height / 4 + 200));
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::Black);

	//Exit
	mainMenu[2].setString("Exit");
	mainMenu[2].setCharacterSize(90);
	mainMenu[2].setPosition(Vector2f(800, height / 4 + 400));
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::Black);

	selected = 0;
}

Menu::~Menu() {}

void Menu::setSelected(int n)
{
	selected = n;
}

int Menu::pressed()
{
	return selected;
}


void Menu::draw(RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(mainMenu[i]);
	}
}

void Menu::moveUp()
{
	if (selected - 1 >= -1) // not play
	{
		mainMenu[selected].setFillColor(Color::Black);
		selected -= 1;
		if (selected == -1)
		{
			selected = 2;
		}
		mainMenu[selected].setFillColor(Color{ 255,204,0 });
	}
}

void Menu::moveDown()
{
	if (selected + 1 <= 3) //not exit
	{
		mainMenu[selected].setFillColor(Color::Black);
		selected += 1;
		if (selected == 3)
		{
			selected = 0;
		}
		mainMenu[selected].setFillColor(Color{ 255,204,0 });
	}
}


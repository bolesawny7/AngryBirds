#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
class Menu
{
public:
	Text mainMenu[3];
	//create my menu
	Menu(float width, float height);

	//draw the window
	void draw(RenderWindow& window);

	//move in the menu
	void moveUp();
	void moveDown();

	// what I am hovering on
	void setSelected(int n);
	int pressed();

	~Menu();


private:
	int selected;
	Font font;
};


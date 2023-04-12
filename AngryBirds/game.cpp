#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Menu.h"



using namespace std;
using namespace sf;

int pagenum = 1000;

void Pname(RenderWindow& window, string& name);
void gamePlay(RenderWindow& window);


int main()
{
	RenderWindow window(VideoMode(1920, 1080), "Game");
	window.setFramerateLimit(30);
	Menu menu(1920, 1080);
	Texture mainBackground;
	mainBackground.loadFromFile("../assets/pics/background1.png");
	Sprite bg;
	string name;
	bg.setTexture(mainBackground);
	while (true)
	{
		if (pagenum == 1000)
		{
			while (window.isOpen())
			{
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
					{
						window.close();
						break;
					}

					if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::Up)
						{
							menu.moveUp();
						}

						if (event.key.code == Keyboard::Down)
						{
							menu.moveDown();
						}
						if (event.key.code == Keyboard::Return)
						{
							if (menu.pressed() == 0)
							{
								pagenum = 0;
							}
							if (menu.pressed() == 1)
							{
								pagenum = 1;
							}
							if (menu.pressed() == 2)
							{
								pagenum = -1;
								//cout << "Break";
							}
						}
					}
				}
				window.clear();
				if (pagenum != 1000) break;
				window.draw(bg);
				menu.draw(window);
				window.display();
			}
		}

		if (pagenum == -1)
		{
			window.close();
			break;
		}
		if (pagenum == 0)
		{
			Pname(window, name);
		}
		if (pagenum == 3)
		{
			gamePlay(window);
		}
	}
}


void Pname(RenderWindow& window, string& name)
{
	if (!name.empty())
	{
		name.clear();
	}
	Texture background;
	background.loadFromFile("../assets/pics/background1.png");
	Sprite bg;
	bg.setTexture(background);
	Font font;
	font.loadFromFile("../assets/fonts/angrybirds.ttf");
	Text t1, t2;
	t1.setFont(font);
	t2.setFont(font);
	t1.setString("Enter Your Name: ");
	t1.setCharacterSize(70);
	t2.setCharacterSize(70);
	t1.setPosition(Vector2f(700, 1080 / 10));
	t2.setPosition(Vector2f(700, 1080 / 5));
	t1.setFillColor(Color{ 255,204,0 });
	t2.setFillColor(Color{ 255,204,0 });
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::TextEntered)
			{
				//bazawed 3ala el string el 7arf el badakhalo
				name += static_cast<char>(event.text.unicode);
			}
			if (Keyboard::isKeyPressed(Keyboard::BackSpace) and name.size() > 0)
			{
				name.resize(name.size() - 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::Return) and name.size() > 1)
			{
				//game win
				pagenum = 3;
				return;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				//game win
				pagenum = 1000;
				return;
			}
		}

		t2.setString(name);
		window.clear();
		window.draw(bg);
		window.draw(t1);
		window.draw(t2);
		window.display();
	}

}


void gamePlay(RenderWindow& window) {
	Texture gpBackground;
	gpBackground.loadFromFile("../assets/pics/GameplayBackground.png");
	//Background
	Sprite bg;
	bg.setTexture(gpBackground);

	//Ground
	// Create Box2D world with gravity pointing downwards


	//bird
	Texture bird;
	bird.loadFromFile("../assets/pics/bird.png");
	Sprite red;
	red.setTexture(bird);
	red.setPosition(500, 500);
	red.setTextureRect(IntRect(200, 400, 500, 400));
	red.setScale(0.2f, 0.2f);

	float currentFrame = 0;

	while (window.isOpen())
	{
		Event event;
		/*
		code to find the pixels desired

		Vector2i mousePosWindow;
		Vector2f mousePosView;
		mousePosWindow = Mouse::getPosition(window);
		mousePosView = window.mapPixelToCoords(mousePosWindow);
		cout << mousePosView.x << '\n' << mousePosView.y << '\n';

		*/
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			red.move(1.5, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			red.move(-1.5, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			red.move(0, -1.5);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			red.move(0, 1.5);
		}


		window.clear();
		window.draw(bg);
		window.draw(red);
		window.display();
	}

}

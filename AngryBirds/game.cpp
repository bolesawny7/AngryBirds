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
			if (Keyboard::isKeyPressed(Keyboard::BackSpace) && name.size() > 0)
			{
				name.resize(name.size() - 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::Return) && name.size() > 1)
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

	bool c1 = false, c2 = false, c3 = false;
	int count = 0;
	Sprite arrs, arrl, map1s, map2s, map3s, lvl1s, lvl2s, lvl3s, lv1s, lv2s, lv3s, locks;
	Texture arr, arl, map1, map2, map3, lvl1, lvl2, lvl3, lv1, lv2, lv3, lock;
	Clock clock1;

	Texture red2, chuck2, terence2, bg2, l1, l2, l3, lock1;
	Sprite red1, chuck1, terence1, bg1, lev1, lev2, lev3, locked, locked1;
	Mouse mose;
	RectangleShape pointer(Vector2f(1, 1));
	pointer.setFillColor(Color::Black);
	bool ch = false, ch2 = false;

	//pics
	if (l1.loadFromFile("../assets/pics/level1,0.png")) {
		lev1.setTexture(l1);
		lev1.setPosition(Vector2f(200, 300));
	}

	if (l2.loadFromFile("../assets/pics/level2,0.png")) {
		lev2.setTexture(l2);
		lev2.setPosition(Vector2f(700, 300));
	}

	if (l3.loadFromFile("../assets/pics/level3,0.png")) {
		lev3.setTexture(l3);
		lev3.setPosition(Vector2f(1200, 300));
		lev3.setScale(.9, .9);

	}

	if (lock.loadFromFile("../assets/pics/locked level.png")) {
		locked.setTexture(lock);
		locked.setPosition(Vector2f(500, 300));

	}
	if (lock1.loadFromFile("../assets/pics/locked level.png")) {
		locked1.setTexture(lock1);
		locked1.setPosition(Vector2f(950, 300));

	}

	if (bg2.loadFromFile("../assets/pics/bg.jpeg")) {
		bg1.setTexture(bg2);
		bg1.setScale(1.7f, 1.3f);


	}

	if (red2.loadFromFile("../assets/pics/RED.jpeg")) {
		red1.setTexture(red2);
		red1.setPosition(450, 2000);
		red1.setOrigin(red1.getGlobalBounds().height / 2, red1.getGlobalBounds().width / 2);
		red1.setScale(0.5f, 0.5f);
	}
	if (chuck2.loadFromFile("../assets/pics/LOCKED CHUCK.jpeg")) {
		chuck1.setTexture(chuck2);

		chuck1.setPosition(1050, 2000);
		chuck1.setOrigin(chuck1.getGlobalBounds().height / 2, chuck1.getGlobalBounds().width / 2);
		chuck1.setScale(.5f, .5f);
	}
	if (terence2.loadFromFile("../assets/pics/LOCKED TERENCE.jpeg")) {
		terence1.setTexture(terence2);
		terence1.setPosition(1650, 2000);
		terence1.setOrigin(terence1.getGlobalBounds().height / 2, terence1.getGlobalBounds().width / 2);
		terence1.setScale(.5, .5f);
	}

	if (arr.loadFromFile("../assets/pics/Arrow.jpg")) {
		arrs.setTexture(arr);
		arrs.setScale(Vector2f(-1.f, 1.f));
		arrs.setPosition(Vector2f(1900, 300));

	}

	if (lv1.loadFromFile("../assets/pics/level1icon.png")) {
		lv1s.setTexture(lv1);
		lv1s.setScale(Vector2f(.4, .4f));
		lv1s.setPosition(Vector2f(850, 750));

	}

	if (lv2.loadFromFile("../assets/pics/level2icon.png")) {
		lv2s.setTexture(lv2);
		lv2s.setScale(Vector2f(.4f, .4f));
		lv2s.setPosition(Vector2f(850, 750));

	}


	if (lv3.loadFromFile("../assets/pics/level3icon.png")) {
		lv3s.setTexture(lv3);
		lv3s.setScale(Vector2f(.4f, .4f));
		lv3s.setPosition(Vector2f(850, 750));
	}

	if (lock.loadFromFile("../assets/pics/locked level.png")) {
		locks.setTexture(lock);
		locks.setScale(Vector2f(.6f, .6f));
		locks.setPosition(Vector2f(870, 750));
	}

	if (arr.loadFromFile("../assets/pics/Arrow.jpg")) {
		arrl.setTexture(arr);
		arrl.setScale(Vector2f(1.f, 1.f));
		arrl.setPosition(Vector2f(10, 300));
	}

	if (map1.loadFromFile("../assets/pics/lvl1.jpg"));
	{
		map1s.setTexture(map1);
		map1s.setPosition(Vector2f(750, 650));
		map1s.setOrigin(map1s.getGlobalBounds().height / 2, map1s.getGlobalBounds().width / 2);
		map1s.setScale(0.8, .8);


	}

	if (map2.loadFromFile("../assets/pics/lvl2.jpg"));
	{
		map2s.setTexture(map2);
		map2s.setPosition(Vector2f(790, 580));
		map2s.setOrigin(map2s.getGlobalBounds().height / 2, map2s.getGlobalBounds().width / 2);
		map2s.setScale(0.8, .7);
	}

	if (map3.loadFromFile("../assets/pics/lvl3.jpg"));
	{
		map3s.setTexture(map3);
		map3s.setPosition(Vector2f(750, 650));
		map3s.setOrigin(map3s.getGlobalBounds().height / 2, map3s.getGlobalBounds().width / 2);
		map3s.setScale(0.8, .8);
	}


	window.draw(pointer);

	Texture gpBackground;
	gpBackground.loadFromFile("../assets/pics/GameplayBackground.png");
	//Background
	Sprite bg;
	bg.setTexture(gpBackground);

	//projectile
	Texture cick;
	cick.loadFromFile("../assets/pics/image.png");
	Sprite bom;
	bom.setTexture(cick);
	bom.setPosition(150, 550);
	bom.setScale(0.85, 0.7);



	//Ground
	// Create Box2D world with gravity pointing downwards


	//bird
	//bird
	Texture bird;
	bird.loadFromFile("../assets/pics/bird.png");
	Sprite red;
	red.setTexture(bird);
	red.setPosition(190, 570);
	red.setTextureRect(IntRect(200, 400, 500, 400));
	red.setScale(0.155f, 0.155f);

	float currentFrame = 0;

	// projectile varaible

	Clock clock;
	float counter = 0, xAxis = 0, yAxis = 0, time, intialVelocityX, intialVelocityY, acc;
	bool stop = 0, clockRestart = 0, start;


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
		pointer.setPosition(Vector2f(mose.getPosition().x - 10, mose.getPosition().y - 40));
		if (pointer.getGlobalBounds().intersects(arrs.getGlobalBounds())) {
			arrs.setScale(-1.1, 1.1);
			if (Mouse::isButtonPressed(Mouse::Left))
				if (clock1.getElapsedTime().asSeconds() > 0.5) {
					count++;
					clock1.restart();
				}
		}
		else {
			arrs.setScale(-1., 1.);
		}
		if (pointer.getGlobalBounds().intersects(arrl.getGlobalBounds())) {
			arrl.setScale(1.1, 1.1);
			if (Mouse::isButtonPressed(Mouse::Left))
				if (clock1.getElapsedTime().asSeconds() > 0.5) {
					count--;
					clock1.restart();
				}
		}
		else {
			arrl.setScale(1., 1.);
		}
		if (pointer.getGlobalBounds().intersects(lv1s.getGlobalBounds())) {
			map1s.setScale(.9, .9);
			if (Mouse::isButtonPressed(Mouse::Left) && count == 0)
				c1 = true;
		}
		else {
			map1s.setScale(0.8, 0.8);
		}
		if (count < 0)
			count = 2;
		if (count > 2)
			count = 0;
		while (window.pollEvent(event))
			if (pointer.getGlobalBounds().intersects(red1.getGlobalBounds()))
			{

				red1.setScale(.56, .56);
				if (Mouse::isButtonPressed(Mouse::Left)) {
					ch2 = true;
				}
			}

		if (c1 == true) {
			red1.setPosition(450, 400);
			chuck1.setPosition(1050, 400);
			terence1.setPosition(1650, 400);
		}

		if (!pointer.getGlobalBounds().intersects(red1.getGlobalBounds())) {
			red1.setScale(.5, .5);
		}
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

		}

		// projetile

		Vector2f mouse;

		mouse = Vector2f(Mouse::getPosition(window).x - 30, Mouse::getPosition(window).y - 5);

		if (Mouse::isButtonPressed(Mouse::Left) &&
			Mouse::getPosition(window).x <= 300 &&
			Mouse::getPosition(window).x >= 0 &&
			Mouse::getPosition(window).y < 850 &&
			Mouse::getPosition(window).y > 350) {

			red.setPosition(mouse);

			stop = 1;

			counter = 0; //restart acceleration

			clock.restart();

			clockRestart = 0;

			xAxis = 190 - red.getPosition().x, // old position - new position
				yAxis = red.getPosition().y - 570; // old position - new position but we reflect them because if we go down y axis value increase not such as x axis

			intialVelocityX = (xAxis / 8.5),
				intialVelocityY = (yAxis / 8.5);

			acc = intialVelocityX / 3;

		}
		else {

			// acceleration

			if (stop == 1) {

				time = clock.getElapsedTime().asSeconds();

				counter = counter + time / 2;
			}

			//return

			if (red.getPosition().x > 1920) {

				red.setPosition(190, 570);

				stop = 0;
			}

		}

		// move bird

		//ground
		RectangleShape ground(Vector2f(1920, 2));
		ground.setPosition(0, 901);

		start = 0;

		if (ground.getGlobalBounds().intersects(red.getGlobalBounds())) {

			if (start == 0) {

				if (clockRestart == 0) {
					clock.restart();
					time = clock.getElapsedTime().asSeconds();

					if (intialVelocityY < 50) {

						intialVelocityY = 5;

					}

				}

				counter = 0;

				counter = counter + time * 5;

				intialVelocityX = intialVelocityX - intialVelocityX / 3;

				if (intialVelocityX < 0) {

					intialVelocityX = 0;
				}

				if (intialVelocityX < 2) intialVelocityY = counter;


				clockRestart = 1;
			}

			start = 1;

		}

		if (stop == 1)
			red.move(intialVelocityX, -intialVelocityY + counter);


		window.clear();

		window.draw(bg1);
		if (c1 == false) {
			window.draw(arrl);
			window.draw(arrs);
			if (count == 0) {
				window.draw(map1s);
				window.draw(lv1s);
			}
			if (count == 1) {
				window.draw(map2s);
				window.draw(locks);
			}
			if (count == 2) {
				window.draw(map3s);
				window.draw(locks);
			}
		}
		if (c1 == true && ch2 == false) {

			window.draw(red1);

			window.draw(chuck1);

			window.draw(terence1);
		}

		if (ch2 == true && c1 == true) {

			window.draw(bg);
			window.draw(red);
			window.draw(bom);
		}
		window.display();
	}
}



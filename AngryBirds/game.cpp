#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Menu.h"
#include "Levels.h"
#include "Pig.h"
#include <fstream>

using namespace std;
using namespace sf;
using std::ofstream;
using std::ifstream;

struct player
{
	string name;
	int points[3];
};

ifstream indata; //to the game
ofstream outdata; // out of the game

int pagenum = 1000;
int score = 0, finalscore = 0, ymove = -25, cnt;

void Pname(RenderWindow& window, string& name);
void gamePlay(RenderWindow& window);
Levels levels;
Pig pigs;

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
	Text prompt, playerName;
	prompt.setFont(font);
	playerName.setFont(font);
	prompt.setString("Enter Your Name: ");
	prompt.setCharacterSize(70);
	playerName.setCharacterSize(70);
	prompt.setPosition(Vector2f(700, 1080 / 10));
	playerName.setPosition(Vector2f(700, 1080 / 5));
	prompt.setFillColor(Color{ 255,204,0 });
	playerName.setFillColor(Color{ 255,204,0 });
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










		playerName.setString(name);
		window.clear();
		window.draw(bg);
		window.draw(prompt);
		window.draw(playerName);
		window.display();
	}

}


void gamePlay(RenderWindow& window) {

	bool chooselv1 = false, chooselv2 = false, chooselv3 = false;
	int count = 0;
	Sprite arrs, arrl, map1s[2], map2s[2], map3s[2], lvl1s, lvl2s, lvl3s, lv1s, lv2s, lv3s, locks, win1s, win2s, win3s, loses, nexts;
	Texture arr, arl, map1, map2, map3, lvl1, lvl2, lvl3, lv1, lv2, lv3, lock, win1, win2, win3, lose, next;
	Clock clock1;

	Texture red2, chuck2, terence2, bg2, l1, l2, l3, lock1;
	Sprite red1, chuck1, terence1, bg1, lev1, lev2, lev3, locked, locked1;
	Mouse mose;
	RectangleShape pointer(Vector2f(1, 1));
	pointer.setFillColor(Color::Black);
	bool choosechar1 = false, choosechar2 = false, choosechar3 = false, nex = false;
	//pics

	if (win1.loadFromFile("../assets/pics/win1.png")) {
		win1s.setTexture(win1);
		win1s.setPosition(Vector2f(1300, 400));
		win1s.setScale(Vector2f(1.2f, 1.4f));
		win1s.setOrigin(win1s.getGlobalBounds().height / 2, win1s.getGlobalBounds().width / 2);
	}

	if (win2.loadFromFile("../assets/pics/win2.png")) {
		win2s.setTexture(win2);
		win2s.setPosition(Vector2f(1300, 400));
		win2s.setScale(Vector2f(1.2f, 1.4f));
		win2s.setOrigin(win2s.getGlobalBounds().height / 2, win2s.getGlobalBounds().width / 2);
	}

	if (win3.loadFromFile("../assets/pics/win3.png")) {
		win3s.setTexture(win3);
		win3s.setPosition(Vector2f(1300, 400));
		win3s.setScale(Vector2f(1.2f, 1.4f));
		win3s.setOrigin(win3s.getGlobalBounds().height / 2, win3s.getGlobalBounds().width / 2);

	}

	if (lose.loadFromFile("../assets/pics/lose.png")) {
		loses.setTexture(lose);
		loses.setPosition(Vector2f(1300, 370));
		loses.setScale(Vector2f(1.2f, 1.4f));
		loses.setOrigin(loses.getGlobalBounds().height / 2, loses.getGlobalBounds().width / 2);
	}

	if (next.loadFromFile("../assets/pics/next.png")) {
		nexts.setTexture(next);
		nexts.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 690, 800));
		nexts.setOrigin(nexts.getGlobalBounds().height / 2, nexts.getGlobalBounds().width / 2);
	}

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

	if (bg2.loadFromFile("../assets/pics/background.jpg")) {
		bg1.setTexture(bg2);
		bg1.setScale(1.5f, 1.f);
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

	Texture chuckop, terenceop;
	Sprite chuckp, terencep;

	if (chuckop.loadFromFile("../assets/pics/CHUCK.jpeg")) {
		chuckp.setTexture(chuckop);
		chuckp.setScale(Vector2f(.5f, .5f));
		chuckp.setPosition(Vector2f(9900, 300));
		chuckp.setOrigin(chuckp.getGlobalBounds().height / 2, chuckp.getGlobalBounds().width / 2);
	}

	if (terenceop.loadFromFile("../assets/pics/TERENCE.jpeg")) {
		terencep.setTexture(terenceop);
		terencep.setScale(Vector2f(.5f, .5f));
		terencep.setPosition(Vector2f(9900, 300));
		terencep.setOrigin(terencep.getGlobalBounds().height / 2, terencep.getGlobalBounds().width / 2);
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
		map1s[0].setTexture(map1);
		map1s[0].setPosition(Vector2f(750, 650));
		map1s[0].setOrigin(map1s[0].getGlobalBounds().height / 2, map1s[0].getGlobalBounds().width / 2);

		map1s[1].setTexture(map1);
		map1s[1].setScale(1.6, 1.52);


	}

	if (map2.loadFromFile("../assets/pics/lvl2.png"));
	{
		map2s[0].setTexture(map2);
		map2s[0].setPosition(Vector2f(790, 580));
		map2s[0].setOrigin(map2s[0].getGlobalBounds().height / 2, map2s[0].getGlobalBounds().width / 2);

		map2s[1].setTexture(map2);
		map2s[1].setScale(.9f, .65f);
	}

	if (map3.loadFromFile("../assets/pics/lvl3.jpg"));
	{
		map3s[0].setTexture(map3);
		map3s[0].setPosition(Vector2f(750, 650));
		map3s[0].setOrigin(map3s[0].getGlobalBounds().height / 2, map3s[0].getGlobalBounds().width / 2);

		map3s[1].setTexture(map3);
		map3s[1].setScale(1.6, 1.49);
	}

	Texture gpBackground;
	gpBackground.loadFromFile("../assets/pics/background.jpg");
	//Background
	Sprite bg;
	bg1.setPosition(-150, 0);
	bg.setTexture(gpBackground);
	bg1.setScale(1.62f, 1.229f);

	//projectile
	Texture cick;
	cick.loadFromFile("../assets/pics/sprite.png");
	Sprite bom[2];
	bom[0].setTextureRect(IntRect(0, 0, 41, 200));
	bom[0].setTexture(cick);
	bom[0].setPosition(180, 520);
	bom[0].setScale(2, 1.8);

	bom[1].setTextureRect(IntRect(942, 0, 41, 126));
	bom[1].setTexture(cick);
	bom[1].setPosition(135, 515);
	bom[1].setScale(1.7, 1.7);


	//Ground
	// Create Box2D world with gravity pointing downwards
	//Bishoy
	//Score
	Font font;
	font.loadFromFile("../assets/fonts/angrybirds.ttf");
	Text text;
	text.setFont(font);
	text.setString("score : " + to_string(score));
	text.setPosition(1570, 11);
	text.setScale(2, 2);
	text.setFillColor(Color(255, 255, 255));



	//wood
	Texture block;
	block.loadFromFile("../assets/pics/wood.png");
	Sprite Wood[3];
	levels.initLevel1(Wood);
	for (int i = 0; i < 3; i++) {
		Wood[i].setTexture(block);
	}

	//wood2
	Sprite Wood2[3];
	levels.initLevel2(Wood2);
	for (int i = 0; i < 3; i++) {
		Wood2[i].setTexture(block);
	}
	//wood3
	Sprite Wood3[5];
	levels.initLevel3(Wood3);
	for (int i = 0; i < 2; i++) {
		Wood3[i].setTexture(block);
	}
	Texture block3;
	block3.loadFromFile("../assets/pics/wood.png");
	Texture Woods3;
	Woods3.loadFromFile("../assets/pics/kingWood.jpg");
	Wood3[2].setTexture(Woods3);
	//Twood
	Texture TWood3;
	TWood3.loadFromFile("../assets/pics/TkingWood.png");
	Wood3[3].setTexture(TWood3);
	Wood3[4].setTexture(TWood3);

	//pig
	Texture evil;
	evil.loadFromFile("../assets/pics/AngryBirdsSpriteSheet.png");
	Sprite Pig[3]/*(Vector2f(81,85))*/;
	pigs.initPigs1(Pig);
	for (int i = 0; i < 3; i++) {
		Pig[i].setTexture(evil);

	}

	//pig2

	Sprite Pig2[3];
	pigs.initPigs2(Pig2);
	for (int i = 0; i < 3; i++) {
		Pig2[i].setTexture(evil);

	}
	//pig3
	Sprite Pig3[3]/*(Vector2f(81,85))*/;
	pigs.initPigs3(Pig3);
	for (int i = 0; i < 3; i++) {
		Pig3[i].setTexture(evil);
	}

	//bird
	//bird
	Texture bird;
	bird.loadFromFile("../assets/pics/bird.png");
	Sprite red;
	red.setTexture(bird);
	red.setPosition(165, 570);
	red.setTextureRect(IntRect(200, 400, 500, 400));
	red.setScale(0.155f, 0.155f);

	// projectile varaibles

	Clock clock;
	float xAxis = 0, yAxis = 0, time, intialVelocityX = 0, intialVelocityY = 0, acc;
	bool stop = 0, clockRestart = 0, start;
	// birds

	int alternate = 0, kill = 1, killFly = 0, increase = 0;

	Texture birds;
	birds.loadFromFile("../assets/pics/bird.png");

	Sprite bird2, bird3, bird4;

	Sprite fly = red;

	// birds

	bird2.setTexture(birds);
	bird2.setPosition(0 * 60, 820);
	bird2.setTextureRect(IntRect(200, 400, 500, 400));
	bird2.setScale(0.155f, 0.155f);


	bird3.setTexture(birds);
	bird3.setPosition(1 * 60, 820);
	bird3.setTextureRect(IntRect(200, 400, 500, 400));
	bird3.setScale(0.155f, 0.155f);


	bird4.setTexture(birds);
	bird4.setPosition(2 * 60, 820);
	bird4.setTextureRect(IntRect(200, 400, 500, 400));
	bird4.setScale(0.155f, 0.155f);



	while (window.isOpen())
	{
		Event event;
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
			map1s[0].setScale(.9, .9);
			if (Mouse::isButtonPressed(Mouse::Left) && count == 0)
				chooselv1 = true;
		}
		else {
			map1s[0].setScale(0.8, 0.8);
		}
		if (pointer.getGlobalBounds().intersects(nexts.getGlobalBounds())) {
			nexts.setScale(1.3, 1.3);
			if (Mouse::isButtonPressed(Mouse::Left) && score >= 3000)
				nex = true;
		}
		else {
			nexts.setScale(1., 1.);
		}
		if (pointer.getGlobalBounds().intersects(lv2s.getGlobalBounds()) && count == 1 && nex == true) {
			map2s[0].setScale(.45, .42);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				chooselv2 = true;
			}
		}
		else {
			map2s[0].setScale(0.4, 0.38);
		}
		if (pointer.getGlobalBounds().intersects(lv3s.getGlobalBounds()) && count == 2 && nex == true
			&& choosechar2 == true) {
			map3s[0].setScale(.9, .9);
			if (Mouse::isButtonPressed(Mouse::Left)) {

				chooselv3 = true;
			}
		}
		else {
			map3s[0].setScale(0.8, 0.8);
		}

		if (pointer.getGlobalBounds().intersects(red1.getGlobalBounds()))
		{
			red1.setScale(.56, .56);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				choosechar1 = true;
			}
		}

		if (chooselv1 == true) {
			red1.setPosition(450, 300);
			chuck1.setPosition(1050, 300);
			terence1.setPosition(1650, 300);
		}

		if (chooselv2 == true && nex == true) {
			chuckp.setPosition(Vector2f(900, 200));

		}
		if (chooselv3 == true) {
			terencep.setPosition(Vector2f(1500, 200));
		}

		if (!pointer.getGlobalBounds().intersects(red1.getGlobalBounds())) {
			red1.setScale(.5, .5);
		}
		if (pointer.getGlobalBounds().intersects(chuckp.getGlobalBounds())) {
			chuckp.setScale(.56, .56);

			if (Mouse::isButtonPressed(Mouse::Left)) {

				choosechar2 = true;
			}
		}
		if (!pointer.getGlobalBounds().intersects(chuckp.getGlobalBounds())) {
			chuckp.setScale(.5, .5);

		}
		if (pointer.getGlobalBounds().intersects(terencep.getGlobalBounds())) {
			terencep.setScale(.56, .56);

			if (Mouse::isButtonPressed(Mouse::Left)) {

				choosechar3 = true;
			}
		}
		if (!pointer.getGlobalBounds().intersects(terencep.getGlobalBounds())) {
			terencep.setScale(.5, .5);

		}
		if (count < 0)
			count = 2;
		if (count > 2)
			count = 0;
		while (window.pollEvent(event))

		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

		}

		// projetile

		Vector2f mouse;

		mouse = Vector2f(Mouse::getPosition(window).x - 30, Mouse::getPosition(window).y - 5);

		if (alternate == 3) {

			if (intialVelocityX <= 2 && fly.getPosition().x > 200) {
				killFly = 1;
			}
		}

		if ((alternate < 3 || fly.getPosition().x < 1920) && killFly == 0) {

			if (Mouse::isButtonPressed(Mouse::Left) &&
				Mouse::getPosition(window).x <= 300 &&
				Mouse::getPosition(window).x >= 0 &&
				Mouse::getPosition(window).y < 850 &&
				Mouse::getPosition(window).y > 350) {

				fly.setPosition(mouse);

				stop = 1;

				acc = 0; //restart acceleration

				increase = 0;

				clock.restart();
				clockRestart = 0;
				xAxis = 190 - fly.getPosition().x, // old position - new position
					yAxis = fly.getPosition().y - 570; // old position - new position but we reflect them because if we go down y axis value increase not such as x axis

				intialVelocityX = (xAxis / 9.5),
					intialVelocityY = (yAxis / 9.5);

			}
			else {

				// acceleration

				if (stop == 1) {

					time = clock.getElapsedTime().asSeconds();

					acc = 9.8 * time;
				}

				//return

				if (fly.getPosition().x > 1920 || (intialVelocityX <= 2 && fly.getPosition().x > 200)) {

					if (alternate == 0) {

						fly = bird2;

					}
					else if (alternate == 1) {

						fly = bird3;

					}
					else {

						fly = bird4;
					}

					fly.setPosition(165, 570);

					stop = 0;

					alternate++;
				}

			}
		}


		//Bishoy
		//Score++
		for (int i = 0; i < 3; i++) {
			if (fly.getGlobalBounds().intersects(Pig[i].getGlobalBounds())) {
				score += 1000;
				//Pig.setTextureRect(IntRect(444, 154, 119, 113));

				Pig[i].setScale(0, 0);
				text.setString("score : " + to_string(score));
			}
		}

		//level2

		if (choosechar2 == true && choosechar3 == false) {
			for (int i = 0; i < 3; i++) {
				if (fly.getGlobalBounds().intersects(Pig2[i].getGlobalBounds())) {
					score += 1000;
					//Pig.setTextureRect(IntRect(444, 154, 119, 113));

					Pig2[i].setScale(0, 0);
					text.setString("score : " + to_string(score));
				}
			}
		}

		//level3
		if (choosechar3 == true) {
			for (int i = 0; i < 3; i++) {
				if (fly.getGlobalBounds().intersects(Pig3[i].getGlobalBounds())) {
					score += 1000;
					//Pig.setTextureRect(IntRect(444, 154, 119, 113));

					Pig3[i].setScale(0, 0);
					text.setString("score : " + to_string(score));
				}
			}
		}
		start = 0;
		if (choosechar2 == false && choosechar3 == false) {
			for (int i = 0; i < 3; i++) {
				if (Wood[i].getGlobalBounds().intersects(fly.getGlobalBounds())) {
					if (!Wood[i].getRotation()) {
						if (start == 0) {

							if (intialVelocityY < 50) intialVelocityY = 5;

							clock.restart();

							intialVelocityX = intialVelocityX - intialVelocityX / 3;

							if (intialVelocityX < 1) intialVelocityY = acc;
						}

						start = 1;
					}


				}


			}
		}

		//level2

		if (choosechar2 == true && choosechar3 == false) {
			for (int i = 0; i < 3; i++) {
				if (Wood2[i].getGlobalBounds().intersects(fly.getGlobalBounds())) {
					if (!Wood2[i].getRotation()) {
						if (start == 0) {

							if (intialVelocityY < 50) intialVelocityY = 5;

							clock.restart();

							intialVelocityX = intialVelocityX - intialVelocityX / 3;

							if (intialVelocityX < 1) intialVelocityY = acc;
						}
						start = 1;
					}


				}


			}
		}

		//level3
		if (choosechar3 == true) {
			for (int i = 0; i < 3; i++) {
				if (Wood3[i].getGlobalBounds().intersects(fly.getGlobalBounds())) {
					if (!Wood3[i].getRotation()) {
						if (start == 0) {

							if (intialVelocityY < 50) intialVelocityY = 5;
							clock.restart();
							intialVelocityX = intialVelocityX - intialVelocityX / 3;
							if (intialVelocityX < 1) intialVelocityY = acc;
						}
						start = 1;
					}
				}
			}

		}

		// move bird

		//ground
		RectangleShape ground(Vector2f(1920, 2));
		ground.setPosition(0, 880);

		start = 0;

		if (ground.getGlobalBounds().intersects(fly.getGlobalBounds())) {

			if (start == 0) {

				if (intialVelocityY < 50) intialVelocityY = 5;

				clock.restart();

				intialVelocityX = intialVelocityX - intialVelocityX / 3;

				if (intialVelocityX < 1) intialVelocityY = acc;
			}
			start = 1;
		}

		if (stop == 1)
			fly.move(intialVelocityX, -intialVelocityY + acc);
		if (choosechar3 == true) {

			if (ymove == -25) {
				cnt = -25;
			}
			if (cnt == -25) {
				ymove += 1;
				if (ymove == 25) {
					cnt = 25;
				}
			}
			if (cnt == 25) {
				ymove -= 1;
			}
		}
		if (ymove != -25) {
			Wood3[0].move(Vector2f(0.0, ymove));
			Wood3[1].move(Vector2f(0, -ymove));
			Pig3[0].move(Vector2f(0.0, +ymove));
			Pig3[1].move(Vector2f(0.0, -ymove));

		}



		window.clear();
		window.draw(bg1);
		if (chooselv1 == false) {
			window.draw(arrl);
			window.draw(arrs);
			if (count == 0) {
				window.draw(map1s[0]);
				window.draw(lv1s);
			}
			if (count == 1) {
				window.draw(map2s[0]);
				window.draw(locks);
			}
			if (count == 2) {
				window.draw(map3s[0]);
				window.draw(locks);
			}
		}
		if (chooselv1 == true && choosechar1 == false) {
			window.draw(red1);
			window.draw(chuck1);
			window.draw(terence1);
		}

		if (choosechar1 == true && chooselv1 == true && finalscore < 3000) {

			window.draw(map1s[1]);
			//Bishoy
			//draw wood
			for (int i = 0; i < 3; i++) {

				window.draw(Wood[i]);
			}

			//draw score
			window.draw(text);
			//draw pig
			for (int i = 0; i < 3; i++) {
				window.draw(Pig[i]);
			}
			window.draw(bom[0]);
			if (alternate == 0) {
				window.draw(bird2);
				window.draw(bird3);
				window.draw(bird4);
			}
			else if (alternate == 1) {

				window.draw(bird3);
				window.draw(bird4);
			}
			else if (alternate == 2) {
				window.draw(bird4);
			}
			window.draw(fly);
			window.draw(bom[1]);
		}
		if (score >= 3000 && nex != true)
		{
			window.draw(win3s);
			window.draw(nexts);
			finalscore = score;
			text.setString("" + to_string(finalscore));
			window.draw(text);
			text.setFillColor(Color{ 255,234,20 });
			text.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 630, 600));

		}

		/*if (alternate == 3 && score < 3000 && nex != true&&intialVelocityX<=2&&fly.getPosition().x>200) {
			window.draw(loses);
			window.draw(nexts);
		}*/

		if (nex == true && chooselv2 == false) {
			score = 0;
			window.draw(arrl);
			window.draw(arrs);
			if (count == 0) {
				window.draw(map1s[0]);
				window.draw(lv1s);
			}
			if (count == 1) {
				window.draw(map2s[0]);
				window.draw(lv2s);
			}
			if (count == 2) {
				window.draw(map3s[0]);
				window.draw(locks);
			}

		}
		if (chooselv2 == true && choosechar2 == false) {
			nex = false;

			window.draw(red1);

			window.draw(chuckp);

			window.draw(terence1);
		}
		if (choosechar2 == true && score < 3000 && chooselv3 == false) {
			alternate = 0;
			window.draw(map2s[1]);
			//draw score
			text.setString("score : " + to_string(score));
			text.setPosition(1570, 11);
			text.setScale(2, 2);
			text.setFillColor(Color(255, 255, 255));
			window.draw(text);

			//draw pig

			for (int i = 0; i < 3; i++) {
				window.draw(Pig2[i]);
			}
			for (int i = 0; i < 3; i++) {

				window.draw(Wood2[i]);
			}

			window.draw(bom[0]);

			if (alternate == 0) {

				window.draw(bird2);
				window.draw(bird3);
				window.draw(bird4);
			}
			else if (alternate == 1) {

				window.draw(bird3);
				window.draw(bird4);

			}
			else if (alternate == 2) {

				window.draw(bird4);

			}


			window.draw(fly);
			window.draw(bom[1]);
		}
		if (score >= 3000 && nex == false)
		{
			window.draw(win3s);
			window.draw(nexts);
			finalscore = score;
			text.setString("" + to_string(finalscore));
			window.draw(text);
			text.setFillColor(Color{ 255,234,20 });
			text.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 630, 600));
		}
		if (nex == true && chooselv3 == false && choosechar2 == true) {
			score = 0;
			window.draw(bg1);
			window.draw(arrl);
			window.draw(arrs);
			if (count == 0) {
				window.draw(map1s[0]);
				window.draw(lv1s);
			}
			if (count == 1) {
				window.draw(map2s[0]);
				window.draw(lv2s);
			}
			if (count == 2) {
				window.draw(map3s[0]);
				window.draw(lv3s);
			}
		}
		if (chooselv3 == true && choosechar3 == false) {
			window.draw(red1);
			window.draw(chuckp);
			window.draw(terencep);
		}
		if (choosechar3 == true && score < 3000) {
			alternate = 0;
			window.draw(map3s[1]);
			//draw score
			text.setString("score : " + to_string(score));
			text.setPosition(1570, 11);
			text.setScale(2, 2);
			text.setFillColor(Color(255, 255, 255));
			window.draw(text);
			//Bishoy
			//draw wood
			for (int i = 4; i >= 0; i--) {

				window.draw(Wood3[i]);
			}

			//draw score
			window.draw(text);

			//draw pig

			for (int i = 0; i < 3; i++) {
				window.draw(Pig3[i]);
			}

			window.draw(bom[0]);

			if (alternate == 0) {

				window.draw(bird2);
				window.draw(bird3);
				window.draw(bird4);
			}
			else if (alternate == 1) {
				window.draw(bird3);
				window.draw(bird4);
			}
			else if (alternate == 2) {
				window.draw(bird4);
			}
			window.draw(fly);
			window.draw(bom[1]);

		}
		if (score >= 3000 && choosechar3 == true) {
			window.draw(win3s);
			window.draw(nexts);
			finalscore = score;
			text.setString("" + to_string(finalscore));
			text.setFillColor(Color{ 255,234,20 });
			text.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 630, 600));
			window.draw(text);
		}





		window.display();
	}

}
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Menu.h"
#include <fstream>
using namespace std;
using namespace sf;

int pagenum = 1000;
int score = 0, finalscore = 0, ymove = -25, cnt, level = 0, counta = 0;
bool play = 0, startG1 = &play, startG2 = 0, startG3 = 0, startch1 = 0, startch2 = 0, startch3 = 0, chcounter = 0;

void history(RenderWindow& window);

struct player
{
	string name;
	int score = 0;
}player;

ifstream indata;
ofstream outdata;


void Pname(RenderWindow& window, string& name);
void gamePlay(RenderWindow& window);
void Blocks(Sprite Wood[]);
void Pigs(Sprite Pig[]);
void Blocks2(Sprite Wood2[]);
void Pigs2(Sprite Pig2[]);
void Blocks3(Sprite Wood3[]);
void Pigs3(Sprite Pig3[]);

int killed = 0;
sf::SoundBuffer buffer;
sf::Sound soundMenu;
int main()
{
	buffer.loadFromFile("../assets/sound/theme.wav");
	soundMenu.setBuffer(buffer);
	soundMenu.play();
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
		if (pagenum == 1)
		{
			history(window);
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
				startG1 = 1;
				pagenum = 3;
				player.name = name;
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
	//pics
	int count = 0;
	Sprite arrs, arrl, map1s[2], map2s[2], map3s[2], lvl1s, lvl2s, lvl3s, lv1s, lv2s, lv3s, locks, win1s, win2s, win3s, loses, nexts, losesIcon;
	Texture arr, arl, map1, map2, map3, lvl1, lvl2, lvl3, lv1, lv2, lv3, lock, win1, win2, win3, lose, next, loseIcon;
	bool choosechar1 = false, choosechar2 = false, choosechar3 = false, nex = 1, playagain = false, speed = 1, scale = 1;
	bool chooselv1 = false, chooselv2 = false, chooselv3 = false, openlv3 = 0;

	Clock clock1;
	Texture red2, chuck2, terence2, bg2, l1, l2, l3, lock1;
	Sprite red1, chuck1, terence1, bg1, lev1, lev2, lev3, locked, locked1;
	Mouse mose;
	RectangleShape pointer(Vector2f(1, 1));
	pointer.setFillColor(Color::Black);


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

	if (loseIcon.loadFromFile("../assets/pics/play again.png")) {
		losesIcon.setTexture(loseIcon);
		losesIcon.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 680, 800));
		losesIcon.setOrigin(losesIcon.getGlobalBounds().height / 2, losesIcon.getGlobalBounds().width / 2);
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
		lv3s.setPosition(Vector2f(8540, 750));
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

	if (map1.loadFromFile("../assets/pics/lvl2.png"));
	{
		map1s[0].setTexture(map1);
		map1s[0].setPosition(Vector2f(790, 580));
		map1s[0].setOrigin(map1s[0].getGlobalBounds().height / 2, map1s[0].getGlobalBounds().width / 2);

		map1s[1].setTexture(map1);
		map1s[1].setScale(.9f, .65f);


	}

	if (map2.loadFromFile("../assets/pics/lvl1.jpg"));
	{
		map2s[0].setTexture(map2);
		map2s[0].setPosition(Vector2f(750, 650));
		map2s[0].setOrigin(map2s[0].getGlobalBounds().height / 2, map2s[0].getGlobalBounds().width / 2);

		map2s[1].setTexture(map2);
		map2s[1].setScale(1.6f, 1.52f);
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
	Sprite bom[4];
	bom[0].setTextureRect(IntRect(0, 0, 41, 200));
	bom[0].setTexture(cick);
	bom[0].setPosition(180, 520);
	bom[0].setScale(2, 1.8);

	bom[1].setTextureRect(IntRect(942, 0, 41, 126));
	bom[1].setTexture(cick);
	bom[1].setPosition(135, 515);
	bom[1].setScale(1.7, 1.7);
	//slingshoot3
	bom[2].setTextureRect(IntRect(1691, 0, 60, 212));
	bom[2].setTexture(cick);
	bom[2].setPosition(185, 540);
	bom[2].setScale(1.6, 1.6);

	bom[3].setTextureRect(IntRect(1751, 1, 52, 127));
	bom[3].setTexture(cick);
	bom[3].setPosition(143, 535);
	bom[3].setScale(1.3, 1.5);


	//Ground
	// Create Box2D world with gravity pointing downwards
	//Bishoy
	//Score
	Font font;
	font.loadFromFile("../assets/fonts/angrybirds.ttf");
	Text text;

	//wood
	Texture block;
	block.loadFromFile("../assets/pics/wood.png");
	Sprite Wood[3];
	Blocks(Wood);
	for (int i = 0; i < 3; i++) {
		Wood[i].setTexture(block);
	}

	//wood2
	Sprite Wood2[5];
	Blocks2(Wood2);
	for (int i = 0; i < 5; i++) {
		Wood2[i].setTexture(block);
	}
	//wood3
	Sprite Wood3[5];
	Blocks3(Wood3);
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
	RectangleShape line1(Vector2f(180, 5));
	RectangleShape line2(Vector2f(180, 5));
	line1.rotate(90 + 30);
	line2.rotate(60);
	line1.setPosition(1600, 283);
	line2.setPosition(1780, 283);

	//pig
	Texture evil;
	evil.loadFromFile("../assets/pics/AngryBirdsSpriteSheet.png");
	Sprite Pig[3]/*(Vector2f(81,85))*/;
	Pigs(Pig);
	for (int i = 0; i < 3; i++) {
		Pig[i].setTexture(evil);

	}

	//pig2

	Sprite Pig2[5];
	Pigs2(Pig2);
	for (int i = 0; i < 5; i++) {
		Pig2[i].setTexture(evil);

	}
	//pig3
	Sprite Pig3[3]/*(Vector2f(81,85))*/;
	/*Pigs3(Pig3);
	for (int i = 0; i < 3; i++) {
		Pig3[i].setTexture(evil);
	}*/
	for (int i = 0; i < 3; i++) {
		Pig3[i].setTexture(evil);
	}
	text.setFont(font);
	text.setString("score : " + to_string(score));
	text.setPosition(1570, 11);
	text.setScale(2, 2);
	text.setFillColor(Color(255, 255, 255));

	//bird
	//bird
	Texture bird;
	bird.loadFromFile("../assets/pics/bird.png");
	Sprite red;
	red.setTexture(bird);
	red.setPosition(165, 570);
	red.setTextureRect(IntRect(200, 400, 500, 400));
	red.setScale(0.155f, 0.155f);

	// chuck

	Texture chuck_img;

	chuck_img.loadFromFile("../assets/pics/chuck.png");

	Sprite chuck;

	chuck.setTexture(chuck_img);

	chuck.setPosition(165, 570);

	chuck.setScale(0.066, 0.066);


	Texture ter_img;

	ter_img.loadFromFile("../assets/pics/ter.png");

	Sprite ter;

	ter.setTexture(ter_img);

	ter.setPosition(165, 570);

	ter.setScale(0.14, 0.14);

	float currentFrame = 0;

	// projectile var

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
			map1s[0].setScale(.45, .42);
			if (Mouse::isButtonPressed(Mouse::Left) && count == 0 && counta > 15) {
				chooselv1 = true;
				fly = red;
				bird2.setTexture(birds);
				chcounter = true;
				startG1 = 0;
				startG2 = 0;
				startG3 = 0;
				if (level == 0) {
					startch1 = 1;
				}
				else if (level == 1) {
					startch2 = 1;
				}
				else {
					startch3 = 1;
				}
			}
		}
		else {
			map1s[0].setScale(0.4, 0.38);
		}
		if (pointer.getGlobalBounds().intersects(nexts.getGlobalBounds())) {
			nexts.setScale(1.3, 1.3);
			if (Mouse::isButtonPressed(Mouse::Left) && score >= 3000) {
				nex = true;
				score = 0;
				counta = 0;
				//ymove = -25;
				if (level == 2 || level == 3) {
					startG3 = 1;
				}
				else {
					startG2 = 1;
				}
				chooselv1 = 0; chooselv2 = 0; chooselv3 = 0; choosechar1 = 0; choosechar2 = 0; choosechar3 = 0;
				startch1 = 0; startch2 = 0; startch3 = 0;
			}
		}
		else {
			nexts.setScale(1., 1.);
		}

		if (pointer.getGlobalBounds().intersects(losesIcon.getGlobalBounds())) {
			losesIcon.setScale(.7, .7);
			if (Mouse::isButtonPressed(Mouse::Left) && score < 3000)
				playagain = true;
		}
		else {
			losesIcon.setScale(.6, .6);
		}

		if (pointer.getGlobalBounds().intersects(lv2s.getGlobalBounds()) && count == 1 && counta > 15) {
			map2s[0].setScale(.9, .9);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				chooselv2 = true;
				killed = 0;
				fly = chuck;
				bird2.setTexture(birds);
				chcounter = true;
				startG1 = 0;
				startG2 = 0;
				startG3 = 0;
				if (level == 0) {
					startch1 = 1;
				}
				else if (level == 1) {
					startch2 = 1;
				}
				else {
					startch3 = 1;
				}
			}
		}
		else {
			map2s[0].setScale(0.8, 0.8);
		}
		if (pointer.getGlobalBounds().intersects(lv3s.getGlobalBounds()) && count == 2 && counta > 15) {
			map3s[0].setScale(.9, .9);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				chooselv3 = true;
				killed = 0;
				fly = chuck;
				bird2 = ter;
				chcounter = true;
				startG1 = 0;
				startG2 = 0;
				startG3 = 0;
				if (level == 0) {
					startch1 = 1;
				}
				else if (level == 1) {
					startch2 = 1;
				}
				else {
					startch3 = 1;
				}
				openlv3 = 1;
			}
		}
		else {
			map3s[0].setScale(0.8, 0.8);
		}
		//cout << counta << endl;
		if (pointer.getGlobalBounds().intersects(red1.getGlobalBounds()))
		{

			red1.setScale(.56, .56);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				choosechar1 = true;
				chcounter = false;
				nex = false;
				openlv3 = false;
				startch1 = 0; startch2 = 0; startch3 = 0;
				/*chooselv1 = chooselv2 = chooselv3 = 0;*/
			}
		}

		red1.setPosition(2000, 2000);
		chuckp.setPosition(2000, 2000);
		terencep.setPosition(2000, 2000);
		if (startch1) {
			red1.setPosition(550, 300);
			chuck1.setPosition(1050, 300);
			terence1.setPosition(1550, 300);
		}

		if (startch2) {
			red1.setPosition(550, 300);
			chuckp.setPosition(Vector2f(900, 200));
			terence1.setPosition(Vector2f(1550, 300));
		}
		if (startch3) {
			red1.setPosition(550, 300);
			chuckp.setPosition(Vector2f(900, 200));
			terencep.setPosition(Vector2f(1400, 200));
		}

		if (level == 2 || level == 3) {
			lv3s.setPosition(Vector2f(850, 750));
		}

		if (!pointer.getGlobalBounds().intersects(red1.getGlobalBounds())) {
			red1.setScale(.5, .5);
		}
		if (pointer.getGlobalBounds().intersects(chuckp.getGlobalBounds())) {
			chuckp.setScale(.56, .56);

			if (Mouse::isButtonPressed(Mouse::Left)) {

				choosechar2 = true;
				chcounter = false;
				nex = false;
				openlv3 = false;
				startch1 = 0; startch2 = 0; startch3 = 0;
			}
		}
		if (!pointer.getGlobalBounds().intersects(chuckp.getGlobalBounds())) {
			chuckp.setScale(.5, .5);

		}
		if (pointer.getGlobalBounds().intersects(terencep.getGlobalBounds())) {
			terencep.setScale(.56, .56);

			if (Mouse::isButtonPressed(Mouse::Left)) {
				choosechar3 = true;
				chcounter = false;
				nex = false;
				openlv3 = false;
				startch1 = 0; startch2 = 0; startch3 = 0;
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
				outdata.open("history.txt", ios::app);
				outdata << player.name << "               " << player.score << '*' << endl;
				player.score = 0;
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
				Mouse::getPosition(window).y > 350 &&
				(choosechar1 || choosechar2 || choosechar3)
				)

			{

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

		if (openlv3) {
			Pigs3(Pig3);
			Blocks3(Wood3);
			//ymove = -25;
		}

		//Bishoy
		//Score++
		if (chooselv1) {
			//soundMenu.pause();
			for (int i = 0; i < 3; i++) {
				if (fly.getGlobalBounds().intersects(Pig[i].getGlobalBounds())) {
					score += 1000;
					//Pig.setTextureRect(IntRect(444, 154, 119, 113));

					Pig[i].setScale(0, 0);
					text.setString("score : " + to_string(score));
					level = max(1, level);
					player.score += score - killed * 1000;
					killed++;
				}
				//cout << 1 << ': ' << killed << '\n';
			}
		}
		//level2
		if (chooselv2) {
			for (int i = 0; i < 5; i++) {
				if (fly.getGlobalBounds().intersects(Pig2[i].getGlobalBounds())) {
					score += 1000;
					//Pig.setTextureRect(IntRect(444, 154, 119, 113));

					Pig2[i].setScale(0, 0);
					text.setString("score : " + to_string(score));
					level = max(2, level);
					player.score += score - killed * 1000;
					killed++;
					//cout << 2 << ': ' << killed << '\n';
				}
			}
		}

		//level3
		if (chooselv3) {
			for (int i = 0; i < 3; i++) {
				if (fly.getGlobalBounds().intersects(Pig3[i].getGlobalBounds())) {
					score += 1000;
					//Pig.setTextureRect(IntRect(444, 154, 119, 113));

					Pig3[i].setScale(0, 0);
					text.setString("score : " + to_string(score));
					level = max(3, level);
					player.score += (score - killed * 1000);
					killed++;
					//cout << 3 << ': ' << killed << '\n';
				}
			}
		}
		//ground
		// besho
		//Wood Collision level1

		start = 0;
		if (chooselv1) {
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

		if (chooselv2) {
			for (int i = 0; i < 5; i++) {
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
		if (chooselv3) {
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
				else if (line1.getGlobalBounds().intersects(fly.getGlobalBounds())

					|| line2.getGlobalBounds().intersects(fly.getGlobalBounds())) {

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



		if (chooselv3 && (choosechar1 || choosechar2 || choosechar3)) {
			if (score >= 3000) {
				ymove = -25;
			}
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

			if (ymove != -25) {
				Wood3[0].move(Vector2f(0.0, ymove));
				Wood3[1].move(Vector2f(0, -ymove));
				Pig3[0].move(Vector2f(0.0, +ymove));
				Pig3[1].move(Vector2f(0.0, -ymove));
			}
		}

		if (chcounter)
			alternate = 0;
		if ((chooselv2 || chooselv1 || chooselv3) && (choosechar2 || choosechar1 || choosechar3) && !nex && !score) {
			if (!score) {
				if (chooselv1)
					Pigs(Pig);
				else if (chooselv2)
					Pigs2(Pig2);
				text.setFont(font);
				text.setString("score : " + to_string(score));
				text.setPosition(1570, 11);
				text.setScale(2, 2);
				text.setFillColor(Color(255, 255, 255));
			}
		}
		if (score >= 3000 && nex != true) {
			finalscore = score;
			text.setString("" + to_string(finalscore));
			text.setFillColor(Color{ 255,234,20 });
			text.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 630, 600));

		}
		counta++;

		window.clear();
		window.draw(bg1);
		//maps
		if (startG1) {
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

		if (startG2) {
			//score = 0;
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
		if (startG3) {
			//	score = 0;
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
		//char

		if (startch1) {


			window.draw(red1);

			window.draw(chuck1);

			window.draw(terence1);


		}

		if (startch2) {

			window.draw(red1);

			window.draw(chuckp);

			window.draw(terence1);

			//restar birds

			speed = 1;

			killFly = 0;

		}

		if (startch3) {

			window.draw(red1);

			window.draw(chuckp);

			window.draw(terencep);

			bird2.setPosition(0 * 60, 820);

			speed = 1;

			scale = 1;

			killFly = 0;


		}
		//lvls
		if (chooselv1 == true && (choosechar1 || choosechar2 || choosechar3) && score < 3000 && !nex) {



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
		if (score < 3000 && chooselv2 && (choosechar2 || choosechar1 || choosechar3) && !nex) {

			if (alternate == 0) {

				if (Mouse::isButtonPressed(Mouse::Left) && speed == 1 && fly.getPosition().x > 190) {

					intialVelocityX = intialVelocityX * 1.8;

					speed = 0;

				}
			}

			window.draw(map2s[1]);
			//draw score

			window.draw(text);

			//draw pig

			for (int i = 0; i < 5; i++) {
				window.draw(Pig2[i]);
			}
			for (int i = 0; i < 5; i++) {

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

		if (chooselv3 && score < 3000/*&&level ==3*/ && (choosechar2 || choosechar1 || choosechar3) && !nex) {

			if (alternate == 0) {

				if (Mouse::isButtonPressed(Mouse::Left) && speed == 1 && fly.getPosition().x > 190) {

					intialVelocityX = intialVelocityX * 1.8;

					speed = 0;

				}

			}


			if (alternate == 1) {

				if (Mouse::isButtonPressed(Mouse::Left) && scale == 1 && fly.getPosition().x > 190) {

					fly.setScale(0.24, 0.24);

					scale = 0;

				}

			}


			window.draw(map3s[1]);

			//draw score
			//Bishoy
			//draw wood
			for (int i = 0; i < 3; i++) {
				window.draw(Pig3[i]);
			}
			for (int i = 4; i >= 0; i--) {

				window.draw(Wood3[i]);
			}

			//draw score
			window.draw(text);

			//draw pig


			window.draw(bom[2]);

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
			window.draw(bom[3]);

		}
		//score
		if (score >= 3000 && nex != true)
		{
			window.draw(win3s);
			window.draw(nexts);

			window.draw(text);
		}

		if (alternate == 3 && (fly.getPosition().x > 1980 || (intialVelocityX < 2 && fly.getPosition().x > 200)) &&
			score < 3000) {
			window.draw(loses);
			window.draw(losesIcon);
		}

		window.display();
	}

}

void history(RenderWindow& window)
{
	Texture histortex;
	histortex.loadFromFile("../assets/pics/background1.png");
	Sprite historySprite;
	historySprite.setTexture(histortex);
	historySprite.setPosition(0, 0);

	Text text[100];
	Font font;
	font.loadFromFile("../assets/fonts/angrybirds.ttf");
	for (int i = 0; i < 40; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(100);
		text[i].setFillColor(Color::Black);
	}
	indata.open("history.txt", ios::in);

	vector<string> lines;
	string line;
	while (getline(indata, line, '*'))
	{
		lines.push_back(line);
	}
	int length = lines.size();

	for (int i = 0; i < length; i++)
	{
		text[i].setString(lines[i]);
		text[i].setPosition(650, 100 * i);
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();


			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				pagenum = 1000;
				return;
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
			{
				if (text[0].getPosition().y <= 5)
				{
					for (int i = 0; i < length + 10 ; i++)
					{
						text[i].move(0, 20);
					}
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Down))
			{
				if (text[length-1].getPosition().y >= window.getPosition().y + 1000)
				{
					for (int i = 0; i < length + 10; i++)
					{
						text[i].move(0, -20);
					}
				}
				//cout << lines.size() << '\n';
			}

			window.clear();
			window.draw(historySprite);
			for (int i = 0; i < length; i++)
			{
				window.draw(text[i]);
			}
			window.display();
		}
	}

}

//Bishoy
void Blocks(Sprite Wood[]) {

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

void Pigs(Sprite Pig[]) {
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
//ahmed
void Blocks2(Sprite Wood2[]) {
	//0
	Wood2[0].setPosition(1140, 420);
	Wood2[0].setTextureRect(IntRect(253, 358, 83, 20));
	Wood2[0].setScale(1.3, 1);
	Wood2[0].setRotation(0);
	//1
	Wood2[1].setPosition(1290, 520);
	Wood2[1].setTextureRect(IntRect(253, 358, 83, 20));
	Wood2[1].setScale(1.3, 1);
	Wood2[1].setRotation(0);
	//2
	Wood2[2].setPosition(1447, 620);
	Wood2[2].setTextureRect(IntRect(253, 358, 83, 20));
	Wood2[2].setScale(1.3, 1);
	Wood2[2].setRotation(0);
	//3
	Wood2[3].setPosition(1590, 520);
	Wood2[3].setTextureRect(IntRect(253, 358, 83, 20));
	Wood2[3].setScale(1.3, 1);
	Wood2[3].setRotation(0);
	//4
	Wood2[4].setPosition(1740, 420);
	Wood2[4].setTextureRect(IntRect(253, 358, 83, 20));
	Wood2[4].setScale(1.3, 1);
	Wood2[4].setRotation(0);
}
void Pigs2(Sprite Pig2[]) {
	Pig2[0].setPosition(1158, 357);
	Pig2[0].setTextureRect(IntRect(786, 569, 80, 85));
	Pig2[0].setScale(0.8, 0.8);
	//1
	Pig2[1].setPosition(1308, 457);
	Pig2[1].setTextureRect(IntRect(786, 569, 80, 85));
	Pig2[1].setScale(0.8, 0.8);
	//2
	Pig2[2].setPosition(1458, 552);
	Pig2[2].setTextureRect(IntRect(770, 482, 96, 88));
	Pig2[2].setScale(0.8, 0.8);
	//3
	Pig2[3].setPosition(1608, 457);
	Pig2[3].setTextureRect(IntRect(786, 569, 80, 85));
	Pig2[3].setScale(0.8, 0.8);
	//4
	Pig2[4].setPosition(1758, 357);
	Pig2[4].setTextureRect(IntRect(786, 569, 80, 85));
	Pig2[4].setScale(0.8, 0.8);
	//sling shoot

}
void Blocks3(Sprite Wood3[]) {


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
void Pigs3(Sprite Pig3[]) {
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

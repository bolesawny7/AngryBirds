#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <algorithm>
#include "Menu.h"
#include <fstream>
using namespace std;
using namespace sf;

int pagenum = 1000;
float xmove = 0, ymove = 0, ymove2 = 25, xmove2 = 0, xmove1 = 0, ymove1 = -18;
int score = 0, finalscore = 0, cnt, cntx, level = 0, counta = 0, playagainlv3 = 0, playagainlv2 = 0;
bool play = 0, startG1 = &play, startG2 = 0, startG3 = 0, startch1 = 0, startch2 = 0, startch3 = 0, chcounter = 0,
clickplayagain = 0, selectlv3 = 0;

void history(RenderWindow& window);
double clamp(double d, double min, double max) {
    const double t = d < min ? min : d;
    return t > max ? max : t;
}
struct player {
    string name;
    int score = 0;
} player;

ifstream indata;
ofstream outdata;

int i1 = 0;
int slingshottime = 0;
bool woodcrack, wooddest;
void Pname(RenderWindow& window, string& name);
void credit(RenderWindow& window);
void gamePlay(RenderWindow& window);
void Blocks(Sprite Wood[]);
void Pigs(Sprite Pig[]);
void Blocks2(Sprite Wood2[]);
void Pigs2(Sprite Pig2[]);
void Blocks3(Sprite Wood3[]);
void Pigs3(Sprite Pig3[]);


SoundBuffer bufferMenu;
SoundBuffer bufferfly;
SoundBuffer bufferfly2;
SoundBuffer bufferfly3;
SoundBuffer bufferlevelPassed;
SoundBuffer bufferSlingshot;
SoundBuffer bufferWoodcrack;
SoundBuffer bufferWooddestroy;
SoundBuffer bufferlose;


Sound soundMenu;
Sound flying;
Sound flying2;
Sound flying3;
Sound levelPassed;
Sound slingshot;
Sound woodcracked;
Sound wooddestroyed;
Sound losing;


void DrawLine(sf::RenderWindow& window, const sf::Vector2f& point1, const sf::Vector2f& point2,
    float thickness, sf::Color color);

void DrawSling(sf::RenderWindow& window, const sf::Texture& leftTex, const sf::Texture& rightTex, const sf::Vector2f& pos,
    float maxLength, const sf::Color stretchColor, const Vector2f& scale = sf::Vector2f(1.0f, 1.0f),
    sf::Sprite* birdSprite = nullptr);

vector<string> lines;
string line;

bool isBirdReleased = false;

int main()
{

    //buffers
    bufferMenu.loadFromFile("../assets/sound/theme.wav");
    bufferfly.loadFromFile("../assets/sound/flying.wav");
    bufferfly2.loadFromFile("../assets/sound/flying2.wav");
    bufferfly3.loadFromFile("../assets/sound/flying3.wav");
    bufferlevelPassed.loadFromFile("../assets/sound/levelPassed.wav");
    bufferSlingshot.loadFromFile("../assets/sound/slingshotStretch.wav");
    bufferWoodcrack.loadFromFile("../assets/sound/wood1.wav");
    bufferWooddestroy.loadFromFile("../assets/sound/wood11.wav");
    bufferlose.loadFromFile("../assets/sound/lose.wav");

    //sound
    soundMenu.setBuffer(bufferMenu);
    flying.setBuffer(bufferfly);
    flying2.setBuffer(bufferfly2);
    flying3.setBuffer(bufferfly3);
    levelPassed.setBuffer(bufferlevelPassed);
    slingshot.setBuffer(bufferSlingshot);
    woodcracked.setBuffer(bufferWoodcrack);
    wooddestroyed.setBuffer(bufferWooddestroy);
    losing.setBuffer(bufferlose);

    soundMenu.play();

    RenderWindow window(VideoMode(1920, 1080), "ANGRY BIRDS X-EDITION");
    window.setFramerateLimit(30);
    Menu menu(1920, 1080);
    Texture mainBackground;
    mainBackground.loadFromFile("../assets/pics/background1.png");
    Sprite bg;
    string name;
    bg.setTexture(mainBackground);

    while (true) {

        if (pagenum == 1000) {
            while (window.isOpen()) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        window.close();
                        break;
                    }

                    if (event.type == Event::KeyPressed) {
                        if (event.key.code == Keyboard::Up) {
                            menu.moveUp();
                        }

                        if (event.key.code == Keyboard::Down) {
                            menu.moveDown();
                        }
                        if (event.key.code == Keyboard::Return) {
                            if (menu.pressed() == 0) {
                                pagenum = 0;
                            }
                            if (menu.pressed() == 1) {
                                pagenum = 1;
                            }
                            if (menu.pressed() == 2) {
                                pagenum = 2;
                            }
                            if (menu.pressed() == 3) {
                                pagenum = -1;
                                //cout << "Break";
                            }
                        }
                    }
                }

                window.clear();
                if (pagenum != 1000)
                    break;

                window.draw(bg);
                menu.draw(window);
                window.display();
            }
        }

        if (pagenum == -1) {
            window.close();
            break;
        }
        if (pagenum == 0) {
            Pname(window, name);
        }
        if (pagenum == 1) {
            history(window);
        }
        if (pagenum == 2) {
            credit(window);
        }
        if (pagenum == 3) {
            gamePlay(window);
        }
    }
}

void credit(RenderWindow& window)
{

    Texture histortex, map2;
    histortex.loadFromFile("../assets/pics/background1.png");
    Sprite historySprite, map2s;
    historySprite.setTexture(histortex);
    historySprite.setPosition(0, 0);
    Clock clocky;
    Text text[4];
    Font font;
    font.loadFromFile("../assets/fonts/angrybirds.ttf");

    text[0].setString("BISHOY AYMAN");
    text[0].setPosition(770 - 20, 100 + 1800);
    text[1].setString("GEORGE EHAB");
    text[1].setPosition(800 - 20, 250 + 1800);
    text[2].setString("POLES AWNY");
    text[2].setPosition(820 - 20, 400 + 1800);
    text[3].setString("THOMAS SEDHOM");
    text[3].setPosition(735 - 20, 550 + 1800);

    for (int i = 0; i < 4; i++) {
        text[i].setFont(font);
        text[i].setFillColor(Color::Black);
        text[i].setLetterSpacing(1.4);
        text[i].setOutlineThickness(3);
        text[i].setOutlineColor(Color(255, 196, 25));
        text[i].setCharacterSize(90);
    }

    while (window.isOpen()) {
        for (int i = 0; i < 4; i++) {
            text[i].move(0, -0.8);
        }
        Event event;

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed)
                window.close();

            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                pagenum = 1000;
                return;
            }
        }
        window.clear();
        window.draw(historySprite);
        for (int i = 0; i < 4; i++) {
            window.draw(text[i]);
        }
        window.display();
    }
}
void Pname(RenderWindow& window, string& name)
{
    if (!name.empty()) {
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
    t1.setFillColor(Color{ 255, 204, 0 });
    t2.setFillColor(Color{ 255, 204, 0 });
    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::TextEntered) {
                //bazawed 3ala el string el 7arf el badakhalo
                name += static_cast<char>(event.text.unicode);
            }
            if (Keyboard::isKeyPressed(Keyboard::BackSpace) && name.size() > 0) {
                name.resize(name.size() - 1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Return) && name.size() > 1) {
                startG1 = 1;
                //game win
                pagenum = 3;

                player.name = name;
                return;
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
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

void gamePlay(RenderWindow& window)
{
    //pics
    int count = 0, esc = 0, counter = 1;
    float x = 1, y = 1;
    Sprite arrs, arrl, sound, mute, map1s[2], map2s[2], map3s[2], lvl1s, lvl2s, lvl3s, lv1s, lv2s, lv3s, locks, win1s,
        win2s, win3s, loses, nexts, losesIcon, menu, GBIRD[3], flag[3], lv22;
    Texture arr, arl, Sound, Mute, map1, map2, map3, lvl1, lvl2, lvl3, lv1, lv2, lv3, lock, win1, win2, win3, lose,
        next, loseIcon, meNu, gBIRD, Flag, Lv22;
    bool choosechar1 = false, choosechar2 = false, choosechar3 = false, nex = 1, playagain = false, speed = 1,
        speed2 = 1, scale = 1, loser = false;
    bool chooselv1 = false, chooselv2 = false, chooselv3 = false, openlv3 = 0, openlv2 = 0, dmg1 = 1, dmg2 = 1,
        bigpig = 0, turn = 0, turn1 = 1;

    Clock clock1, clock2, clock3, animy;
    Texture red2, chuck2, terence2, bg2, l1, l2, l3, lock1, Cloud1, Cloud2, CMouse, MouSe;
    Sprite red1, chuck1, terence1, bg1, lev1, lev2, lev3, locked, locked1, cloud1[2], cloud2, cmouse, mousa;
    Mouse mose;
    RectangleShape pointer(Vector2f(1, 1));
    pointer.setFillColor(Color::Black);

    if (Sound.loadFromFile("../assets/pics/sound.png")) {
        sound.setTexture(Sound);
        sound.setPosition(Vector2f(1800, 950));
        sound.setScale(Vector2f(1.2f, 1.2f));
        sound.setOrigin(sound.getGlobalBounds().height / 2, sound.getGlobalBounds().width / 2);
    }
    if (Mute.loadFromFile("../assets/pics/mute.png")) {
        mute.setTexture(Mute);
        mute.setPosition(Vector2f(1810, 940));
        mute.setScale(Vector2f(1.2f, 1.2f));
        mute.setOrigin(mute.getGlobalBounds().height / 2, mute.getGlobalBounds().width / 2);
    }

    window.setMouseCursorVisible(false);
    if (MouSe.loadFromFile("../assets/pics/pointer.png")) {
        mousa.setTexture(MouSe);
    }

    if (CMouse.loadFromFile("../assets/pics/pointerclicked.png")) {
        cmouse.setTexture(CMouse);
    }

    if (Flag.loadFromFile("../assets/pics/redflags.png")) {
        for (int i = 0; i < 3; i++) {
            flag[i].setTexture(Flag);
            flag[i].setOrigin(flag[i].getGlobalBounds().height / 2, flag[i].getGlobalBounds().width / 2);
        }
        flag[0].setPosition(Vector2f(905, 540 + 15));
        flag[0].setScale(Vector2f(0.09f, 0.09f));

        flag[1].setPosition(Vector2f(1295, 435 + 15));
        flag[1].setScale(Vector2f(0.17f, 0.17f));

        flag[2].setPosition(Vector2f(1420, 605 + 10));
        flag[2].setScale(Vector2f(0.09f, 0.09f));
    }

    if (Cloud1.loadFromFile("../assets/pics/cloud1.png")) {
        for (int i = 0; i < 2; i++) {
            cloud1[i].setTexture(Cloud1);
        }
        cloud1[0].setPosition(Vector2f(2040, 300));
        cloud1[0].setScale(Vector2f(0.7f, 0.7f));
        cloud1[0].setOrigin(cloud1[0].getGlobalBounds().height / 2, cloud1[0].getGlobalBounds().width / 2);
        cloud1[1].setPosition(Vector2f(3490, 330));
        cloud1[1].setScale(Vector2f(0.7f, 0.7f));
        cloud1[1].setOrigin(cloud1[1].getGlobalBounds().height / 2, cloud1[1].getGlobalBounds().width / 2);
    }

    if (Cloud2.loadFromFile("../assets/pics/cloud2.png")) {
        cloud2.setTexture(Cloud2);
        cloud2.setPosition(Vector2f(2700, 230));
        cloud2.setScale(Vector2f(0.75f, 0.75f));
        cloud2.setOrigin(cloud2.getGlobalBounds().height / 2, cloud2.getGlobalBounds().width / 2);
    }

    if (gBIRD.loadFromFile("../assets/pics/GUIBIRD.png")) {
        for (int i = 0; i < 3; i++) {
            GBIRD[i].setTexture(gBIRD);
        }
        GBIRD[0].setPosition(Vector2f(1800, 100));
        GBIRD[0].setScale(Vector2f(0.7f, 0.7f));
        GBIRD[0].setOrigin(GBIRD[0].getGlobalBounds().height / 2, GBIRD[0].getGlobalBounds().width / 2);
        GBIRD[1].setPosition(Vector2f(1650, 150));
        GBIRD[1].setScale(Vector2f(0.9f, 0.9f));
        GBIRD[1].setOrigin(GBIRD[1].getGlobalBounds().height / 2, GBIRD[1].getGlobalBounds().width / 2);
        GBIRD[2].setPosition(Vector2f(1500, 100));
        GBIRD[2].setScale(Vector2f(0.7f, 0.7f));
        GBIRD[2].setOrigin(GBIRD[2].getGlobalBounds().height / 2, GBIRD[2].getGlobalBounds().width / 2);
    }

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
        losesIcon.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 6840, 800));
        losesIcon.setOrigin(losesIcon.getGlobalBounds().height / 2, losesIcon.getGlobalBounds().width / 2);
    }
    if (meNu.loadFromFile("../assets/pics/menu.png")) {
        menu.setTexture(meNu);
        //menu.setPosition(Vector2f(60 , 60));
        menu.setScale(0, 0);
        menu.setPosition(2000, 2000);
        menu.setOrigin(menu.getGlobalBounds().height / 2, menu.getGlobalBounds().width / 2);
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
        lv2s.setPosition(Vector2f(8540, 750));

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
        map2s[1].setScale(1.3f, 1.225f);
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

    sf::Texture sling1Left;
    sf::Texture sling1Right;
    sf::Texture sling3Left;
    sf::Texture sling3Right;

    sling1Left.loadFromFile("../assets/pics/sprite.png", IntRect(0, 0, 41, 200));
    sling1Right.loadFromFile("../assets/pics/sprite.png", IntRect(942, 0, 41, 126));
    sling3Left.loadFromFile("../assets/pics/sprite.png", IntRect(1691, 0, 60, 212));
    sling3Right.loadFromFile("../assets/pics/sprite.png", IntRect(1751, 1, 52, 127));


    //    bom[0].setTextureRect(IntRect(0, 0, 41, 200));
    //    bom[0].setTexture(cick);
    //    bom[0].setPosition(180, 520);
    //    bom[0].setScale(2, 1.8);
    //
    //    bom[1].setTextureRect(IntRect(942, 0, 41, 126));
    //    bom[1].setTexture(cick);
    //    bom[1].setPosition(135, 515);
    //    bom[1].setScale(1.7, 1.7);
    //
    //    //slingshoot3
    //    bom[2].setTextureRect(IntRect(1691, 0, 60, 212));
    //    bom[2].setTexture(cick);
    //    bom[2].setPosition(185, 540);
    //    bom[2].setScale(1.6, 1.6);
    //
    //    bom[3].setTextureRect(IntRect(1751, 1, 52, 127));
    //    bom[3].setTexture(cick);
    //    bom[3].setPosition(143, 535);
    //    bom[3].setScale(1.3, 1.5);


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
    int h_wood[3] = { 200, 200, 200 };
    Blocks(Wood);
    for (int i = 0; i < 3; i++) {
        Wood[i].setTexture(block);
    }

    //wood2
    Sprite Wood2[5];
    Blocks2(Wood2);
    int h_wood2[5] = { 200, 200, 200, 200, 200 };
    for (int i = 0; i < 5; i++) {
        Wood2[i].setTexture(block);
    }
    //wood3
    Sprite Wood3[7];
    Blocks3(Wood3);
    int h_wood3[4] = { 200, 200, 200, 200 };
    for (int i = 0; i < 4; i++) {
        Wood3[i].setTexture(block);
    }

    Texture block3;
    block3.loadFromFile("../assets/pics/wood.png");
    Texture Woods3;
    Woods3.loadFromFile("../assets/pics/kingWood.jpg");
    Wood3[4].setTexture(Woods3);
    //Twood
    Texture TWood3;
    TWood3.loadFromFile("../assets/pics/TkingWood.png");
    Wood3[5].setTexture(TWood3);
    Wood3[6].setTexture(TWood3);
    RectangleShape line1(Vector2f(180, 5));
    RectangleShape line2(Vector2f(180, 5));
    line1.rotate(90 + 30);
    line2.rotate(60);
    line1.setPosition(1170, 383);
    line2.setPosition(1395, 383);

    //pig
    Texture evil;
    evil.loadFromFile("../assets/pics/AngryBirdsSpriteSheet.png");
    Sprite Pig[3]/*(Vector2f(81,85))*/;
    Pigs(Pig);
    int h_pig[3] = { 100, 100, 100 };
    for (int i = 0; i < 3; i++) {
        Pig[i].setTexture(evil);

    }

    //pig2

    Sprite Pig2[5];
    Pigs2(Pig2);
    int h_pig2[5] = { 100, 100, 200, 100, 100 };
    for (int i = 0; i < 5; i++) {
        Pig2[i].setTexture(evil);

    }
    //pig3
    Sprite Pig3[5]/*(Vector2f(81,85))*/;

    int h_pig3[5] = { 100, 100, 100, 100, 300 };
    for (int i = 0; i < 5; i++) {
        Pig3[i].setTexture(evil);
    }

    text.setFont(font);
    text.setString("score : " + to_string(score));
    text.setPosition(1570, 11);
    text.setScale(2, 2);
    text.setFillColor(Color(255, 255, 255));

    //bird
    int h_birds[4] = { 100, 100, 100, 100 };
    //bird
    Texture bird;
    bird.loadFromFile("../assets/pics/bird.png");
    Sprite red;
    red.setTexture(bird);

    red.setPosition(195, 560);
    //red.setTextureRect(IntRect(200, 400, 500, 400));
    red.setScale(0.155f, 0.155f);

    // chuck

    Texture chuck_img;

    chuck_img.loadFromFile("../assets/pics/chuck.png");

    Sprite chuck;

    chuck.setTexture(chuck_img);

    chuck.setPosition(195, 560);

    chuck.setScale(0.066, 0.066);


    //chuckB

    Texture chuckB_img;

    chuckB_img.loadFromFile("../assets/pics/chuck.png");

    Sprite chuckB;

    chuckB.setTexture(chuckB_img);

    chuckB.setPosition(60, 810);

    chuckB.setScale(0.066, 0.066);

    //ter
    Texture ter_img;

    ter_img.loadFromFile("../assets/pics/ter.png");

    Sprite ter;

    ter.setTexture(ter_img);

    ter.setPosition(1 * 60, 820);

    ter.setScale(0.14, 0.14);

    int h_ter = 200;

    float currentFrame = 0;

    // projectile var

    Clock clock, clocks;
    float xAxis = 0, yAxis = 0, time, intialVelocityX = 0, intialVelocityY = 0, acc;
    bool stop = 0, clockRestart = 0, start;
    // birds

    int alternate = 0, kill = 1, killFly = 0, increase = 0, reload = 0;

    Texture birds;
    birds.loadFromFile("../assets/pics/bird.png");

    Sprite bird2, bird3, bird4;

    Sprite fly = red;

    // birds

    bird2.setTexture(birds);
    bird2.setPosition(0 * 60, 820);
    //bird2.setTextureRect(IntRect(200, 400, 500, 400));
    bird2.setScale(0.155f, 0.155f);

    bird3.setTexture(birds);
    bird3.setPosition(1 * 60, 820);
    //bird3.setTextureRect(IntRect(200, 400, 500, 400));
    bird3.setScale(0.155f, 0.155f);

    bird4.setTexture(birds);
    bird4.setPosition(2 * 60, 820);
    //bird4.setTextureRect(IntRect(200, 400, 500, 400));
    bird4.setScale(0.155f, 0.155f);

    while (window.isOpen()) {

        if (animy.getElapsedTime().asSeconds() > 0.2) {
            x += 2.33;
            animy.restart();
        }
        if (x >= 6) {
            x = 1;
            if (y > 1)
                y = 1;
            else
                y += 0.93;
        }

        for (int i = 0; i < 3; i++) {
            flag[i].setTextureRect(IntRect(x * 376, y * 933, 870, 756));
        }
        Event event;

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            if (clock2.getElapsedTime().asSeconds() > 0.3) {
                esc++;
                clock2.restart();
            }
        }
        pointer.setPosition(Vector2f(mose.getPosition().x - 10, mose.getPosition().y - 40));
        mousa.setPosition(Vector2f(mose.getPosition().x - 40, mose.getPosition().y - 60));
        cmouse.setPosition(Vector2f(mose.getPosition().x - 40, mose.getPosition().y - 60));

        if (pointer.getGlobalBounds().intersects(mute.getGlobalBounds())) {
            mute.setScale(1.4, 1.4);
        }
        else
            mute.setScale(1.2, 1.2);

        if (pointer.getGlobalBounds().intersects(sound.getGlobalBounds())) {
            sound.setScale(1.4, 1.4);

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (clocks.getElapsedTime().asSeconds() > 0.25) {
                    counter++;
                    if (counter % 2) {
                        soundMenu.pause();
                        flying.pause();
                        flying2.pause();
                        flying3.pause();
                        levelPassed.pause();
                        slingshot.pause();
                        woodcracked.pause();
                        wooddestroyed.pause();
                        losing.pause();
                    }

                    clocks.restart();
                }
            }
        }
        else {
            sound.setScale(1.2, 1.2);
        }

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
            if (Mouse::isButtonPressed(Mouse::Left) && count == 0 && counta > 15 && !playagain) {
                chooselv1 = true;
                finalscore = 0;
                soundMenu.pause();

                bird3.setTexture(birds);
                bird3.setPosition(1 * 60, 820);
                //bird3.setTextureRect(IntRect(200, 400, 500, 400));
                bird3.setScale(0.155f, 0.155f);

                fly = red;
                bird2.setTexture(birds);
                //bird3 = red;
                chcounter = true;
                esc = 0;
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
            if (Mouse::isButtonPressed(Mouse::Left)
                && ((score >= 3000 && chooselv1) || (score >= 6000 && chooselv2) || (score >= 9000 && chooselv3))) {
                nex = true;
                menu.setScale(0, 0);
                menu.setPosition(2000, 2000);
                reload = 0;
                esc = 0;
                lv1s.setScale(Vector2f(.4, .4f));
                lv2s.setScale(Vector2f(.4, .4f));
                lv3s.setScale(Vector2f(.4, .4f));

                losesIcon.setPosition(2000, 10010);

                score = 0;
                counta = 0;
                //ymove = -25;
                if (level == 2 || level == 3) {
                    startG3 = 1;
                }
                else {
                    startG2 = 1;
                }

                chooselv1 = 0;
                chooselv2 = 0;
                chooselv3 = 0;
                choosechar1 = 0;
                choosechar2 = 0;
                choosechar3 = 0;
                startch1 = 0;
                startch2 = 0;
                startch3 = 0;
                count = 0;
            }
        }
        else {
            nexts.setScale(1., 1.);
        }
        if (pointer.getGlobalBounds().intersects(menu.getGlobalBounds())) {
            menu.setScale(0.9, 0.9);
            if (Mouse::isButtonPressed(Mouse::Left)) {
                esc = 2;
                menu.setScale(0, 0);
                menu.setPosition(2000, 2000);
                losesIcon.setScale(0, 0);
            }
        }
        else {
            menu.setScale(0.8, 0.8);
        }
        if (esc == 2) {
            lv1s.setScale(Vector2f(.4, .4f));
            lv3s.setScale(Vector2f(.4, .4f));
            menu.setScale(0, 0);
            menu.setPosition(2000, 2000);
            losesIcon.setScale(0, 0);
            losesIcon.setPosition(2000, 2000);
            score = 0;
            ymove = 0;
            xmove = 0;
            ymove1 = -18;
            ymove2 = 15;

            if (level == 2 || level == 3) {
                startG3 = 1;
            }
            else {
                startG2 = 1;
            }
            chooselv1 = 0;
            chooselv2 = 0;
            chooselv3 = 0;
            choosechar1 = 0;
            choosechar2 = 0;
            choosechar3 = 0;
            startch1 = 0;
            startch2 = 0;
            startch3 = 0;
            openlv3 == 1;
            reload = 0;

        }

        if (pointer.getGlobalBounds().intersects(losesIcon.getGlobalBounds())) {
            losesIcon.setScale(.7, .7);
            if (Mouse::isButtonPressed(Mouse::Left)
                && ((score <= 3000 && chooselv1) || (score < 6000 && chooselv2) || (score < 9000 && chooselv3))
                && (choosechar1 || choosechar2 || choosechar3)) {
                playagain = true;
                reload = 0;
                esc = 0;
                speed = 1;
                speed2 = 1;
                scale = 1;
                bigpig = 1;
                if (!chooselv1)
                    fly = chuck;
                if (chooselv3)
                    fly = chuck;
                score = 0;
                alternate = 0;
                chcounter = 0;
                killFly = 0;
                ymove = 0;
                xmove = 0;
                ymove1 = -18;
                clickplayagain = 1;

                losesIcon.setPosition(240, 87);
                losesIcon.setScale(0.01, 0.01);
            }
        }
        else {
            losesIcon.setScale(.6, .6);
        }

        if (clickplayagain) {
            playagainlv3++;
            playagainlv2++;
        }
        if (playagainlv3 > 6)
            openlv3 = 1;
        if (playagainlv2 > 6)
            openlv2 = 1;
        if (pointer.getGlobalBounds().intersects(lv2s.getGlobalBounds()) && count == 1 && counta > 15) {
            map2s[0].setScale(.76, .76);
            if (Mouse::isButtonPressed(Mouse::Left)) {
                chooselv2 = true;
                i1 = 0;
                finalscore = 0;
                bird3.setTexture(birds);
                bird3.setPosition(1 * 60, 820);
                //bird3.setTextureRect(IntRect(200, 400, 500, 400));
                bird3.setScale(0.155f, 0.155f);
                esc = 0;
                bigpig = 1;
                reload = 0;
                fly = chuck;
                bird3 = chuckB;
                bird2.setTexture(birds);
                //bird3 = red;
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
                openlv2 = 1;

            }
        }
        else {
            map2s[0].setScale(0.7, 0.7);
        }
        if (pointer.getGlobalBounds().intersects(lv3s.getGlobalBounds()) && count == 2 && counta > 15) {
            map3s[0].setScale(.9, .9);
            if (Mouse::isButtonPressed(Mouse::Left)) {
                chooselv3 = true;
                finalscore = 0;
                i1 = 0;
                esc = 0;
                bigpig = 1;
                fly = chuck;
                bird3 = ter;
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
                selectlv3 = 1;

            }
        }
        else {
            map3s[0].setScale(0.8, 0.8);
        }

        if (pointer.getGlobalBounds().intersects(red1.getGlobalBounds())) {

            red1.setScale(.56, .56);
            if (Mouse::isButtonPressed(Mouse::Left)) {
                choosechar1 = true;
                lv1s.scale(0, 0);
                lv2s.scale(0, 0);
                lv3s.scale(0, 0);
                losesIcon.setPosition(240, 87);
                chcounter = false;
                nex = false;
                openlv3 = false;
                openlv2 = false;
                menu.setScale(0.8, 0.8);
                menu.setPosition(30, 30);
                startch1 = 0;
                startch2 = 0;
                startch3 = 0;
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

        if ((level == 2 || level == 3) && nex) {
            lv3s.setPosition(Vector2f(850, 750));
            lv2s.setPosition(Vector2f(850, 750));
        }
        if (level == 1 && nex) {
            lv2s.setPosition(Vector2f(850, 750));
        }

        if (!pointer.getGlobalBounds().intersects(red1.getGlobalBounds())) {
            red1.setScale(.5, .5);
        }
        if (pointer.getGlobalBounds().intersects(chuckp.getGlobalBounds())) {
            chuckp.setScale(.56, .56);

            if (Mouse::isButtonPressed(Mouse::Left)) {

                choosechar2 = true;
                lv1s.scale(0, 0);
                lv2s.scale(0, 0);
                lv3s.scale(0, 0);
                menu.setScale(0.8, 0.8);
                menu.setPosition(30, 30);
                losesIcon.setPosition(240, 87);
                chcounter = false;
                nex = false;
                openlv3 = false;
                openlv2 = false;
                startch1 = 0;
                startch2 = 0;
                startch3 = 0;
            }
        }
        if (!pointer.getGlobalBounds().intersects(chuckp.getGlobalBounds())) {
            chuckp.setScale(.5, .5);

        }
        if (pointer.getGlobalBounds().intersects(terencep.getGlobalBounds())) {
            terencep.setScale(.56, .56);

            if (Mouse::isButtonPressed(Mouse::Left)) {
                choosechar3 = true;
                lv1s.scale(0, 0);
                lv2s.scale(0, 0);
                lv3s.scale(0, 0);
                menu.setScale(0.8, 0.8);
                menu.setPosition(30, 30);
                losesIcon.setPosition(240, 87);
                chcounter = false;
                nex = false;
                openlv3 = false;
                openlv2 = false;

                startch1 = 0;
                startch2 = 0;
                startch3 = 0;
            }
        }
        if (!pointer.getGlobalBounds().intersects(terencep.getGlobalBounds())) {
            terencep.setScale(.5, .5);

        }
        if (count < 0)
            count = 2;
        if (count > 2)
            count = 0;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {

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

            if (sf::Mouse::isButtonPressed(Mouse::Left) &&
                Mouse::getPosition(window).x <= 350 &&
                Mouse::getPosition(window).x >= 0 &&
                Mouse::getPosition(window).y < 950 &&
                Mouse::getPosition(window).y > 350 &&
                (choosechar1 || choosechar2 || choosechar3) /* &&
                fly.getPosition().x < 300*/
                ) {

                fly.setPosition(mouse);

                int i = 0;
                if (i == 0 && counter % 2 != 0) {
                    flying.play();
                    i++;
                }

                if (slingshottime == 0 && counter % 2 != 0) {
                    slingshot.play();
                    slingshottime++;
                }

                dmg1 = 1;

                dmg2 = 1;

                stop = 1;

                acc = 0; //restart acceleration

                increase = 0;

                clock.restart();

                clockRestart = 0;

                xAxis = 190 - fly.getPosition().x, // old position - new position
                    yAxis = fly.getPosition().y
                    - 570; // old position - new position but we reflect them because if we go down y axis value increase not such as x axis

                intialVelocityX = (xAxis / 9.5),
                    intialVelocityY = (yAxis / 9.5);

                isBirdReleased = false;
            }
            else {

                // acceleration
                isBirdReleased = true;

                if (stop == 1) {

                    time = clock.getElapsedTime().asSeconds();

                    acc = 9.8 * time;
                }

                //return
                if (fly.getPosition().x > 1920 || (intialVelocityX <= 2 && fly.getPosition().x > 200)) {
                    slingshottime = 0;
                    woodcrack = 0;
                    wooddest = 0;
                    if (alternate == 0) {

                        fly = bird2;

                        alternate++;

                    }
                    else if (alternate == 1) {

                        fly = bird3;

                        alternate++;

                    }
                    else {

                        if (chooselv3 && reload < 1) {

                            fly = bird2;

                            reload++;

                        }
                        else {

                            fly = bird4;

                            alternate++;
                        }
                    }



                    //aktb eh?
                    fly.setPosition(195, 560);

                    stop = 0;
                }

            }
        }

        if (openlv3) {
            Pigs3(Pig3);
            Blocks3(Wood3);
            for (int i = 0; i < 4; i++) {
                h_wood3[i] = 200;
            }
            h_pig3[4] = 300;
            clickplayagain = 0;
            playagainlv3 = 0;

            openlv3 = 0;
            //ymove = -25;
        }
        if (openlv2) {
            Pigs2(Pig2);
            Blocks2(Wood2);
            for (int i = 0; i < 5; i++) {
                h_wood2[i] = 200;
            }
            h_pig2[2] = 200;
            clickplayagain = 0;
            playagainlv2 = 0;

            openlv2 = 0;
            //ymove = -25;
        }

        //Bishoy
        //Score++
        if (chooselv1) {

            for (int i = 0; i < 3; i++) {
                if (fly.getGlobalBounds().intersects(Pig[i].getGlobalBounds())) {

                    score += 10000;
                    player.score += 1000;
                    if (dmg1 == 1) {

                        //Pig.setTextureRect(IntRect(444, 154, 119, 113));

                        h_pig[i] = h_pig[i] - h_birds[i];

                        if (h_pig[i] <= 0) {

                            Pig[i].setScale(0, 0);

                        }

                        //	dmg1 = 0;

                    }

                    text.setString("score : " + to_string(score));
                    if (score >= 3000)
                        level = max(1, level);
                }
            }

            for (int i = 0; i < 3; i++) {
                if (fly.getGlobalBounds().intersects(Wood[i].getGlobalBounds())) {
                    //Pig.setTextureRect(IntRect(444, 154, 119, 113));

                    if (dmg2 == 1) {

                        if (woodcrack == 0 && counter % 2 != 0) {
                            woodcracked.play();
                            woodcrack = 1;
                        }

                        h_wood[i] = h_wood[i] - h_birds[alternate];

                        if (h_wood[i] <= 0) {

                            if (wooddest == 0 && counter % 2 != 0) {
                                wooddestroyed.play();
                                wooddest = 1;
                            }

                            score += 140;
                            player.score += 140;
                            Wood[i].setScale(0, 0);

                        }
                        else {
                            Wood[i].setTextureRect(IntRect(335, 379, 84, 21));
                        }

                    }

                    dmg2 = 0;

                }
                text.setString("score : " + to_string(score));
            }
        }

        //level2

        if (chooselv2) {
            for (int i = 0; i < 5; i++) {
                if (fly.getGlobalBounds().intersects(Pig2[i].getGlobalBounds())) {
                    if (i != 2) {
                        score += 10000;
                        player.score += 1000;
                    }
                    if (i != 2)

                        Pig2[i].setScale(0, 0);

                    if (dmg1 == 1) {


                        //Pig.setTextureRect(IntRect(444, 154, 119, 113));

                        h_pig2[i] = h_pig2[i] - h_birds[i];

                        if (h_pig2[i] > 0)
                            intialVelocityX = 0;

                        if (h_pig2[i] <= 0) {

                            Pig2[i].setScale(0, 0);

                        }

                        if (h_pig2[2] <= 0 && bigpig == 1) {
                            score += 2000;
                            player.score += 2000;
                            bigpig = 0;
                        }
                        dmg1 = 0;
                    }
                    text.setString("score : " + to_string(score));
                    if (score >= 6000)
                        level = max(2, level);
                }
            }

            for (int i = 0; i < 5; i++) {
                if (fly.getGlobalBounds().intersects(Wood2[i].getGlobalBounds())) {
                    //Pig.setTextureRect(IntRect(444, 154, 119, 113));

                    if (dmg2 == 1) {

                        if (woodcrack == 0 && counter % 2 != 0) {
                            woodcracked.play();
                            woodcrack = 1;
                        }

                        h_wood2[i] = h_wood2[i] - h_birds[alternate];

                        if (h_wood2[i] <= 0) {

                            if (wooddest == 0 && counter % 2 != 0) {
                                wooddestroyed.play();
                                wooddest = 1;
                            }

                            score += 140;
                            player.score += 140;
                            Wood2[i].setScale(0, 0);
                        }
                        else {
                            Wood2[i].setTextureRect(IntRect(335, 379, 84, 21));
                        }

                    }

                    dmg2 = 0;

                }
                text.setString("score : " + to_string(score));
            }
        }

        //level3
        if (chooselv3) {

            h_birds[2] = 300;
            for (int i = 0; i < 5; i++) {
                if (fly.getGlobalBounds().intersects(Pig3[i].getGlobalBounds())) {

                    if (i != 4) {
                        score += 1000;
                        player.score += 1000;
                    }
                    if (i != 4)

                        Pig3[i].setScale(0, 0);

                    if (dmg1 == 1) {

                        //Pig.setTextureRect(IntRect(444, 154, 119, 113));
                        //h=300-
                        h_pig3[i] = h_pig3[i] - h_birds[alternate];

                        if (h_pig3[i] > 0)
                            intialVelocityX = 0;

                        if (h_pig3[i] <= 0) {

                            Pig3[i].setScale(0, 0);

                        }
                        if (h_pig3[4] <= 0 && bigpig == 1) {
                            score += 5000;
                            player.score += 5000;
                            bigpig = 0;
                        }
                        dmg1 = 0;

                    }
                    text.setString("score : " + to_string(score));
                    if (score >= 9000)
                        level = max(3, level);
                }
            }

            for (int i = 0; i < 4; i++) {
                if (fly.getGlobalBounds().intersects(Wood3[i].getGlobalBounds())) {
                    //Pig.setTextureRect(IntRect(444, 154, 119, 113));

                    if (dmg2 == 1) {

                        if (woodcrack == 0 && counter % 2 != 0) {
                            woodcracked.play();
                            woodcrack = 1;
                        }

                        h_wood3[i] = h_wood3[i] - h_birds[alternate];

                        if (h_wood3[i] <= 0) {

                            if (wooddest == 0 && counter % 2 != 0) {
                                wooddestroyed.play();
                                wooddest = 1;
                            }

                            Wood3[i].setScale(0, 0);
                            score += 140;
                            player.score += 140;
                        }
                        else {
                            Wood3[i].setTextureRect(IntRect(335, 379, 84, 21));
                        }
                    }

                    dmg2 = 0;

                }
                text.setString("score : " + to_string(score));
            }
        }

        //ground
        // besho
        //Wood Collision level1

        start = 0;
        if (chooselv1) {

            GBIRD[0].move(-5, 0);
            GBIRD[1].move(-5, 0);
            GBIRD[2].move(-5, 0);

            for (int i = 0; i < 3; i++) {
                if (Wood[i].getGlobalBounds().intersects(fly.getGlobalBounds())) {
                    if (!Wood[i].getRotation()) {
                        if (start == 0) {

                            if (intialVelocityY < 50)
                                intialVelocityY = 5;

                            clock.restart();

                            intialVelocityX = intialVelocityX - intialVelocityX / 3;

                            if (intialVelocityX < 1)
                                intialVelocityY = acc;
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

                            if (intialVelocityY < 50)
                                intialVelocityY = 5;

                            clock.restart();

                            intialVelocityX = intialVelocityX - intialVelocityX / 3;

                            if (intialVelocityX < 1)
                                intialVelocityY = acc;
                        }
                        start = 1;
                    }

                }

            }
        }

        if (cloud1[1].getPosition().x <= -450) {
            turn = 1;
            turn1 = 0;
        }

        if (cloud1[0].getPosition().x >= 2190) {
            turn = 0;
            turn1 = 1;
        }

        //level3
        if (chooselv3) {
            if (turn == 0 && turn1 == 1) {
                cloud1[0].move(-5, 0);
                cloud1[1].move(-5, 0);
                cloud2.move(-5, 0);
            }
            if (turn == 1 && turn1 == 0) {
                cloud1[0].move(5, 0);
                cloud1[1].move(5, 0);
                cloud2.move(5, 0);
            }
            for (int i = 0; i < 5; i++) {
                if (Wood3[i].getGlobalBounds().intersects(fly.getGlobalBounds())) {
                    if (!Wood3[i].getRotation()) {
                        if (start == 0) {

                            if (intialVelocityY < 50)
                                intialVelocityY = 5;

                            clock.restart();

                            intialVelocityX = intialVelocityX - intialVelocityX / 3;

                            if (intialVelocityX < 1)
                                intialVelocityY = acc;
                        }
                        start = 1;
                    }

                }
                else if (line1.getGlobalBounds().intersects(fly.getGlobalBounds())
                    || line2.getGlobalBounds().intersects(fly.getGlobalBounds())) {

                    if (start == 0) {

                        if (intialVelocityY < 50)
                            intialVelocityY = 5;

                        clock.restart();

                        intialVelocityX = intialVelocityX - intialVelocityX / 3;

                        if (intialVelocityX < 1)
                            intialVelocityY = acc;
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

                if (intialVelocityY < 50)
                    intialVelocityY = 5;

                clock.restart();

                intialVelocityX = intialVelocityX - intialVelocityX / 3;

                if (intialVelocityX < 1)
                    intialVelocityY = acc;
            }

            start = 1;

        }

        if (stop == 1)
            fly.move(intialVelocityX, -intialVelocityY + acc);
        if (chooselv2 && (choosechar1 || choosechar2 || choosechar3)) {
            if (score >= 6000) {
                ymove1 = -18;
            }
            if (ymove1 == -18) {
                cnt = -18;
            }
            if (cnt == -18) {
                ymove1 += 1;
                if (ymove1 == 18) {
                    cnt = 18;
                }
            }

            if (cnt == 18) {
                ymove1 -= 1;
                if (ymove1 == -18) {
                    cnt = -18;
                }
            }

            if (ymove1 != -18) {
                Wood2[0].move(Vector2f(0, ymove1));
                Wood2[1].move(0, -ymove1);
                Wood2[3].move(0, ymove1);
                Wood2[4].move(0, -ymove1);
                Pig2[0].move(0, ymove1);
                Pig2[1].move(0, -ymove1);
                Pig2[3].move(0, ymove1);
                Pig2[4].move(0, -ymove1);
            }

        }

        if (chooselv3 && (choosechar1 || choosechar2 || choosechar3)) {
            if (score >= 9000) {
                ymove = 0;
                xmove = 0;
            }
            if (ymove == 0 && xmove == 0) {
                cnt = 0;
                cntx = 0;
            }
            if (cnt == 0 && cntx == 0) {
                ymove += 0.25;
                if (ymove == 25) {
                    cnt = 25;
                }
            }
            if (cnt == 25 && cntx == 0) {
                xmove += 0.25;
                if (xmove == 25) {
                    cntx = 25;
                }
            }
            if (cnt == 25 && cntx == 25) {
                ymove -= 0.25;
                if (ymove == 0) {
                    cnt = 0;
                }
            }
            if (cnt == 0 && cntx == 25) {
                xmove -= 0.25;
                if (xmove == 0) {
                    cntx = 0;
                }
            }

            if (ymove != 0 && (xmove == 0)) {
                Wood3[0].move(Vector2f(0.0, 6));
                Wood3[1].move(Vector2f(-6, 0));
                Wood3[2].move(Vector2f(0, -6));
                Wood3[3].move(Vector2f(6, 0));
                Pig3[0].move(Vector2f(0, 6));
                Pig3[1].move(Vector2f(-6, 0));
                Pig3[2].move(Vector2f(0, -6));
                Pig3[3].move(Vector2f(6, 0));
            }
            if (ymove != 0 && (xmove == 25)) {
                Wood3[0].move(Vector2f(0.0, -6));
                Wood3[1].move(Vector2f(6, 0));
                Wood3[2].move(Vector2f(0, 6));
                Wood3[3].move(Vector2f(-6, 0));
                Pig3[0].move(Vector2f(0.0, -6));
                Pig3[1].move(Vector2f(6, 0));
                Pig3[2].move(Vector2f(0, 6));
                Pig3[3].move(Vector2f(-6, 0));
            }
            if (xmove != 0 && (ymove == 25)) {
                Wood3[0].move(Vector2f(6, 0));
                Wood3[1].move(Vector2f(0, 6));
                Wood3[2].move(Vector2f(-6, 0));
                Wood3[3].move(Vector2f(0, -6));
                Pig3[0].move(Vector2f(6, 0));
                Pig3[1].move(Vector2f(0.0, 6));
                Pig3[2].move(Vector2f(-6, 0));
                Pig3[3].move(Vector2f(0, -6));

            }
            if (xmove != 0 && (ymove == 0)) {
                Wood3[0].move(Vector2f(-6, 0));
                Wood3[1].move(Vector2f(0, -6));
                Wood3[2].move(Vector2f(6, 0));
                Wood3[3].move(Vector2f(0, 6));
                Pig3[0].move(Vector2f(-6, 0));
                Pig3[1].move(Vector2f(0.0, -6));
                Pig3[2].move(Vector2f(6, 0));
                Pig3[3].move(Vector2f(0, 6));
            }

        }

        if (chcounter) {
            alternate = 0;

        }
        if (((chooselv2 || chooselv1 || chooselv3) && (choosechar2 || choosechar1 || choosechar3) && !nex)
            || playagain) {
            if (!score) {
                if (chooselv1) {
                    Pigs(Pig);
                    Blocks(Wood);
                    for (int i = 0; i < 3; i++) {
                        h_wood[i] = 200;
                    }
                }
                text.setFont(font);
                text.setString("score : " + to_string(score));
                text.setPosition(1570, 11);
                text.setScale(2, 2);
                text.setFillColor(Color(255, 255, 255));
            }
        }

        if ((chooselv1) && score >= 3000) {
            finalscore = score;
            finalscore += (4 - alternate) * 2000;
            if ((intialVelocityX < 2 && fly.getPosition().x > 200) || fly.getPosition().x > 1980) {
                finalscore -= 2000;
            }
            text.setString("" + to_string(finalscore));
            text.setFillColor(Color{ 255, 234, 20 });
            text.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 630, 600));
            menu.scale(0, 0);
            menu.setPosition(2000, 2000);
        }
        else if (chooselv2 && score >= 6000) {
            finalscore = score;
            finalscore += (4 - alternate) * 2000;
            if ((intialVelocityX < 2 && fly.getPosition().x > 200) || fly.getPosition().x > 1980) {
                finalscore -= 2000;
            }
            text.setString("" + to_string(finalscore));
            text.setFillColor(Color{ 255, 234, 20 });
            text.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 630, 600));
            menu.scale(0, 0);
            menu.setPosition(2000, 2000);
        }
        else if (chooselv3 && score >= 9000) {
            finalscore = score;

            finalscore += (5 - (alternate + reload)) * 2000;
            if ((intialVelocityX < 2 && fly.getPosition().x > 200) || fly.getPosition().x > 1980) {
                finalscore -= 2000;
            }
            text.setString("" + to_string(finalscore));
            text.setFillColor(Color{ 255, 234, 20 });
            text.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 630, 600));
            menu.setPosition(2000, 2000);
            menu.scale(0, 0);
        }

        counta++;

        if (score < 3000 && (chooselv2 || chooselv3) && (choosechar2 || choosechar1 || choosechar3) && !nex) {

            if (alternate == 0) {

                if (Mouse::isButtonPressed(Mouse::Left) && speed == 1 && fly.getPosition().x > 300) {

                    intialVelocityX = intialVelocityX * 1.8;

                    speed = 0;

                    h_birds[0] = 200;

                }
            }

            if (alternate == 2) {

                if (Mouse::isButtonPressed(Mouse::Left) && speed2 == 1 && fly.getPosition().x > 300 && chooselv2) {

                    intialVelocityX = intialVelocityX * 1.8;

                    speed2 = 0;

                    h_birds[2] = 200;

                }
            }

            if (alternate == 2 && chooselv3) {

                if (Mouse::isButtonPressed(Mouse::Left) && scale == 1 && fly.getPosition().x > 300) {

                    fly.setScale(0.24, 0.24);

                    scale = 0;

                }

            }
        }
        window.clear();
        window.draw(bg1);
        //maps
        if (startG1 || esc == 2) {

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

        if (startG2 || (esc == 2 && (level == 1))) {
            //score = 0;
            //cout << level;
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
        if (startG3 || esc == 2) {
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

        if (esc == 2 && level == 0) {
            if (count == 1)
                window.draw(locks);
            if (count == 2)
                window.draw(locks);
        }
        if (esc == 2 && level == 1) {
            if (count == 1) {
                lv2s.setPosition(Vector2f(850, 750));
                lv2s.setScale(0.4, 0.4);
                window.draw(lv2s);
            }
            if (count == 2)
                window.draw(locks);
        }
        if (esc == 2 && level == 2) {
            if (count == 1) {
                lv2s.setPosition(Vector2f(850, 750));
                lv2s.setScale(0.4, 0.4);
                window.draw(lv2s);
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
        if ((chooselv1 == true && (choosechar1 || choosechar2 || choosechar3) && score < 3000 && !nex
            && esc != 2)/*||(chooselv1 && playagain)*/) {

            if (clock3.getElapsedTime().asSeconds() > 15) {
                GBIRD[0].setPosition(Vector2f(2250, 100));

                GBIRD[1].setPosition(Vector2f(2100, 150));

                GBIRD[2].setPosition(Vector2f(1950, 100));

                clock3.restart();
            }

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

            //            window.draw(bom[0]);

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

            playagain = 0;
            //            window.draw(fly);
            //            window.draw(bom[1]);
            DrawSling(window, sling1Left, sling1Right, sf::Vector2f(230, 700),
                10000000.0f, sf::Color(48, 23, 8, 255), sf::Vector2f(2, 1.8), &fly);

            for (int i = 0; i < 3; i++) {
                window.draw(GBIRD[i]);
            }
        }
        if (score < 6000 && chooselv2 && (choosechar2 || choosechar1 || choosechar3) && !nex && esc != 2) {

            window.draw(map2s[1]);
            for (int i = 0; i < 3; i++) {
                window.draw(flag[i]);
            }
            //draw score

            window.draw(text);

            //draw pig

            for (int i = 0; i < 5; i++) {
                window.draw(Pig2[i]);
            }
            for (int i = 0; i < 5; i++) {

                window.draw(Wood2[i]);
            }

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
            playagain = 0;



            //            window.draw(bom[0]);
            //            window.draw(fly);
            //            window.draw(bom[1]);
            DrawSling(window, sling1Left, sling1Right, sf::Vector2f(220, 700),
                10000000.0f, sf::Color(48, 23, 8, 255), sf::Vector2f(2, 1.8), &fly);
        }

        if (chooselv3 && score < 9000/*&&level ==3*/ && (choosechar2 || choosechar1 || choosechar3) && !nex
            && esc != 2) {

            if (alternate == 0) {

                if (Mouse::isButtonPressed(Mouse::Left) && speed == 1 && fly.getPosition().x > 300) {

                    intialVelocityX = intialVelocityX * 1.8;

                    speed = 0;

                    h_birds[0] = 200;

                }

            }

            if (alternate == 2) {

                if (Mouse::isButtonPressed(Mouse::Left) && scale == 1 && fly.getPosition().x > 300) {

                    fly.setScale(0.24, 0.24);

                    h_pig3[4] = 300;

                    scale = 0;

                }

            }

            window.draw(map3s[1]);

            //draw score
            //Bishoy
            //draw wood
            for (int i = 0; i < 2; i++) {
                window.draw(cloud1[i]);
            }
            window.draw(cloud2);

            for (int i = 0; i < 5; i++) {
                window.draw(Pig3[i]);
            }
            for (int i = 6; i >= 0; i--) {

                window.draw(Wood3[i]);
            }

            //draw score
            window.draw(text);

            //draw pig



            if (alternate == 0) {

                window.draw(bird2);
                window.draw(bird3);
                window.draw(bird4);
            }
            else if (alternate == 1) {

                window.draw(bird2);
                window.draw(bird3);
                window.draw(bird4);

            }
            else if (alternate == 2) {

                window.draw(bird4);

            }

            playagain = 0;
            DrawSling(window, sling3Left, sling3Right, sf::Vector2f(230, 700),
                10000000.0f, sf::Color(161, 0, 0, 255), sf::Vector2f(1.6, 1.8), &fly);
        }
        //score
        if (nex != true && chooselv1) {
            if (finalscore >= 3000 && finalscore < 3500) {
                if (i1 == 0 && counter % 2 != 0) {
                    levelPassed.play();

                    i1++;
                }
                losesIcon.setPosition(2000, 10010);
                window.draw(win1s);
                window.draw(nexts);
                window.draw(text);
            }
            if (finalscore >= 5000 && finalscore < 5500) {
                if (i1 == 0 && counter % 2 != 0) {
                    levelPassed.play();
                    i1++;
                }
                losesIcon.setPosition(2000, 10010);
                window.draw(win2s);
                window.draw(nexts);
                window.draw(text);
            }
            if (finalscore > 5500) {
                if (i1 == 0 && counter % 2 != 0) {
                    levelPassed.play();
                    i1++;
                }
                losesIcon.setPosition(2000, 10010);
                window.draw(win3s);
                window.draw(nexts);
                window.draw(text);
            }
        }

        if (score >= 6000 && nex != true && chooselv2) {
            if (i1 == 0 && counter % 2 != 0) {
                levelPassed.play();
                i1++;
            }
            losesIcon.setPosition(2000, 10010);
            window.draw(win3s);
            window.draw(nexts);

            window.draw(text);
        }
        if (score >= 9000 && nex != true && chooselv3) {
            if (finalscore >= 9000 && finalscore < 9500) {
                if (i1 == 0 && counter % 2 != 0) {
                    levelPassed.play();
                    i1++;
                }
                losesIcon.setPosition(2000, 10010);
                window.draw(win1s);
                window.draw(nexts);
                window.draw(text);
            }

            if (finalscore >= 9000 && finalscore < 9500) {
                if (i1 == 0 && counter % 2 != 0) {
                    levelPassed.play();
                    i1++;
                }
                losesIcon.setPosition(2000, 10010);
                window.draw(win2s);
                window.draw(nexts);
                window.draw(text);
            }

            if (finalscore > 9500) {
                if (i1 == 0 && counter % 2 != 0) {
                    levelPassed.play();
                    i1++;
                }
                losesIcon.setPosition(2000, 10010);
                window.draw(win3s);
                window.draw(nexts);
                window.draw(text);
            }
        }

        if (alternate == 3 && (fly.getPosition().x > 1980 || (intialVelocityX < 2 && fly.getPosition().x > 200))
            && score < 3000 && chooselv1) {
            losesIcon.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 680, 800));

            if (i1 == 0 && counter % 2 != 0) {
                losing.play();
                i1++;
            }
            window.draw(loses);
        }
        window.draw(losesIcon);

        if (alternate == 3 && (fly.getPosition().x > 1980 || (intialVelocityX < 2 && fly.getPosition().x > 200))
            && score < 6000 && chooselv2) {
            losesIcon.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 680, 800));
            losesIcon.setScale(0.6, 0.6);

            if (i1 == 0 && counter % 2 != 0) {
                losing.play();
                i1++;
            }
            window.draw(loses);
            window.draw(losesIcon);
        }

        if (alternate == 3 && (fly.getPosition().x > 1980 || (intialVelocityX < 2 && fly.getPosition().x > 200))
            && score < 9000 && chooselv3) {
            losesIcon.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 680, 800));
            losesIcon.setScale(0.6, 0.6);

            if (i1 == 0 && counter % 2 != 0) {
                losing.play();
                i1++;
            }
            window.draw(loses);
            window.draw(losesIcon);
        }
        /*if ( bird4 && (fly.getPosition().x > 1980 || (intialVelocityX < 2 && fly.getPosition().x > 200)) && score < 7000 && chooselv3) {
            losesIcon.setPosition(Vector2f(win3s.getGlobalBounds().width / 2 + 680, 800));
            window.draw(loses);
            window.draw(losesIcon);
        }*/

        if (alternate == 0 && playagain && speed == 1) {
            alternate++;
        }
        window.draw(menu);

        if (counter % 2) {
            window.draw(sound);
        }
        else {
            window.draw(mute);
        }

        if (!Mouse::isButtonPressed(Mouse::Left)) {
            window.draw(mousa);
        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            window.draw(cmouse);
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
    for (int i = 0; i < 40; i++) {
        text[i].setFont(font);
        text[i].setCharacterSize(100);
        text[i].setFillColor(Color::Black);
    }
    indata.open("history.txt", ios::in);

    while (getline(indata, line, '*')) {
        lines.push_back(line);
    }
    int length = lines.size();

    for (int i = 0; i < length; i++) {
        text[i].setString(lines[i]);
        text[i].setPosition(650, 100 * i);
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                pagenum = 1000;
                return;
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
                if (text[0].getPosition().y <= 5) {
                    for (int i = 0; i < length + 10; i++) {
                        text[i].move(0, 20);
                    }
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
                if (text[length - 1].getPosition().y >= window.getPosition().y + 800) {
                    for (int i = 0; i < length + 10; i++) {
                        text[i].move(0, -20);
                    }
                }
                //cout << lines.size() << '\n';
            }

            window.clear();
            window.draw(historySprite);
            for (int i = 0; i < length; i++) {
                window.draw(text[i]);
            }
            window.display();
        }
    }

}

//Bishoy
void Blocks(Sprite Wood[])
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

void Pigs(Sprite Pig[])
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
//ahmed
void Blocks2(Sprite Wood2[])
{
    //0
    Wood2[0].setPosition(1140, 520);
    Wood2[0].setTextureRect(IntRect(253, 358, 83, 20));
    Wood2[0].setScale(1.3, 1);
    Wood2[0].setRotation(0);
    //1
    Wood2[1].setPosition(1290, 520);
    Wood2[1].setTextureRect(IntRect(253, 358, 83, 20));
    Wood2[1].setScale(1.3, 1);
    Wood2[1].setRotation(0);
    //2
    Wood2[2].setPosition(1447, 520);
    Wood2[2].setTextureRect(IntRect(253, 358, 83, 20));
    Wood2[2].setScale(1.3, 1);
    Wood2[2].setRotation(0);
    //3
    Wood2[3].setPosition(1590, 520);
    Wood2[3].setTextureRect(IntRect(253, 358, 83, 20));
    Wood2[3].setScale(1.3, 1);
    Wood2[3].setRotation(0);
    //4
    Wood2[4].setPosition(1740, 520);
    Wood2[4].setTextureRect(IntRect(253, 358, 83, 20));
    Wood2[4].setScale(1.3, 1);
    Wood2[4].setRotation(0);
}
void Pigs2(Sprite Pig2[])
{
    Pig2[0].setPosition(1158, 457);
    Pig2[0].setTextureRect(IntRect(786, 569, 80, 85));
    Pig2[0].setScale(0.8, 0.8);
    //1
    Pig2[1].setPosition(1308, 457);
    Pig2[1].setTextureRect(IntRect(786, 569, 80, 85));
    Pig2[1].setScale(0.8, 0.8);
    //2
    Pig2[2].setPosition(1458, 457);
    Pig2[2].setTextureRect(IntRect(770, 482, 96, 88));
    Pig2[2].setScale(0.8, 0.8);
    //3
    Pig2[3].setPosition(1608, 457);
    Pig2[3].setTextureRect(IntRect(786, 569, 80, 85));
    Pig2[3].setScale(0.8, 0.8);
    //4
    Pig2[4].setPosition(1758, 457);
    Pig2[4].setTextureRect(IntRect(786, 569, 80, 85));
    Pig2[4].setScale(0.8, 0.8);
    //sling shoot

}
void Blocks3(Sprite Wood3[])
{


    //1

    Wood3[0].setPosition(940, 200);
    Wood3[0].setTextureRect(IntRect(253, 358, 83, 20));
    Wood3[0].setScale(1, 1);
    Wood3[0].setRotation(0);

    //2

    Wood3[1].setPosition(1535, 200);
    Wood3[1].setTextureRect(IntRect(252, 358, 83, 22));
    Wood3[1].setScale(1, 1);
    Wood3[1].setRotation(0);

    //4

    Wood3[2].setPosition(1535, 796);
    Wood3[2].setTextureRect(IntRect(252, 358, 83, 22));
    Wood3[2].setScale(1, 1);
    Wood3[2].setRotation(0);

    //5

    Wood3[3].setPosition(940, 796);
    Wood3[3].setTextureRect(IntRect(252, 358, 83, 22));
    Wood3[3].setScale(1, 1);
    Wood3[3].setRotation(0);

    //3

    Wood3[4].setPosition(1070, 550);
    Wood3[4].setScale(0.33, 0.09);
    Wood3[4].setRotation(0);

    //triangle
    Wood3[5].setPosition(1010, 338);
    Wood3[5].setScale(0.07, 0.07);
    Wood3[5].setRotation(0);

    Wood3[6].setPosition(1555, 338);
    Wood3[6].setScale(-0.07, 0.07);
    Wood3[6].setRotation(0);

}
void Pigs3(Sprite Pig3[])
{
    //1 *score scale /5*

    Pig3[0].setPosition(950, 137);
    Pig3[0].setTextureRect(IntRect(786, 569, 80, 85));
    Pig3[0].setScale(0.8, 0.8);
    //2
    Pig3[1].setPosition(1545, 137);
    Pig3[1].setTextureRect(IntRect(786, 569, 80, 85));
    Pig3[1].setScale(0.8, 0.8);
    //3
    Pig3[2].setPosition(1545, 733);
    Pig3[2].setTextureRect(IntRect(786, 569, 80, 85));
    Pig3[2].setScale(0.8, 0.8);
    //4
    Pig3[3].setPosition(950, 733);
    Pig3[3].setTextureRect(IntRect(786, 569, 80, 85));
    Pig3[3].setScale(0.8, 0.8);
    //5
    Pig3[4].setPosition(1233, 430);
    Pig3[4].setTextureRect(IntRect(40, 2, 128, 155));
    Pig3[4].setScale(0.8, 0.8);
}

void DrawLine(sf::RenderWindow& window, const sf::Vector2f& point1, const sf::Vector2f& point2,
    float thickness, sf::Color color)
{
    sf::Vector2f direction = point2 - point1;
    float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f unitDirection = direction / mag;
    sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

    sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

    sf::Vertex vertices[4];

    vertices[0].position = point1 + offset;
    vertices[1].position = point2 + offset;
    vertices[2].position = point2 - offset;
    vertices[3].position = point1 - offset;

    for (int i = 0; i < 4; ++i) {
        vertices[i].color = color;
    }

    window.draw(vertices, 4, sf::Quads);
}

void DrawSling(sf::RenderWindow& window,
    const sf::Texture& leftTex,
    const sf::Texture& rightTex,
    const sf::Vector2f& pos,
    float maxLength,
    const sf::Color stretchColor,
    const Vector2f& scale,
    sf::Sprite* birdSprite)
{
    //    const sf::Color stretchColor = sf::Color(48, 23, 8, 255);
    const float ropeThickness = 7.0f * scale.y;

    const sf::Vector2f leftPointOffset(-10 * scale.x, 70.0f * scale.y);
    const sf::Vector2f rightPointOffset(27.0f * scale.x, 65.0f * scale.y);

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window)));
    sf::Sprite slingLeft;
    sf::Sprite slingRight;

    slingLeft.setTexture(leftTex);
    slingRight.setTexture(rightTex);

    slingLeft.setOrigin((float)leftTex.getSize().x / 2.0f, (float)leftTex.getSize().y / 2.0f);
    slingRight.setOrigin((float)rightTex.getSize().x / 2.0f, (float)rightTex.getSize().y / 2.0f);

    slingLeft.setPosition(pos);
    slingRight.setPosition(pos.x - rightPointOffset.x, pos.y - (43.0f * scale.y));

    slingLeft.setScale(scale);
    slingRight.setScale(scale);

    sf::Vector2f slingPointLeft(pos.x - leftPointOffset.x, pos.y - leftPointOffset.y);
    sf::Vector2f slingPointRight(pos.x - rightPointOffset.x, pos.y - rightPointOffset.y);
    sf::Vector2f midPoint((slingPointLeft + slingPointRight) / 2.0f);
    sf::Vector2f cacheOrigin;

    if (birdSprite) {
        cacheOrigin = birdSprite->getOrigin();
        birdSprite->setOrigin((float)birdSprite->getTextureRect().width / 2.0f,
            (float)birdSprite->getTextureRect().height / 2.0f);
    }

    window.draw(slingLeft);

    float birdRopeOffset = 20.0f;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !isBirdReleased) {
        sf::Vector2f delta = midPoint - mousePos;
        float deltaMag = sqrt(delta.x * delta.x + delta.y * delta.y);
        sf::Vector2f deltaDir = delta / deltaMag;

        delta.x = clamp(delta.x, -maxLength, maxLength);
        delta.y = clamp(delta.y, -maxLength, maxLength);
        sf::Vector2f drawPos = midPoint - delta;

        // NOTE(Tony): To avoid clipping with slingshot base (Can be safely removed)
        const float slingshotWidth = (float)(leftTex.getSize().x + rightTex.getSize().x);
        float maxLengthInYDir = 50.0f * scale.y;
        if (fabs(drawPos.x - midPoint.x) < slingshotWidth && drawPos.y > midPoint.y + maxLengthInYDir) {
            drawPos.y = midPoint.y + maxLengthInYDir;
        }

        DrawLine(window, drawPos, slingPointLeft, ropeThickness, stretchColor);

        if (birdSprite) {
            if (!isBirdReleased) {
                birdSprite->setPosition(drawPos);
                birdSprite->move(deltaDir * birdRopeOffset);
            }

            window.draw(*birdSprite);
        }

        DrawLine(window, drawPos, slingPointRight, ropeThickness, stretchColor);
    }
    else {
        DrawLine(window, slingPointRight, slingPointLeft, ropeThickness, stretchColor);
        if (birdSprite) {
            window.draw(*birdSprite);
        }
    }

    window.draw(slingRight);

    if (birdSprite) {
        birdSprite->setOrigin(cacheOrigin);
    }
}

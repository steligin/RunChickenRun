#include <SFML/Graphics.hpp> // ����������� ������������� �����, ����������� �� ������ � ��������
#include <SFML/Audio.hpp> // ����������� ������������� �����, ����������� �� ������ �� ������
#include "map.h" // ����������� ���� � ������ ������
#include "view.h" // ����������� ���� � �������
#include <sstream> // ����������� ����������� ���������� �++, ������� �������� �� ����-�����
#include <iostream>
//#include "mission.h" // ����������� ���� � ������� ������

//#define _WIN32_WINNT 0x0500 // ��� ������� �������
//#include <windows.h> // ��� ������� �������

//////////////////// ����� ������ ////////////////////

class Player // ����� ������ ��� ��������� Player
{
public: // ����������� ������� ��� ����������� ��������� � ���������� �� ������� main, � �� ��������� �������� �������
	// ���������� ������, ������ � ������ �������, ��������� �� x � y, ��������
	float x, y, w, h, dx, dy, speed;
	// ����������� �������� ������ (direction) � ����������, �������� ���� ������, ���������� �� ����� ������, ��������� �������� � ����� �������
	int dir, playerScore, health, mana, chickenSpeed, thorn, alien, pepper, openChest, takeKey; // takeCoins; //hammer;
	// ���������� ����������, ��������� ��� ����� ��� ���, ��������� ������� ������ ��� ���
	bool life, action, overGame, takeCoin, takeThorn, takeHp, zombieChicken, fullSpeed, chestOpen, keyTaked;  //gameOverMusic, winMusic, isMove, isSelect,

	sf::String File; // ���� � �����������
	sf::Image image;// ����������� (����������)
	sf::Texture texture;// ��������
	sf::Sprite sprite;// ������

	Player (sf::String F, float X, float Y, float W, float H)// ����������� ������ Player ��� ������������� ����������
	{

		dir = 0;
		speed = 0;
		dx = 0;
		dy = 0;
		playerScore = 0;
		health = 100;
		mana = 20000; // 20000 �� 7� ���� ��� ������
		chickenSpeed = 1;
		thorn = 0;
		alien = 0;
		pepper = 0;
		openChest = 0;
		takeKey = 0;

		life = true;
		action = false;
		overGame = false;
		takeCoin = false;
		takeThorn = false;
		takeHp = false;
		//gameOverMusic = false;
		//winMusic = false;
		zombieChicken = false;
		fullSpeed = false;
		chestOpen = false;
		keyTaked = false;

		File = F; // ��� �����+����������
		w = W; h = H; // ������ � ������

		image.loadFromFile(File); // �������� � image �������� �� �����
		image.createMaskFromColor(sf::Color(204, 204, 204)); // �������� ����� ��� ���������� ������� ������������ �� ����
		texture.loadFromImage(image); // �������� ����������� � ��������
		sprite.setTexture(texture); // �������� �������� � ������
		x = X; y = Y; // ���������� ��������� �������
		sprite.setTextureRect(sf::IntRect(120, 0, 60, 60)); // ������� ������� �������������� ��� ������ ������� �����������
	}

	void update(float time) // ������� update � ���������� time (����� �������� ����������)
	{

		switch (dir) // ��������� ��������� � ����������� �� �����������, ������ ����� ������������� �����������
		{
		case 0: dx = speed; dy = 0; break; // �� � - ������������� ��������, �� � - 0, �������� ��� ������ ������
		case 1: dx = -speed; dy = 0; break; // �� � - ������������� ��������, �� � - 0, �������� ��� ������ �����
		case 2: dx = 0; dy = speed; break; // �� � - 0, �� � - ������������� ��������, �������� ��� ������ ����
		case 3: dx = 0; dy = -speed; break; // �� � - 0, �� � - ������������� ��������, �������� ��� ������ �����
		}

		x += dx * time; // ��������� �� ����� = �������� � ��� ��������� �������� ���������
		y += dy * time; // ���� ����� ��� �

		speed = 0; // ��������� ��������, ����� �������� �����������

		//sprite.setPosition(x, y);
		sprite.setPosition(x + w/2, y + h/2); // ����� ������� � ������� �,�
		sprite.setOrigin(w/2, h/2); // ��� ������ ������� ����������

		InteractionWithMap(); // ����� ������� �������������� � ������

		if (health <= 0) // ������� ������� ���������, ���� health = 0, �� ����� ���� - ��������
		{
			life = false;
			overGame = false;
			zombieChicken = false;
			fullSpeed = false;
			dx = 0;
			dy = 0;
			speed = 0;
			//gameOverMusic = true;
			sprite.setColor(sf::Color(255, 255, 255));
		}

		if (playerScore >= 100) // ������� ������� ������, ���� playerScore = 100, �� ����� ���� - ������
		{
			life=true;
			overGame = true;
			zombieChicken = false;
			fullSpeed = false;
			dx = 0;
			dy = 0;
			speed = 0;
			sprite.setColor(sf::Color(255, 255, 255));
		}

		if (chickenSpeed > 1) speed *= 0.5;


	}

	float getPlayerCoordinateX() {return x;} // ��� ������� �������� � ���������
	float getPlayerCoordinateY() {return y;} // ��� ������� �������� y ���������

	void InteractionWithMap() // ������� �������������� Player � ������
	{
		for (int i = y/32; i < (y+h)/32; i++) // ������ �� ���� �����
		for (int j = x/32; j < (x+w)/32; j++) // �/32 ���������� ����� �������, � ������� ������������� ��������
		{

			if (TileMap[i][j] == 'G') // ���� ������� G, �� ��������� ����������� �������� �������� ���������, ����
			{
				if (dy>0) // ���� �� ��� ����
				{
					y=i*32-h; dy = 0;
				}

				if (dy<0) // ���� �� ��� �����
				{
					y=i*32+32; dy = 0;
				}

				if (dx>0) // ���� �� ��� ������
				{
					x=j*32-w; dx = 0;
				}

				if (dx<0) // ���� �� ��� �����
				{
					x=j*32+32; dx = 0;
				}
			}

			if (TileMap[i][j] == 'S') // ������
			{
				if (dy>0)
				{
					y=i*32-h; dy = 0;
				}

				if (dy<0)
				{
					y=i*32+32; dy = 0;
				}

				if (dx>0)
				{
					x=j*32-w; dx = 0;
				}

				if (dx<0)
				{
					x=j*32+32; dx = 0;
				}
			}

			if (TileMap[i][j] == 'T') // �������� ������
			{
				if (dy>0)
				{
					y=i*32-h; dy = 0;
				}

				if (dy<0)
				{
					y=i*32+32; dy = 0;
				}

				if (dx>0)
				{
					x=j*32-w; dx = 0;
				}

				if (dx<0)
				{
					x=j*32+32; dx = 0;
				}

				if (takeKey > 0)
				{
					TileMap[i][j] = 'U';
					playerScore += 10;
					health += 100;
					mana += 10000;
					openChest += 1;
					takeKey -= 1;
					chestOpen = true;
				}
			}

			if (TileMap[i][j] == 'U') // �������� ������
			{
				if (dy>0)
				{
					y=i*32-h; dy = 0;
				}

				if (dy<0)
				{
					y=i*32+32; dy = 0;
				}

				if (dx>0)
				{
					x=j*32-w; dx = 0;
				}

				if (dx<0)
				{
					x=j*32+32; dx = 0;
				}
			}


			if (TileMap[i][j] == 'K') // ����
			{
				takeKey += 1;
				keyTaked = true;

				TileMap[i][j] = ' ';
			}


			if (TileMap[i][j] == 'C') // ���� ������� C, �� ���������� ��������, �������
			{

				playerScore += 1; // ���� ���� �������, ������������ ����
				takeCoin = true; // ������� �����, ������ ����

				TileMap[i][j] = ' '; // ����� ���� ��� ��������
			}

			/*
			// ���� ������� C, �� ���������� ��������
			if (TileMap[i][j] == 'D')
			{
				// ���� ���� �������, ������������ ����
				playerScore += 5;
				takeCoin = true;
				// ����� ���� �� ��������
				TileMap[i][j] = ' ';
			}

			// ���� ������� C, �� ���������� ��������
			if (TileMap[i][j] == 'E')
			{
				// ���� ���� �������, ������������ ����
				playerScore += 10;
				takeCoin = true;
				// ����� ���� �� ��������
				TileMap[i][j] = ' ';
			}
			*/

			if (TileMap[i][j] == 'F') // �������
			{
				health -= 10;
				thorn += 1;
				takeThorn = true;

				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'A') // �������������
			{
				health -= 10;
				alien += 1;
				//playerScore -= 5;
				//takeThorn = true;
				zombieChicken = true;

				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'H') // ��������
			{
				health += 20;
				takeHp = true;

				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'B') // ������ � ������ ��� ��������
			{
				health += 50;
				takeHp = true;

				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'M') // ������ � ������ ��� ����
			{
				mana += 5000;
				takeHp = true;

				TileMap[i][j] = ' ';
			}

			/*
			if (TileMap[i][j] == 'X') // ����������� �������
			{
				health -= 100;
				takeThorn = true;

				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'Y')  // ��������� �������
			{
				health += 100;
				takeHp = true;

				TileMap[i][j] = ' ';
			}
			*/

			if (TileMap[i][j] == 'P') // �����
			{
				health += 10;
				fullSpeed = true;
				pepper += 1;

				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'L') // ������ ���
			{
				health += 5;
				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'W') // �������
			{
				speed *= 2;
				TileMap[i][j] = ' ';
			}

		}
	}
};


/*
class Enemy
{
public:
	float x, y, w, h, dx, dy, speed;
	sf::String File; // ���� � �����������
	sf::Image image;// ����������� (����������)
	sf::Texture texture;// ��������
	sf::Sprite sprite;// ������

	Enemy (sf::String F, float X, float Y, float W, float H)// ����������� ������ Player ��� ������������� ����������
	{
		speed = 0;
		dx = 0.1;
		dy = 0;

		image.loadFromFile(File); // �������� � image �������� �� �����
		image.createMaskFromColor(sf::Color(204, 204, 204)); // �������� ����� ��� ���������� ������� ������������ �� ����
		texture.loadFromImage(image); // �������� ����������� � ��������
		sprite.setTexture(texture); // �������� �������� � ������
		x = X; y = Y; // ���������� ��������� �������
		sprite.setTextureRect(sf::IntRect(0, 0, 192, 96));
	}


	void checkCollisionWithMap() // ������� �������������� Player � ������
	{
		for (int i = y/32; i < (y+h)/32; i++) // ������ �� ���� �����
		for (int j = x/32; j < (x+w)/32; j++) // �/32 ���������� ����� �������, � ������� ������������� ��������
		{

			if (TileMap[i][j] == 'G') // ���� ������� G, �� ��������� ����������� �������� �������� ���������, ����
			{
				if (dy>0) // ���� �� ��� ����
				{
					y=i*32-h; dy = 0;
				}

				if (dy<0) // ���� �� ��� �����
				{
					y=i*32+32; dy = 0;
				}

				if (dx>0) // ���� �� ��� ������
				{
					x=j*32-w; dx = -0.1;
				}

				if (dx<0) // ���� �� ��� �����
				{
					x=j*32+32; dx = 0.1;
				}
			}
		}
	}

	void update(float time)
	{
		//sprite.setPosition(x + w/2, y + h/2);
		//checkCollisionWithMap(dx, 0);
		//x += dx*time;

	}

};
*/


//// ���� ���� ////
void menu(sf::RenderWindow & window)
{
    sf::Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("images/111.png");
    menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
    menuTexture4.loadFromFile("images/444.png");
    aboutTexture.loadFromFile("images/about.png");
    menuBackground.loadFromFile("images/menulogo.png");
    sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menu4(menuTexture4), about(aboutTexture), menuBg(menuBackground);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(0, 0);
    menu2.setPosition(0, 120);
    menu3.setPosition(0, 240);
	menu4.setPosition(0, 360);
    menuBg.setPosition(320, 0);

    sf::Music musicMenu; // ������� ������
	musicMenu.openFromFile("sounds/menutheme.ogg");
	musicMenu.play();
	musicMenu.setLoop(true);

//////////////////////////////����///////////////////
    while (isMenu)
    {
        menu1.setColor(sf::Color::White);
        menu2.setColor(sf::Color::White);
        menu3.setColor(sf::Color::White);
		menu4.setColor(sf::Color::White);
        menuNum = 0;
        window.clear(sf::Color(181, 230, 29));

        if (sf::IntRect(0, 0, 320, 120).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::Yellow); menuNum = 1; }
        if (sf::IntRect(0, 120, 320, 120).contains(sf::Mouse::getPosition(window))) { menu2.setColor(sf::Color::Yellow); menuNum = 2; }
        if (sf::IntRect(0, 240, 320, 120).contains(sf::Mouse::getPosition(window))) { menu3.setColor(sf::Color::Yellow); menuNum = 3; }
		if (sf::IntRect(0, 360, 320, 120).contains(sf::Mouse::getPosition(window))) { menu4.setColor(sf::Color::Yellow); menuNum = 4; }
        if (sf::IntRect(320, 0, 320, 480).contains(sf::Mouse::getPosition(window))) {  }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) isMenu = false; //���� ������ ������ ������, �� ������� �� ����
            if (menuNum == 2)
			{
				window.draw(about);
				window.draw(menu1);
				window.display();
				while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));


				//menu1.setColor(sf::Color::White);
				if (sf::IntRect(320, 0, 320, 120).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::Yellow); menuNum = 1; isMenu = false;}


			}
			if (menuNum == 3)  { window.close(); isMenu = false; }
            if (menuNum == 4)  { window.close(); isMenu = false; }
        }

		//if (event.type == sf::Event::Closed) window.close(); // ������� �������� ���� (���� ����� ������� �� ����)

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);
		window.draw(menu4);

        window.display();
    }
////////////////////////////////////////////////////
}


bool startGame()
{

	//randomMapGenerate(); // ��� ����������� �������� ��������� ������� �� ��������� �����
    sf::RenderWindow window(sf::VideoMode(640, 480), "Run, Chicken! Run!"); //, sf::Style::Fullscreen); // �������� ���� ��� ������ window � �����������, ���������� � �������

    menu(window); //����� ���� ����

	//window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);

	//window.setMouseCursorVisible(false); // ������� ������� ���� � �������� �������� ����

	view.reset(sf::FloatRect(0, 0, 640, 480)); // ������ "����" ������

	sf::Font font; // �������� ������ ��� �������� (������ Font)
	font.loadFromFile("fonts/ptmonobold.ttf");// �������� ������ �� �����

	sf::Text text("", font, 12); // �������� ������ (������ Text) � ������� �����, ������������ �����, ������ ������
	//text.setColor(sf::Color(255, 255, 255));
	//text.setStyle(sf::Text::Bold);

	sf::Text text5("", font, 12);
	//text5.setColor(sf::Color(255, 255, 255));

	sf::Text text11("", font, 12);
	//text11.setColor(sf::Color(255, 255, 255));

	sf::Text text1("", font, 20);
	//text1.setColor(sf::Color(255,255,255));
	text1.setStyle(sf::Text::Bold);

	sf::Text text2("", font, 20);
	//text2.setColor(sf::Color(255,255,255));
	text2.setStyle(sf::Text::Bold);

	sf::Text textCoinStringer("", font, 20);
	//textCoinStringer.setColor(sf::Color(255,255,255));

	sf::Text text22("", font, 36);
	//text22.setColor(sf::Color(255, 0, 0));
	text22.setStyle(sf::Text::Bold);

	sf::Text text33("", font, 36);
	//text33.setColor(sf::Color(255, 255, 0));
	text33.setStyle(sf::Text::Bold);

	sf::Text textTakeitem("", font, 16);

	sf::Text textHealthState("", font, 12);
	//textHealthState.setColor(sf::Color(255, 0, 0));

	sf::Text textManaState("", font, 12);
	//textManaState.setColor(sf::Color(0, 0, 255));

	/*
	sf::Image mask_image; // �������� �����
	mask_image.loadFromFile("images/maskfon.png");
	sf::Texture mask_texture;
	mask_texture.loadFromImage(mask_image);
	sf::Sprite mask_sprite;
	mask_sprite.setTexture(mask_texture);
	*/

	sf::Image map_image; // �������� ����� ������
	map_image.loadFromFile("images/tilesetlist.png");
	map_image.createMaskFromColor(sf::Color(204,204,204));
	sf::Texture map_texture;
	map_texture.loadFromImage(map_image);
	sf::Sprite map_sprite;
	map_sprite.setTexture(map_texture);

	sf::Image quest_image; // �������� ������ � ��������
	quest_image.loadFromFile("images/scroll.png");
	//quest_image.createMaskFromColor(sf::Color(204,204,204));
	sf::Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	sf::Sprite scroll_quest;
	scroll_quest.setTexture(quest_texture);
	scroll_quest.setTextureRect(sf::IntRect(0, 0, 500, 355)); // ������ ������

	sf::Image stateLine_image; // �������� ������ ��������� ������ ������
	stateLine_image.loadFromFile("images/state_line.png");
	//quest_image.createMaskFromColor(sf::Color(204,204,204));
	sf::Texture stateLine_texture;
	stateLine_texture.loadFromImage(stateLine_image);
	sf::Sprite stateLine_sprite;
	stateLine_sprite.setTexture(stateLine_texture);
	stateLine_sprite.setTextureRect(sf::IntRect(0, 0, 640, 60)); // ������ ������ ���������

	// ������ ������ p ������ Player, ����� ���� � ������������, ���������� ������������ ������� �� ������, ������ � ������ �������
	Player p("images/spritesetlist.png", 20*32, 15*32, 60, 60); // ��� ����� 40�30
	//Player p("images/spritesetlist.png", 9*32, 6*32, 60, 60); // ��� ����� 20�15

	//Enemy e("images/spritesetlist.png", 2*32, 2*32, 192, 96);

	bool showMissionText = true; // ���������� ���������� ���������� �� ��������� ������ �� ������

	bool fullSizeMap = true; // ����������� ���� �����

	//bool musicStopPlay = true; // ���������� ������

	sf::Music music; // ������� ������
	music.openFromFile("sounds/theme.ogg");
	music.play();
	music.setLoop(true);

	sf::SoundBuffer buffer1; // ���� �������� ����, ������ ��������
	buffer1.loadFromFile("sounds/take.ogg");
	sf::Sound soundtake(buffer1);

	sf::SoundBuffer buffer2; // ���� ��� ������ �������
	buffer2.loadFromFile("sounds/hit.ogg");
	sf::Sound soundhit(buffer2);

	//sf::SoundBuffer buffer3; // ���� ����� ����
	//buffer3.loadFromFile("sounds/gameover.ogg");
	//sf::Sound soundgameover(buffer3);

	sf::SoundBuffer buffer4; // ���� ������ �������
	buffer4.loadFromFile("sounds/takecoin.ogg");
	sf::Sound soundtakecoin(buffer4);

	sf::SoundBuffer buffer5; // ���� ��������� �������
	buffer5.loadFromFile("sounds/soundChestOpen.ogg");
	sf::Sound soundChestOpen(buffer5);

	sf::SoundBuffer buffer6; // ���� ������� �����
	buffer6.loadFromFile("sounds/soundTakeKey.ogg");
	sf::Sound soundTakeKey(buffer6);

	//sf::SoundBuffer buffer5; // ���� ������� ��������
	//buffer5.loadFromFile("sounds/takehp.ogg");
	//sf::Sound soundtakehp(buffer5);

	float CurrentFrame=0; // ���������� ������ ������� ����

	sf::Clock clock; // �������� ���������� �������, �� �������� �� �������, � �� � ������� ����������
	sf::Clock gameTimeClock; // �������� ���������� �������, ��� �������� ������� ���� � ������������ ������ �� �����

	int gameTime = 0; // ���������� �������� �������, �������������

	// ������� ��� ��������� ��������� ���������
	int createObjectForMapCoinTimer = 0;
	int createObjectForMapCoin5Timer = 0;
	int createObjectForMapCoin10Timer = 0;
	int createObjectForMapHeartTimer = 0;
	int createObjectForMapThornTimer = 0;
	int createObjectForMapBottleTimer = 0;
	int createObjectForMapBottleManaTimer = 0;
	int createObjectForMapAlienTimer = 0;
	int createObjectForMapBadMushroomTimer = 0;
	int createObjectForMapGoodMushroomTimer = 0;
	int createObjectForMapStoneTimer = 0;
	int createObjectForMapPepperTimer = 0;
	int createObjectForMapChestTimer = 0;
	int createObjectForMapKeyTimer = 0;
	int createObjectForMapCrayfishTimer = 0;
	int createObjectForMapMowerTimer = 0;

	// ������� �������� ������ �������� �� ����������� �����
	int zombieChickenTimer = 0;
	int takeThornTimer = 0;
	int fullSpeedTimer = 0;
	int takeCoin1Timer = 0;
	int takeHpTimer = 0;
	int chestOpenTimer = 0;
	int keyTakedTimer = 0;

	bool tileInGame;

	tileInGame = false;

	int tileInGameTimer = 0;









	//////////////////////////////////////// ���� "���� ������� ����" ////////////////////////////////////////

    while (window.isOpen()) // ������������ ����, �������� ��� "���� ������� ����", � ������ ������ ���� window
    {

		float time=clock.getElapsedTime().asMicroseconds(); // �������� ���������� time ���� float � �������� ���������� ������� � �������������
		clock.restart();// ������������ �������
		time=time/800;// ����������� �������� ����

		if (p.life) // ���� ����� ���, ������� ����� ��� �����, ����� (�� ����� �� ����) ���������� �����, �������� ��������� ������, ��������������� ������, � ������� ��������� ����������
		{
			gameTime=gameTimeClock.getElapsedTime().asSeconds();

		if (p.overGame) // ���� ������� � ���������� ����� (��. ����� ������), ���������� �����, �������� ���������� ������
		{
			//text2.setString("Chicken is yellow! Press [Q] to quit.");
			text2.setString("Congratulations! Press [Q] to quit.");
			text2.setPosition(view.getCenter().x-240, view.getCenter().y+210);
			text33.setString("YOU WIN!");
			text33.setPosition(view.getCenter().x-240, view.getCenter().y+170);
			p.sprite.setTextureRect(sf::IntRect(0, 300, 60, 60));
			view.move(-0.033,0);

			createObjectForMapCoinTimer = 0;
			createObjectForMapCoin5Timer = 0;
			createObjectForMapCoin10Timer = 0;
			createObjectForMapHeartTimer = 0;
			createObjectForMapThornTimer = 0;
			createObjectForMapBottleTimer = 0;
			createObjectForMapBottleManaTimer = 0;
			createObjectForMapAlienTimer = 0;
			createObjectForMapBadMushroomTimer = 0;
			createObjectForMapGoodMushroomTimer = 0;
			createObjectForMapStoneTimer = 0;
			createObjectForMapPepperTimer = 0;
			createObjectForMapChestTimer = 0;
			createObjectForMapKeyTimer = 0;
			createObjectForMapCrayfishTimer = 0;
			createObjectForMapMowerTimer = 0;
		}

		}
		else
			{
				//text1.setString("Chicken is red! Press [Q] to quit.");
				//text1.setString("Chicken is sad! Press [Q] to quit.");
				text1.setString("Careful in next time. Press [Q] to quit.");
				text1.setPosition(view.getCenter().x-220, view.getCenter().y+210);
				text22.setString("YOU LOSE!");
				text22.setPosition(view.getCenter().x-220, view.getCenter().y+170);
				//p.sprite.setTextureRect(sf::IntRect(128, 0, w, h));
				p.sprite.setTextureRect(sf::IntRect(0, 240, 60, 60));
				music.stop();
				//music1.play();
				//CurrentFrame+=0.00001*time;
				//if (CurrentFrame>4) CurrentFrame-=4;
				//p.sprite.setTextureRect(sf::IntRect(192*int(CurrentFrame), 0, 64, 64));
				//view.reset(sf::FloatRect(p.getPlayerCoordinateX() - 220, p.getPlayerCoordinateY() - 180, 320, 240));
				//view.rotate(0.1f);
				view.move(0.033,0);

				createObjectForMapCoinTimer = 0;
				createObjectForMapCoin5Timer = 0;
				createObjectForMapCoin10Timer = 0;
				createObjectForMapHeartTimer = 0;
				createObjectForMapThornTimer = 0;
				createObjectForMapBottleTimer = 0;
				createObjectForMapBottleManaTimer = 0;
				createObjectForMapAlienTimer = 0;
				createObjectForMapBadMushroomTimer = 0;
				createObjectForMapGoodMushroomTimer = 0;
				createObjectForMapStoneTimer = 0;
				createObjectForMapPepperTimer = 0;
				createObjectForMapChestTimer = 0;
				createObjectForMapKeyTimer = 0;
				createObjectForMapCrayfishTimer = 0;
				createObjectForMapMowerTimer = 0;
			}

		if (p.health > 15) {p.sprite.setColor(sf::Color(255, 255, 255));} // ������� ������ ���������
		if (p.health <= 15) {p.fullSpeed = false; p.sprite.setColor(sf::Color(0, 0, 255));} // ������� ������ ���������

		if (p.playerScore <= 0) {p.playerScore = 0;}// ������������� �����������, ������� �� ����� ���� ��������������
		if (p.health >= 100) {p.health = 100;}
		if (p.health <= 0) {p.health = 0;}
		if (p.takeKey <= 0) {p.takeKey = 0;}
		if (p.mana >= 20000) {p.mana = 20000;}
		if (p.mana <= 0) {p.mana = 0;}

		if (p.takeCoin == true) // ����� ����� �������� 1 ������� ������ ����, ���������� � �������� ������� "+1"
		{

			textTakeitem.setString("+1");
			//textTakeitem.setColor(sf::Color(255, 255, 0));
			//textTakeitem.setPosition(p.getPlayerCoordinateX()+20, p.getPlayerCoordinateY()-20);
			textTakeitem.setPosition(p.getPlayerCoordinateX()+20, p.getPlayerCoordinateY()-20*takeCoin1Timer/150);

			takeCoin1Timer += time;
			if ((takeCoin1Timer > 0) && (takeCoin1Timer < 7))
			{
				soundtakecoin.play();
				//p.takeCoin = false;
				//takeCoin1Timer = 0;
			}

			if (takeCoin1Timer > 500)
			{
				textTakeitem.setString("");
				p.takeCoin = false;
				takeCoin1Timer = 0;
			}

		}

		if (p.takeThorn == true)
		{
			textTakeitem.setString("-10");
			//textTakeitem.setColor(sf::Color(255, 0, 0));
			textTakeitem.setPosition(p.getPlayerCoordinateX()+15, p.getPlayerCoordinateY()-20*takeThornTimer/150);

			takeThornTimer += time;
			if ((takeThornTimer > 0) && (takeThornTimer < 7))
			{
				soundhit.play();
			}

			if ((takeThornTimer > 0) && (takeThornTimer < 100))
			{
				//p.sprite.setColor(sf::Color(255, 0, 0));
				p.sprite.setTextureRect(sf::IntRect(60, 360, 60, 60));
			}

			if (takeThornTimer > 500)
			{
				//p.speed=0.025;
				textTakeitem.setString("");
				p.takeThorn = false;
				takeThornTimer = 0;
			}

		}

		if (p.takeHp == true)
		{
			textTakeitem.setString("+20");
			//textTakeitem.setColor(sf::Color(0, 255, 0));
			textTakeitem.setPosition(p.getPlayerCoordinateX()+15, p.getPlayerCoordinateY()-20*takeHpTimer/150);

			takeHpTimer += time;

			if ((takeHpTimer > 0) && (takeHpTimer < 10))
			{
				soundtake.play();
			}

			if (takeHpTimer > 500)
			{
				textTakeitem.setString("");
				p.takeHp = false;
				takeHpTimer = 0;
			}
		}

		if (p.zombieChicken == true)
		{
			p.fullSpeed = false;
			p.sprite.setColor(sf::Color(0, 255, 0));
			//p.takeCoin == false;
			//p.sprite.setTextureRect(sf::IntRect(192, 64, 64, 64));
			p.speed += 0.05;
			p.mana -= 5;
			zombieChickenTimer += time;
			if ((zombieChickenTimer > 0) && (zombieChickenTimer < 25))
			{
				soundhit.play();
				p.playerScore -= 1;
			}

			if (zombieChickenTimer > 5000)
			{
				p.sprite.setColor(sf::Color(255, 255, 255));
				p.zombieChicken = false;
				zombieChickenTimer = 0;
			}
		}

		if (p.fullSpeed == true)
		{
			p.zombieChicken = false;
			p.speed += 0.25;
			p.sprite.setColor(sf::Color(255, 255, 0));
		//	p.sprite.setTextureRect(sf::IntRect(192, 64, 64, 64));

			fullSpeedTimer += time;
			if (fullSpeedTimer > 5000)
			{
				p.sprite.setColor(sf::Color(255, 255, 255));
				p.fullSpeed = false;
				fullSpeedTimer = 0;
			}
		}

		if (p.chestOpen == true)
		{
			chestOpenTimer += time;

			if ((chestOpenTimer > 0) && (chestOpenTimer < 10))
			{
				soundChestOpen.play();
				p.chestOpen = false;
				chestOpenTimer = 0;
			}
		}

		if (p.keyTaked == true)
		{
			keyTakedTimer += time;

			if ((keyTakedTimer > 0) && (keyTakedTimer < 10))
			{
				soundTakeKey.play();
				p.keyTaked = false;
				keyTakedTimer = 0;
			}
		}


		//////////////////// ������� ��������� �������� ////////////////////


		createObjectForMapCoinTimer += time; // ����������� ������� ��� ��������� ������� +1 ����� 2�
		if (createObjectForMapCoinTimer > 3000)
		{
			randomCoinGenerate(); // ���������
			createObjectForMapCoinTimer = 0; // ��������� �������
		}

		/*
		createObjectForMapCoin5Timer += time; // ����������� ������� ��� ��������� ������� +5 ����� 30�
		if (createObjectForMapCoin5Timer > 30000)
		{
			randomCoin5Generate();
			createObjectForMapCoin5Timer = 0;
		}

		createObjectForMapCoin10Timer += time; // ����������� ������� ��� ��������� ������� +10 ����� 90�
		if (createObjectForMapCoin10Timer > 90000)
		{
			randomCoin10Generate();
			createObjectForMapCoin10Timer = 0;
		}*/

		createObjectForMapHeartTimer += time; // ��������
		if (createObjectForMapHeartTimer > 6000)
		{
			randomHeartGenerate();
			createObjectForMapHeartTimer = 0;
		}

		createObjectForMapThornTimer += time; // �������
		if (createObjectForMapThornTimer > 1000)
		{
			randomThornGenerate();
			createObjectForMapThornTimer = 0;
		}

		createObjectForMapAlienTimer += time; // ������������
		if (createObjectForMapAlienTimer > 20000)
		{
			randomAlienGenerate();
			createObjectForMapAlienTimer = 0;
		}

		createObjectForMapBottleTimer += time; // ����� ��������
		if (createObjectForMapBottleTimer > 35000)
		{
			randomBottleGenerate();
			createObjectForMapBottleTimer = 0;
		}

		createObjectForMapBottleManaTimer += time; // ����� ����
		if (createObjectForMapBottleManaTimer > 45000)
		{
			randomBottleManaGenerate();
			createObjectForMapBottleManaTimer = 0;
		}
		/*
		createObjectForMapBadMushroomTimer += time; // ����������� �������
		if (createObjectForMapBadMushroomTimer > 60000)
		{
			randomBadMushroomGenerate();
			createObjectForMapBadMushroomTimer = 0;
		}

		createObjectForMapGoodMushroomTimer += time; // ��������� �������
		if (createObjectForMapGoodMushroomTimer > 60000)
		{
			randomGoodMushroomGenerate();
			createObjectForMapGoodMushroomTimer = 0;
		}
		*/
		createObjectForMapStoneTimer += time; // �����
		if (createObjectForMapStoneTimer > 15000)
		{
			randomStoneGenerate();
			createObjectForMapStoneTimer = 0;
		}

		createObjectForMapPepperTimer += time; // �����
		if (createObjectForMapPepperTimer > 20000)
		{
			randomPepperGenerate();
			createObjectForMapPepperTimer = 0;
		}

		createObjectForMapChestTimer += time; // ������
		if (createObjectForMapChestTimer > 100000)
		{
			randomChestGenerate();
			createObjectForMapChestTimer = 0;
		}

		createObjectForMapKeyTimer += time; // ����
		if (createObjectForMapKeyTimer > 100000)
		{
			randomKeyGenerate();
			createObjectForMapKeyTimer = 0;
		}

		createObjectForMapCrayfishTimer += time; // ������ ���
		if (createObjectForMapCrayfishTimer > 20000)
		{
			randomCrayfishGenerate();
			createObjectForMapCrayfishTimer = 0;
		}

		/*
		createObjectForMapMowerTimer += time; // �������
		if (createObjectForMapMowerTimer > 2000)
		{
			randomMowerGenerate();
			createObjectForMapMowerTimer = 0;
		}
		*/


		//////////////////// ���������� ������� ����� "���� ������� ����" ////////////////////


        sf::Event event; // ���������� ������� ���� window
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed) window.close(); // ������� �������� ���� (���� ����� ������� �� ����)
			//if (event.key.code == sf::Keyboard::Q) window.close();

			if (event.type == sf::Event::KeyPressed) // ������� �������� �������
			if (event.key.code == sf::Keyboard::Tab)// ���� ������ ������� TAB
			{
				soundtake.play();
				switch (showMissionText) // �������������, ����������� �� ���������� ���������� showMissionText
				{
				case true:
					{
						showMissionText = false; // ������, ��������� ��, ��� ���� �������� �� �����
						break; // �����, ����� �� ��������� ������� false, ������� ����
					}

				case false:
					{
						//text.setString(""); // ���� ������� TAB �� ������, �� ���� ����� ������
						showMissionText = true; // ������, ����������� ����� ������ TAB � �������� ����� ������ ������ �� �����
						break;
					}
				}
			}

			/*
			// ������� �������� �������
			if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::M)
			{
				switch (musicStopPlay)
				{
				case true:
					{
							musicStopPlay = true;
							break;
					}

				case false:
					{
						musicStopPlay = false;
						break;
					}
				}
			}
			*/

		}

/*
		while (menu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close(); // ������� �������� ���� (���� ����� ������� �� ����)
		}
*/



		//////////////////// ���������� ���������� ��� ������� �� ������� + �������� ////////////////////


		if (p.life)
		{

			if (!p.overGame)
			{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // ����� �������� ������� p �����, ���� ������ ������� Up, �� ���������� �������� � ������� {playersprite �������� �� ��� �� ��������� 0.1}
			{
				p.dir=3; p.speed=0.1;// p.dir=1 - ����������� �����, p.speed=0.1 - ��������

				CurrentFrame+=0.006*time; // ������ �� ������ �� ��������� 0.005 ��� ��������������� ��������
				if (CurrentFrame>2) CurrentFrame-=2; // ������������ ��������, ���� ���������� ������ 4 (���-�� ������), �� �������� �������
				p.sprite.setTextureRect(sf::IntRect(60*int(CurrentFrame), 180, 60, 60)); // ������ �� ������, ��������� ���������� �� ���������� 0,128 ������ � ���� �� 60 � 60

				if ((p.health>0) && (p.health<=15)) {p.sprite.setColor(sf::Color(0, 0, 255)); p.speed=0.025;}
				if (p.zombieChicken == true) {p.dir = 0; p.speed += 0.05;}
				if (p.takeThorn == true) {p.speed = 0.025;}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				p.dir=2; p.speed=0.1;

				CurrentFrame+=0.006*time;
				if (CurrentFrame>2) CurrentFrame-=2;
				p.sprite.setTextureRect(sf::IntRect(60*int(CurrentFrame), 120, 60, 60));

				if ((p.health>0) && (p.health<=15)) {p.sprite.setColor(sf::Color(0, 0, 255)); p.speed=0.025;}
				if (p.zombieChicken == true) {p.dir = 3; p.speed += 0.05;}
				if (p.takeThorn == true) {p.speed = 0.025;}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				p.dir=1; p.speed=0.1;

				CurrentFrame+=0.006*time;
				if (CurrentFrame>2) CurrentFrame-=2;
				p.sprite.setTextureRect(sf::IntRect(60*int(CurrentFrame), 60, 60, 60));

				if ((p.health>0) && (p.health<=15)) {p.sprite.setColor(sf::Color(0, 0, 255)); p.speed=0.025;}
				if (p.zombieChicken == true) {p.dir = 2; p.speed += 0.05;}
				if (p.takeThorn == true) {p.speed = 0.025;}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				p.dir=0; p.speed=0.1;

				CurrentFrame+=0.006*time;
				if (CurrentFrame>2) CurrentFrame-=2;
				p.sprite.setTextureRect(sf::IntRect(60*int(CurrentFrame), 0, 60, 60));

				if ((p.health>0) && (p.health<=15)) {p.sprite.setColor(sf::Color(0, 0, 255)); p.speed=0.025;}
				if (p.zombieChicken == true) {p.dir = 1; p.speed += 0.05;}
				if (p.takeThorn == true) {p.speed = 0.025;}
			}

			if (p.mana > 0)
			{
				if (p.health > 15)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						p.speed = 0.25;
						p.mana -= 10;
					}
				}
			}

			setPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY()); // ������� ���������� ������ � ������� ���������� ������� ���� �� ���

			}

		}

		//////////////////// ����� ���������� ���������� � ��������� ��� ������� �� ������� ////////////////////

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) { return true; }//���� ���, �� ������������� ����
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { return false; }//���� ������, �� ������� �� ����




		if (event.type == sf::Event::KeyPressed) // ������� �������� �������
			if (event.key.code == sf::Keyboard::M)// ���� ������ ������� TAB
			{
				soundtake.play();
				switch (fullSizeMap) // �������������, ����������� �� ���������� ���������� showMissionText
				{
				case true:
					{
						fullSizeMap = true; // ������, ��������� ��, ��� ���� �������� �� �����
						break; // �����, ����� �� ��������� ������� false, ������� ����
					}

				case false:
					{
						//text.setString(""); // ���� ������� TAB �� ������, �� ���� ����� ������
						fullSizeMap = false; // ������, ����������� ����� ������ TAB � �������� ����� ������ ������ �� �����
						break;
					}
				}
			}

			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			//{
			//	music.stop();
			//}


		p.update(time); // ������� ������ p ������ Player � ������� ������� SFML, ��������� ����� � �������� ��������� ������� update, ��������� ���� �������� ����� ���������

		viewmap(time); // ������� ���������� ������� �����
		changeview(); // ������� �������� � ��������������� ������� �����
		window.setView(view); // ��������� ������ � ����

		window.clear(sf::Color(181,230,29)); // ������� �������� ���� window

		//////////////////// ��������� ����� ������ ////////////////////
		for (int i=0; i < HEIGHT_MAP; i++)
		for (int j=0; j < WIDTH_MAP; j++)
		{
			// ���� ������ " ", �� �������� ����������� �����
			if (TileMap[i][j] == ' ') map_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
			// ���� ������ "G", �� �������� ����������� �����
			if (TileMap[i][j] == 'G') map_sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
			// ���� ������ "C", �� �������� ������ +1
			if (TileMap[i][j] == 'C') map_sprite.setTextureRect(sf::IntRect(0, 32, 32,32));
			// ���� ������ "D", �� �������� ������ +5
			if (TileMap[i][j] == 'D') map_sprite.setTextureRect(sf::IntRect(32, 32, 32, 32));
			// ���� ������ "E", �� �������� ������ +10
			if (TileMap[i][j] == 'E') map_sprite.setTextureRect(sf::IntRect(64, 32, 32, 32));
			// ���� ������ "F", �� �������� ������ �������
			if (TileMap[i][j] == 'F') map_sprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
			// ���� ������ "A", �� �������� ����������� �������������
			if (TileMap[i][j] == 'A') map_sprite.setTextureRect(sf::IntRect(32, 64, 32, 32));
			// ���� ������ "H", �� �������� ������� ������ +20
			if (TileMap[i][j] == 'H') map_sprite.setTextureRect(sf::IntRect(0, 96, 32, 32));
			// ���� ������ "B", �� �������� ������� � ������ +50
			if (TileMap[i][j] == 'B') map_sprite.setTextureRect(sf::IntRect(32, 96, 32, 32));
			// ���� ������ "B", �� �������� ������� � ������ +50
			if (TileMap[i][j] == 'M') map_sprite.setTextureRect(sf::IntRect(96, 96, 32, 32));
			// ���� ������ "X", �� �������� ������� -100
			if (TileMap[i][j] == 'X') map_sprite.setTextureRect(sf::IntRect(64, 96, 32, 32));
			// ���� ������ "Y", �� �������� ������� +100
			if (TileMap[i][j] == 'Y') map_sprite.setTextureRect(sf::IntRect(64, 96, 32, 32));
			// ���� ������ "S", �� �������� ������
			if (TileMap[i][j] == 'S') map_sprite.setTextureRect(sf::IntRect(0, 128, 32, 32));
			// ���� ������ "P", �� �������� �����
			if (TileMap[i][j] == 'P') map_sprite.setTextureRect(sf::IntRect(32, 128, 32, 32));
			// ���� ������ "T", �� �������� �������� ������
			if (TileMap[i][j] == 'T') map_sprite.setTextureRect(sf::IntRect(0, 160, 32, 32));
			// ���� ������ "U", �� �������� �������� ������
			if (TileMap[i][j] == 'U') map_sprite.setTextureRect(sf::IntRect(32, 160, 32, 32));
			// ���� ������ "K", �� �������� ���� ��� �������
			if (TileMap[i][j] == 'K') map_sprite.setTextureRect(sf::IntRect(64, 160, 32, 32));
			// ���� ������ "L", �� �������� ���
			if (TileMap[i][j] == 'L') map_sprite.setTextureRect(sf::IntRect(0, 192, 32, 32));
			// ���� ������ "M", �� �������� �������������
			if (TileMap[i][j] == 'W') map_sprite.setTextureRect(sf::IntRect(0, 224, 32, 32));

			map_sprite.setPosition(j*32,i*32); // �������� ����� �������� ������� �������� ����� �������
			window.draw(map_sprite); // ��������� ����� �� ������
		}
		////////////////////////////////////////////////////////////////////////////////

		window.draw(p.sprite); // ������� ��������� ������� p ������ Player
		//window.draw(e.sprite);

		window.draw(stateLine_sprite); // ��������� ������ ���������
		stateLine_sprite.setPosition(view.getCenter().x-320, view.getCenter().y-240);// ������� ������ ��������� ������ ������

		// ����� �������� �� ������ ���������
		if (p.health == 0) {textHealthState.setString("");}
		if (p.health == 5) {textHealthState.setString("=");}
		if ((p.health > 5) && (p.health <= 10)) {textHealthState.setString("==");}
		if ((p.health > 10) && (p.health <= 15)) {textHealthState.setString("===");}
		if ((p.health > 15) && (p.health <= 20)) {textHealthState.setString("====");}
		if ((p.health > 20) && (p.health <= 25)) {textHealthState.setString("=====");}
		if ((p.health > 25) && (p.health <= 30)) {textHealthState.setString("======");}
		if ((p.health > 30) && (p.health <= 35)) {textHealthState.setString("=======");}
		if ((p.health > 35) && (p.health <= 40)) {textHealthState.setString("========");}
		if ((p.health > 40) && (p.health <= 45)) {textHealthState.setString("=========");}
		if ((p.health > 45) && (p.health <= 50)) {textHealthState.setString("==========");}
		if ((p.health > 50) && (p.health <= 55)) {textHealthState.setString("===========");}
		if ((p.health > 55) && (p.health <= 60)) {textHealthState.setString("============");}
		if ((p.health > 60) && (p.health <= 65)) {textHealthState.setString("=============");}
		if ((p.health > 65) && (p.health <= 70)) {textHealthState.setString("==============");}
		if ((p.health > 70) && (p.health <= 75)) {textHealthState.setString("===============");}
		if ((p.health > 75) && (p.health <= 80)) {textHealthState.setString("================");}
		if ((p.health > 80) && (p.health <= 85)) {textHealthState.setString("=================");}
		if ((p.health > 85) && (p.health <= 90)) {textHealthState.setString("==================");}
		if ((p.health > 90) && (p.health <= 95)) {textHealthState.setString("===================");}
		if ((p.health > 95) && (p.health <= 100)) {textHealthState.setString("====================");}
		if (p.health > 100) {textHealthState.setString("====================");}
		textHealthState.setPosition(view.getCenter().x-256, view.getCenter().y-210);
		window.draw(textHealthState);

		// ����� ���� �� ������ ���������
		if (p.mana == 0) {textManaState.setString("");}
		if (p.mana == 1000) {textManaState.setString("=");}
		if ((p.mana > 1000) && (p.mana <= 2000)) {textManaState.setString("==");}
		if ((p.mana > 2000) && (p.mana <= 3000)) {textManaState.setString("===");}
		if ((p.mana > 3000) && (p.mana <= 4000)) {textManaState.setString("====");}
		if ((p.mana > 4000) && (p.mana <= 5000)) {textManaState.setString("=====");}
		if ((p.mana > 5000) && (p.mana <= 6000)) {textManaState.setString("======");}
		if ((p.mana > 6000) && (p.mana <= 7000)) {textManaState.setString("=======");}
		if ((p.mana > 7000) && (p.mana <= 8000)) {textManaState.setString("========");}
		if ((p.mana > 8000) && (p.mana <= 9000)) {textManaState.setString("=========");}
		if ((p.mana > 9000) && (p.mana <= 10000)) {textManaState.setString("==========");}
		if ((p.mana > 10000) && (p.mana <= 11000)) {textManaState.setString("===========");}
		if ((p.mana > 11000) && (p.mana <= 12000)) {textManaState.setString("============");}
		if ((p.mana > 12000) && (p.mana <= 13000)) {textManaState.setString("=============");}
		if ((p.mana > 13000) && (p.mana <= 14000)) {textManaState.setString("==============");}
		if ((p.mana > 14000) && (p.mana <= 15000)) {textManaState.setString("===============");}
		if ((p.mana > 15000) && (p.mana <= 16000)) {textManaState.setString("================");}
		if ((p.mana > 16000) && (p.mana <= 17000)) {textManaState.setString("=================");}
		if ((p.mana > 17000) && (p.mana <= 18000)) {textManaState.setString("==================");}
		if ((p.mana > 18000) && (p.mana <= 19000)) {textManaState.setString("===================");}
		if ((p.mana > 19000) && (p.mana <= 20000)) {textManaState.setString("====================");}
		if (p.mana > 20000) {textManaState.setString("====================");}
		textManaState.setPosition(view.getCenter().x-256, view.getCenter().y-200);
		window.draw(textManaState);

		// ��� ��� ������ ����� ��������� ���������, ������� ���������� ����������
		std::ostringstream playerScoreString, playerHealthString, gameTimeString, thornString, alienString, pepperString, openChestString, takeKeysString, manaString;
		// ��������� � �� ����� �����, �� ������������ ������, � ����� ������ �� ��������� � ��������� ��������
		playerScoreString << p.playerScore;
		playerHealthString << p.health;
		gameTimeString << gameTime;
		thornString << p.thorn;
		alienString << p.alien;
		pepperString << p.pepper;
		openChestString << p.openChest;
		takeKeysString << p.takeKey;
		manaString << p.mana;
		// ������� ������ ������ �� ������
		text.setString("Health:" + playerHealthString.str() + " Mana:" + manaString.str() + " Time:" + gameTimeString.str() + "\nCoins:" + playerScoreString.str() + " Keys:" + takeKeysString.str() + " Chests:" + openChestString.str() + "\nThorns:" + thornString.str() + " Aliens:" + alienString.str() + " Peppers:" + pepperString.str());
		text.setPosition(view.getCenter().x+56, view.getCenter().y-230); // ������� ������� ������ (� ������ ������)

		//text11.setString("Yellow chicken is win! Paint chicken in yellow! Take 100 coins!");
		text11.setString("Press [TAB] for info");
		//text11.setString(L"��� ��������� ���������� ����� [TAB]");
		//text11.setPosition(view.getCenter().x-256, view.getCenter().y-230); // ������� ������� ������ (� ������ ������)
		text11.setPosition(view.getCenter().x+160, view.getCenter().y+215);

		window.draw(text); // ��������� ������ �� ������
		window.draw(text1);
		window.draw(text2);
		window.draw(text11);
		window.draw(text22);
		window.draw(text33);
		window.draw(textTakeitem);

		textCoinStringer.setString("" + playerScoreString.str());
		textCoinStringer.setPosition(view.getCenter().x-60, view.getCenter().y-220);
		window.draw(textCoinStringer);

		if (!showMissionText) // ���� ������ ������� TAB ���������� ��������� ����� ������ � ��� ��������
		{
			// ������� ������ ������ �� ������ + ����� ������ �����
			//text5.setString(L"INFO\n\nYellow chicken is win! Paint chicken in yellow!\nTake 100 coins for this!\n\nRed chicken is fail! Not paint chicken in red!\nNot take black thorns for this!\n\nRemember! If chicken is blue, he sick!\n\nBONUSES\n\nCuprum coin: +1 score\nSilver coin: +5 score\nBlack thorn: -25 health\nRed hurt: +20 health\nBlue bottle: +50 health\nStrange mushroom: edible or inedible, be careful!");
			//text5.setString(L"����������\n\nƸ���� ������ - � ������!\n������� ������ �����!\n��� ����� ������ 100 �����!\n\n������� ������ - � ���������!\n�� ����� ������ �������!\n�� �������� ������ �������!\n\n�������!\n���� ������ ����� - ��� ������!\n\n������\n\n������ ������: +1 � �����\n���������� ������: +5 � �����\n׸���� �������: -25 � ��������\n������� ������: +20 � ��������\n����� ������: +50 � ��������\n�������� �������: ��������� ��� �����������, ���� ���������!");
			// ������� ������ �� ������
			text5.setString(L"INFO\n\n   You win if chicken is happy! Take 100 coins for this!\nYou lose if chicken is sad. Not take black thorns for this.\nRemember! If chicken is blue, he very sick.\n\nCONTROL\n\n[Up] - move up\n[Down] - move down\n[Left] - move left\n[Right] - move right\n[Space] - action move\n\nBONUSES\n\nCuprum coin: +1 score\nSilver coin: +5 score\nGold coin: +10 score\nBlack thorn: -25 health\nGreen alien: make you zombie\nRed hurt: +20 health\nBlue bottle: +50 health\nStrange mushroom: edible or inedible, be careful!\nKey: need for open the chest\nChest: have a mega bknus!");
			text5.setPosition(view.getCenter().x-200, view.getCenter().y-160);
			scroll_quest.setPosition(view.getCenter().x-250, view.getCenter().y-180);// ������� ���� ��� ������ (������� ������)

			window.draw(scroll_quest); // ��������� ������� ������ � ������ �� ��
			window.draw(text5);
		}

        window.display(); // ������� ������ ����������� �� �����

	}
	//////////////////// ����� ����� "���� ������� ����" ////////////////////


}


void gameRunning() //�-��� ������������� ����, ���� ��� ����������
{
    if (startGame())
    {
        gameRunning(); //���� startGame() == true, �� �������� ������ �-��� isGameRunning, ������� � ���� ������� ����� �������� startGame()
    }
}

//////////////////////////////////////// ������� ������� ��������� ////////////////////////////////////////

int main() // ������������ ������� ������� ����� C++
{
	//HWND hWnd = GetConsoleWindow(); //����� ����� �������, (�������� ������� (�������� ������ ��� windows))
	//ShowWindow(hWnd, SW_HIDE); //�������� �������

    gameRunning(); //��������� ������� ����
    return 0;
}


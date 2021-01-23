#include <SFML/Graphics.hpp> // подключение заголовочного файла, отвечающего за работу с графикой
#include <SFML/Audio.hpp> // подключение заголовочного файла, отвечающего за работу со звуком
#include "map.h" // подключение кода с картой уровня
#include "view.h" // подключение кода с камерой
#include <sstream> // подключение стандартной библиотеки С++, которая отвечает за ввод-вывод
#include <iostream>
//#include "mission.h" // подключение кода с текстом миссий

//#define _WIN32_WINNT 0x0500 // для скрытия консоли
//#include <windows.h> // для скрытия консоли

//////////////////// КЛАСС ИГРОКА ////////////////////

class Player // класс игрока под названием Player
{
public: // модификатор доступа для возможности обращения к переменным из функции main, в нём указываем свойства объекта
	// координаты игрока, ширина и высота спрайта, ускорение по x и y, скорость
	float x, y, w, h, dx, dy, speed;
	// направление движения игрока (direction) и переменная, хранящая очки игрока, отвечающая за жизнь игрока, состояния движения и выбор объекта
	int dir, playerScore, health, mana, chickenSpeed, thorn, alien, pepper, openChest, takeKey; // takeCoins; //hammer;
	// логическая переменная, говорящая жив игрок или нет, выполнено условие победы или нет
	bool life, action, overGame, takeCoin, takeThorn, takeHp, zombieChicken, fullSpeed, chestOpen, keyTaked;  //gameOverMusic, winMusic, isMove, isSelect,

	sf::String File; // файл с расширением
	sf::Image image;// изображение (спрайтлист)
	sf::Texture texture;// текстура
	sf::Sprite sprite;// спрайт

	Player (sf::String F, float X, float Y, float W, float H)// конструктор класса Player для инициализации переменных
	{

		dir = 0;
		speed = 0;
		dx = 0;
		dy = 0;
		playerScore = 0;
		health = 100;
		mana = 20000; // 20000 на 7с бега для курицы
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

		File = F; // имя файла+расширение
		w = W; h = H; // ширина и высота

		image.loadFromFile(File); // загрузка в image текстуры из файла
		image.createMaskFromColor(sf::Color(204, 204, 204)); // создание маски для добавления спрайту прозрачности на фоне
		texture.loadFromImage(image); // загрузка изображения в текстуру
		sprite.setTexture(texture); // загрузка текстуры в спрайт
		x = X; y = Y; // координаты появления спрайта
		sprite.setTextureRect(sf::IntRect(120, 0, 60, 60)); // задание спрайту прямоугольника для вывода вначале поумолчанию
	}

	void update(float time) // функция update с параметром time (будет работать бесконечно)
	{

		switch (dir) // поведение персонажа в зависимости от направления, каждая цифра соответствует направлению
		{
		case 0: dx = speed; dy = 0; break; // по х - положительная скорость, по у - 0, персонаж идёт только вправо
		case 1: dx = -speed; dy = 0; break; // по х - отрицательная скорость, по у - 0, персонаж идёт только влево
		case 2: dx = 0; dy = speed; break; // по х - 0, по у - положительная скорость, персонаж идёт только вниз
		case 3: dx = 0; dy = -speed; break; // по х - 0, по у - отрицательная скорость, персонаж идёт только вверх
		}

		x += dx * time; // ускорение на время = смещение и как следствие движение персонажа
		y += dy * time; // тоже самое для у

		speed = 0; // зануление скорости, чтобы персонаж остановился

		//sprite.setPosition(x, y);
		sprite.setPosition(x + w/2, y + h/2); // вывод спрайта в позицию х,у
		sprite.setOrigin(w/2, h/2); // для взятия спрайта посередине

		InteractionWithMap(); // вызов функции взаимодействия с картой

		if (health <= 0) // функция условий поражения, если health = 0, то конец игры - проигрыш
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

		if (playerScore >= 100) // функция условий победы, если playerScore = 100, то конец игры - победа
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

	float getPlayerCoordinateX() {return x;} // эта функция забирает х персонажа
	float getPlayerCoordinateY() {return y;} // эта функция забирает y персонажа

	void InteractionWithMap() // функция взаимодействия Player с картой
	{
		for (int i = y/32; i < (y+h)/32; i++) // проход по всей карте
		for (int j = x/32; j < (x+w)/32; j++) // х/32 получается левый квадрат, с которым соприкасается персонаж
		{

			if (TileMap[i][j] == 'G') // если квадрат G, то проверяем направление скорости движения персонажа, куст
			{
				if (dy>0) // если он шёл вниз
				{
					y=i*32-h; dy = 0;
				}

				if (dy<0) // если он шёл вверх
				{
					y=i*32+32; dy = 0;
				}

				if (dx>0) // если он шёл вправо
				{
					x=j*32-w; dx = 0;
				}

				if (dx<0) // если он шёл влево
				{
					x=j*32+32; dx = 0;
				}
			}

			if (TileMap[i][j] == 'S') // камень
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

			if (TileMap[i][j] == 'T') // закрытый сундук
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

			if (TileMap[i][j] == 'U') // открытый сундук
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


			if (TileMap[i][j] == 'K') // ключ
			{
				takeKey += 1;
				keyTaked = true;

				TileMap[i][j] = ' ';
			}


			if (TileMap[i][j] == 'C') // если квадрат C, то происходит действие, монетка
			{

				playerScore += 1; // если взял монетку, прибавляются очки
				takeCoin = true; // монетка взята, звучит звук

				TileMap[i][j] = ' '; // после чего она исчезает
			}

			/*
			// если квадрат C, то происходит действие
			if (TileMap[i][j] == 'D')
			{
				// если взял монетку, прибавляются очки
				playerScore += 5;
				takeCoin = true;
				// после чего он исчезает
				TileMap[i][j] = ' ';
			}

			// если квадрат C, то происходит действие
			if (TileMap[i][j] == 'E')
			{
				// если взял монетку, прибавляются очки
				playerScore += 10;
				takeCoin = true;
				// после чего он исчезает
				TileMap[i][j] = ' ';
			}
			*/

			if (TileMap[i][j] == 'F') // колючка
			{
				health -= 10;
				thorn += 1;
				takeThorn = true;

				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'A') // инопланетянин
			{
				health -= 10;
				alien += 1;
				//playerScore -= 5;
				//takeThorn = true;
				zombieChicken = true;

				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'H') // сердечко
			{
				health += 20;
				takeHp = true;

				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'B') // бутыль с зельем для здоровья
			{
				health += 50;
				takeHp = true;

				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'M') // бутыль с зельем для маны
			{
				mana += 5000;
				takeHp = true;

				TileMap[i][j] = ' ';
			}

			/*
			if (TileMap[i][j] == 'X') // несъедобный мухомор
			{
				health -= 100;
				takeThorn = true;

				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'Y')  // съедобный мухомор
			{
				health += 100;
				takeHp = true;

				TileMap[i][j] = ' ';
			}
			*/

			if (TileMap[i][j] == 'P') // перец
			{
				health += 10;
				fullSpeed = true;
				pepper += 1;

				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'L') // речной рак
			{
				health += 5;
				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'W') // косилка
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
	sf::String File; // файл с расширением
	sf::Image image;// изображение (спрайтлист)
	sf::Texture texture;// текстура
	sf::Sprite sprite;// спрайт

	Enemy (sf::String F, float X, float Y, float W, float H)// конструктор класса Player для инициализации переменных
	{
		speed = 0;
		dx = 0.1;
		dy = 0;

		image.loadFromFile(File); // загрузка в image текстуры из файла
		image.createMaskFromColor(sf::Color(204, 204, 204)); // создание маски для добавления спрайту прозрачности на фоне
		texture.loadFromImage(image); // загрузка изображения в текстуру
		sprite.setTexture(texture); // загрузка текстуры в спрайт
		x = X; y = Y; // координаты появления спрайта
		sprite.setTextureRect(sf::IntRect(0, 0, 192, 96));
	}


	void checkCollisionWithMap() // функция взаимодействия Player с картой
	{
		for (int i = y/32; i < (y+h)/32; i++) // проход по всей карте
		for (int j = x/32; j < (x+w)/32; j++) // х/32 получается левый квадрат, с которым соприкасается персонаж
		{

			if (TileMap[i][j] == 'G') // если квадрат G, то проверяем направление скорости движения персонажа, куст
			{
				if (dy>0) // если он шёл вниз
				{
					y=i*32-h; dy = 0;
				}

				if (dy<0) // если он шёл вверх
				{
					y=i*32+32; dy = 0;
				}

				if (dx>0) // если он шёл вправо
				{
					x=j*32-w; dx = -0.1;
				}

				if (dx<0) // если он шёл влево
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


//// МЕНЮ ИГРЫ ////
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

    sf::Music musicMenu; // фоновая музыка
	musicMenu.openFromFile("sounds/menutheme.ogg");
	musicMenu.play();
	musicMenu.setLoop(true);

//////////////////////////////МЕНЮ///////////////////
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
            if (menuNum == 1) isMenu = false; //если нажали первую кнопку, то выходим из меню
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

		//if (event.type == sf::Event::Closed) window.close(); // условие закрытия окна (если нажат крестик на окне)

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

	//randomMapGenerate(); // для расстановки объектов случайным образом до отрисовки карты
    sf::RenderWindow window(sf::VideoMode(640, 480), "Run, Chicken! Run!"); //, sf::Style::Fullscreen); // создание окна под именем window с параметрами, указанными в скобках

    menu(window); //вызов меню игры

	//window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);

	//window.setMouseCursorVisible(false); // скрытие курсора мыши в пределах игрового окна

	view.reset(sf::FloatRect(0, 0, 640, 480)); // размер "вида" камеры

	sf::Font font; // создание шрифта для надписей (объект Font)
	font.loadFromFile("fonts/ptmonobold.ttf");// загрузка шрифта из файла

	sf::Text text("", font, 12); // создание текста (объект Text) в скобках текст, подключенный шрифт, размер шрифта
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
	sf::Image mask_image; // создание маски
	mask_image.loadFromFile("images/maskfon.png");
	sf::Texture mask_texture;
	mask_texture.loadFromImage(mask_image);
	sf::Sprite mask_sprite;
	mask_sprite.setTexture(mask_texture);
	*/

	sf::Image map_image; // создание карты уровня
	map_image.loadFromFile("images/tilesetlist.png");
	map_image.createMaskFromColor(sf::Color(204,204,204));
	sf::Texture map_texture;
	map_texture.loadFromImage(map_image);
	sf::Sprite map_sprite;
	map_sprite.setTexture(map_texture);

	sf::Image quest_image; // создание свитка с миссиями
	quest_image.loadFromFile("images/scroll.png");
	//quest_image.createMaskFromColor(sf::Color(204,204,204));
	sf::Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	sf::Sprite scroll_quest;
	scroll_quest.setTexture(quest_texture);
	scroll_quest.setTextureRect(sf::IntRect(0, 0, 500, 355)); // размер свитка

	sf::Image stateLine_image; // создание строки состояния вверху экрана
	stateLine_image.loadFromFile("images/state_line.png");
	//quest_image.createMaskFromColor(sf::Color(204,204,204));
	sf::Texture stateLine_texture;
	stateLine_texture.loadFromImage(stateLine_image);
	sf::Sprite stateLine_sprite;
	stateLine_sprite.setTexture(stateLine_texture);
	stateLine_sprite.setTextureRect(sf::IntRect(0, 0, 640, 60)); // размер строки состояния

	// создаём объект p класса Player, задаём файл с изображением, координаты расположения спрайта на экране, ширина и высота спрайта
	Player p("images/spritesetlist.png", 20*32, 15*32, 60, 60); // для карты 40х30
	//Player p("images/spritesetlist.png", 9*32, 6*32, 60, 60); // для карты 20х15

	//Enemy e("images/spritesetlist.png", 2*32, 2*32, 192, 96);

	bool showMissionText = true; // логическая переменная отвечающая за появление миссии на экране

	bool fullSizeMap = true; // отображение всей карты

	//bool musicStopPlay = true; // выключение музыки

	sf::Music music; // фоновая музыка
	music.openFromFile("sounds/theme.ogg");
	music.play();
	music.setLoop(true);

	sf::SoundBuffer buffer1; // звук открытия инфо, взятие сердечка
	buffer1.loadFromFile("sounds/take.ogg");
	sf::Sound soundtake(buffer1);

	sf::SoundBuffer buffer2; // звук при взятии колючки
	buffer2.loadFromFile("sounds/hit.ogg");
	sf::Sound soundhit(buffer2);

	//sf::SoundBuffer buffer3; // звук конца игры
	//buffer3.loadFromFile("sounds/gameover.ogg");
	//sf::Sound soundgameover(buffer3);

	sf::SoundBuffer buffer4; // звук взятой монетки
	buffer4.loadFromFile("sounds/takecoin.ogg");
	sf::Sound soundtakecoin(buffer4);

	sf::SoundBuffer buffer5; // звук открытого сундука
	buffer5.loadFromFile("sounds/soundChestOpen.ogg");
	sf::Sound soundChestOpen(buffer5);

	sf::SoundBuffer buffer6; // звук взятого ключа
	buffer6.loadFromFile("sounds/soundTakeKey.ogg");
	sf::Sound soundTakeKey(buffer6);

	//sf::SoundBuffer buffer5; // звук взятого здоровья
	//buffer5.loadFromFile("sounds/takehp.ogg");
	//sf::Sound soundtakehp(buffer5);

	float CurrentFrame=0; // переменная хранит текущий кадр

	sf::Clock clock; // создание переменной времени, те привязки ко времени, а не к частоте процессора
	sf::Clock gameTimeClock; // создание переменной времени, для хранения времени игры и последующего вывода на экран

	int gameTime = 0; // объявление игрового времени, инициализация

	// таймеры для появления рандомных элементов
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

	// тыймеры действий разных эффектов от подобранных вещей
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









	//////////////////////////////////////// ЦИКЛ "ПОКА ОТКРЫТО ОКНО" ////////////////////////////////////////

    while (window.isOpen()) // обязательный цикл, читаемый как "пока открыто окно", в данном случае окно window
    {

		float time=clock.getElapsedTime().asMicroseconds(); // создание переменной time типа float с заданием прошедшего времени в микросекундах
		clock.restart();// перезагрузка времени
		time=time/800;// регулировка скорости игры

		if (p.life) // пока игрок жив, игровое время идёт вперёд, иначе (те когда он умер) появляется текст, начинает двигаться камера, останавливается музыка, а объекты перестают появляться
		{
			gameTime=gameTimeClock.getElapsedTime().asSeconds();

		if (p.overGame) // если собрано н количество монет (см. класс игрока), появляется текст, начинает отдаляться камера
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

		if (p.health > 15) {p.sprite.setColor(sf::Color(255, 255, 255));} // заливка цветом персонажа
		if (p.health <= 15) {p.fullSpeed = false; p.sprite.setColor(sf::Color(0, 0, 255));} // заливка цветом персонажа

		if (p.playerScore <= 0) {p.playerScore = 0;}// корректировка показателей, которые не могут быть отрицательными
		if (p.health >= 100) {p.health = 100;}
		if (p.health <= 0) {p.health = 0;}
		if (p.takeKey <= 0) {p.takeKey = 0;}
		if (p.mana >= 20000) {p.mana = 20000;}
		if (p.mana <= 0) {p.mana = 0;}

		if (p.takeCoin == true) // когда игрок собирает 1 монетку звучит звук, появляется и исчезает надпись "+1"
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


		//////////////////// ТАЙМЕРЫ РАНДОМНЫХ ОБЪЕКТОВ ////////////////////


		createObjectForMapCoinTimer += time; // наращивание таймера для появления монеток +1 через 2с
		if (createObjectForMapCoinTimer > 3000)
		{
			randomCoinGenerate(); // генерация
			createObjectForMapCoinTimer = 0; // обнуление таймера
		}

		/*
		createObjectForMapCoin5Timer += time; // наращивание таймера для появления монеток +5 через 30с
		if (createObjectForMapCoin5Timer > 30000)
		{
			randomCoin5Generate();
			createObjectForMapCoin5Timer = 0;
		}

		createObjectForMapCoin10Timer += time; // наращивание таймера для появления монеток +10 через 90с
		if (createObjectForMapCoin10Timer > 90000)
		{
			randomCoin10Generate();
			createObjectForMapCoin10Timer = 0;
		}*/

		createObjectForMapHeartTimer += time; // сердечки
		if (createObjectForMapHeartTimer > 6000)
		{
			randomHeartGenerate();
			createObjectForMapHeartTimer = 0;
		}

		createObjectForMapThornTimer += time; // колючки
		if (createObjectForMapThornTimer > 1000)
		{
			randomThornGenerate();
			createObjectForMapThornTimer = 0;
		}

		createObjectForMapAlienTimer += time; // инопланетяне
		if (createObjectForMapAlienTimer > 20000)
		{
			randomAlienGenerate();
			createObjectForMapAlienTimer = 0;
		}

		createObjectForMapBottleTimer += time; // зелье здоровья
		if (createObjectForMapBottleTimer > 35000)
		{
			randomBottleGenerate();
			createObjectForMapBottleTimer = 0;
		}

		createObjectForMapBottleManaTimer += time; // зелье маны
		if (createObjectForMapBottleManaTimer > 45000)
		{
			randomBottleManaGenerate();
			createObjectForMapBottleManaTimer = 0;
		}
		/*
		createObjectForMapBadMushroomTimer += time; // несъедобный мухомор
		if (createObjectForMapBadMushroomTimer > 60000)
		{
			randomBadMushroomGenerate();
			createObjectForMapBadMushroomTimer = 0;
		}

		createObjectForMapGoodMushroomTimer += time; // съедобный мухомор
		if (createObjectForMapGoodMushroomTimer > 60000)
		{
			randomGoodMushroomGenerate();
			createObjectForMapGoodMushroomTimer = 0;
		}
		*/
		createObjectForMapStoneTimer += time; // камни
		if (createObjectForMapStoneTimer > 15000)
		{
			randomStoneGenerate();
			createObjectForMapStoneTimer = 0;
		}

		createObjectForMapPepperTimer += time; // перец
		if (createObjectForMapPepperTimer > 20000)
		{
			randomPepperGenerate();
			createObjectForMapPepperTimer = 0;
		}

		createObjectForMapChestTimer += time; // сундук
		if (createObjectForMapChestTimer > 100000)
		{
			randomChestGenerate();
			createObjectForMapChestTimer = 0;
		}

		createObjectForMapKeyTimer += time; // ключ
		if (createObjectForMapKeyTimer > 100000)
		{
			randomKeyGenerate();
			createObjectForMapKeyTimer = 0;
		}

		createObjectForMapCrayfishTimer += time; // речной рак
		if (createObjectForMapCrayfishTimer > 20000)
		{
			randomCrayfishGenerate();
			createObjectForMapCrayfishTimer = 0;
		}

		/*
		createObjectForMapMowerTimer += time; // косилка
		if (createObjectForMapMowerTimer > 2000)
		{
			randomMowerGenerate();
			createObjectForMapMowerTimer = 0;
		}
		*/


		//////////////////// ОБРАБОТЧИК СОБЫТИЙ цикла "ПОКА ОТКРЫТО ОКНО" ////////////////////


        sf::Event event; // обработчик событий окна window
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed) window.close(); // условие закрытия окна (если нажат крестик на окне)
			//if (event.key.code == sf::Keyboard::Q) window.close();

			if (event.type == sf::Event::KeyPressed) // событие нажатияя клафиши
			if (event.key.code == sf::Keyboard::Tab)// если нажата клавиша TAB
			{
				soundtake.play();
				switch (showMissionText) // переключатель, реагирующий на логическую переменную showMissionText
				{
				case true:
					{
						showMissionText = false; // строка, убирающая всё, что было выведено на экран
						break; // выход, чтобы не выполнять условие false, которое ниже
					}

				case false:
					{
						//text.setString(""); // если клавише TAB не нажата, то весь текст пустой
						showMissionText = true; // строка, позволяющая вновь нажать TAB и получить вывод текста миссии на экран
						break;
					}
				}
			}

			/*
			// событие нажатияя клафиши
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
            if (event.type == sf::Event::Closed) window.close(); // условие закрытия окна (если нажат крестик на окне)
		}
*/



		//////////////////// УПРАВЛЕНИЕ ПЕРСОНАЖЕМ ПРИ НАЖАТИИ НА СТРЕЛКИ + АНИМАЦИЯ ////////////////////


		if (p.life)
		{

			if (!p.overGame)
			{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // задаём движение спрайту p вверх, если нажата клавиша Up, то происходит действие в скобках {playersprite движется по оси со скоростью 0.1}
			{
				p.dir=3; p.speed=0.1;// p.dir=1 - направление вверх, p.speed=0.1 - скорость

				CurrentFrame+=0.006*time; // проход по кадрам со скоростью 0.005 для воспроизведения анимации
				if (CurrentFrame>2) CurrentFrame-=2; // зацикливание анимации, если переменная больше 4 (кол-во кадров), то начинаем сначала
				p.sprite.setTextureRect(sf::IntRect(60*int(CurrentFrame), 180, 60, 60)); // проход по кадрам, рисование начинается от координаты 0,128 вправо и вниз на 60 и 60

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

			setPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY()); // передаём координаты игрока в функцию управления камерой пока он жив

			}

		}

		//////////////////// КОНЕЦ УПРАВЛЕНИЯ ПЕРСОНАЖЕМ С АНИМАЦИЕЙ ПРИ НАЖАТИИ НА СТРЕЛКИ ////////////////////

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) { return true; }//если таб, то перезагружаем игру
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { return false; }//если эскейп, то выходим из игры




		if (event.type == sf::Event::KeyPressed) // событие нажатияя клафиши
			if (event.key.code == sf::Keyboard::M)// если нажата клавиша TAB
			{
				soundtake.play();
				switch (fullSizeMap) // переключатель, реагирующий на логическую переменную showMissionText
				{
				case true:
					{
						fullSizeMap = true; // строка, убирающая всё, что было выведено на экран
						break; // выход, чтобы не выполнять условие false, которое ниже
					}

				case false:
					{
						//text.setString(""); // если клавише TAB не нажата, то весь текст пустой
						fullSizeMap = false; // строка, позволяющая вновь нажать TAB и получить вывод текста миссии на экран
						break;
					}
				}
			}

			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			//{
			//	music.stop();
			//}


		p.update(time); // функция объект p класса Player с помощью времени SFML, передавая время в качестве параметра функции update, благодаря чему персонаж может двигаться

		viewmap(time); // функция скроллинга камерой карты
		changeview(); // функция поворота и масштабирования камерой карты
		window.setView(view); // оживление камеры в окне

		window.clear(sf::Color(181,230,29)); // функция очищения окна window

		//////////////////// РИСОВАНИЕ КАРТЫ УРОВНЯ ////////////////////
		for (int i=0; i < HEIGHT_MAP; i++)
		for (int j=0; j < WIDTH_MAP; j++)
		{
			// если символ " ", то рисуется изображение травы
			if (TileMap[i][j] == ' ') map_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
			// если символ "G", то рисуется изображение куста
			if (TileMap[i][j] == 'G') map_sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
			// если символ "C", то рисуется монета +1
			if (TileMap[i][j] == 'C') map_sprite.setTextureRect(sf::IntRect(0, 32, 32,32));
			// если символ "D", то рисуется монета +5
			if (TileMap[i][j] == 'D') map_sprite.setTextureRect(sf::IntRect(32, 32, 32, 32));
			// если символ "E", то рисуется монета +10
			if (TileMap[i][j] == 'E') map_sprite.setTextureRect(sf::IntRect(64, 32, 32, 32));
			// если символ "F", то рисуется чёрная колючка
			if (TileMap[i][j] == 'F') map_sprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
			// если символ "A", то рисуется зомбирующий инопланетянин
			if (TileMap[i][j] == 'A') map_sprite.setTextureRect(sf::IntRect(32, 64, 32, 32));
			// если символ "H", то рисуется красное сердце +20
			if (TileMap[i][j] == 'H') map_sprite.setTextureRect(sf::IntRect(0, 96, 32, 32));
			// если символ "B", то рисуется бутылка с зельем +50
			if (TileMap[i][j] == 'B') map_sprite.setTextureRect(sf::IntRect(32, 96, 32, 32));
			// если символ "B", то рисуется бутылка с зельем +50
			if (TileMap[i][j] == 'M') map_sprite.setTextureRect(sf::IntRect(96, 96, 32, 32));
			// если символ "X", то рисуется мухомор -100
			if (TileMap[i][j] == 'X') map_sprite.setTextureRect(sf::IntRect(64, 96, 32, 32));
			// если символ "Y", то рисуется мухомор +100
			if (TileMap[i][j] == 'Y') map_sprite.setTextureRect(sf::IntRect(64, 96, 32, 32));
			// если символ "S", то рисуется камень
			if (TileMap[i][j] == 'S') map_sprite.setTextureRect(sf::IntRect(0, 128, 32, 32));
			// если символ "P", то рисуется перец
			if (TileMap[i][j] == 'P') map_sprite.setTextureRect(sf::IntRect(32, 128, 32, 32));
			// если символ "T", то рисуется закрытый сундук
			if (TileMap[i][j] == 'T') map_sprite.setTextureRect(sf::IntRect(0, 160, 32, 32));
			// если символ "U", то рисуется открытый сундук
			if (TileMap[i][j] == 'U') map_sprite.setTextureRect(sf::IntRect(32, 160, 32, 32));
			// если символ "K", то рисуется ключ для сундука
			if (TileMap[i][j] == 'K') map_sprite.setTextureRect(sf::IntRect(64, 160, 32, 32));
			// если символ "L", то рисуется рак
			if (TileMap[i][j] == 'L') map_sprite.setTextureRect(sf::IntRect(0, 192, 32, 32));
			// если символ "M", то рисуется газонокосилка
			if (TileMap[i][j] == 'W') map_sprite.setTextureRect(sf::IntRect(0, 224, 32, 32));

			map_sprite.setPosition(j*32,i*32); // создание карты заданием каждому квадрату своей позиции
			window.draw(map_sprite); // рисование карты на экране
		}
		////////////////////////////////////////////////////////////////////////////////

		window.draw(p.sprite); // функция рисования объекта p класса Player
		//window.draw(e.sprite);

		window.draw(stateLine_sprite); // рисование строки состояния
		stateLine_sprite.setPosition(view.getCenter().x-320, view.getCenter().y-240);// позиция строки состояния вверху экрана

		// шкала здоровья на строке состояния
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

		// шкала маны на строке состояния
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

		// код для вывода числа собранных предметов, сначала объявление переменных
		std::ostringstream playerScoreString, playerHealthString, gameTimeString, thornString, alienString, pepperString, openChestString, takeKeysString, manaString;
		// занесение в неё числа очков, те формирование строки, а также строки со здоровьем и прошедшим временем
		playerScoreString << p.playerScore;
		playerHealthString << p.health;
		gameTimeString << gameTime;
		thornString << p.thorn;
		alienString << p.alien;
		pepperString << p.pepper;
		openChestString << p.openChest;
		takeKeysString << p.takeKey;
		manaString << p.mana;
		// задание строки текста на экране
		text.setString("Health:" + playerHealthString.str() + " Mana:" + manaString.str() + " Time:" + gameTimeString.str() + "\nCoins:" + playerScoreString.str() + " Keys:" + takeKeysString.str() + " Chests:" + openChestString.str() + "\nThorns:" + thornString.str() + " Aliens:" + alienString.str() + " Peppers:" + pepperString.str());
		text.setPosition(view.getCenter().x+56, view.getCenter().y-230); // задание позиции текста (в центре камеры)

		//text11.setString("Yellow chicken is win! Paint chicken in yellow! Take 100 coins!");
		text11.setString("Press [TAB] for info");
		//text11.setString(L"Для получения инструкций нажми [TAB]");
		//text11.setPosition(view.getCenter().x-256, view.getCenter().y-230); // задание позиции текста (в центре камеры)
		text11.setPosition(view.getCenter().x+160, view.getCenter().y+215);

		window.draw(text); // рисование текста на экране
		window.draw(text1);
		window.draw(text2);
		window.draw(text11);
		window.draw(text22);
		window.draw(text33);
		window.draw(textTakeitem);

		textCoinStringer.setString("" + playerScoreString.str());
		textCoinStringer.setPosition(view.getCenter().x-60, view.getCenter().y-220);
		window.draw(textCoinStringer);

		if (!showMissionText) // если нажата клавиша TAB происходит отрисовка блока текста и его смещение
		{
			// задание строки текста на экране + текст миссии снизу
			//text5.setString(L"INFO\n\nYellow chicken is win! Paint chicken in yellow!\nTake 100 coins for this!\n\nRed chicken is fail! Not paint chicken in red!\nNot take black thorns for this!\n\nRemember! If chicken is blue, he sick!\n\nBONUSES\n\nCuprum coin: +1 score\nSilver coin: +5 score\nBlack thorn: -25 health\nRed hurt: +20 health\nBlue bottle: +50 health\nStrange mushroom: edible or inedible, be careful!");
			//text5.setString(L"ИНФОРМАЦИЯ\n\nЖёлтая курица - к победе!\nПокрась курицу жёлтым!\nДля этого собери 100 монет!\n\nКрасная курица - к поражению!\nНе крась рукицу красным!\nНе подбирай чёрные колючки!\n\nЗапомни!\nЕсли курица синяя - она больна!\n\nБОНУСЫ\n\nМедная монета: +1 к очкам\nСеребряная монета: +5 к очкам\nЧёрная колючка: -25 к здоровью\nКрасное сердце: +20 к здоровью\nСиняя бутыль: +50 к здоровью\nСтранный мухомор: съедобный или несъедобный, будь осторожен!");
			// позиция текста на экране
			text5.setString(L"INFO\n\n   You win if chicken is happy! Take 100 coins for this!\nYou lose if chicken is sad. Not take black thorns for this.\nRemember! If chicken is blue, he very sick.\n\nCONTROL\n\n[Up] - move up\n[Down] - move down\n[Left] - move left\n[Right] - move right\n[Space] - action move\n\nBONUSES\n\nCuprum coin: +1 score\nSilver coin: +5 score\nGold coin: +10 score\nBlack thorn: -25 health\nGreen alien: make you zombie\nRed hurt: +20 health\nBlue bottle: +50 health\nStrange mushroom: edible or inedible, be careful!\nKey: need for open the chest\nChest: have a mega bknus!");
			text5.setPosition(view.getCenter().x-200, view.getCenter().y-160);
			scroll_quest.setPosition(view.getCenter().x-250, view.getCenter().y-180);// позиция фона для текста (позиция свитка)

			window.draw(scroll_quest); // рисование спрайта свитка и текста на нём
			window.draw(text5);
		}

        window.display(); // функция вывода изображения на экран

	}
	//////////////////// КОНЕЦ ЦИКЛА "ПОКА ОТКРЫТО ОКНО" ////////////////////


}


void gameRunning() //ф-ция перезагружает игру, если это необходимо
{
    if (startGame())
    {
        gameRunning(); //если startGame() == true, то вызываем занова ф-цию isGameRunning, которая в свою очередь опять вызывает startGame()
    }
}

//////////////////////////////////////// ГЛАВНАЯ ФУНКЦИЯ ПРОГРАММЫ ////////////////////////////////////////

int main() // обязательная главная функция языка C++
{
	//HWND hWnd = GetConsoleWindow(); //берем текущ консоль, (скрывает консоль (работает только под windows))
	//ShowWindow(hWnd, SW_HIDE); //скрывает консоль

    gameRunning(); //запускаем процесс игры
    return 0;
}


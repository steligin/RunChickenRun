#include <SFML/Graphics.hpp>

const int HEIGHT_MAP = 30; // размеры карты в тайлах по 32х32
const int WIDTH_MAP = 40;

sf::String TileMap[HEIGHT_MAP] = // массив строк, отображающий карту
{
"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"G                                      G",
"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
};

// рандомно расставляемые объекты на карте

void randomCoinGenerate() // монетки +1
{
	// случайный элемент по горизонтали
	int randomElementX = 0;
	// случайный элемент по вертикали
	int randomElementY = 0;
	// сам рандом
	srand(time(0));
	// количество (счётчик) монет 1
	int countCoin = 1;

	while (countCoin > 0)
	{
		// рандом по х от 1 до ширина карты-1, чтобы не получать числа бордюра карты и монеты там не появлялись
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// то же самое и по игреку
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// если встретили символ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// то ставим туда монетку
			TileMap[randomElementY][randomElementX] = 'C';
			// создана монетка -> счётчик монет будет "текущий-1"
			countCoin --;
		}
	}

}

void randomCoin5Generate() // монетки +5
{
	int randomElementX = 0;
	int randomElementY = 0;

	srand(time(0));

	int countCoin5 = 1;

	while (countCoin5 > 0)
	{
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 'D';
			countCoin5 --;
		}
	}

}

void randomCoin10Generate() // монетки +10
{
	int randomElementX = 0;
	int randomElementY = 0;

	srand(time(0));

	int countCoin10 = 1;

	while (countCoin10 > 0)
	{
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 'E';
			countCoin10 --;
		}
	}

}

void randomHeartGenerate() // сердечки
{
	int randomElementX = 0;
	int randomElementY = 0;

	srand(time(0));

	int countHeart = 1;

	while (countHeart > 0)
	{
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 'H';
			countHeart --;
		}
	}
}

void randomThornGenerate() // колючки
{
	// случайный элемент по горизонтали
	int randomElementX = 0;
	// случайный элемент по вертикали
	int randomElementY = 0;
	// сам рандом
	srand(time(0));
	// количество монет 1
	int countThorn = 1;

	while (countThorn > 0)
	{
		// рандом по х от 1 до ширина карты-1, чтобы не получать числа бордюра карты и монеты там не появлялись
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// то же самое и по игреку
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// если встретили символ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// то ставим туда монетку
			TileMap[randomElementY][randomElementX] = 'F';
			// создана монетка -> счётчик монет будет "текущий-1"
			countThorn --;
		}
	}
}

// бутылка с зельем
void randomBottleGenerate()
{
	// случайный элемент по горизонтали
	int randomElementX = 0;
	// случайный элемент по вертикали
	int randomElementY = 0;
	// сам рандом
	srand(time(0));
	// количество монет 1
	int countBottle = 1;

	while (countBottle > 0)
	{
		// рандом по х от 1 до ширина карты-1, чтобы не получать числа бордюра карты и монеты там не появлялись
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// то же самое и по игреку
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// если встретили символ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// то ставим туда монетку
			TileMap[randomElementY][randomElementX] = 'B';
			// создана монетка -> счётчик монет будет "текущий-1"
			countBottle --;
		}
	}
}

// бутылка с зельем
void randomBottleManaGenerate()
{
	// случайный элемент по горизонтали
	int randomElementX = 0;
	// случайный элемент по вертикали
	int randomElementY = 0;
	// сам рандом
	srand(time(0));
	// количество монет 1
	int countBottleMana = 1;

	while (countBottleMana > 0)
	{
		// рандом по х от 1 до ширина карты-1, чтобы не получать числа бордюра карты и монеты там не появлялись
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// то же самое и по игреку
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// если встретили символ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// то ставим туда монетку
			TileMap[randomElementY][randomElementX] = 'M';
			// создана монетка -> счётчик монет будет "текущий-1"
			countBottleMana --;
		}
	}
}

// зомбирующий инопланетянин
void randomAlienGenerate()
{
	// случайный элемент по горизонтали
	int randomElementX = 0;
	// случайный элемент по вертикали
	int randomElementY = 0;
	// сам рандом
	srand(time(0));
	// количество монет 1
	int countAlien = 1;

	while (countAlien > 0)
	{
		// рандом по х от 1 до ширина карты-1, чтобы не получать числа бордюра карты и монеты там не появлялись
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// то же самое и по игреку
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// если встретили символ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// то ставим туда монетку
			TileMap[randomElementY][randomElementX] = 'A';
			// создана монетка -> счётчик монет будет "текущий-1"
			countAlien --;
		}
	}
}

// хороший мухомор
void randomGoodMushroomGenerate()
{
	// случайный элемент по горизонтали
	int randomElementX = 0;
	// случайный элемент по вертикали
	int randomElementY = 0;
	// сам рандом
	srand(time(0));
	// количество монет 1
	int countGoodMushroom = 1;

	while (countGoodMushroom > 0)
	{
		// рандом по х от 1 до ширина карты-1, чтобы не получать числа бордюра карты и монеты там не появлялись
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// то же самое и по игреку
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// если встретили символ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// то ставим туда монетку
			TileMap[randomElementY][randomElementX] = 'Y';
			// создана монетка -> счётчик монет будет "текущий-1"
			countGoodMushroom --;
		}
	}
}

// плохой мухомор
void randomBadMushroomGenerate()
{
	// случайный элемент по горизонтали
	int randomElementX = 0;
	// случайный элемент по вертикали
	int randomElementY = 0;
	// сам рандом
	srand(time(0));
	// количество монет 1
	int countBadMushroom = 1;

	while (countBadMushroom > 0)
	{
		// рандом по х от 1 до ширина карты-1, чтобы не получать числа бордюра карты и монеты там не появлялись
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// то же самое и по игреку
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// если встретили символ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// то ставим туда монетку
			TileMap[randomElementY][randomElementX] = 'X';
			// создана монетка -> счётчик монет будет "текущий-1"
			countBadMushroom --;
		}
	}
}

// камень
void randomStoneGenerate()
{
	// случайный элемент по горизонтали
	int randomElementX = 0;
	// случайный элемент по вертикали
	int randomElementY = 0;
	// сам рандом
	srand(time(0));
	// количество монет 1
	int countStone = 1;

	while (countStone > 0)
	{
		// рандом по х от 1 до ширина карты-1, чтобы не получать числа бордюра карты и монеты там не появлялись
		randomElementX = 3 + rand() % (WIDTH_MAP - 6);
		// то же самое и по игреку
		randomElementY = 3 + rand() % (HEIGHT_MAP - 6);

		// если встретили символ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// то ставим туда монетку
			TileMap[randomElementY][randomElementX] = 'S';
			// создана монетка -> счётчик монет будет "текущий-1"
			countStone --;
		}
	}
}

// перец
void randomPepperGenerate()
{
	// случайный элемент по горизонтали
	int randomElementX = 0;
	// случайный элемент по вертикали
	int randomElementY = 0;
	// сам рандом
	srand(time(0));
	// количество монет 1
	int countPepper = 1;

	while (countPepper > 0)
	{
		// рандом по х от 1 до ширина карты-1, чтобы не получать числа бордюра карты и монеты там не появлялись
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// то же самое и по игреку
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// если встретили символ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// то ставим туда монетку
			TileMap[randomElementY][randomElementX] = 'P';
			// создана монетка -> счётчик монет будет "текущий-1"
			countPepper --;
		}
	}
}

// сундук с драгоценностями
void randomChestGenerate()
{
	int randomElementX = 0;
	int randomElementY = 0;

	srand(time(0));

	int countChest = 1;

	while (countChest > 0)
	{
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 'T';
			countChest --;
		}
	}
}

// ключ для сундука
void randomKeyGenerate()
{
	int randomElementX = 0;
	int randomElementY = 0;

	srand(time(0));

	int countKey = 1;

	while (countKey > 0)
	{
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 'K';
			countKey --;
		}
	}

}

// речной рак
void randomCrayfishGenerate()
{
	int randomElementX = 0;
	int randomElementY = 0;

	srand(time(0));

	int countCrayfish = 1;

	while (countCrayfish > 0)
	{
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 'L';
			countCrayfish --;
		}
	}

}

// газонокосилка
void randomMowerGenerate()
{
	int randomElementX = 0;
	int randomElementY = 0;

	srand(time(0));

	int countMower = 1;

	while (countMower > 0)
	{
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 'W';
			countMower --;
		}
	}

}
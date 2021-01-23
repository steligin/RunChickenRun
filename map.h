#include <SFML/Graphics.hpp>

const int HEIGHT_MAP = 30; // ������� ����� � ������ �� 32�32
const int WIDTH_MAP = 40;

sf::String TileMap[HEIGHT_MAP] = // ������ �����, ������������ �����
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

// �������� ������������� ������� �� �����

void randomCoinGenerate() // ������� +1
{
	// ��������� ������� �� �����������
	int randomElementX = 0;
	// ��������� ������� �� ���������
	int randomElementY = 0;
	// ��� ������
	srand(time(0));
	// ���������� (�������) ����� 1
	int countCoin = 1;

	while (countCoin > 0)
	{
		// ������ �� � �� 1 �� ������ �����-1, ����� �� �������� ����� ������� ����� � ������ ��� �� ����������
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// �� �� ����� � �� ������
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// ���� ��������� ������ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// �� ������ ���� �������
			TileMap[randomElementY][randomElementX] = 'C';
			// ������� ������� -> ������� ����� ����� "�������-1"
			countCoin --;
		}
	}

}

void randomCoin5Generate() // ������� +5
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

void randomCoin10Generate() // ������� +10
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

void randomHeartGenerate() // ��������
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

void randomThornGenerate() // �������
{
	// ��������� ������� �� �����������
	int randomElementX = 0;
	// ��������� ������� �� ���������
	int randomElementY = 0;
	// ��� ������
	srand(time(0));
	// ���������� ����� 1
	int countThorn = 1;

	while (countThorn > 0)
	{
		// ������ �� � �� 1 �� ������ �����-1, ����� �� �������� ����� ������� ����� � ������ ��� �� ����������
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// �� �� ����� � �� ������
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// ���� ��������� ������ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// �� ������ ���� �������
			TileMap[randomElementY][randomElementX] = 'F';
			// ������� ������� -> ������� ����� ����� "�������-1"
			countThorn --;
		}
	}
}

// ������� � ������
void randomBottleGenerate()
{
	// ��������� ������� �� �����������
	int randomElementX = 0;
	// ��������� ������� �� ���������
	int randomElementY = 0;
	// ��� ������
	srand(time(0));
	// ���������� ����� 1
	int countBottle = 1;

	while (countBottle > 0)
	{
		// ������ �� � �� 1 �� ������ �����-1, ����� �� �������� ����� ������� ����� � ������ ��� �� ����������
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// �� �� ����� � �� ������
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// ���� ��������� ������ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// �� ������ ���� �������
			TileMap[randomElementY][randomElementX] = 'B';
			// ������� ������� -> ������� ����� ����� "�������-1"
			countBottle --;
		}
	}
}

// ������� � ������
void randomBottleManaGenerate()
{
	// ��������� ������� �� �����������
	int randomElementX = 0;
	// ��������� ������� �� ���������
	int randomElementY = 0;
	// ��� ������
	srand(time(0));
	// ���������� ����� 1
	int countBottleMana = 1;

	while (countBottleMana > 0)
	{
		// ������ �� � �� 1 �� ������ �����-1, ����� �� �������� ����� ������� ����� � ������ ��� �� ����������
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// �� �� ����� � �� ������
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// ���� ��������� ������ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// �� ������ ���� �������
			TileMap[randomElementY][randomElementX] = 'M';
			// ������� ������� -> ������� ����� ����� "�������-1"
			countBottleMana --;
		}
	}
}

// ����������� �������������
void randomAlienGenerate()
{
	// ��������� ������� �� �����������
	int randomElementX = 0;
	// ��������� ������� �� ���������
	int randomElementY = 0;
	// ��� ������
	srand(time(0));
	// ���������� ����� 1
	int countAlien = 1;

	while (countAlien > 0)
	{
		// ������ �� � �� 1 �� ������ �����-1, ����� �� �������� ����� ������� ����� � ������ ��� �� ����������
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// �� �� ����� � �� ������
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// ���� ��������� ������ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// �� ������ ���� �������
			TileMap[randomElementY][randomElementX] = 'A';
			// ������� ������� -> ������� ����� ����� "�������-1"
			countAlien --;
		}
	}
}

// ������� �������
void randomGoodMushroomGenerate()
{
	// ��������� ������� �� �����������
	int randomElementX = 0;
	// ��������� ������� �� ���������
	int randomElementY = 0;
	// ��� ������
	srand(time(0));
	// ���������� ����� 1
	int countGoodMushroom = 1;

	while (countGoodMushroom > 0)
	{
		// ������ �� � �� 1 �� ������ �����-1, ����� �� �������� ����� ������� ����� � ������ ��� �� ����������
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// �� �� ����� � �� ������
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// ���� ��������� ������ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// �� ������ ���� �������
			TileMap[randomElementY][randomElementX] = 'Y';
			// ������� ������� -> ������� ����� ����� "�������-1"
			countGoodMushroom --;
		}
	}
}

// ������ �������
void randomBadMushroomGenerate()
{
	// ��������� ������� �� �����������
	int randomElementX = 0;
	// ��������� ������� �� ���������
	int randomElementY = 0;
	// ��� ������
	srand(time(0));
	// ���������� ����� 1
	int countBadMushroom = 1;

	while (countBadMushroom > 0)
	{
		// ������ �� � �� 1 �� ������ �����-1, ����� �� �������� ����� ������� ����� � ������ ��� �� ����������
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// �� �� ����� � �� ������
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// ���� ��������� ������ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// �� ������ ���� �������
			TileMap[randomElementY][randomElementX] = 'X';
			// ������� ������� -> ������� ����� ����� "�������-1"
			countBadMushroom --;
		}
	}
}

// ������
void randomStoneGenerate()
{
	// ��������� ������� �� �����������
	int randomElementX = 0;
	// ��������� ������� �� ���������
	int randomElementY = 0;
	// ��� ������
	srand(time(0));
	// ���������� ����� 1
	int countStone = 1;

	while (countStone > 0)
	{
		// ������ �� � �� 1 �� ������ �����-1, ����� �� �������� ����� ������� ����� � ������ ��� �� ����������
		randomElementX = 3 + rand() % (WIDTH_MAP - 6);
		// �� �� ����� � �� ������
		randomElementY = 3 + rand() % (HEIGHT_MAP - 6);

		// ���� ��������� ������ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// �� ������ ���� �������
			TileMap[randomElementY][randomElementX] = 'S';
			// ������� ������� -> ������� ����� ����� "�������-1"
			countStone --;
		}
	}
}

// �����
void randomPepperGenerate()
{
	// ��������� ������� �� �����������
	int randomElementX = 0;
	// ��������� ������� �� ���������
	int randomElementY = 0;
	// ��� ������
	srand(time(0));
	// ���������� ����� 1
	int countPepper = 1;

	while (countPepper > 0)
	{
		// ������ �� � �� 1 �� ������ �����-1, ����� �� �������� ����� ������� ����� � ������ ��� �� ����������
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		// �� �� ����� � �� ������
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		// ���� ��������� ������ ' '
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			// �� ������ ���� �������
			TileMap[randomElementY][randomElementX] = 'P';
			// ������� ������� -> ������� ����� ����� "�������-1"
			countPepper --;
		}
	}
}

// ������ � ���������������
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

// ���� ��� �������
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

// ������ ���
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

// �������������
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
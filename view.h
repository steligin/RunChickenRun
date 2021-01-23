#include <SFML/Graphics.hpp>

sf::View view; // ������� ������ sfml "view", ������� �������� �������

sf::View setPlayerCoordinateForView(float x, float y) // ������� ��� ���������� ��������� ������ (�������� �� ����������)
{
	float tempX = x; float tempY = y; // ���������� ��������� ������ � �������� ��, ����� ������ ����
	/*
	// ��� ����� �=40 y=20 � ������ 640�480
	if (x < 320) tempX = 320; // ������� �� ���� ����� �������
	if (x > 960) tempX = 960; // ������� �� ���� ������ �������
	if (y < 240) tempY = 240; // ������� �� ���� ������� �������
	if (y > 400) tempY = 400; // ������� �� ���� ������ �������
	
	// ��� ����� �=40 y=30 � ������ 640�480
	if (x < 320) tempX = 320; 
	if (x > 960) tempX = 960;
	if (y < 240) tempY = 240;
	if (y > 720) tempY = 720;
	
	// ��� ����� �=40 y=30 � ������ 640�400
	if (x < 320) tempX = 320; 
	if (x > 960) tempX = 960;
	if (y < 200) tempY = 200;
	if (y > 680) tempY = 680;
	*/

	// ��� ����� �=40 y=30 � ������ 640�480 �� ������� ��������� 640�60
	if (x < 320) tempX = 320; 
	if (x > 960) tempX = 960;
	if (y < 180) tempY = 180;
	if (y > 720) tempY = 720;

	view.setCenter(tempX, tempY); // �������� �� ������� � �������� ��� ���������
	return view; // ����������� ������, ��� ��������� �
}

sf::View viewmap(float time) // ������� ��� ���������� �����
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // ���� ������ ������� D, �� ���������� ��������� ����� ������
	{
		view.move(0.2*time, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // ���� ������ ������� S, �� ���������� ��������� ����� ����
	{
		view.move(0, 0.2*time);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // ���� ������ ������� A, �� ���������� ��������� ����� �����
	{
		view.move(-0.2*time, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // ���� ������ ������� W, �� ���������� ��������� ����� �����
	{
		view.move(0, -0.2*time);
	}

	return view;// ����������� ������, ��� ��������� �
}

sf::View changeview() // ������� ����� ���� ������
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) // ���� ������ ������� U, �� ���������� ���������� �������� ����� (������ ����������)
	{
		view.zoom(1.005f);
		//view.zoom(1.0005f); �� �� ����� ���������
	}

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // ���� ������ ������� R, �� ���������� ������� ����� ������
	{
		view.rotate(0.05);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) // ���� ������ ������� T, �� ���������� ������� ����� ����� �� 90 ��������
	{
		view.setRotation(-90);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) // ���� ������ ������� I, �� ���������� ����������� ������ � ��������� ���
	{
		view.setSize(640,480);
	}

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) // ���� ������ ������� Q, �� ���������� ���������� ������ ��� ���� �� �����, ��� ����� ���� ������� ��� ���� ������ View � ��������� ���
	{
		view.setViewport(sf::FloatRect(0,0,0.5f,1));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		view.setSize(1280, 960);
	}

	return view; // ����������� ������, ��� ��������� �
}
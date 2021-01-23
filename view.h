#include <SFML/Graphics.hpp>

sf::View view; // объявим объект sfml "view", который является камерой

sf::View setPlayerCoordinateForView(float x, float y) // функция для считывания координат игрока (слежения за персонажем)
{
	float tempX = x; float tempY = y; // считывание координат игрока и проверка их, чтобы убрать края
	/*
	// для карты х=40 y=20 и камеры 640х480
	if (x < 320) tempX = 320; // убираем из вида левую сторону
	if (x > 960) tempX = 960; // убираем из вида правую сторону
	if (y < 240) tempY = 240; // убираем из вида верхнюю сторону
	if (y > 400) tempY = 400; // убираем из вида нижнюю сторону
	
	// для карты х=40 y=30 и камеры 640х480
	if (x < 320) tempX = 320; 
	if (x > 960) tempX = 960;
	if (y < 240) tempY = 240;
	if (y > 720) tempY = 720;
	
	// для карты х=40 y=30 и камеры 640х400
	if (x < 320) tempX = 320; 
	if (x > 960) tempX = 960;
	if (y < 200) tempY = 200;
	if (y > 680) tempY = 680;
	*/

	// для карты х=40 y=30 и камеры 640х480 со строкой состояния 640х60
	if (x < 320) tempX = 320; 
	if (x > 960) tempX = 960;
	if (y < 180) tempY = 180;
	if (y > 720) tempY = 720;

	view.setCenter(tempX, tempY); // слежение за игроком и передача его координат
	return view; // возвращение камеры, что обновляет её
}

sf::View viewmap(float time) // функция для скроллинга карты
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // если нажата клавиша D, то происходит скроллинг карты вправо
	{
		view.move(0.2*time, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // если нажата клавиша S, то происходит скроллинг карты вниз
	{
		view.move(0, 0.2*time);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // если нажата клавиша A, то происходит скроллинг карты влево
	{
		view.move(-0.2*time, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // если нажата клавиша W, то происходит скроллинг карты вверх
	{
		view.move(0, -0.2*time);
	}

	return view;// возвращение камеры, что обновляет её
}

sf::View changeview() // функция смена вида камеры
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) // если нажата клавиша U, то происходит уменьшение масштаба карты (камера отдаляется)
	{
		view.zoom(1.005f);
		//view.zoom(1.0005f); то же самое медленнее
	}

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // если нажата клавиша R, то происходит поворот карты вправо
	{
		view.rotate(0.05);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) // если нажата клавиша T, то происходит поворот карты влево на 90 градусов
	{
		view.setRotation(-90);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) // если нажата клавиша I, то происходит возвращение камеры в начальный вид
	{
		view.setSize(640,480);
	}

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) // если нажата клавиша Q, то происходит разделение экрана для игры на двоих, для этого надо создать ещё один объект View и привязать его
	{
		view.setViewport(sf::FloatRect(0,0,0.5f,1));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		view.setSize(1280, 960);
	}

	return view; // возвращение камеры, что обновляет её
}
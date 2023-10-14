#include <SFML/Graphics.hpp>

sf::View view;										//обьект сфмл-камера

sf::View GetPosit(const float x, const float y)		//функция для считывания координат игрока
{
	float tempX = x; float tempY = y;				//считываем координа игрока и проверяем их, чтоб убрать края
	if (x < 640) tempX = 640;						//убираем из вида левую сторону
	if (y < 340) tempY = 340;						//убираем верхнюю сторону
	if (y > 1920) tempY = 1920;						//нижнюю сторону
	if (x > 9850) tempX = 9850;						//нижнюю сторону
	view.setCenter(tempX, tempY);					//следим за игроком, передавая его координаты
	return view;									//возращаем нашу камеру, что обновляет ее
}


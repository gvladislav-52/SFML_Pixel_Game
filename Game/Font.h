#include <SFML/Graphics.hpp>


class Font_Text
{
private:
	sf::Font font;
	sf::Text text;
	sf::Color color;
	sf::Clock timer;
	int numer;
	int X;
	int Y;
public:
	Font_Text( int XY, int YY, std::string name = "", int num = 60, sf::Color color_main = sf::Color::White)
	{
		numer = num;
		color = color_main;
		font.loadFromFile("images/fontpi2.ttf");
		sf::Text text2 (name, font, num);
		text = text2;
		text.setColor(color_main);
		text.setStyle(sf::Text::Bold);
		X = XY;
		Y = YY;
	}

	sf::Text& GetText() { return text; }

	sf::Text& StringTextTime(int time)
	{
		std::ostringstream gameTimeStringMinut, gameTimeStringSecund;
		gameTimeStringMinut << (150 - time) / 60;									//вывод минут
		gameTimeStringSecund << (150 - time) % 60;								//вывод секунд
		if (((150 - time) % 60) < 10)
		{
			text.setString(gameTimeStringMinut.str() + ":0" + gameTimeStringSecund.str());
			text.setPosition(view.getCenter().x + X, view.getCenter().y + Y);
			return text;
		}
		else
		{
			text.setString(gameTimeStringMinut.str() + ":" + gameTimeStringSecund.str());
			text.setPosition(view.getCenter().x + X, view.getCenter().y + Y);
			return text;
		}
	}

	sf::Text& ResultTextTime(int time, int& ik, bool WIN)
	{
		std::ostringstream gameTimeStringMinut, gameTimeStringSecund;
		if (WIN == false)
		{
			gameTimeStringMinut << (time) / 60;									//вывод минут
			gameTimeStringSecund << (time) % 60;								//вывод секунд
			ik = time;
		}
		else
		{
			gameTimeStringMinut << (ik) / 60;									//вывод минут
			gameTimeStringSecund << (ik) % 60;
			if ((ik % 60) < 10)
			{
				text.setString(gameTimeStringMinut.str() + ":0" + gameTimeStringSecund.str());
				text.setPosition(view.getCenter().x + X, view.getCenter().y + Y);
				return text;
			}
			else
			{
				text.setString(gameTimeStringMinut.str() + ":" + gameTimeStringSecund.str());
				text.setPosition(view.getCenter().x + X, view.getCenter().y + Y);
				return text;
			}
		}
	}

	void SetXY(int XY, int YY)
	{
		X = XY;
		Y = YY;
	}

	sf::Text& TextWithCoordinate(sf::View& view)
	{
			text.setPosition(view.getCenter().x + X, view.getCenter().y + Y);
			return text;
	}

	sf::Text& StringTextFruit(int score)
	{
		std::ostringstream  FruitScore;
		FruitScore << score;
		text.setString(FruitScore.str());
		text.setPosition(view.getCenter().x + X, view.getCenter().y + Y);
		return text;
	}

};
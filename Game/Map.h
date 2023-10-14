#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int HEIGHT_MAP = 23;	
const int WIDTH_MAP = 110;

sf::String TileMap[HEIGHT_MAP] = {
	"                                      933333333333ooooooooooooooooooooooooooooooooooooooooooooooooooooooooo33",
	"                                       93333333334                                                         53",
	"                                        5333333334                                                         53",
	"0                                       5333333334       78                                       2111110  53",
	"s10                  211110             5333333334       gg             21110               211111z333334  53",
	"334                 2z33334     211110  5333333334       gg       211111z333s111111111111111z333333333334  53",
	"33s110             2z33333s11111z33334  5333333334       gg2111111z33333333333333333333333333333333333334  53",
	"33333s1111111111111z333333333333333334  933333333q       665333333333333333333333333333333333333333333334  53",
	"33333333333333333333333333333333333334   9o3333oq        665333333333333ooooooooooooooooooooooooooooooooq  53",
	"33333333333333333333333333333333333334     9ooq          66533333ooooooq                                   53",
	"3333333333333ooooo33333333333333333334              2111066533334                                          53",
	"3333333333334     9ooo333333333333333s1110       211z333466533334                                       211z3",
	"3333333333334         9ooo3333333333333334      2z333333s11z33334  211110    210     210     210    2111z3333",
	"333ooooo33334             9oo333333333333s111111z3333333333333334  533334    534     534     534    533333333",
	"3oq     9oooq                9ooo33333333333333333333333333333ooq  533334    534     534     534    533333333",
	"4                                933333333333333333333333koooq     533334    534     534     534    533333333",
	"4                                 9ooofoofoofoofoofoofoooq         533334    534     534     534    533333333",
	"4     2111111110                                                   533333111133311111333111113331111333333333",
	"311111z33333333s11110                                        211111z33333333333333333333333333333333333333333",
	"33333333333333333333s11111110                              21z33333333333333333333333333333333333333333333333",
	"3333333333333333333333333333s111111111t11t11t11t11t11t11111z3333333333333333333333333333333333333333333333333",
	"3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333",
	"3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333",
};

class Map
{
private:
	std::string File;						//файл с расширением
	sf::Image image;						//сфмл изображение
	sf::Texture texture;					//сфмл текстура
	sf::Sprite sprite;						//сфмл спрайт
	int X;
	int Y;
	bool chose;
public:

	Map(std::string F, bool yes = false, int XY = 0, int YY = 0, sf::Color color = sf::Color::White)
	{
		File = F;
		image.loadFromFile("images/" + File);		//запихиваем в image наше изображение, вместо File мы передаем то, что пропишем при создании обьекта.
		texture.loadFromImage(image);						//закижываем изображение в текстуру
		sprite.setTexture(texture);							//заливаем спрайт текстурой
		sprite.setOrigin(72 / 2, 72 / 2);
		X = XY;
		Y = YY;
		chose = yes;
		sprite.setColor(color);
	}

	void SetXY(int XY, int YY)
	{
		X = XY;
		Y = YY;
	}
	sf::Sprite& GetSprite() { return sprite; }
	sf::Sprite& ImageWithCoordinate(sf::View& view)
	{
		if (chose)
		{
			sprite.setPosition(view.getCenter().x + X, view.getCenter().y + Y);
			return sprite;
		}
		else
		{
			sprite.setPosition(X, Y);
			return sprite;
		}
	}

	void health_point(const int health)
	{
		if (health == 3)
		{
			image.loadFromFile("images/hel.png");
			texture.loadFromImage(image);						
			sprite.setTexture(texture);
		}
		else if (health == 2)
		{
			image.loadFromFile("images/hel2.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
		else if (health == 1)
		{
			image.loadFromFile("images/hel3.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
		else
		{
			image.loadFromFile("images/hel5.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
	}

	void StarScore(int score)
	{
		if (score == 3)
		{
			image.loadFromFile("images/starpoint3.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
		else if (score == 2)
		{
			image.loadFromFile("images/starpoint2.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
		else if (score == 1)
		{
			image.loadFromFile("images/starpoint.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
		else
		{
			image.loadFromFile("images/starpoint0.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
	}

	void getTextMisson(int time,float x, float y)
	{
		if ((x > 730)&&(time < 10))
		{
		image.loadFromFile("images/quest.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		}
		else if ((time > 10) && (time < 15))
		{
		image.loadFromFile("images/quest1.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		}
		else if ((x > 4706 && x < 5300) && (y> 700 && y < 1200))
		{
			image.loadFromFile("images/quest2.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
		else if ((x > 5733 && x < 7000) && (y > 250 && y < 600))
		{
			image.loadFromFile("images/quest3.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
		else 
		{
			image.loadFromFile("images/quest0.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
	}

	void drawMap(sf::RenderWindow& window) {
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ') GetSprite().setTextureRect(sf::IntRect(0, 0, 96, 96));    //пустота
				if (TileMap[i][j] == '0') GetSprite().setTextureRect(sf::IntRect(96, 0, 96, 96));    //правый угол травы
				if (TileMap[i][j] == '6') GetSprite().setTextureRect(sf::IntRect(192, 0, 96, 96));    //трава центр
				if (TileMap[i][j] == '2') GetSprite().setTextureRect(sf::IntRect(288, 0, 96, 96));    //левый угол травы
				if (TileMap[i][j] == '3') GetSprite().setTextureRect(sf::IntRect(384, 0, 96, 96));    //земля
				if (TileMap[i][j] == '4') GetSprite().setTextureRect(sf::IntRect(480, 0, 96, 96));    //правая стенка земли
				if (TileMap[i][j] == '5') GetSprite().setTextureRect(sf::IntRect(576, 0, 96, 96));    //левая стенка земли
				if (TileMap[i][j] == '1') GetSprite().setTextureRect(sf::IntRect(672, 0, 96, 96));    //трава центр
				if (TileMap[i][j] == '7') GetSprite().setTextureRect(sf::IntRect(768, 0, 96, 96));    //трава центр
				if (TileMap[i][j] == '8') GetSprite().setTextureRect(sf::IntRect(864, 0, 96, 96));    //трава центр
				if (TileMap[i][j] == '9') GetSprite().setTextureRect(sf::IntRect(960, 0, 96, 96));    //трава центр
				if (TileMap[i][j] == 'q') GetSprite().setTextureRect(sf::IntRect(1056, 0, 96, 96));    //трава центр
				if (TileMap[i][j] == 'o') GetSprite().setTextureRect(sf::IntRect(1152, 0, 96, 96));    //трава центр
				if (TileMap[i][j] == 'g') GetSprite().setTextureRect(sf::IntRect(192, 0, 96, 96));    //трава центр
				if (TileMap[i][j] == 'i') GetSprite().setTextureRect(sf::IntRect(1248, 0, 96, 96));    //трава центр
				if (TileMap[i][j] == 't') GetSprite().setTextureRect(sf::IntRect(1344, 0, 96, 96));    //трава центр
				if (TileMap[i][j] == 'f') GetSprite().setTextureRect(sf::IntRect(1440, 0, 96, 96));    //трава центр
				if (TileMap[i][j] == 'z') GetSprite().setTextureRect(sf::IntRect(1536, 0, 96, 96));    //трава центр
				if (TileMap[i][j] == 's') GetSprite().setTextureRect(sf::IntRect(1632, 0, 96, 96));    //трава центр
				GetSprite().setPosition(j * 96, i * 96);                        //обрисока изображений по координатам
				window.draw(GetSprite());                                //рисовка карты
			}
	}

};

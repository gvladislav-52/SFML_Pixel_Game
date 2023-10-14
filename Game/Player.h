#ifndef PLAYER_H_
#define PLAYER_H_
#include <SFML/Graphics.hpp>

class Entity
{
protected:
	std::string File;						//���� � �����������
	sf::Image image;						//���� �����������
	sf::Texture texture;					//���� ��������
	sf::Sprite sprite;						//���� ������
	std::string name;
	float x, y, dx, dy, speed;	//���������� ������ �� � � �, ������ � ������, ��������� (�� � � �� �), ���� ��������
	int w, h;
	int health;								//������ ���-�� ������
	int time;								//�������� �������
	int timeWin;
	bool life;								//���������� ���������� ��� ��� �����
	bool onGround;
	float CurrentFrame;
public:
	Entity(std::string F, float X, float Y, int W, int H, std::string Name)
	{
		CurrentFrame = 0;
		File = F;
		image.loadFromFile("images/" + File);
		x = X; y = Y; w = W; h = H; name = Name; time = 0;
		speed = 0; health = 1; dx = 0; dy = 0;
		life = true; onGround = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
	std::string GetName() const { return name; }
	float GetXforView() const { return x; }
	float GetYforView() const { return y; }
	int GetHealth() const { return health; }

	int& GetTime() { return time; }
	int& GetTimeWin() { return timeWin; }
	float& GetX() { return x; }
	float& GetY() { return y; }
	int& GetW() { return w; }
	int& GetH() { return h; }
	float& GetSpeed() { return speed; }
	bool& GetLife() { return life; }

	sf::Sprite& GetSprite() { return sprite; }
	float GetDy() { return dy; }
	float GetDx() { return dx; }
};

class Platform : public Entity
{
public:
	Platform(std::string F, float X, float Y, int W, int H, std::string Name) :Entity(F, X, Y, W, H, Name)
	{
		sprite.setTextureRect(sf::IntRect(0, 0, w, h));
		if (name == "Platform")
			dx = 0.1;
	}

	void interactive_func(float Dx, float Dy, sf::String TileMap[])					//������� �������������� � ������
	{
		for (int i = y / 96; i < (y + h) / 96; i++)
			for (int j = x / 96; j < (x + w) / 96; j++)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == '1' || TileMap[i][j] == '2' || TileMap[i][j] == '3' || TileMap[i][j] == '4' || TileMap[i][j] == '5')				//���� ��������� ������������ 0, �� ��������� ��� ���
				{
					if (Dy > 0) { y = i * 96 - h; }
					if (Dy < 0) { y = i * 96 + 96; }
					if (Dx > 0) { x = j * 96 - w; dx = -0.1; }
					if (Dx < 0) { x = j * 96 + 96; dx = 0.1; }
				}
			}
	}

	void update(float time, sf::String TileMap[])
	{
		if (name == "Platform")
		{
		interactive_func(dx, 0, TileMap);
		x += dx * time;
		sprite.setPosition(x + w / 3, y + h / 3);
		}

		if (name == "Port")
		{
			sprite.setPosition(x + w / 3, y + h / 3);
			CurrentFrame += 0.0045 * time;																	//����� �������� ������� �� �������
			if (CurrentFrame > 3) CurrentFrame -= 3;														//����� �������� ��� ������
			GetSprite().setTextureRect(sf::IntRect(72 * int(CurrentFrame), 0, 72, 144));
		}

		if (name == "Door")
		{
			sprite.setPosition(x + w / 2, y + h / 2);
		}
	}

	void StarImage(const int StarScore)
	{
		if (StarScore == 3)
		{
			image.loadFromFile("images/door3.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
		else if (StarScore == 2)
		{
			image.loadFromFile("images/door2.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
		else if (StarScore == 1)
		{
			image.loadFromFile("images/door1.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
		else
		{
			image.loadFromFile("images/door.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}
	}
};

class Enemy :public Entity
{
public:
	sf::Sprite& GetSpriteEnemy() { return sprite; }

	Enemy(std::string F, float X, float Y, int W, int H, std::string Name) :Entity(F, X, Y, W, H, Name)
	{
			sprite.setTextureRect(sf::IntRect(0, 0, w, h));
			if (name == "EasyEnemy")
				dx = 0.1;
			if (name == "Pila")
				dy = 0.1;
	}

	void interactive_func(float Dx, float Dy, sf::String TileMap[])					//������� �������������� � ������
	{
		for (int i = y / 96; i < (y + h) / 96; i++)
			for (int j = x / 96; j < (x + w) / 96; j++)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == '1' || TileMap[i][j] == '2' || TileMap[i][j] == '3' || TileMap[i][j] == '4' || TileMap[i][j] == '5' || TileMap[i][j] == 't' || TileMap[i][j] == 'f')				//���� ��������� ������������ 0, �� ��������� ��� ���
				{
					if (Dy > 0) { y = i * 96 - h;}
					if (Dy < 0) { y = i * 96 + 96;}
					if (Dx > 0) { x = j * 96 - w; dx = -0.1; sprite.scale(-1, 1); }
					if (Dx < 0) { x = j * 96 + 96; dx = 0.1; sprite.scale(-1, 1); }
				}
			}
	}

	void interactive_func_Y(float Dx, float Dy, sf::String TileMap[])					//������� �������������� � ������
	{
		for (int i = y / 96; i < (y + h) / 96; i++)
			for (int j = x / 96; j < (x + w) / 96; j++)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == '1' || TileMap[i][j] == '2' || TileMap[i][j] == '3' || TileMap[i][j] == '4' || TileMap[i][j] == '5' || TileMap[i][j] == 't' || TileMap[i][j] == 'f')				//���� ��������� ������������ 0, �� ��������� ��� ���
				{
					if (Dy > 0) { y = i * 96 - h; dy = -0.1;}
					if (Dy < 0) { y = i * 96 + 96; dy = 0.1;}
					if (Dx > 0) { x = j * 96 - w; }
					if (Dx < 0) { x = j * 96 + 96; }
				}
			}
	}

	void update(float time, sf::String TileMap[])					//������� "���������" ������� ������.
	{
		if (name == "EasyEnemy")
		{
			interactive_func(dx, 0, TileMap);
			x += dx * time;
			sprite.setPosition(x+w/3, y+h/3);
			CurrentFrame += 0.0045 * time;																	//����� �������� ������� �� �������
			if (CurrentFrame > 7) CurrentFrame -= 7;														//����� �������� ��� ������
			GetSprite().setTextureRect(sf::IntRect(144 * int(CurrentFrame), 0, 144, 72));
		}

		if (name == "Pila")
		{
			interactive_func_Y(0, dy, TileMap);
			y += dy * time;
			sprite.setPosition(x, y);
			CurrentFrame += 0.0045 * time;																	//����� �������� ������� �� �������
			if (CurrentFrame > 3) CurrentFrame -= 3;														//����� �������� ��� ������
			GetSprite().setTextureRect(sf::IntRect(72 * int(CurrentFrame), 0, 72, 144));
		}

		if (name == "Flower")
		{
			sprite.setPosition(x + w / 3, y + h / 3);
			CurrentFrame += 0.0045 * time;																	//����� �������� ������� �� �������
			if (CurrentFrame > 4) CurrentFrame -= 4;														//����� �������� ��� ������
			GetSprite().setTextureRect(sf::IntRect(185 * int(CurrentFrame), 0, 185, 272));
		}
	}
};

class Fruit :public Entity
{
public:
	Fruit(std::string F, float X, float Y, int W, int H, std::string Name) :Entity(F, X, Y, W, H, Name)
	{
			sprite.setTextureRect(sf::IntRect(0, 0, w, h));
	}

	void update(float time)
	{
			sprite.setPosition(x + w / 3, y + h / 3);
		if (name == "Banana" || name == "Kiwi")
		{
			CurrentFrame += 0.0025 * time;																	//����� �������� ������� �� �������
			if (CurrentFrame > 7) CurrentFrame -= 7;														//����� �������� ��� ������
			GetSprite().setTextureRect(sf::IntRect(54 * int(CurrentFrame), 0, 54, 54));
		}
	}
};

class Player :public Entity
{
private:
	bool isWin;
	bool JumpKill;
	int dir;
	int FruitScore;
	int StarScore;
public:
	Player(std::string F, float X, float Y, int W, int H, std::string Name) :Entity(F, X, Y, W, H, Name)
	{
		isWin = false;
		JumpKill = true;
		StarScore = 0;
		FruitScore = 0;
		health = 3;
		dir = 0;
		if (name == "Player1")
		{
			sprite.setTextureRect(sf::IntRect(w, h, w, h));
		}
	}

	int& GetDir() { return dir; }
	bool& GetIsWin() { return isWin; }
	int GetStarScore() const { return StarScore; }

	bool checkCollision(Enemy &enemy) {
		sf::FloatRect playerBounds = sprite.getGlobalBounds();
		sf::FloatRect enemyBounds = enemy.GetSpriteEnemy().getGlobalBounds();
		if (playerBounds.intersects(enemyBounds)) {
			return true;
		}
		return false;
	}

	bool checkCollision(Fruit &fruit) {
		sf::FloatRect playerBounds = sprite.getGlobalBounds();
		sf::FloatRect fruitBounds = fruit.GetSprite().getGlobalBounds();
		if (playerBounds.intersects(fruitBounds)) {
			return true;
		}
		return false;
	}

	bool checkCollision(Platform &plat) {
		sf::FloatRect playerBounds = sprite.getGlobalBounds();
		sf::FloatRect platBounds = plat.GetSprite().getGlobalBounds();
		if (playerBounds.intersects(platBounds)) {
			return true;
		}
		return false;
	}

	void update(float time, sf::String TileMap[])					//������� "���������" ������� ������.
	{
		control(time);
		switch (dir)											//��������� ��������� � ����������� ������� �������
		{
		case 0: dx = speed;  break;						//�� ���� ������ ��������, �� ������ �������� - �������� ������
		case 1: dx = -speed;  break;						//�� ���� ������ �������� ��������, �� ������ �������� - �������� �����
		case 2: break;
		}
		// ��������, ������� ��������� ��������� �������, � �� ������������� �������������� ��
		x += dx * time;
		interactive_func(dx, 0, TileMap);
		y += dy * time;
		interactive_func(0, dy, TileMap);

		speed = 0;												//�������� ��������, ��� ���������, ����� ������ ������
		sprite.setPosition(x, y);								//������� ��������� �� ������ �� ������ ������������ �����������
		if (health <= 0) { life = false; }						//���� ������ ��� - ������.
		dy = dy + 0.0015 * time;
	}

	void interactive_func(float Dx, float Dy, sf::String TileMap[])					//������� �������������� � ������
	{
		for (int i = y / 96; i < (y + h) / 96; i++)
			for (int j = x / 96; j < (x + w) / 96; j++)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == '1' || TileMap[i][j] == '2' || TileMap[i][j] == '3' || TileMap[i][j] == '4' ||
					TileMap[i][j] == '5'  || TileMap[i][j] == '9' || TileMap[i][j] == 'q' || TileMap[i][j] == 'o' ||
					TileMap[i][j] == 'i' || TileMap[i][j] == 't' || TileMap[i][j] == 'f')				//���� ��������� ������������ 0, �� ��������� ��� ���
				{
					if (Dy > 0) { y = i * 96 - h; dy = 0; onGround = true; }
					if (Dy < 0) { y = i * 96 + 96; dy = 0; }
					if (Dx > 0) { x = j * 96 - w; dy = dy + 0.00075 * time; }
					if (Dx < 0) { x = j * 96 + 96; dy = dy + 0.0075 * time; }
				}

				if (TileMap[i][j] == '6')
				{
					dy = dy - 0.00025*time;
				}
			}
	}

	void takeDamage() {
		health -= 1; // ���������� �������� �� 1
	}

	void  jump()
	{
		dy = -0.8;
	}

	int GetFruitScore() const { return FruitScore; }

	void control(float time)
	{

		if (GetLife())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	//�������� �����
			{
				dir = 1;																		//����������� switch
				speed = 0.2;																	//�������� ��������
				CurrentFrame += 0.0075 * time;																	//����� �������� ������� �� �������
				if (CurrentFrame > 5) CurrentFrame -= 5;														//����� �������� ��� ������
				GetSprite().setTextureRect(sf::IntRect(72 * int(CurrentFrame), 0, 72, 72));	//����������� �������� ��������
			}
			else GetSprite().setTextureRect(sf::IntRect(0, 72, 72, 72));

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 	//�������� ������
			{
				dir = 0;																		 //����������� switch
				speed = 0.2;																   	 //�������� ��������
				CurrentFrame += 0.0075 * time;		                                                             //����� �������� ������� �� �������
				if (CurrentFrame > 5) CurrentFrame -= 5;														 //����� �������� ��� ������
				GetSprite().setTextureRect(sf::IntRect(72 * int(CurrentFrame), 72, 72, 72)); //����������� �������� ��������
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (onGround))
			{
				dir = 2;
				dy = -0.6;
				onGround = false;
			}
		}
	}

	bool checkFruit(std::vector<Fruit>& fruit)
	{
		for (int i = 0; i < fruit.size(); i++)
		{
			if (checkCollision(fruit[i]) && ((fruit[i].GetName() == "Banana") || (fruit[i].GetName() == "Kiwi")))
			{
				fruit.erase(fruit.begin() + i);
				FruitScore++;
				return true;
			}

			if (checkCollision(fruit[i]) && (fruit[i].GetName() == "Star"))
			{
				fruit.erase(fruit.begin() + i);
				StarScore++;
				return true;
			}
		}
			return false;
	}

	int checkEnemy(std::vector<Enemy>& enemy, sf::Clock &timer)
	{
		for (int i = 0; i < enemy.size(); i++) {
			if (checkCollision(enemy[i]))
			{
				if ((GetSprite().getPosition().y < enemy[i].GetSprite().getPosition().y)&& enemy[i].GetName() == "EasyEnemy")	//������� �����, ���� ������ �� ������
				{
					if ((timer.getElapsedTime().asSeconds() >= 0.5)&& !JumpKill)
					{
						JumpKill = true;
						timer.restart();
					}
					if (JumpKill)
					{
						enemy.erase(enemy.begin() + i);
						jump();
						return 0;
					}
				}
				else if ((GetSprite().getPosition().x < enemy[i].GetSprite().getPosition().x)&& enemy[i].GetName() != "Port")	//�������� ����, ���� ��������� ����� �����
				{
					if (timer.getElapsedTime().asSeconds() >= 1.f)
					{
						if (enemy[i].GetName() == "EasyEnemy")
						{
						jump();
						JumpKill = false;
						}
						if (enemy[i].GetName() == "Pila")
						{
							dy = -0.5;
						}
						if (enemy[i].GetName() == "Flower")
						{
							health = 0;
							GetLife() = false;
						}
						takeDamage();
						timer.restart();
					}
					return 1;
				}
				else																							//�������� ����, ���� ��������� ������ �����.
				{
					if ((timer.getElapsedTime().asSeconds() >= 1.f) && enemy[i].GetName() != "Port")
					{
						if (enemy[i].GetName() == "EasyEnemy")
						{
							jump();
							JumpKill = false;
						}
						if (enemy[i].GetName() == "Pila")
						{
							dy = -0.5;
						}
						if (enemy[i].GetName() == "Flower")
						{
							health = 0;
							GetLife() = false;
						}
						
						takeDamage();
						timer.restart();
					}
					return 1;
				}
			}
		}
		return 2;
	}

	void checkPlatform(std::vector<Platform>& plat)
	{
		for (int i = 0; i < plat.size(); i++)
		{
			if (checkCollision(plat[i]) && (plat[i].GetName() == "Platform"))
			{
				if ((GetDy() > 0) || (onGround = false))
					if (GetY() + GetH() < plat[i].GetY() + plat[i].GetH())
					{
						GetX() += plat[i].GetDx()*10;
						dy = 0;
						onGround = true;
					}
			}

			if (checkCollision(plat[i]) && (plat[i].GetName() == "Door") && (StarScore < 3))
			{
				if (GetX() < plat[i].GetX())
				{
					GetX() -= 4; 
				}
				else 
				{
					GetX() += 4;
				}
			}

			if (checkCollision(plat[i]) && (plat[i].GetName() == "Door") && (StarScore == 3))
			{
				plat.erase(plat.begin() + i);
			}

			if (checkCollision(plat[i]) && plat[i].GetName() == "Port")
			{
				isWin = true;
			}
		}
	}

	void changeColor(std::string F)
	{
		File = F;
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
};


#endif
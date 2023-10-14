#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Map.h"
#include "View.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include "Font.h"
#include "Sound.h"

void SetColor(std::vector<Font_Text>& font_dead, std::vector<Font_Text>& font_start, std::vector<Font_Text>& exit, std::vector<Map>& menu_map_list, std::vector<Map>& button_list, std::vector<Map>& menu_playing_list)
{
	//функция изменения цвета панелек на белый
	font_dead[1].GetText().setColor(sf::Color::White);
	button_list[0].GetSprite().setColor(sf::Color::Black);
	button_list[1].GetSprite().setColor(sf::Color::Black);
	font_start[1].GetText().setColor(sf::Color::White);
	exit[1].GetText().setColor(sf::Color::White);
	menu_map_list[2].GetSprite().setColor(sf::Color::White);
	menu_map_list[3].GetSprite().setColor(sf::Color::White);
	menu_map_list[4].GetSprite().setColor(sf::Color::White);
	menu_playing_list[7].GetSprite().setColor(sf::Color::White);
}
void Colision_Function(std::vector<Enemy>& enemy_list, std::vector<Fruit>& fruit_list, std::vector<Platform>& platform_list, Player& Player_hero, std::vector<SoundBar>& sounds, sf::Clock& timer)
{
	//функция проверки колиззии с обьектами и издаваемым звуком
	if (Player_hero.GetDir() == 2) { sounds[3].playSound(); Player_hero.GetDir() = 3; }
	if (Player_hero.checkEnemy(enemy_list, timer) == 0) sounds[1].playSound();
	else if (Player_hero.checkEnemy(enemy_list, timer) == 1) sounds[2].playSound();
	if (Player_hero.checkFruit(fruit_list)) sounds[0].playSound();		//функция по сбору бананов
	Player_hero.checkPlatform(platform_list);
}
void Update_Function(std::vector<Enemy>& enemy_list, std::vector<Fruit>& fruit_list, std::vector<Platform>& platform_list, Player& Player_hero, float &time, sf::String TileMap[])
{
	//функция обновления всех обьектов
	Player_hero.update(time, TileMap);
	//std::cout << Player_hero.GetX() << ", " << Player_hero.GetY() << std::endl;
	for (int i = 0; i < size(enemy_list); i++)
		enemy_list[i].update(time, TileMap);
	for (int i = 0; i < size(fruit_list); i++)
		fruit_list[i].update(time);//обновление врага
	for (int i = 0; i < size(platform_list); i++)
		platform_list[i].update(time, TileMap);//обновление врага
}
void Menu_Function(sf::RenderWindow& window, std::vector<Map>& menu_map_list, std::vector<Map>& button_list, std::vector<Font_Text>& font_start, std::vector<Font_Text>& exit)
{
	//функция вывода на экран начального меню
	button_list[0].SetXY(-115, -13);
	button_list[1].SetXY(-115, 68);
	font_start[0].SetXY(-45, -66);
	font_start[1].SetXY(-48, -68);
	exit[0].SetXY(-37, 13);
	exit[1].SetXY(-40, 11);
	if (sf::IntRect(490, 360, 295, 58).contains(sf::Mouse::getPosition(window))) { font_start[1].GetText().setColor(sf::Color::Blue); button_list[0].GetSprite().setColor(sf::Color::Blue); }
	if (sf::IntRect(490, 440, 295, 58).contains(sf::Mouse::getPosition(window))) { exit[1].GetText().setColor(sf::Color::Blue); button_list[1].GetSprite().setColor(sf::Color::Blue); }
	if (sf::IntRect(105, 320, 206, 234).contains(sf::Mouse::getPosition(window))) { menu_map_list[3].GetSprite().setColor(sf::Color::Blue); }
	if (sf::IntRect(965, 35, 206, 234).contains(sf::Mouse::getPosition(window))) { menu_map_list[4].GetSprite().setColor(sf::Color::Blue); }
	window.clear();
	for (int i = 0; i < size(menu_map_list); i++)
		window.draw(menu_map_list[i].ImageWithCoordinate(view));
	for (int i = 0; i < size(button_list); i++)
		window.draw(button_list[i].ImageWithCoordinate(view));
	for (int i = 0; i < size(font_start); i++)
		window.draw(font_start[i].TextWithCoordinate(view));
	for (int i = 0; i < size(exit); i++)
		window.draw(exit[i].TextWithCoordinate(view));
	window.display();
}
void Playing_Function(sf::RenderWindow& window, std::vector<Map>& menu_playing_list, Map& map, Platform& door, std::vector<Font_Text>& font_playing, std::vector<Enemy>& enemy_list, std::vector<Fruit>& fruit_list, std::vector<Platform>& platform_list, Player& Player_hero, int & timeStat)
{
	//фукнция прохождение самой игры
	if (sf::IntRect(15, 20, 64, 64).contains(sf::Mouse::getPosition(window))) { menu_playing_list[7].GetSprite().setColor(sf::Color::Green); }
	window.setView(view);																//оживление камеры
	window.clear();	
	window.draw(menu_playing_list[0].GetSprite());								//рисунка фона, ДО КАРТЫ!
	map.drawMap(window);																//вывод карты по пикселям
	menu_playing_list[8].health_point(Player_hero.GetHealth());							//передаем значение здоровья, для изменения иконки здоровья
	door.StarImage(Player_hero.GetStarScore());
	menu_playing_list[10].getTextMisson(Player_hero.GetTime(), Player_hero.GetX(), Player_hero.GetY());			//меню значений квеста
	font_playing[0].ResultTextTime(Player_hero.GetTime(), timeStat, Player_hero.GetIsWin());				//вывод изображения времени игры
	font_playing[1].ResultTextTime(Player_hero.GetTime(), timeStat, Player_hero.GetIsWin());				
	font_playing[2].SetXY(584, -221);
	font_playing[3].SetXY(580, -225);
	for (int i = 1; i < size(menu_playing_list)-1; i++)
		window.draw(menu_playing_list[i].ImageWithCoordinate(view));
	for (int i = 0; i < size(enemy_list); i++)
		window.draw(enemy_list[i].GetSprite());					
	for (int i = 0; i < size(fruit_list); i++)
		window.draw(fruit_list[i].GetSprite());
	for (int i = 0; i < size(platform_list); i++)
		window.draw(platform_list[i].GetSprite());
	window.draw(Player_hero.GetSprite());					
	for (int i = 0; i < size(font_playing); i++)
		if (i <2)  window.draw(font_playing[i].StringTextTime(Player_hero.GetTime()));
		else window.draw(font_playing[i].StringTextFruit(Player_hero.GetFruitScore()));
	window.draw(menu_playing_list[11].ImageWithCoordinate(view));
	window.display();
}
void Dead_Funtion(sf::RenderWindow& window, std::vector<Map>& menu_dead_list, std::vector<Map>& button_list, std::vector<Font_Text>& font_dead, std::vector<Font_Text>& exit)
{
	//функция вывода меню при условии, если игрок умер
	if (sf::IntRect(490, 290, 295, 58).contains(sf::Mouse::getPosition(window))) { font_dead[1].GetText().setColor(sf::Color::Blue); button_list[0].GetSprite().setColor(sf::Color::Blue); }
	if (sf::IntRect(490, 370, 295, 58).contains(sf::Mouse::getPosition(window))) { exit[1].GetText().setColor(sf::Color::Blue); button_list[1].GetSprite().setColor(sf::Color::Blue); }

	exit[0].SetXY(-42, 56);
	exit[1].SetXY(-45, 54);
	button_list[0].SetXY( - 115, 30);
	button_list[1].SetXY(- 115, 110);

	for (int i = 0; i < size(menu_dead_list); i++)
		window.draw(menu_dead_list[i].ImageWithCoordinate(view));
	for (int i = 0; i < size(button_list); i++)
		window.draw(button_list[i].ImageWithCoordinate(view));
	for (int i = 0; i < size(font_dead); i++)
		window.draw(font_dead[i].TextWithCoordinate(view));
	for (int i = 0; i < size(exit); i++)
		window.draw(exit[i].TextWithCoordinate(view));
	window.display();
}
void Win_Function(sf::RenderWindow& window, std::vector<Map>& menu_win_list, std::vector<Map>& button_list, std::vector<Font_Text>& font_win,std::vector<Font_Text>& exit, Player & Player_hero,int & timeStat)
{ 
	//фукнция вывода победы
	if (sf::IntRect(500, 400, 295, 58).contains(sf::Mouse::getPosition(window))) { exit[1].GetText().setColor(sf::Color::Blue); button_list[1].GetSprite().setColor(sf::Color::Blue); }
	menu_win_list[1].SetXY(-50, 50);
	menu_win_list[2].SetXY(-40, -20);
	menu_win_list[3].SetXY(-105, 140);
	button_list[1].SetXY(-105, 140);
	font_win[0].SetXY(4, -71);
	font_win[1].SetXY(0, -75);
	font_win[2].SetXY(29, 4);
	font_win[3].SetXY(25, 0);
	exit[0].SetXY(-27, 86);
	exit[1].SetXY(-32, 84);
	for (int i = 0; i < size(menu_win_list); i++)
		window.draw(menu_win_list[i].ImageWithCoordinate(view));
	for (int i = 1; i < size(button_list); i++)
		window.draw(button_list[i].ImageWithCoordinate(view));
	for (int i = 0; i < size(font_win); i++)
	 if(i < 2) window.draw(font_win[i].ResultTextTime(Player_hero.GetTime(), timeStat, Player_hero.GetIsWin()));
	 else window.draw(font_win[i].StringTextFruit(Player_hero.GetFruitScore()));
	for (int i = 0; i < size(exit); i++)
		window.draw(exit[i].TextWithCoordinate(view));
	window.display();
}
void Pause_Function(sf::RenderWindow &window, std::vector<Map>& menu_pause_list, std::vector<Map>& button_list, std::vector<Font_Text>& font_start, std::vector<Font_Text>& exit)
{
	//фукнция вывода меню паузы
	if (sf::IntRect(490, 290, 295, 58).contains(sf::Mouse::getPosition(window))) { font_start[1].GetText().setColor(sf::Color::Blue); button_list[0].GetSprite().setColor(sf::Color::Blue); }
	if (sf::IntRect(490, 370, 295, 58).contains(sf::Mouse::getPosition(window))) { exit[1].GetText().setColor(sf::Color::Blue); button_list[1].GetSprite().setColor(sf::Color::Blue); }
	button_list[0].SetXY(- 115, 30);
	button_list[1].SetXY(- 115, 110);
	font_start[0].SetXY(-50, -24);
	font_start[1].SetXY(-53, -26);
	exit[0].SetXY(-42, 56);
	exit[1].SetXY(-45,54);
	for (int i = 0; i < size(menu_pause_list); i++)
		window.draw(menu_pause_list[i].ImageWithCoordinate(view));
	for (int i = 0; i < size(button_list); i++)
		window.draw(button_list[i].ImageWithCoordinate(view));
	for (int i = 0; i < size(font_start); i++)
		window.draw(font_start[i].TextWithCoordinate(view));
	for (int i = 0; i < size(exit); i++)
		window.draw(exit[i].TextWithCoordinate(view));
	window.display();
}

bool startGame()
{
	int timeStat;														//переменная сохраняет последнее значение времени для победы
	sf::Clock timer;													//переменная передает значение времени, для игрока и врага, чтоб не получать урон или не убивать врага некое время
	sf::Clock gameTimeClock;											//переменная передает значение времени, для времени в игре (сек)
	sf::Clock clock;													//переменная передает значение времени, для плавного движения (микросек)
	bool isPlaying = false;
	bool isPause = false;
	bool isDead = false;
	sf::RenderWindow window(sf::VideoMode(1280, 591), "SFMLworks");		
	view.reset(sf::FloatRect(0, 0, 1280, 591));					
	Map map("map77.png",false);															
	Player Player_hero("hero72.png", 430, 408, 72, 72, "Player1");		
	Enemy enemy1("enemy.png", 2600, 480, 144, 72, "EasyEnemy");					
	Enemy enemy2("enemy.png", 7460, 384, 144, 72, "EasyEnemy");
	Enemy enemy3("enemy.png", 8050, 384, 144, 72, "EasyEnemy");
	Enemy enemy4("enemy.png", 8550, 384, 144, 72, "EasyEnemy");
	Enemy enemy5("enemy.png", 4161, 1152, 144, 72, "EasyEnemy");
	Enemy enemyPila1("pila.png", 5140, 1440, 144, 72, "Pila");
	Enemy enemyPila2("pila.png", 4850, 1740, 144, 72, "Pila");
	Enemy enemyPila3("pila.png", 4565, 1440, 144, 72, "Pila");
	Enemy enemyPila4("pila.png", 4275, 1740, 144, 72, "Pila");
	Enemy enemyPila5("pila.png", 3985, 1440, 144, 72, "Pila");
	Enemy enemyPila6("pila.png", 3695, 1740, 144, 72, "Pila");
	Enemy flower("flower.png", 9412, 1374, 185, 272, "Flower");
	Enemy flower2("flower.png", 9212, 1374, 185, 272, "Flower");
	Enemy flower3("flower.png", 8732, 1374, 185, 272, "Flower");
	Enemy flower4("flower.png", 8452, 1374, 185, 272, "Flower");
	Enemy flower5("flower.png", 7957, 1374, 185, 272, "Flower");
	Enemy flower6("flower.png", 7682, 1374, 185, 272, "Flower");
	Enemy flower7("flower.png", 7200, 1374, 185, 272, "Flower");
	Enemy flower8("flower.png", 7010, 1374, 185, 272, "Flower");
	std::vector<Enemy> enemy_list = { enemy1,enemy2,enemy3,enemy4,enemy5, enemyPila1,enemyPila2,enemyPila3,enemyPila4,enemyPila5,enemyPila6,flower,flower2,flower3,flower4,flower5,flower6,flower7,flower8 };

	Fruit Banana1("banana1.png", 760, 585, 54, 54, "Banana");
	Fruit Banana2("banana1.png", 888, 585, 54, 54, "Banana");
	Fruit Banana3("banana1.png", 1395, 585, 54, 54, "Banana");
	Fruit Banana4("banana1.png", 1523, 585, 54, 54, "Banana");
	Fruit Banana5("banana1.png", 3204, 396, 54, 54, "Banana");
	Fruit Banana6("banana1.png", 3336, 396, 54, 54, "Banana");
	Fruit Banana7("banana1.png", 3464, 396, 54, 54, "Banana");
	Fruit Banana8("banana1.png", 3738, 970, 54, 54, "Banana");
	Fruit Banana9("banana1.png", 3866, 970, 54, 54, "Banana");
	Fruit Banana10("banana1.png", 5841, 492, 54, 54, "Banana");
	Fruit Banana11("banana1.png", 5969, 492, 54, 54, "Banana");
	Fruit Banana12("banana1.png", 6097, 492, 54, 54, "Banana");
	Fruit Banana13("banana1.png", 9008, 300, 54, 54, "Banana");
	Fruit Banana14("banana1.png", 9136, 300, 54, 54, "Banana");
	Fruit Banana15("banana1.png", 10126, 344, 54, 54, "Banana");
	Fruit Banana16("banana1.png", 10126, 572, 54, 54, "Banana");
	Fruit Banana17("banana1.png", 9023, 1060, 54, 54, "Banana");
	Fruit Banana18("banana1.png", 7490, 1060, 54, 54, "Banana");
	Fruit Banana19("banana1.png", 6280, 1274, 54, 54, "Banana");
	Fruit Banana20("banana1.png", 6280, 1502, 54, 54, "Banana");
	Fruit Banana24("banana1.png", 4646, 1828, 54, 54, "Banana");
	Fruit Banana25("banana1.png", 4080, 1828, 54, 54, "Banana");
	Fruit Banana26("banana1.png", 2164, 1732, 54, 54, "Banana");
	Fruit Banana27("banana1.png", 2332, 1732, 54, 54, "Banana");
	Fruit Banana28("banana1.png", 2500, 1732, 54, 54, "Banana");
	Fruit Kiwi1("kiwi1.png", 824, 585, 54, 54, "Kiwi");
	Fruit Kiwi2("kiwi1.png", 1459, 585, 54, 54, "Kiwi");
	Fruit Kiwi3("kiwi1.png", 3272, 396, 54, 54, "Kiwi");
	Fruit Kiwi4("kiwi1.png", 3400, 396, 54, 54, "Kiwi");
	Fruit Kiwi5("kiwi1.png", 3140, 396, 54, 54, "Kiwi");
	Fruit Kiwi6("kiwi1.png", 3802, 970, 54, 54, "Kiwi");
	Fruit Kiwi7("kiwi1.png", 5905, 492, 54, 54, "Kiwi");
	Fruit Kiwi8("kiwi1.png", 6033, 492, 54, 54, "Kiwi");
	Fruit Kiwi9("kiwi1.png", 8944, 300, 54, 54, "Kiwi");
	Fruit Kiwi10("kiwi1.png", 9072, 300, 54, 54, "Kiwi");
	Fruit Kiwi11("kiwi1.png", 9200, 300, 54, 54, "Kiwi");
	Fruit Kiwi12("kiwi1.png", 10126, 458, 54, 54, "Kiwi");
	Fruit Kiwi13("kiwi1.png", 10126, 686, 54, 54, "Kiwi");
	Fruit Kiwi14("kiwi1.png", 8255, 1060, 54, 54, "Kiwi");
	Fruit Kiwi15("kiwi1.png", 6280, 1160, 54, 54, "Kiwi");
	Fruit Kiwi16("kiwi1.png", 6280, 1388, 54, 54, "Kiwi");
	Fruit Kiwi19("kiwi1.png", 4944, 1828, 54, 54, "Kiwi");
	Fruit Kiwi20("kiwi1.png", 4358, 1828, 54, 54, "Kiwi");
	Fruit Kiwi21("kiwi1.png", 3782, 1828, 54, 54, "Kiwi");
	Fruit Kiwi22("kiwi1.png", 2248, 1732, 54, 54, "Kiwi");
	Fruit Kiwi23("kiwi1.png", 2416, 1732, 54, 54, "Kiwi");
	Fruit Star1("star2.png", 5214, 848, 26, 26, "Star");
	Fruit Star2("star2.png", 6671, 1050, 26, 26, "Star");
	Fruit Star3("star2.png", 1739, 1626, 26, 26, "Star");

	std::vector<Fruit> fruit_list = { Banana1, Banana2, Banana3, Banana4, Banana5, Banana6, Banana7,
		Banana8, Banana9, Banana10, Banana11, Banana12, Banana13, Banana14,Banana15,Banana16,Banana17,Banana18,Banana19,Banana20,Banana24,Banana25,Banana26,Banana27,Banana28,
		Kiwi1, Kiwi2, Kiwi3, Kiwi4, Kiwi5, Kiwi6, Kiwi7, Kiwi8, Kiwi9, Kiwi10, Kiwi11,Kiwi12,Kiwi13,Kiwi14,Kiwi15,Kiwi16,Kiwi19,Kiwi20,
		Kiwi21, Kiwi22,Kiwi23,Star1,Star2,Star3
	};

	Platform forma1("platform2.png", 9280, 1125, 144, 72, "Platform");
	Platform forma2("platform2.png", 8519, 1125, 144, 72, "Platform");
	Platform forma3("platform2.png", 7745, 1125, 144, 72, "Platform");
	Platform forma4("platform2.png", 7068, 1125, 144, 72, "Platform");
	Platform door("door.png", 1141, 1404, 72, 192, "Door");
	Platform port("port.png", 189, 1500, 144, 72, "Port");
	std::vector<Platform> platform_list = { forma1,forma2,forma3,forma4, door,port };

	Map fon("fon_map.png", false);												
	Map timeUp("timt55.png", true, 530, -235);											
	Map health("hel.png",true, -510, - 250);											
	Map quest("quest0.png",true, -120, - 130);
	Map Three_Star("3star.png", false,5070, 677);
	Map salat("salat.png",true, 520, -175);
	Map startGame("button.png",false, 525, 395);
	Map endGame("buttonexit.png", false,525, 475);
	Map artPlayer1("artPlayer1.png",false, 140, 360);
	Map artPlayer2("artPlayer2.png", false,1000, 70);
	Map TrapImage("trap.png", false,3552, 1920);
	Map Pause("pause.png",true, -590,  - 240);
	Map background("menufon1.png",false,36,36);
	Map menuPause("menupause.png",true,-165,-150);
	Map continuePause("button.png",true,-115,30);
	Map exitPause("buttonexit.png",true,-115,110);
	Map button_Color_1("buttoncolor.png",true, -115, 30,sf::Color::Black);
	Map button_Color_2("buttoncolor.png",true, -115, 110,sf::Color::Black);
	Map restart("button.png",true,-115,30);
	Map lose("lose.png",true,-165,-150);
	Map result("result.png",true,-215,-150);
	Map Kill_enemy("kill_enemy.png",false,2150,110);
	Map stone1("stone.png",false,6695,1115);
	Map stone2("stone.png",false,5240,920);
	Map stone3("stone.png",false,1764,1691);

	std::vector<Map> menu_map_list = { background,  startGame,  endGame, artPlayer1,  artPlayer2 };
	std::vector<Map> button_list = {  button_Color_1, button_Color_2};
	std::vector<Map> menu_pause_list = { menuPause, continuePause,  exitPause };
	std::vector<Map> menu_win_list = { result, salat, timeUp,  exitPause };
	std::vector<Map> menu_dead_list = { lose,  restart,  exitPause, };
	std::vector<Map> menu_playing_list = { fon, Kill_enemy,  stone3,  stone2, stone1,  timeUp,  salat,  Pause,  health, Three_Star, quest, TrapImage, };

	Font_Text text_time_white2(550, -289,"", 60, sf::Color::White);
	Font_Text text_time_black2(554, -285,"", 60, sf::Color::Black);
	Font_Text text_fruit_white(580,-225,"", 60, sf::Color::White);
	Font_Text text_fruit_black(584,-221,"", 60, sf::Color::Black);

	Font_Text menu_start_white(-48,-167,"START", 55, sf::Color::White);
	Font_Text menu_start_black(-45,-165,"START", 55, sf::Color::Black);
	Font_Text menu_exit_white(-43, -87,"EXIT", 55, sf::Color::White);
	Font_Text menu_exit_black(-40, -85,"EXIT", 55, sf::Color::Black);
	Font_Text menu_restart_white(-59,-26,"RESTART", 55, sf::Color::White);
	Font_Text menu_restart_black(-56,-24,"RESTART", 55, sf::Color::Black);

	std::vector<Font_Text> font_start = { menu_start_black, menu_start_white };
	std::vector<Font_Text> exit = { menu_exit_black, menu_exit_white };
	std::vector<Font_Text> font_win = { text_time_black2, text_time_white2,  text_fruit_black,  text_fruit_white };
	std::vector<Font_Text> font_dead = {  menu_restart_black,menu_restart_white };
	std::vector<Font_Text> font_playing = { text_time_black2, text_time_white2, text_fruit_black, text_fruit_white };

	MusicBar music("track.ogg");
	SoundBar sound_coin("Money.ogg");
	SoundBar sound_dead_enemy("dead_enemy.ogg");
	SoundBar sound_hit_people("hit.ogg");
	SoundBar sound_jump("jump.ogg");
	std::vector<SoundBar> sounds = { sound_coin ,sound_dead_enemy ,sound_hit_people ,sound_jump };

	music.playMusic();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return false;
			}

			SetColor(font_dead, font_start, exit, menu_map_list, button_list, menu_playing_list);		//изменение цвета на белый
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));		//значчение курсора мыши, и проверяем соприкосается ли он с картинками для взаимодействия
				if (menu_map_list[1].GetSprite().getGlobalBounds().contains(mousePos) || menu_pause_list[1].GetSprite().getGlobalBounds().contains(mousePos)) //реализация кнопки старт
				{
					isPlaying = true; 
					isPause = false;
				}
				if (menu_map_list[3].GetSprite().getGlobalBounds().contains(mousePos) && !isPlaying)	//изменение цвета игрока (выбор из 2 персонажей)
					Player_hero.changeColor("hero72.png");
				if (menu_map_list[4].GetSprite().getGlobalBounds().contains(mousePos) && !isPlaying)
					Player_hero.changeColor("hero72pink.png");
				if (menu_map_list[2].GetSprite().getGlobalBounds().contains(mousePos) && !isPlaying)	//реализация кнопки выход
				{
					window.close();
					return false;
				}
				if (menu_pause_list[2].GetSprite().getGlobalBounds().contains(mousePos) || menu_win_list[3].GetSprite().getGlobalBounds().contains(mousePos) || menu_dead_list[2].GetSprite().getGlobalBounds().contains(mousePos))
				{
					window.close();
					return false;
				}
				if (menu_playing_list[7].GetSprite().getGlobalBounds().contains(mousePos) && (isPlaying))	//реализация кнопки пауза
					isPause = true;
				if (menu_dead_list[1].GetSprite().getGlobalBounds().contains(mousePos))					//реализация кнопки рестарт
				{
					return true;
				}
			}
		}
		if (Player_hero.GetLife()) { Player_hero.GetTime() = gameTimeClock.getElapsedTime().asSeconds(); }	//установка времени в обьект класса Игрока
		if (Player_hero.GetTime() == 150) Player_hero.GetLife() = false;									//если время закончится, игра останавливается
		if (!Player_hero.GetLife()) isDead = true;															//если здоровья нет, то смерть
		float time = clock.getElapsedTime().asMicroseconds();												 //установка времени для плавного движения
		clock.restart();																					//перезагрузка времени
		time = time / 800;

		if (!isPause && Player_hero.GetLife() && !Player_hero.GetIsWin() && isPlaying)						
		{
			Update_Function(enemy_list, fruit_list, platform_list, Player_hero, time, TileMap);
			Colision_Function(enemy_list, fruit_list, platform_list, Player_hero, sounds, timer);
		}
		GetPosit(Player_hero.GetXforView(), Player_hero.GetYforView());		//слежение за игроком
		if (Player_hero.GetIsWin()) Win_Function(window, menu_win_list, button_list, font_win, exit, Player_hero, timeStat);
		if (isDead) Dead_Funtion(window, menu_dead_list, button_list, font_dead, exit);
		if (isPause) Pause_Function(window, menu_pause_list, button_list, font_start, exit);
		if (isPlaying) Playing_Function(window, menu_playing_list, map, door,font_playing, enemy_list, fruit_list, platform_list, Player_hero, timeStat);
		else Menu_Function(window, menu_map_list, button_list, font_start, exit);
	}
}

void gameRunning()
{
	if (startGame())
	{
		gameRunning();
	}
}

int main()
{
	gameRunning();
	return 0;
}

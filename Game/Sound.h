#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SoundBar
{
private:
	std::string File;
	sf::SoundBuffer buf;
	sf::Sound sound;
public:

	SoundBar(std::string F)
	{
		File = F;
		buf.loadFromFile("images/" + File);
		sound.setBuffer(buf);
	}
	void playSound() { sound.play(); }
};

class MusicBar
{
private:
	std::string File;
	sf::Music music;
public:
	MusicBar(std::string F)
	{
		File = F;
		music.openFromFile("images/" + File);
	}
	void playMusic() { music.play(); }
};
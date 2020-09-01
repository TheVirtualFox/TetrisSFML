#include "Digital.h"

namespace Tetris {

	Digital::Digital(int v, int x, int y)
	{
		using namespace sf;
		texture.loadFromFile("..\\Tetris\\assets\\digits.png");
		Sprite sprite(texture);
		this->sprite = sprite;
		sprite.setTextureRect(IntRect(0, 0, 13, 20));
		value = v;
		this->x = x;
		this->y = y;
	}

	Digital::~Digital()
	{
	}

	void Digital::Render(sf::RenderWindow& window)
	{
		int v = value;
		int offset = 0;
		while (v > 0) {
			int digit = v % 10;
			v /= 10;
			++offset;
			RenderDigit(digit, offset, window);
		}

		while (++offset < 6) {
			RenderDigit(-1, offset, window);
		}

	}
	
	void Digital::setValue(int value)
	{
		this->value = value;
	}
	void Digital::RenderDigit(int digit, int offset, sf::RenderWindow& window)
	{
		sprite.setTextureRect(sf::IntRect(13 * (digit + 1), 0, 13, 20));
		sprite.setPosition(x - offset * 13, y);
		window.draw(sprite);
	}
}


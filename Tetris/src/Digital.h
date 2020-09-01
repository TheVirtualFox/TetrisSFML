#pragma once
#include <SFML/Graphics.hpp>

namespace Tetris {
	class Digital {
	public:
		Digital(int value, int x, int y);
		~Digital();
		void Render(sf::RenderWindow& window);
		void setValue(int value);
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		int value = 0;
		void RenderDigit(int digit, int offset, sf::RenderWindow& window);
		int x;
		int y;
	};
}

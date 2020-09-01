#pragma once

#include <vector>
#include <initializer_list>
#include "Point.h"
#include <SFML/Graphics.hpp>

namespace Tetris {

	const int figures[7][4] = {
	{1,3,5,7}, // I
	{2,4,5,7}, // S
	{3,5,4,6}, // Z
	{3,5,4,7}, // T
	{2,3,5,7}, // L
	{3,5,7,6}, // J
	{2,3,4,5}  // O
	};

	template <int height, int width>
	class Figure {
	private:
		std::vector<int> figure;
		std::vector<Tetris::Point> points;
		Point fieldPositions[4] = {0};
		Point prevFieldPositions[4] = {0};
		int tileSize;
		int(&field)[height][width];
	public:

		Figure(int id, int ts, int (&f)[height][width]) : tileSize(ts), field(f)
		{
			reset(id);
		}

		int getSize() const {
			return figure.size();
		}

		std::vector<Tetris::Point> getPoints() const
		{
			return points;
		}

		void Render(sf::RenderWindow& window, sf::Sprite sprite) {
			sprite.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
			for (int i = 0; i < 4; ++i) {
				sprite.setPosition(fieldPositions[i].x * tileSize + 4, fieldPositions[i].y * tileSize + 4);
				window.draw(sprite);
			}
		}

		void down() {
			for (int i = 0; i < 4; ++i) {
				prevFieldPositions[i] = fieldPositions[i];
				fieldPositions[i].y += 1;
			}
		}

		void move(int dx) {
			for (int i = 0; i < 4; ++i) {
				prevFieldPositions[i] = fieldPositions[i];
				fieldPositions[i].x += dx;
			}
		}

		void rotate()
		{
			Point p = fieldPositions[1];
			for (int i = 0; i < 4; ++i) {
				prevFieldPositions[i] = fieldPositions[i];
				int x = fieldPositions[i].y - p.y;
				int y = fieldPositions[i].x - p.x;
				fieldPositions[i].x = p.x - x;
				fieldPositions[i].y = p.y + y;
			}
		}

		bool check() {
			for (int i = 0; i < 4; ++i) {
				if (fieldPositions[i].x < 0 || fieldPositions[i].x >= width || fieldPositions[i].y >= height) {
					return false;
				}
				else if (field[fieldPositions[i].y][fieldPositions[i].x]) {
					return false;
				}
			}
			return true;
		}

		void revert() {
			for (int i = 0; i < 4; ++i) {
				fieldPositions[i] = prevFieldPositions[i];
			}
		}


		typedef Point point_array4[4];
		point_array4& getFieldPosition() {
			return fieldPositions;
		}

		void reset(int id) {
			figure.clear();
			for (int i = 0; i < 4; ++i) {
				figure.push_back(figures[id][i]);
				fieldPositions[i].x = figures[id][i] % 2 + (width / 2) - 2;
				fieldPositions[i].y = figures[id][i] / 2;
			}

		}

		void toField() {
			for (int i = 0; i < 4; ++i) {
				field[fieldPositions[i].y][fieldPositions[i].x] = 2;
			}
		}

		void RenderNext(sf::RenderWindow& window, sf::Sprite sprite, int n) {
			sprite.setTextureRect(sf::IntRect(tileSize, 0, tileSize, tileSize));
			
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 4; ++j) {
					sprite.setPosition(i * tileSize + 199, j * tileSize + 170);
					window.draw(sprite);
				}
			}
			
			for (int i = 0; i < 4; ++i) {
				sprite.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
				sprite.setPosition((figures[n][i] % 2) * tileSize + 199, (figures[n][i] / 2) * tileSize + 170);
				window.draw(sprite);
			}
			
		}

	};
	
}

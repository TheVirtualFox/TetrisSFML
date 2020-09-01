#pragma once

#include <vector>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "Figure.h";
#include "Point.h"
#include "Digital.h"

namespace Tetris {
	inline constexpr int TILE_SIZE { 18 };
	inline extern const int GAME_FIELD_HEIGHT { 20 };
	inline extern const int GAME_FIELD_WIDTH { 10 };
	inline extern const float DELAY_STEP { 0.001 };
	inline extern const float DELAY_START { 0.3 };
	class Application {
	private:
		static const int NUMBER_OF_FIGURES = 7;
		static const int TILE_SIZE = 18;
		int field[GAME_FIELD_HEIGHT][GAME_FIELD_WIDTH] = { 0 };
		float timer = 0;
		float delay = DELAY_START;
		sf::Clock clock;
		int colorNum = 1;
		bool beginGame = true;
		int currentFugureId = 0;
		std::vector<Tetris::Point> figureFieldPoints;
		std::vector<Tetris::Point> prevFigureFieldPoints;
		int score = 0;
		Digital points;
		Digital cleans;
		Digital level;
		int next;
	public:
		Application();
	private:
		void Run(sf::RenderWindow& window);
		bool check(Tetris::Figure<GAME_FIELD_HEIGHT, GAME_FIELD_WIDTH> figure);
		void deleteFullLines();
		void displayScore();
		bool checkGameOver();
	};

}
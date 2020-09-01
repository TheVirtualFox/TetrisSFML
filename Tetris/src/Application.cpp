#include "Application.h"
#include "Point.h"
#include <iostream>

Tetris::Application::Application(): points(0, 265, 26), cleans(0, 265, 71), level(0, 265, 116)
{
	using namespace sf;
	srand(time(0));
	RenderWindow window(VideoMode(TILE_SIZE * GAME_FIELD_WIDTH + 100, TILE_SIZE * GAME_FIELD_HEIGHT + 8), "The Tetris Game!");
	Run(window);
}

typedef Tetris::Point point_array4[4];
void Tetris::Application::Run(sf::RenderWindow& window)
{
	using namespace sf;
	// Load texture
	Texture texture;
	texture.loadFromFile("..\\Tetris\\assets\\til.png");
	Sprite sprite(texture);
	sprite.setTextureRect(IntRect(0, 0, TILE_SIZE, TILE_SIZE));

	Texture backgroundTexture;
	backgroundTexture.loadFromFile("..\\Tetris\\assets\\bg.png");
	Sprite background(backgroundTexture);
	background.setTextureRect(IntRect(0, 0, 305, 368));
	

	Figure<GAME_FIELD_HEIGHT, GAME_FIELD_WIDTH> figure(0, TILE_SIZE, field);
	// Digital digital;
	points.setValue(0);
	next = rand() % 6;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		int dx = 0;
		bool rotate = false;
		float currentDelay = delay;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Up) {
					rotate = true;
				}
				else if (event.key.code == Keyboard::Left) {
					dx = -1;
				}
				else if (event.key.code == Keyboard::Right) {
					dx = 1;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				currentDelay = 0.05;
			}
		}

		if (dx != 0) {
			figure.move(dx);
			if (!check(figure)) {
				figure.revert();
			}
		}

		if (rotate) {
			figure.rotate();
			if (!check(figure)) {
				figure.revert();
			}
		}

		if (timer > currentDelay) {
			figure.down();
			timer = 0;
			if (!check(figure)) {
				figure.revert();
				figure.toField();
				figure.reset(next);
				next = rand() % 6;
				if (checkGameOver()) {
					// RESET GAME
				}
			}
			deleteFullLines();
		}

		dx = 0;
		rotate = false;
		currentDelay = delay;
		
		// window.clear(sf::Color(158, 171, 135, 255));
		window.draw(background);
		
		// RENDER FIELD BACK
		for (int i = 0; i < GAME_FIELD_HEIGHT; ++i) {
			for (int j = 0; j < GAME_FIELD_WIDTH; ++j) {
				if (field[i][j] == 0) {
					sprite.setTextureRect(IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
					sprite.setPosition(j * TILE_SIZE + 4, i * TILE_SIZE + 4);
					window.draw(sprite);
				}
				else {
					sprite.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
					sprite.setPosition(j * TILE_SIZE + 4, i * TILE_SIZE + 4);
					window.draw(sprite);
				}
			}
		}
		// RENDER FIGURES
		figure.Render(window, sprite);
		figure.RenderNext(window, sprite, next);
		points.Render(window);
		cleans.Render(window);
		level.Render(window);
		

		window.display();
	}
}

void Tetris::Application::deleteFullLines() {
	int k = GAME_FIELD_HEIGHT - 1;
	for (int i = GAME_FIELD_HEIGHT - 1; i > 0; --i) {
		int count = 0;
		for (int j = 0; j < GAME_FIELD_WIDTH; ++j) {
			if (field[i][j]) {
				count++;
			}
			field[k][j] = field[i][j];
		}
		if (count < GAME_FIELD_WIDTH) {
			--k;
		} else {
			score++;
			delay -= DELAY_STEP;
			displayScore();
		}
	}
}

bool Tetris::Application::checkGameOver() {
	for (int i = 0; i < GAME_FIELD_WIDTH; ++i) {
		if (field[0][i]) {
			return true;
		}
	}
	return false;
}

void Tetris::Application::displayScore()
{
		#if defined _WIN32
		system("cls");
		#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");
		#elif defined (__APPLE__)
		system("clear");
		#endif
		int levelValue = static_cast<int>((DELAY_START - delay) * 100);
		std::cout << "SCORE: " << score << std::endl;
		std::cout << "LEVEL: " << levelValue << std::endl;
		points.setValue(score);
		cleans.setValue(score);
		level.setValue(levelValue);
}

bool Tetris::Application::check(Tetris::Figure<GAME_FIELD_HEIGHT, GAME_FIELD_WIDTH> figure) {
	typedef Tetris::Point point_array4[4];
	point_array4& array = figure.getFieldPosition();
	for (int i = 0; i < 4; ++i) {
		if (array[i].x < 0 || array[i].x >= GAME_FIELD_WIDTH || array[i].y >= GAME_FIELD_HEIGHT) {
			return false;
		}
		else if (field[array[i].y][array[i].x]) {
			return false;
		}
	}
	return true;
}

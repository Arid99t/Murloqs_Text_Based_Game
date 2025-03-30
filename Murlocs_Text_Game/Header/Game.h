#ifndef GAME_H
#define GAME_H

#include "Header/Player.h"
#include "Header/Level.h"
#include <vector>
#include <memory>
using namespace std;

class Game {
private:
	unique_ptr<Player> player;
	vector<unique_ptr<Level>> levels;
	int currentLevel;
	bool gameOver;


	//methods to initialize game
	void initializePlayer();
	void initializeLevels();
	void displayIntroduction() const;


public:
	//constructor
	Game();

	~Game() = default;

	//to run the game
	void start();
	bool runCurrentLevel();
	void displayGameOver(bool victory) const;

	//getters
	bool isGameOver() const;
	int getCurrentLevel() const;

	//static method for game-wide settings
	static void setConsoleFormatting();

};

#endif
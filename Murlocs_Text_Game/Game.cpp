#include "Header/Game.h"
#include "Header/Item.h"
#include <iostream>
#include <chrono>
using namespace std;
//constructor
Game::Game() : currentLevel(0), gameOver(false) {
	setConsoleFormatting();
}

//method initialize player
void Game::initializePlayer() {
	string playerName;
	cout << "Enter the hero's name: ";
	getline(cin, playerName);

	if (playerName.empty()) { //using empty instead of playerName.length == 0 because empty() if more efficient although negligible 
		playerName = "Hero";
	}

	player = make_unique<Player>(playerName);

	//add the map - first item
	player->addItem(make_unique<Map>());


}

//initialize all levels 
void Game::initializeLevels() {
	//level 1: Forest Entrance
	auto level1 = make_unique<Level>(1, "Forest Entrance",
		"You enter the dark forest that surrounds your village. The air is thick with foreboding.");

	//add one enemy to level 1
	auto enemy1 = make_unique<Enemy>(Enemy::generateEnemyName(), 50, 10, 5, 3, 20);
	level1->addEnemy(move(enemy1));

	//Level 1 has no new ability but gives map from initializePlayer
	levels.push_back(move(level1));


	//Level 2 
	auto level2 = make_unique<Level>(2, "Abandoned Mines", "You descend into the abandoned mines beneath the forest. The darkness is oppressive.");

	//Add two enemies to level 2
	for (int i = 0; i < 2; ++i) {
		auto enemy = make_unique<Enemy>(Enemy::generateEnemyName(), 60, 12, 8, 4, 30);
		level2->addEnemy(move(enemy));
	}

	//Level 2 rewards: Sword and Critical Hit ability
	level2->setReward(make_unique<Sword>());
	level2->setNewAbility(make_unique<CriticalHit>());
	levels.push_back(move(level2));

	//Level 3
	auto level3 = make_unique<Level>(3, "Ancient Ruins",
		"You emerge from the mines into what appears to be ancient ruins. Symbols on the walls warn of danger.");

	//3 enemies to level 3
	for (int i = 0; i < 3; ++i) {
		auto enemy = make_unique<Enemy>(Enemy::generateEnemyName(), 70, 14, 10, 5, 40);
		level3->addEnemy(move(enemy));
	}

	//level 3 rewards (Shield and BLocker)
	level3->setReward(make_unique<Shield>());
	level3->setNewAbility(make_unique<Blocker>());
	levels.push_back(move(level3));

	//Level 4: 
	auto level4 = make_unique<Level>(4, "Cursed Swamp",
		"Beyond the ruins lies a fetid swamp. The air is thick with miasma and the cries of strange creatures.");

	//add 4 enemies
	for (int i = 0; i < 4; ++i) {
		auto enemy = make_unique<Enemy>(Enemy::generateEnemyName(), 80, 16, 12, 6, 50);
		level4->addEnemy(move(enemy));
	}
	//level 4 rewards
	level4->setReward(make_unique<Armor>());
	level4->setNewAbility(make_unique<LifeSteal>());
	levels.push_back(move(level4));

	//level 5
	auto level5 = make_unique<Level>(5, "Mountain Pass",
		"The swamp gives way to a treacherous mountain pass. The wind howls as you climb higher.");
	
	//add five enemies to level 5
	for (int i = 0; i < 5; ++i) {
		auto enemy = make_unique<Enemy>(Enemy::generateEnemyName(), 90, 18, 14, 7, 60);
		level5->addEnemy(move(enemy));
	}

	//level 5 rewards
	level5->setReward(make_unique<Bow>());
	level5->setNewAbility(make_unique<RangedAttack>());
	levels.push_back(move(level5));


	//level 6 
	auto level6 = make_unique<Level>(6, "Murlocs Lair",
		"At the peak of the mountain, you find a massive cave - Murlocs' lair. Your village's fate depends on you now.");

	auto boss = make_unique<Boss>("Murlocs the Devourer", 200, 25, 20, 10, 100);
	level6->addEnemy(move(boss));

	levels.push_back(move(level6));
}

void Game::displayIntroduction() const {
	cout << "\n=================================================" << endl;
	cout << "           HERO'S QUEST: PATH TO FREEDOM         " << endl;
	cout << "=================================================" << endl;
	cout << "\nIn the peaceful village of Elderbrook, life was once simple and joyful." << endl;
	cout << "But darkness fell when the terrible monster Murlocs and his minions attacked," << endl;
	cout << "capturing the village and enslaving its people." << endl;
	cout << "\nYou, the only warrior who managed to escape, must now embark on a perilous journey" << endl;
	cout << "to collect four legendary items: the Sword, Shield, Armor, and Bow." << endl;
	cout << "Only with these artifacts will you have the power to defeat Murlocs and free your people." << endl;
	cout << "\nYour quest begins now..." << endl;
	cout << "\nPress Enter to start your adventure...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//method to start the game
void Game::start() {
	initializePlayer();
	initializeLevels();

	//display intro
	displayIntroduction();

	//game loop
	while (!gameOver && currentLevel < static_cast<int>(levels.size())) {
		if (!runCurrentLevel()) {
			gameOver = true;
			displayGameOver(false); //defeat
			break;
		}
		//next level
		currentLevel++;

		//check for victory
		if (currentLevel >= static_cast<int>(levels.size())) {
			gameOver = true;
			displayGameOver(true); //victory
			break;
		}

		//break between levels
		cout << "\nPress Enter to continue to the next level...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}
//Method to run the current level
bool Game::runCurrentLevel() {
	if (currentLevel < 0 || currentLevel >= static_cast<int>(levels.size())) {
		return false;
	}

	return levels[currentLevel]->runLevel(*player);
}

//method to display game over
void Game::displayGameOver(bool victory) const {
	if (victory) {
		cout << "\n=================================================" << endl;
		cout << "                   VICTORY!                     " << endl;
		cout << "=================================================" << endl;
		cout << "\nWith a final, mighty blow, Murlocs the Devourer falls to his knees and then collapses." << endl;
		cout << "The dark energy that had been sustaining his reign of terror dissipates," << endl;
		cout << "and his monstrous form begins to crumble into dust." << endl;
		cout << "\nAs word of your victory spreads, the people of Elderbrook emerge from their captivity," << endl;
		cout << "cheering your name and celebrating their newfound freedom." << endl;
		cout << "\nYou have completed your quest, collected the four legendary items," << endl;
		cout << "mastered powerful abilities, and defeated the terrible Murlocs." << endl;
		cout << "\nYour village is free, and you are hailed as its greatest hero." << endl;
		cout << "\nTHE END" << endl;
	}
	else {
		cout << "\n=================================================" << endl;
		cout << "                  GAME OVER                     " << endl;
		cout << "=================================================" << endl;
		cout << "\nDespite your valiant efforts, the journey proved too perilous." << endl;
		cout << "Your quest ends here, and the village of Elderbrook remains under Murlocs' control." << endl;
		cout << "\nPerhaps another hero will rise to complete what you began..." << endl;
		cout << "\nBetter luck next time!" << endl;
	}
}

//getters
bool Game::isGameOver() const {
	return gameOver;
}

int Game::getCurrentLevel() const {
	return currentLevel;
}

//static method for game-wide settings
void Game::setConsoleFormatting() {
	// This would normally set console colors, but it's platform-dependent
	// For a cross-platform solution, we're just putting a placeholder
	cout << "Setting up game environment..." << endl;
}
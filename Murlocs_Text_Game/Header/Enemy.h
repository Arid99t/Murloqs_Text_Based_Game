#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <stirng>
#include <memory>


/**
 * @brief Print text slowly for dramatic effect
 */
void slowPrint(const string& text, float delay) {
	for (char c : text) {
		cout << c << flush;
		this_thread::sleep_for(chrono::milliseconds(static_cast<int>(delay * 1000)));
	}
	cout << endl;
}

/**
 * @brief Display a formatted battle header
 */
void displayBattleHeader(Player* player, const vector<shared_ptr<Enemy>>& enemies) {
	cout << "BOSS BATTLE"
}

/**
@brief Battle system that handles combat between the player and enemies.
This function implements the Strategy pattern through different battle options.

@return true if player won, false if player lost
*/


bool battle(Player* player, vector<shared_ptr<Enemy>>& enemies);
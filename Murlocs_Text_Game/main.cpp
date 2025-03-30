#pragma once

#include "Header/Game.h"
#include <iostream>
#include <stdexcept>

using namespace std;


int main() {

	try {
		//Create and start the game
		Game heroQuest;
		heroQuest.start();

		//wait for user input before closing
		cout << "\nPress Enter to exit...";
		cin.get();

		return 0;
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "Unknown error occured!" << endl;
		return 1;
	}
}
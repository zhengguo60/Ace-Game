#include <iostream>
#include <unistd.h> 
#include "Game.h"
#include "Utils.h"

void showMenu() {
    Utils::clearScreen();
    std::cout << "=== LINUX C++ PLANE WAR ===" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Choose: ";
}
int main() {
    int choice;
    
    while(true) {
        showMenu();
        std::cin >> choice;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::cout << "Select Difficulty (1-Easy, 2-Medium, 3-Hard): ";
            int level;
            std::cin >> level;
            std::cin.ignore(10000, '\n'); 

            Game game(50, 20); 
            game.setDifficulty(level);
            game.init();
            game.run(); 
            

        } 
        else if (choice == 2) {
            Game game(50, 20);
            if (game.loadGame()) {
                std::cout << "Load successful!" << std::endl;
                sleep(1);
                game.init();
                game.run();
            } else {
                std::cout << "No save file found!" << std::endl;
                sleep(2);
            }
        } 
        else if (choice == 3) {
            std::cout << "Goodbye!" << std::endl;
            break; 
        }
    }

    return 0;
}
#include "Player.h"
#include "iostream"
#include "GameState.h"
#include <algorithm>
#include <cctype>

int main() {
    std::cout << "Welcome to type racer, input your name :";
    string Name;
    std::cin >> Name;
    Player Player1{ Name };
    GameState GameState1{ &Player1 };
    std::cout << std::endl;
    std::cout << "Welcome " << Name;
    GameState1.ChangeDifficulty();
    std::list<string>::iterator i = GameState1.Text->begin();
    GameState1.GamePlayLoop();


    return 0;
}


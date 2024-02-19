#pragma once

#ifndef GAMESTATE_H
#define GAMESTATE_H
#pragma once
#include "Player.h"
#include "list"
#include "iostream"
#include <algorithm>
#include <cctype>

enum Difficulty {
    Easy,
    Medium,
    Hard
};


class GameState {
private:
    std::list<Player> LeaderBoard;
    string DataFile;
    Player* PlayingPlayer;
public:
    GameState(Player* PlayingPlayer);
    ~GameState();

    void OpenFile();
    void GamePlayLoop();
    void SetDataFile(string DataFile);
    void ChangeDifficulty();
public:
    std::list<string>* Text;
};

std::istream& operator>>(std::istream& Is, Difficulty& DifficultyValue);

#endif
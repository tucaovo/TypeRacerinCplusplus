#pragma once
#include "string"
#include "list"

using namespace std;

class Player {
private:
    string Name;
    string* SubmitedText;
public:
    double HighScore;
    Player(string Name, string* SubmitedText, double HighScore);
    Player(string Name);
    Player(const Player& OtherPlayer);
    Player(Player&& OtherPlayer) noexcept;
    ~Player();

    void GetName();
    string* GetSubmitedText();
    double GetHighScore();
    void SetSubmitedText(string* Text);
    void SetHighScore(double NewHighScore);
};
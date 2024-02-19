#include "Player.h"
#include "iostream"

Player::Player(string Name, string* SubmitedText, double HighScore) : Name{ Name }, HighScore{ HighScore }
{
    this->SubmitedText = new string;
    if (SubmitedText != nullptr) {
        (this->SubmitedText) = SubmitedText;
    }
}

Player::Player(string Name) : Player{ Name, nullptr, 0.0 } {

}

Player::Player(const Player& OtherPlayer) : Name{ OtherPlayer.Name }, HighScore{ OtherPlayer.HighScore }
{
    this->SubmitedText = new string;
    (this->SubmitedText) = (OtherPlayer.SubmitedText);
}

Player::Player(Player&& OtherPlayer) noexcept : Name{ OtherPlayer.Name }, HighScore{ OtherPlayer.HighScore }
{
    this->SubmitedText = OtherPlayer.SubmitedText;
    OtherPlayer.SubmitedText = nullptr;
}

Player::~Player()
{
    delete SubmitedText;
}

void Player::GetName() {
    cout << "The name is " << this->Name << endl;
}

string* Player::GetSubmitedText()
{
    return SubmitedText;
}

double Player::GetHighScore() {
    return this->HighScore;
}

void Player::SetHighScore(double NewHighScore) {
    this->HighScore = NewHighScore;
}

void Player::SetSubmitedText(string* Text) {
    SubmitedText = Text;
}

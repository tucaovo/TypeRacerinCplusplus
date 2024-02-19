#include "GameState.h"
#include "fstream"
#include "iostream"
#include "chrono"
#include <algorithm>
#include <cctype>

GameState::GameState(Player* PlayingPlayer) : PlayingPlayer{ PlayingPlayer }
{
    this->Text = new list<string>;
}

void GameState::SetDataFile(string DataFile) {
    this->DataFile = DataFile;
}

void GameState::ChangeDifficulty()
{
    std::cout << " choose your difficulty (Easy, Medium, Hard) ->";
    Difficulty Difficulty;
    bool hasInputedCorrectly = 0;
    while (!hasInputedCorrectly)
    {
        try {
            std::cin >> Difficulty;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "Try easy, medium or hard" << std::endl;
        }
        if (Difficulty == Easy)
        {
            DataFile = string{ "easy.txt" };
            hasInputedCorrectly = 1;
        }
        if (Difficulty == Medium)
        {
            DataFile = string{ "medium.txt" };
            hasInputedCorrectly = 1;

        }
        if (Difficulty == Hard)
        {
            DataFile = string{ "hard.txt" };
            hasInputedCorrectly = 1;

        }
    }
    OpenFile();
}

GameState::~GameState()
{
    delete Text;
}

void GameState::OpenFile() {
    try
    {
        std::ifstream ReadFile(DataFile);

        if (!ReadFile)
        {
            std::cerr << "ERROR: Cannot open " << DataFile << " !" << std::endl;
            exit(1);
        }
        std::string Word;
        while (ReadFile >> Word)
        {
            Text->push_back(Word);
        }
        ReadFile.close();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Exception: '" << ex.what() << "'!" << std::endl;
        exit(1);
    }
}

void GameState::GamePlayLoop()
{
    std::chrono::steady_clock::time_point Begin = std::chrono::steady_clock::now();

    while (Text->size() > 0) {
        list<string>::iterator Itr;
        Itr = Text->begin();
        for (Itr; Itr != Text->end(); Itr++) {
            std::cout << *Itr << " ";
        }
        std::cout << endl;
        string* WordsFromKeyboard = new string;
        std::cout << "->";
        std::cin >> *WordsFromKeyboard;
        PlayingPlayer->SetSubmitedText(WordsFromKeyboard);
        if (*PlayingPlayer->GetSubmitedText() == *Text->begin()) {
            Text->pop_front();
            std::cout << endl;
        }
    }
    std::chrono::steady_clock::time_point End = std::chrono::steady_clock::now();
    std::chrono::duration_cast <std::chrono::nanoseconds> (End - Begin).count();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(End - Begin);
    double DurationDouble = duration.count();
    if (PlayingPlayer->GetHighScore() < DurationDouble)
    {
        PlayingPlayer->SetHighScore(DurationDouble);
    }
    LeaderBoard.push_back(*PlayingPlayer);
    LeaderBoard.sort([](const Player& a, const Player& b) {return a.HighScore < b.HighScore; });
    std::cout << "The leaderboard is ";
    for (auto v : LeaderBoard)
        std::cout << v.HighScore << ", ";
    std::cout << "Congratulation \n Do you want to continue playing the game ?\n->";
    string StringInput;
    bool HasInputedCorrectly = 0;
    while (!HasInputedCorrectly) {
        std::cin >> StringInput;
        std::transform(StringInput.begin(), StringInput.end(),
            StringInput.begin(), [](unsigned char c) { return std::tolower(c); });
        if (StringInput == "yes") {
            HasInputedCorrectly = 1;
            Difficulty NewDifficulty;
            ChangeDifficulty();
            GamePlayLoop();
        }
        else if (StringInput == "no") {
            HasInputedCorrectly = 1;
            break;
        }
        else {
            std::cout << "Wrong input, try yes or no" << std::endl;
        }
    }
}

std::istream& operator>>(std::istream& Is, Difficulty& DifficultyValue) {
    int UserInput;
    string StringInput;
    Is >> StringInput;
    std::transform(StringInput.begin(), StringInput.end(),
        StringInput.begin(), [](unsigned char c) { return std::tolower(c); });
    if (StringInput == string{ "easy" })
        UserInput = 0;
    else if (StringInput == string{ "medium" })
        UserInput = 1;
    else if (StringInput == string{ "hard" })
        UserInput = 2;
    else
        UserInput = 3;
    switch (UserInput) {
    case Easy:
        DifficultyValue = Difficulty(UserInput);
        break;
    case Medium:
        DifficultyValue = Difficulty(UserInput);
        break;
    case Difficulty::Hard:
        DifficultyValue = Difficulty(UserInput);
        break;
    default: throw std::invalid_argument("Invalid input for Difficulty");
    }
    return Is;
}

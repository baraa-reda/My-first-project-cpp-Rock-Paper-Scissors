
#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoice {Rock = 1, Paper, Scissor};

enum enWinner {Player = 1, Computer, Draw};

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner RoundWinner;
    string RoundWinnerName = "";
};

struct stGameResults
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string GameWinnerName = "";
};

short ReadHowManyRounds()
{
    short HowManyRounds = 0;

    do
    {
        cout << "Please enter How Many Round from 1 to 10\n";
        cin >> HowManyRounds;

    } while (HowManyRounds < 1 || HowManyRounds > 10);

    return HowManyRounds;
}

enGameChoice ReadPlayerChoice()
{
    short PlayerChoice = 0;

    do
    {
        cout << "\nYour Choice : Rock [1], Paper [2], Siccor [3]\n";
        cin >> PlayerChoice; 

    } while (PlayerChoice < 1 || PlayerChoice > 3);

    return (enGameChoice)PlayerChoice;
}

short RandomNumber(short From, short To)
{
    short Random = 0;
    Random = rand() % (To - From + 1) + From;

    return Random;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWinTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Rock:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
            return enWinner::Computer;
        break;

    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
            return enWinner::Computer;
        break;

    case enGameChoice::Scissor:
        if (RoundInfo.ComputerChoice == enGameChoice::Rock)
            return enWinner::Computer;
        break;
    }

    return enWinner::Player;
}

string ChoiceName(enGameChoice Choice)
{
    string arrChoiceName[3] = { "Rock", "Paper", "Scissor" };
    return arrChoiceName[Choice - 1];
}


string WinnerName(enWinner Winner)
{
    string arrRoundWinner[3] = { "Player", "Computer", "Draw" };
    return arrRoundWinner[Winner - 1];
}

void PrintRound(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.RoundWinnerName << "]\n";
    cout << "_________________________________________\n" << endl;
}

enWinner WhoWinTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
    if (PlayerWinTimes > ComputerWinTimes)
        return enWinner::Player;
    else if (ComputerWinTimes > PlayerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

void SetColorScreen(enWinner Winner)
{
    if (Winner == enWinner::Player)
        system("color 2F");
    else if (Winner == enWinner::Computer)
        system("color 4F");
    else
        system("color 6F");
}

stGameResults FillGameResults(short HowManyRounds, short PlayerWin, short ComputerWin, short Draw)
{
    stGameResults GameResult;

    GameResult.GameRounds = HowManyRounds;
    GameResult.DrawTimes = Draw;
    GameResult.ComputerWinTimes = ComputerWin;
    GameResult.PlayerWinTimes = PlayerWin;
    GameResult.GameWinner = WhoWinTheGame(PlayerWin, ComputerWin);
    GameResult.GameWinnerName = WinnerName(GameResult.GameWinner);

    return GameResult;
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo; 

    short PlayerWinsTime = 0, ComputerWinsTime = 0, DrawTimes = 0;

    for (short GameRounds = 1; GameRounds <= HowManyRounds; GameRounds++)
    {
        cout << "Game Round [ " << GameRounds << " ] begins\n";
        RoundInfo.RoundNumber = GameRounds;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.RoundWinner = WhoWinTheRound(RoundInfo);
        RoundInfo.RoundWinnerName = WinnerName(RoundInfo.RoundWinner);

        if (RoundInfo.RoundWinner == enWinner::Draw)       
            DrawTimes++;

        else if (RoundInfo.RoundWinner == enWinner::Computer)
            ComputerWinsTime++;

        else
            PlayerWinsTime++;

        SetColorScreen(RoundInfo.RoundWinner);

        PrintRound(RoundInfo);
    }

    return FillGameResults(HowManyRounds, PlayerWinsTime, ComputerWinsTime, DrawTimes);
}

string Tabs(short Number)
{
    string t = "";

    for (short i = 1; i <= Number; i++)
    {
        t += "\t";
    }
    return t;
}

void ShowGameOver()
{
    cout << Tabs(2) << "--------------------------------------------------------\n" << endl;
    cout << Tabs(2) << "                 +++ Game Over +++                      \n" << endl;
    cout << Tabs(2) << "--------------------------------------------------------\n" << endl;

}

void PrintGameResult(stGameResults GameResult)
{ 

    cout << Tabs(2) << "------------------- Game Results ---------------------" << endl;
    cout << Tabs(2) << " Game Rounds        : " << GameResult.GameRounds << endl;
    cout << Tabs(2) << " Player won time    : " << GameResult.PlayerWinTimes << endl;
    cout << Tabs(2) << " Computer won times : " << GameResult.ComputerWinTimes << endl;
    cout << Tabs(2) << " Draw Times         : " << GameResult.DrawTimes << endl;
    cout << Tabs(2) << " Final Winner       : " << GameResult.GameWinnerName << endl;
    cout << Tabs(2) << "------------------------------------------------------" << endl;

}

void ResetGame()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'y';

    do
    {
        ResetGame();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOver();
        PrintGameResult(GameResults);
        cout << "Do you Want to Play Again ? (Y/N)\n";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
   
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}


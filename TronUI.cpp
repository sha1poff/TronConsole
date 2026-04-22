#include "pch.h"

#include "TronUI.h"
#include "TronManager.h"
#include "TronHumanPlayer.h"
#include "TronComputerPlayer.h"


void TronUI::SetupConsole() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci = { 1, FALSE };
    SetConsoleCursorInfo(hOut, &ci);
}

void TronUI::Clear()
{
    system("cls"); // Простейший способ для полной очистки при смене экранов
}

void TronUI::WaitKey()
{
    while (_kbhit())
        _getch();
    _getch();
}

void TronUI::PrintCentered(std::string text, int width) {
    int spaces = (width - (int)text.length()) / 2;
    if (spaces > 0) std::cout << std::string(spaces, ' ');
    std::cout << text << std::endl;
}

void TronUI::ShowHeader() {
    Clear();
    std::cout << "========================================" << std::endl;
    PrintCentered("TRON");
    std::cout << "========================================" << std::endl;
}

int TronUI::SelectGameMode() {
    ShowHeader();
    std::cout << "\n    ВЫБЕРИТЕ РЕЖИМ ИГРЫ:" << std::endl;
    std::cout << "    1. Игрок vs ИИ (PvE)" << std::endl;
    std::cout << "    2. Игрок vs Игрок (PvP)" << std::endl;
    std::cout << "\n    Ваш выбор: ";
    int choice;
    while (!(std::cin >> choice) || (choice < 1 || choice > 2)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "    Введите 1 или 2: ";
    }
    return choice;
}

std::string TronUI::RequestName(const std::string& label) {
    std::cout << "    " << label << ": ";
    std::string name;
    std::cin >> name;
    return name;
}

void TronUI::StartGameLoop() {
    int mode = SelectGameMode();
    bool isPvE = (mode == 1);

    std::cout << "\n    РЕГИСТРАЦИЯ УЧАСТНИКОВ:" << std::endl;
    std::string p1Name = RequestName("Игрок 1 (WASD)");
    std::string p2Name = isPvE ? "Бот" : RequestName("Игрок 2 (Стрелки)");

    int p1Wins = 0, p2Wins = 0, round = 1, currentDiff = 1;

    while (p1Wins < 3 && p2Wins < 3) {
        ShowMatchStatus(p1Name, p2Name, p1Wins, p2Wins, round, currentDiff, isPvE);

        TronManager game(70, 25);
        TronPlayer* p1 = new TronHumanPlayer(p1Name, 1);
        TronPlayer* p2 = nullptr;

        if (isPvE)
        {
            TronComputerPlayer* bot = new TronComputerPlayer(p2Name, 2);
            bot->SetDifficulty(currentDiff);
            p2 = bot;
        }
        else {
            p2 = new TronHumanPlayer(p2Name, 2);
        }

        game.SetPlayer(1, p1);
        game.SetPlayer(2, p2);

        int result = game.Run();

        if (result == 1) {
            p1Wins++;
            if (isPvE && currentDiff < 3) currentDiff++;
        }
        else if (result == 2) {
            p2Wins++;
        }

        ShowRoundResult(result, p1Name, p2Name, p1Wins, p2Wins);
        round++;
    }
    ShowFinalResults(p1Name, p2Name, p1Wins, p2Wins);
}

void TronUI::ShowMatchStatus(const std::string& p1, const std::string& p2, int w1, int w2, int r, int d, bool pve) {
    ShowHeader();
    PrintCentered("РАУНД №" + std::to_string(r));
    std::cout << "----------------------------------------" << std::endl;
    PrintCentered(p1 + " [" + std::to_string(w1) + "] : [" + std::to_string(w2) + "] " + p2);
    if (pve) PrintCentered("Сложность ИИ: Уровень " + std::to_string(d));
    else PrintCentered("Режим: БИТВА ИГРОКОВ");
    std::cout << "========================================" << std::endl;
    PrintCentered("Нажмите любую клавишу...");
    WaitKey();
}

void TronUI::ShowRoundResult(int winner, const std::string& p1, const std::string& p2, int w1, int w2) {
    ShowHeader();
    PrintCentered("РАУНД ЗАВЕРШЕН!");
    std::cout << "----------------------------------------" << std::endl;
    if (winner == 0) PrintCentered("НИЧЬЯ!");
    else PrintCentered("ПОБЕДИЛ: " + (winner == 1 ? p1 : p2));
    PrintCentered("СЧЕТ: " + std::to_string(w1) + " - " + std::to_string(w2));
    std::cout << "========================================" << std::endl;
    WaitKey();
}

void TronUI::ShowFinalResults(const std::string& p1, const std::string& p2, int w1, int w2) {
    ShowHeader();
    PrintCentered("ФИНАЛ МАТЧА");
    std::cout << "----------------------------------------" << std::endl;
    std::string winner = (w1 > w2) ? p1 : p2;
    PrintCentered("АБСОЛЮТНЫЙ ЧЕМПИОН: " + winner);
    std::cout << "========================================" << std::endl;
    WaitKey();
}
#pragma once
#include "pch.h"

class TronUI
{
public:
    // настройка консоли при старте
    static void SetupConsole();

    // очистка экрана без лишних сообщений
    static void Clear();

    // красивый заголовок и ввод имени
    static std::string ShowStartScreen();

    // экран перед раундом (счет и сложность)
    static void ShowMatchStatus(const std::string& p1Name, int p1Wins, int p2Wins, int round, int diff);

	// экран после раунда с результатами
    static void ShowRoundResult(int winner, const std::string& pName, int pWins, int bWins);

    // экран итогов серии
    static void ShowFinalResults(const std::string& p1Name, int p1Wins, int p2Wins);

    // удобная пауза без текста "Для продолжения..."
    static void WaitKey();
};


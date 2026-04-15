#include "pch.h"
#include "TronUI.h"


void TronUI::SetupConsole() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci = { 1, FALSE };
    SetConsoleCursorInfo(hOut, &ci);
}

void TronUI::Clear() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    COORD homeCoords = { 0, 0 };

    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) return;

    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Заполняем пробелами и сбрасываем атрибуты (цвета)
    FillConsoleOutputCharacter(hOut, (TCHAR)' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hOut, homeCoords);
}

void TronUI::WaitKey() {
    while (_kbhit()) (void)_getch(); // Очистка буфера
    (void)_getch();                  // Ожидание
}

std::string TronUI::ShowStartScreen() {
    Clear();
    std::cout << "========================================" << std::endl;
    std::cout << "        TRON CONSOLE: BEST OF 5        " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Введите ваше имя: ";
    std::string name;
    std::cin >> name;
    return name;
}

void TronUI::ShowMatchStatus(const std::string& p1Name, int p1Wins, int p2Wins, int round, int diff) {
    Clear();
    std::cout << "========================================" << std::endl;
    std::cout << "             РАУНД №" << round << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << " Счёт: " << p1Name << " [" << p1Wins << "] : [" << p2Wins << "] Бот" << std::endl;
    std::cout << " Сложность ИИ: Уровень " << diff << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\nНажмите любую клавишу для начала боя..." << std::endl;
    WaitKey();
}

void TronUI::ShowRoundResult(int winner, const std::string& pName, int pWins, int bWins) {
    // 1. Сначала подготавливаем ТЕКСТ в переменной, а не выводим сразу
    std::string resultMsg;
    if (winner == 1)      resultMsg = "  ПОБЕДИТЕЛЬ: ИГРОК"; // Временно без pName для теста
    else if (winner == 2) resultMsg = "  ПОБЕДИТЕЛЬ: БОТ";
    else                  resultMsg = "  НИЧЬЯ!";

    // 2. Очищаем экран
    Clear();

    // 3. СБРОС СОСТОЯНИЯ (Критично для русского языка в UTF-8)
    std::cout.clear();

    // 4. Вывод константных строк
    std::cout << "========================================\n";
    std::cout << "        РАУНД ЗАВЕРШЕН!\n";
    std::cout << "========================================\n";

    std::cout << resultMsg << "\n"; // Выводим заранее подготовленную строку

    std::cout << "----------------------------------------\n";
    std::cout << "  ТЕКУЩИЙ СЧЕТ: " << pWins << " - " << bWins << "\n";
    std::cout << "========================================\n";
    std::cout << "Нажмите любую клавишу для продолжения...\n";

    std::cout.flush(); // Принудительно выталкиваем текст на экран

    WaitKey();
}

void TronUI::ShowFinalResults(const std::string& p1Name, int p1Wins, int p2Wins) {
    Clear();
    std::cout << "========================================" << std::endl;
    std::cout << "             ФИНАЛ МАТЧА               " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << p1Name << " : " << p1Wins << " | Бот : " << p2Wins << std::endl;

    if (p1Wins > p2Wins)
        std::cout << "\nПОЗДРАВЛЯЕМ! ВЫ ВЫИГРАЛИ СЕРИЮ!" << std::endl;
    else
        std::cout << "\nПОРАЖЕНИЕ. МАШИНЫ ОКАЗАЛИСЬ СИЛЬНЕЕ." << std::endl;

    std::cout << "\nНажмите клавишу для выхода..." << std::endl;

    WaitKey();
}
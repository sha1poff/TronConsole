#include "pch.h"

#include "TronField.h"

#include "TronPlayer.h"
#include "TronHumanPlayer.h"
#include "TronComputerPlayer.h"

#include "TronManager.h"


int main() {
    setlocale(LC_ALL, "Russian");

    std::string name1, name2;

    // 1. Запрашиваем имена у пользователей
    std::cout << "=== ДОБРО ПОЖАЛОВАТЬ В TRON ===\n" << std::endl;

    std::cout << "Введите имя первого игрока (WASD): ";
    std::cin >> name1;

    std::cout << "Введите имя второго игрока (Стрелки): ";
    std::cin >> name2;

    system("cls");

    TronManager manager(70, 25);

    TronPlayer* player1 = new TronHumanPlayer(name1, 10, 12, Direction::RIGHT, 10, false);
    TronPlayer* player2 = new TronHumanPlayer(name2, 60, 12, Direction::LEFT, 12, true);

    // игрок 1: зеленый цвет (10)
    manager.SetPlayer(1, player1);

    // игрок 2: красный цвет (12)
    manager.SetPlayer(2, player2);

    // 4. Запуск
    manager.Run();

    return 0;
}
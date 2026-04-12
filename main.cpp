#include "pch.h"

#include "TronField.h"

#include "TronPlayer.h"
#include "TronHumanPlayer.h"
#include "TronComputerPlayer.h"

#include "TronManager.h"


void ShowMenu() {
    system("cls");
    std::cout << "==============================" << std::endl;
    std::cout << "          TRON В КОНСОЛИ      " << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "1. Человек против Человека (PvP)" << std::endl;
    std::cout << "2. Человек против Бота (PvE)" << std::endl;
    std::cout << "3. Выход" << std::endl;
    std::cout << "\nВыберите режим: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand((unsigned int)time(NULL));

    bool exitProgram = false;

    while (!exitProgram) {
        ShowMenu();
        int choice;
        std::cin >> choice;

        if (choice == 3) {
            exitProgram = true;
            continue;
        }

        std::string n1, n2 = "Бот";
        std::cout << "Введите имя первого игрока: ";
        std::cin >> n1;

        if (choice == 1) {
            std::cout << "Введите имя второго игрока: ";
            std::cin >> n2;
        }

        // Создаем игру
        TronManager manager(70, 25);
        manager.SetPlayer(1, new TronHumanPlayer(n1, 10, 12, Direction::RIGHT, 10, false));

        if (choice == 1) {
            manager.SetPlayer(2, new TronHumanPlayer(n2, 60, 12, Direction::LEFT, 12, true));
        }
        else {
            manager.SetPlayer(2, new TronComputerPlayer(n2, 60, 12, Direction::LEFT, 12));
        }

        // Запуск раунда
        system("cls");
        manager.Run();

        std::cout << "\nХотите сыграть еще раз? (1 - Да, 0 - Нет): ";
        int again;
        std::cin >> again;
        if (again == 0) exitProgram = true;
    }

    return 0;
}
#include "TronUI.h"
#include <ctime>

/**
 * TRON CONSOLE GAME
 * Основной файл запуска.
 * Вся логика управления сессией находится в классе TronUI.
 */
int main() {
    // 1. Предварительная настройка консоли (кодировка, курсор)
    TronUI::SetupConsole();

    // 2. Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(0)));

    // 3. Создание интерфейса и запуск игрового цикла
    TronUI ui;
    ui.StartGameLoop();

    return 0;
}
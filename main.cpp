#include "pch.h"

#include "TronUI.h"
#include "TronManager.h"
#include "TronHumanPlayer.h"
#include "TronComputerPlayer.h"


int main() {
    // 1. Инициализация систем
    TronUI::SetupConsole();
    srand(static_cast<unsigned int>(time(0)));

    // 2. Начальный экран и получение имени игрока
    std::string pName = TronUI::ShowStartScreen();

    // Состояние серии (Best of 5)
    int pWins = 0, bWins = 0;
    int currentDiff = 1;
    int round = 1;

    // 3. Главный цикл серии матчей
    while (pWins < 3 && bWins < 3) {
        // Показываем заставку перед раундом (счет и уровень сложности)
        TronUI::ShowMatchStatus(pName, pWins, bWins, round, currentDiff);

        // Создаем менеджер игры для конкретного раунда
        TronManager game(70, 25);

        // Создаем игроков. Номер (1 или 2) автоматически задает:
        // - Стартовую позицию и направление
        // - Цвет (Зеленый или Фиолетовый)
        // - Управление (WASD или Стрелки)
        TronHumanPlayer* human = new TronHumanPlayer(pName, 1);
        TronComputerPlayer* bot = new TronComputerPlayer("Бот", 2);

        // Устанавливаем текущую сложность для ИИ
        bot->SetDifficulty(currentDiff);

        game.SetPlayer(1, human);
        game.SetPlayer(2, bot);

        // 4. Запуск игрового процесса раунда
        int result = game.Run();

        // 5. Обработка результатов раунда
        if (result == 1) {
            pWins++;
            // Если игрок победил, повышаем сложность для следующего раунда
            if (currentDiff < 3) currentDiff++;
        }
        else if (result == 2) {
            bWins++;
        }

        // Показываем промежуточный результат и ждем нажатия клавиши
        TronUI::ShowRoundResult(result, pName, pWins, bWins);

        round++;
    }

    // 6. Финальный экран с итогами всей серии
    TronUI::ShowFinalResults(pName, pWins, bWins);

    return 0;
}
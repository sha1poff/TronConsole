#pragma once

#include "pch.h"

/// <summary>
/// Класс для управления пользовательским интерфейсом игры Tron. Отвечает за отображение информации, запросы ввода и организацию игрового процесса.
/// </summary>
class TronUI
{
public:
    static void SetupConsole();

    /// <summary>
    /// Очистка экрана
    /// </summary>
    static void Clear();

    /// <summary>
    /// 
    /// </summary>
    static void WaitKey();

    // Запуск всего игрового процесса

    /// <summary>
    /// Запускает основной цикл серии матчей (Best of 5).
    /// Управляет регистрацией игроков, сменой раундов и подсчетом очков.
    /// </summary>
    void StartGameLoop();

private:
    /// <summary>
    /// Название игры
    /// </summary>
    void ShowHeader();

    /// <summary>
    /// Выбор игрового режима
    /// PvP или PvE
    /// </summary>
    /// <returns>Режим игры<returns>
    int SelectGameMode();

    /// <summary>
    /// Ввод имени игрока
    /// </summary>
    /// <param name="label">Управление</param>
    /// <returns>Имя игрока</returns>
    std::string RequestName(const std::string& label);

    void PrintCentered(std::string text, int width = 40);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="p1"></param>
    /// <param name="p2"></param>
    /// <param name="w1"></param>
    /// <param name="w2"></param>
    /// <param name="r"></param>
    /// <param name="d"></param>
    /// <param name="pve"></param>
    void ShowMatchStatus(const std::string& p1, const std::string& p2,
        int w1, int w2, int r, int d, bool pve);

    /// <summary>
    /// Результат раунда
    /// </summary>
    /// <param name="winner">Номер победителя</param>
    /// <param name="p1">Ссылка на имя первого игрока</param>
    /// <param name="p2">Ссылка на имя второго игрока</param>
    /// <param name="w1">Счет первого игрока</param>
    /// <param name="w2">Счет второго игрока</param>
    void ShowRoundResult(int winner, const std::string& p1, const std::string& p2,
        int w1, int w2);

    /// <summary>
    /// Итоги игры
    /// </summary>
    /// <param name="p1">Ссылка на имя первого игрока</param>
    /// <param name="p2">Ссылка на имя второго игрока</param>
    /// <param name="w1">Счет первого игрока</param>
    /// <param name="w2">Счет второго игрока</param>
    void ShowFinalResults(const std::string& p1, const std::string& p2,
        int w1, int w2);
};
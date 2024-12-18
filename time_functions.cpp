﻿#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Извлекает номер месяца из строки с датой в формате DD-MM-YYYY.
 *
 * Данная функция разбивает строку с датой по разделителю `-` и извлекает второе поле,
 * соответствующее номеру месяца (MM). Предполагается, что входная строка имеет
 * корректный формат (например, "22-01-2453").
 *
 * @param date Строка с датой в формате DD-MM-YYYY.
 * @return Номер месяца (целое число от 1 до 12).
 */
short dateToMonth(string date)
{
    short month{}; // Переменная для хранения номера месяца.
    stringstream date_ss(date); // Поток для обработки строки даты.
    string current_line; // Временная строка для хранения текущего поля.
    short counter = 0; // Счетчик полей, разделенных '-'.

    // Разделяем строку с датой по символу '-' и обрабатываем части.
    while (getline(date_ss, current_line, '-')) {
        if (counter == 1)
        {
            // Если это второе поле, преобразуем его в число и сохраняем как месяц.
            month = stoi(current_line);
        }
        counter++; // Увеличиваем счетчик полей.
    }
    return month; // Возвращаем извлеченный номер месяца.
}

/** 
* Функция для вычисления отработанного времени в минутах.
* На вход получает вектор, состоящий из 4 элементов(час начала, минуты начала, час конца, минуты конца).
* @param time Входной вектор, необходимый для подсчета времени в минутах.
* @return Отработанное время в минутах(int).
*/
int timeToMinute(vector<int> time)
{
    // Преобразуем время начала в минуты
    int start_minutes = (time[0] * 60) + time[1];
    // Преобразуем время окончания в минуты
    int end_minutes = (time[2] * 60) + time[3];

    // Если время начала меньше или равно времени окончания
    if (start_minutes <= end_minutes)
    {
        // Если разница превышает 240 минут (4 часа)
        if ((end_minutes - start_minutes) > 240)
        {
            // Возвращаем разницу минус 45 минут (перерыв)
            return end_minutes - start_minutes - 45;
        }
        else
        {
            // Возвращаем простую разницу в минутах
            return end_minutes - start_minutes;
        }
    }
    else // Если время начала больше времени окончания (переход через полночь)
    {
        // Проверяем, если разница превышает 240 минут
        if (((1440 - start_minutes) + end_minutes) > 240)
        {
            // Возвращаем разницу минус 45 минут
            return (1440 - start_minutes) + end_minutes - 45;
        }
        else
        {
            // Возвращаем простую разницу в минутах
            return (1440 - start_minutes) + end_minutes;
        }
    }
}

/**
* Функция для преобразования количества отработанного времени в формат string (DD:HH:MM).
* На вход получает количество отработанных минут.
* @param time Входное число, количество отработанных минут.
* @return Строка (string) формата DD:HH:MM
*/
string minuteToDDHHMM(int time)
{
    int work_in_hours = 0;
    int work_in_minutes = 0;
    int work_in_days = 0;

    string result;

    // Проверяем, если общее время больше или равно 1440 минутам (1 день)
    if (time >= 1440)
    {
        // Вычисляем количество полных дней
        work_in_days = time / 1440;
        // Вычисляем оставшиеся часы после вычитания дней
        work_in_hours = (time - (work_in_days * 1440)) / 60;
        // Вычисляем оставшиеся минуты после вычитания дней и часов
        work_in_minutes = (time - (work_in_days * 1440) - (work_in_hours * 60));
    }
    else // Если время меньше одного дня
    {
        // Вычисляем часы и минуты без учёта дней
        work_in_hours = time / 60;
        work_in_minutes = (time - (work_in_hours * 60));
    }

    // Формируем строку результата в формате "дни:часы:минуты"
    result = to_string(work_in_days) + ":" + to_string(work_in_hours) + ":" + to_string(work_in_minutes);

    return result;
}

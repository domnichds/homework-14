#include <iostream>
#include<vector>
#include <string>
#include <fstream>
#include <sstream>
#include "time_functions.h"
#include "worker.h"

using namespace std;

/**
 * @brief Читает данные из файла и преобразует их в вектор структур worker.
 *
 * Данная функция обрабатывает текстовый файл, содержащий записи о сотрудниках, их рабочем времени
 * и дате. Каждая строка файла содержит дату, имя сотрудника, время начала и окончания работы.
 * Данные преобразуются в вектор структур worker, где для каждого сотрудника сохраняется
 * общее рабочее время по месяцам.
 *
 * @param file_name Ссылка на строку с именем файла для чтения.
 * @return Вектор структур worker, содержащий:
 *         - имя сотрудника (name);
 *         - список месяцев с общим количеством отработанных минут (work_time).
 * @throws runtime_error Если файл не удается открыть.
 */
vector<worker> readData(const string& file_name)
{
    vector<worker> result; // Вектор для хранения обработанных данных о сотрудниках.
    string line; // Переменная для строки, считанной из файла.
    ifstream inFile(file_name); // Поток для чтения файла.

    // Проверяем, удалось ли открыть файл.
    if (!inFile) {
        throw runtime_error("Ошибка: файл \"" + file_name + "\" не найден или не может быть открыт!");
    }

    // Чтение строк из файла.
    while (getline(inFile, line)) {
        short month; // Переменная для хранения номера месяца.
        string name; // Имя текущего сотрудника.
        vector<int> time; // Вектор для хранения времени начала и конца работы (часы и минуты).
        string current_line; // Временная строка для разбора текущей строки.
        stringstream file_ss(line); // Поток для обработки строки.
        short counter = 0; // Счетчик для отслеживания позиции текущего поля в строке.

        // Разделяем строку по разделителю ';' и обрабатываем данные.
        while (getline(file_ss, current_line, ';')) {
            if (counter == 0) {
                month = dateToMonth(current_line); // Получаем номер месяца из даты.
            }
            else if (counter == 1) {
                name = current_line; // Извлекаем имя сотрудника.
            }
            else if (counter == 2) {
                // Обработка времени начала работы.
                stringstream start_ss(current_line); // Поток для разбора времени.
                string current_time; // Временная строка для текущего времени.
                short time_counter = 0; // Счетчик для часов и минут.
                while (getline(start_ss, current_time, ':')) {
                    time.push_back(stoi(current_time)); // Преобразуем часы/минуты в целые числа и добавляем в вектор.
                    time_counter++;
                }
            }
            else if (counter == 3) {
                // Обработка времени окончания работы.
                stringstream end_ss(current_line); // Поток для разбора времени.
                string current_time; // Временная строка для текущего времени.
                short time_counter = 0; // Счетчик для часов и минут.
                while (getline(end_ss, current_time, ':')) {
                    time.push_back(stoi(current_time)); // Преобразуем часы/минуты в целые числа и добавляем в вектор.
                    time_counter++;
                }
            }
            counter++; // Переходим к следующему полю строки.
        }

        // Проверяем, есть ли уже запись для сотрудника.
        bool flag_1 = false; // Флаг, указывающий, найден ли сотрудник в текущем списке.

        for (int i = 0; i < result.size(); i++) {
            if (result[i].name == name) {
                flag_1 = true; // Указываем, что сотрудник уже существует.
                bool flag_2 = false; // Флаг для проверки наличия записи о месяце.

                for (short j = 0; j < result[i].work_time.size(); j++) {
                    if (result[i].work_time[j][0] == month) {
                        flag_2 = true; // Месяц найден, добавляем время к существующей записи.
                        result[i].work_time[j][1] += timeToMinute(time);
                    }
                }

                if (flag_2 == false) {
                    // Если месяца нет, добавляем новую запись с месяцем и временем.
                    result[i].work_time.push_back({ month, timeToMinute(time) });
                }
            }
        }

        if (flag_1 == false) {
            // Если сотрудник не найден, создаем новую структуру worker.
            worker current_worker;
            current_worker.name = name; // Устанавливаем имя сотрудника.
            current_worker.work_time = { {month, timeToMinute(time)} }; // Добавляем запись о месяце и времени.
            result.push_back(current_worker); // Добавляем сотрудника в список.
        }
    }

    return result; // Возвращаем заполненный вектор структур worker.
}



int main()
{
	return 0;
}
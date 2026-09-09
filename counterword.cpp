#include "count.h"           // подключаем все функции
#include <clocale>           // для setlocale (русский язык)
#include <sstream>           // для дополнительного ввода (не обязательно)
#include <string>

using namespace std;

// ---------- Вспомогательные функции для красивого вывода ----------

// Вывод результатов задания 1 (слово - счётчик)
void printCountResult(const map<string, int>& data) {
    for (const auto& entry : data) {
        cout << entry.first << " - " << entry.second << '\n';
    }
}

// Вывод результатов задания 2 (слово – позиция №1, позиция №2, …)
void printPositionResult(const vector<pair<string, vector<int>>>& data) {
    for (const auto& entry : data) {
        cout << entry.first << " – ";
        for (size_t i = 0; i < entry.second.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << entry.second[i];
        }
        cout << '\n';
    }
}

// Вывод вектора (для заданий 3–5)
void printVector(const vector<int>& v, const string& label = "") {
    if (!label.empty()) cout << label << ": ";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << v[i];
    }
    cout << '\n';
}

// Ввод вектора с клавиатуры (завершение по 0 или нечисловому символу)
vector<int> inputVector() {
    cout << "Введите целые числа через пробел (завершение – 0 или буква):\n";
    vector<int> vec;
    int x;
    while (cin >> x) {
        if (x == 0) break;
        vec.push_back(x);
    }
    cin.clear();                // сбрасываем флаг ошибки, если ввод был не числом
    cin.ignore(10000, '\n');    // очищаем буфер
    return vec;
}

// ====================== ГЛАВНАЯ ФУНКЦИЯ ======================
int main() {
    setlocale(LC_ALL, "Russian");   // поддержка русского языка в консоли

    cout << "============================================\n";
    cout << "   ЛАБОРАТОРНАЯ РАБОТА (все задания в одном)\n";
    cout << "============================================\n\n";

    cout << "Выберите задание:\n";
    cout << "1 - Подсчёт уникальных слов в файле\n";
    cout << "2 - Индексация позиций слов в файле\n";
    cout << "3 - Модификация простых чисел в векторе (возведение в квадрат)\n";
    cout << "4 - Сортировка: нечётные ↑, чётные ↓\n";
    cout << "5 - Поиск уникальных чисел в заданном диапазоне\n";
    cout << "Ваш выбор: ";
    int choice;
    cin >> choice;
    cin.ignore(10000, '\n');   // очищаем буфер после ввода числа

    // Обработка выбора
    switch (choice) {
    case 1: {
        cout << "Введите имя файла: ";
        string fname;
        getline(cin, fname);
        auto result = countUniqueWords(fname);
        if (result.empty()) {
            cerr << "Файл пуст или не найден.\n";
            return 1;
        }
        cout << "\nРезультат подсчёта:\n";
        printCountResult(result);
        break;
    }
    case 2: {
        cout << "Введите имя файла: ";
        string fname;
        getline(cin, fname);
        auto result = getWordPositions(fname);
        if (result.empty()) {
            cerr << "Файл пуст или не найден.\n";
            return 1;
        }
        cout << "\nПозиции слов:\n";
        printPositionResult(result);
        break;
    }
    case 3: {
        vector<int> v = inputVector();
        if (v.empty()) {
            cerr << "Вектор пуст. Завершение.\n";
            return 1;
        }
        modifyPrimes(v);
        cout << "\nРезультат (простые возведены в квадрат):\n";
        printVector(v);
        break;
    }
    case 4: {
        vector<int> v = inputVector();
        if (v.empty()) {
            cerr << "Вектор пуст. Завершение.\n";
            return 1;
        }
        vector<int> result = sortOddEven(v);
        cout << "\nРезультат сортировки (нечётные ↑, чётные ↓):\n";
        printVector(result);
        break;
    }
    case 5: {
        vector<int> v = inputVector();
        if (v.empty()) {
            cerr << "Вектор пуст. Завершение.\n";
            return 1;
        }
        int low, high;
        cout << "Введите нижнюю границу диапазона: ";
        cin >> low;
        cout << "Введите верхнюю границу диапазона: ";
        cin >> high;
        vector<int> result = uniqueInRange(v, low, high);
        cout << "\nУникальные числа в диапазоне [" << low << ", " << high << "]:\n";
        printVector(result);
        break;
    }
    default:
        cerr << "Неверный выбор.\n";
        return 1;
    }

    return 0;
}
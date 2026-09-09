#ifndef COUNT_H
#define COUNT_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cctype>      // isalnum, tolower
#include <algorithm>
#include <cmath>
#include <iterator>

using namespace std;

// ========================================================================
// ========== ЗАДАНИЕ 1: Подсчёт уникальных слов (регистронезависимый) ===
// Знаки препинания игнорируются, слова состоят только из букв и цифр.
// ========================================================================
map<string, int> countUniqueWords(const string& filename) {
    map<string, int> wordCount;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << '\n';
        return wordCount;
    }

    string currentWord;
    char ch;
    while (file.get(ch)) {
        unsigned char uc = static_cast<unsigned char>(ch);
        if (isalnum(uc)) {                     // буква или цифра – часть слова
            currentWord.push_back(ch);
        }
        else {
            if (!currentWord.empty()) {        // накопилось слово – обрабатываем
                // Приводим к нижнему регистру
                string lowerWord;
                for (char c : currentWord) {
                    lowerWord.push_back(tolower(static_cast<unsigned char>(c)));
                }
                ++wordCount[lowerWord];        // увеличиваем счётчик
                currentWord.clear();
            }
            // иначе разделитель – пропускаем
        }
    }
    // Обработка последнего слова, если файл не заканчивался разделителем
    if (!currentWord.empty()) {
        string lowerWord;
        for (char c : currentWord) {
            lowerWord.push_back(tolower(static_cast<unsigned char>(c)));
        }
        ++wordCount[lowerWord];
    }

    return wordCount;
}

// ========================================================================
// ========== ЗАДАНИЕ 2: Индексация позиций слов (регистронезависимый) ===
// Знаки препинания игнорируются, позиции нумеруются с 0.
// ========================================================================
vector<pair<string, vector<int>>> getWordPositions(const string& filename) {
    map<string, vector<int>> positions;
    vector<string> order;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << '\n';
        return {};
    }

    string currentWord;
    int wordIndex = 0;
    char ch;
    while (file.get(ch)) {
        unsigned char uc = static_cast<unsigned char>(ch);
        if (isalnum(uc)) {
            currentWord.push_back(ch);
        }
        else {
            if (!currentWord.empty()) {
                string lowerWord;
                for (char c : currentWord) {
                    lowerWord.push_back(tolower(static_cast<unsigned char>(c)));
                }
                if (positions.find(lowerWord) == positions.end()) {
                    order.push_back(lowerWord);
                }
                positions[lowerWord].push_back(wordIndex);
                currentWord.clear();
                ++wordIndex;
            }
        }
    }
    if (!currentWord.empty()) {
        string lowerWord;
        for (char c : currentWord) {
            lowerWord.push_back(tolower(static_cast<unsigned char>(c)));
        }
        if (positions.find(lowerWord) == positions.end()) {
            order.push_back(lowerWord);
        }
        positions[lowerWord].push_back(wordIndex);
    }

    vector<pair<string, vector<int>>> result;
    for (const string& w : order) {
        result.push_back({ w, positions[w] });
    }
    return result;
}

// ========================================================================
// ========== ЗАДАНИЕ 3 (a): Модификация элементов вектора ==========
// Все простые числа возводит в квадрат.
// ========================================================================
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    int limit = static_cast<int>(sqrt(n));
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

void modifyPrimes(vector<int>& vec) {
    for_each(vec.begin(), vec.end(), [](int& x) {
        if (isPrime(x)) x = x * x;
        });
}

// ========================================================================
// ========== ЗАДАНИЕ 4 (b): Сортировка по правилу ==========
// Сначала нечётные по возрастанию, затем чётные по убыванию.
// ========================================================================
vector<int> sortOddEven(const vector<int>& vec) {
    vector<int> result = vec;
    vector<int> odds, evens;
    copy_if(result.begin(), result.end(), back_inserter(odds), [](int x) { return x % 2 != 0; });
    copy_if(result.begin(), result.end(), back_inserter(evens), [](int x) { return x % 2 == 0; });
    sort(odds.begin(), odds.end());
    sort(evens.begin(), evens.end(), greater<int>());
    result.clear();
    result.insert(result.end(), odds.begin(), odds.end());
    result.insert(result.end(), evens.begin(), evens.end());
    return result;
}

// ========================================================================
// ========== ЗАДАНИЕ 5 (c): Поиск уникальных чисел в диапазоне ==========
// Возвращает уникальные числа из исходного вектора, попадающие в [low, high],
// сохраняя порядок первого появления.
// ========================================================================
vector<int> uniqueInRange(const vector<int>& vec, int low, int high) {
    vector<int> result;
    for (int x : vec) {
        if (x >= low && x <= high) {
            if (find(result.begin(), result.end(), x) == result.end()) {
                result.push_back(x);
            }
        }
    }
    return result;
}

#endif
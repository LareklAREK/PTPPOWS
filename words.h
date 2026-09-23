#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <set>

#include <chrono>

using namespace std;
//Приведение к ниинему регистру слова
inline string toLower(const string& src) {
    string s = src;
    for (auto& c : s) {
        unsigned char u = (unsigned char)c;
        if (u < 0x80)   c = (char)tolower(u);
        else if (u >= 0xC0 && u <= 0xDF)    c = (char)(u + 0x20);
        else if (u == 0xA8)                 c = (char)0xB8;
    }
    return s;
}

//Проверка что это буква 
inline bool isLetter(unsigned char c) {
    if (c < 0x80) return isalpha(c); 
    return c >= 0xC0 || c == 0xA8 || c == 0xB8;
}

// чтение файла
inline string readFile(const string& path) {
    ifstream in(path, ios::binary);
    if (!in) throw runtime_error("Не удалось открыть файл: " + path);
    stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

// 1 задание - подсчет слов в тексте
inline void countWords(const string& text, const string& outFile = "results1.txt") {
    auto startTime = chrono::high_resolution_clock::now();

    string s = toLower(text);
    map<string, int> counter;

    string word;
    for (size_t i = 0; i < s.size(); ) {
        unsigned char c = s[i];
        if (isLetter(c)) {
            word += s[i];
            i += 1;
        }
        else {
            if (!word.empty()) {
                counter[word]++;
                word.clear();
            }
            i++;
        }
    }
    if (!word.empty()) counter[word]++;

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;

    // перезаписываем файл результата при каждом запуске
    ofstream out(outFile, ios::trunc);
    if (!out) throw runtime_error("Не удалось создать файл: " + outFile);

    out << "Задание 1: подсчёт слов\n";
    out << "Время выполнения: " << elapsed.count() << " сек.\n";
    out << "Всего уникальных слов: " << counter.size() << "\n";
    out << "----------------------------------------\n";

    cout << "1 задание\n";
    cout << "Время выполнения: " << elapsed.count() << " сек.\n";

    for (auto& [w, n] : counter) {
        cout << w << " - " << n << '\n';
        out << w << " - " << n << '\n';
    }
    out.close();
    cout << "\nРезультат сохранён в " << outFile << "\n";
}

//2 задание - индексация позиций слов в тексте
inline void indexWords(const string& text, const string& outFile = "results2.txt") {
    auto startTime = chrono::high_resolution_clock::now();

    string s = toLower(text);
    map<string, vector<int>> index;
    int pos = 0;
    string word;

    for (size_t i = 0; i < s.size(); ) {
        unsigned char c = s[i];
        if (isLetter(c)) {
            word += s[i];
            i += 1;
        }
        else {
            if (!word.empty()) {
                index[word].push_back(pos);
                pos++;
                word.clear();
            }
            i++;
        }
    }
    if (!word.empty()) {
        index[word].push_back(pos);
        pos++;
    }

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;

    // перезаписываем файл результата при каждом запуске
    ofstream out(outFile, ios::trunc);
    if (!out) throw runtime_error("Не удалось создать файл: " + outFile);

    out << "Задание 2: индексация позиций слов\n";
    out << "Время выполнения: " << elapsed.count() << " сек.\n";
    out << "Всего слов (с повторами): " << pos << "\n";
    out << "Уникальных слов: " << index.size() << "\n";
    out << "----------------------------------------\n";

    cout << "2 задание\n";
    cout << "Время выполнения: " << elapsed.count() << " сек.\n";

    for (auto& [w, positions] : index) {
        cout << w << " -- ";
        out << w << " -- ";
        for (size_t k = 0; k < positions.size(); k++) {
            if (k > 0) { cout << ", "; out << ", "; }
            cout << positions[k];
            out << positions[k];
        }
        cout << '\n';
        out << '\n';
    }
    out.close();
    cout << "\nРезультат сохранён в " << outFile << "\n";
}
inline bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int d = 3; d * d <= n; d += 2)
        if (n % d == 0) return false;
    return true;
}

//Ввод вектора
inline vector<int> readIntVector() {
    int n;
    cout << "Сколько чисел введёте? ";
    cin >> n;

    vector<int> v(n);
    cout << "Введите " << n << " чисел через пробел: ";
    for (int i = 0; i < n; i++)
        cin >> v[i];
    return v;
}

//Печать вектора
inline void printVector(const vector<int>& v) {
    cout << "[ ";
    for (int x : v) cout << x << " ";
    cout << "]\n";
}

//Задание 3а - проверка на простоту и их возведение в квадрат
inline void task3a() {
    cout << "\nЗадание3a\n";

    vector<int> v = readIntVector();
    cout << "Исходный вектор:      ";
    printVector(v);

    transform(v.begin(), v.end(), v.begin(), [](int x) {
        return isPrime(x) ? x * x : x;
        });

    cout << "После преобразования: ";
    printVector(v);
}
//Задание 3б - четные и нечетные
inline void task3b() {
    cout << "\nЗадание3б\n";

    vector<int> v = readIntVector();
    cout << "Исходный вектор:   ";
    printVector(v);

    sort(v.begin(), v.end(), [](int a, int b) {
        bool aOdd = a % 2 != 0;
        bool bOdd = b % 2 != 0;
        if (aOdd != bOdd) return aOdd;   
        if (aOdd) return a < b;          
        return a > b;
        });

    cout << "Отсортированный:   ";
    printVector(v);
}

inline vector<int> findInRange(const vector<int>& v, int lo, int hi) {
    set<int> uniq;
    for (int x : v) {
        if (x >= lo && x <= hi)
            uniq.insert(x);
    }
    return vector<int>(uniq.begin(), uniq.end());
}
//Задание 3с - диапазон уникальных чисел
inline void task3c() {
    cout << "\nЗадание3с\n";

    vector<int> v = readIntVector();

    int lo, hi;
    cout << "Введите левую границу диапазона:  ";
    cin >> lo;
    cout << "Введите правую границу диапазона: ";
    cin >> hi;

    cout << "Исходный вектор:   ";
    printVector(v);

    vector<int> result = findInRange(v, lo, hi);
    cout << "Диапазон [" << lo << ", " << hi << "]\n";
    cout << "Уникальные числа:  ";
    printVector(result);
}
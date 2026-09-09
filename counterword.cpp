#include "count.h"
#include <clocale>   
using namespace std;

void printCountResults(const map<string, int>& data) {
    for (const auto& entry : data) {
        cout << entry.first << " - " << entry.second << '\n';
    }
}

void printPositionResults(const vector<pair<string, vector<int>>>& data) {
    for (const auto& entry : data) {
        cout << entry.first << " – ";
        for (size_t i = 0; i < entry.second.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << entry.second[i];
        }
        cout << '\n';
    }
}

int main() {
    setlocale(LC_ALL, "Russian");   
    cout << "Выберите задание:\n";
    cout << "1 - Подсчёт уникальных слов\n";
    cout << "2 - Индексация позиций слов\n";
    cout << "Ваш выбор: ";
    int choice;
    cin >> choice;
    cin.ignore();   
    cout << "Введите имя файла: ";
    string filename;
    getline(cin, filename);

    switch (choice) {
    case 1: {
        auto result = countUniqueWords(filename);
        if (result.empty()) {
            cerr << "Файл пуст или не найден.\n";
            return 1;
        }
        printCountResults(result);
        break;
    }
    case 2: {
        auto result = getWordPositions(filename);
        if (result.empty()) {
            cerr << "Файл пуст или не найден.\n";
            return 1;
        }
        printPositionResults(result);
        break;
    }
    default:
        cerr << "Неверный выбор.\n";
        return 1;
    }

    return 0;
}
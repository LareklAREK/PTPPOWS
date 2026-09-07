#include "count.h"
#include <clocale>
#include <iostream>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "");

    cout << "ֲגוהטעו טלÿ פאיכא: ";
    string filename;
    getline(cin, filename);

    auto result = countUniqueWords(filename);

    if (result.empty()) {

        return 1;
    }

    for (const auto& entry : result) {
        cout << entry.first << " - " << entry.second << '\n';
    }

    return 0;
}
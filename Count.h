#pragma once
#ifndef COUNT_H
#define COUNT_H

#include <fstream>   
#include <iostream>  
#include <map>      
#include <string>    
using namespace std;   
map<string, int> countUniqueWords(const string& filename) 
{
    map<string, int> wordCount;
    ifstream file(filename);

    if (!file.is_open()) 
    {
        cerr << "Ошибка: не удалось открыть файл " << filename << '\n';
        return wordCount;      
    }

    string word;
    while (file >> word) 
    {
        ++wordCount[word];      
    }

    return wordCount;
}

#endif
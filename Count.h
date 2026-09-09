#ifndef COUNT_H
#define COUNT_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cctype>   
using namespace std;

map<string, int> countUniqueWords(const string& filename) 
{
    map<string, int> wordCount;
    ifstream file(filename);
    if (!file.is_open()) {
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

vector<pair<string, vector<int>>> getWordPositions(const string& filename) 
{
    map<string, vector<int>> positions;       
    vector<string> order;                 
    ifstream file(filename);
    if (!file.is_open()) 
    {
        cerr << "Ошибка: не удалось открыть файл " << filename << '\n';
        return {};       
    }

    string currentWord;       int wordIndex = 0;    
    char ch;
    while (file.get(ch)) 
    {                             
        unsigned char uc = static_cast<unsigned char>(ch);           
        if (isalnum(uc)) 
        {   
            currentWord.push_back(ch);
        }
        else 
        {
            if (!currentWord.empty()) 
            {                                        
                string lowerWord;
                for (char c : currentWord) 
                {
                    lowerWord.push_back(tolower(static_cast<unsigned char>(c)));
                }
                
                if (positions.find(lowerWord) == positions.end()) 
                {
                    order.push_back(lowerWord);
                }
                                
                positions[lowerWord].push_back(wordIndex);

                currentWord.clear();                   
                ++wordIndex;                       
            }
                    
        }
    }
        if (!currentWord.empty()) 
        {
            string lowerWord;
            for (char c : currentWord) 
            {
                lowerWord.push_back(tolower(static_cast<unsigned char>(c)));
            }
            if (positions.find(lowerWord) == positions.end()) 
            {
                order.push_back(lowerWord);
            }
            
            positions[lowerWord].push_back(wordIndex); 
        }
        
        vector<pair<string, vector<int>>> result;
        for (const string& w : order) 
        {
            result.push_back({ w, positions[w] });
        }
    return result;
}

#endif
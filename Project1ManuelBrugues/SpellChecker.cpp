/*
    Program Name: SpellChecker.cpp
    Assignment: P8.2 Spell Checker
    Course: C++
    Team Members: Matthew Holm, Jenni Helvik, Manuel Brugues
    Description:
    This program reads a dictionary file and stores the words in a vector.
    Then it reads another file and prints all words that are not found
    in the dictionary.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;


//Converting a word to lowercase and removes punctuation.
string cleanWord(string word)
{
    string cleaned = "";

    for (unsigned char ch : word)
    {
        if (isalpha(ch))
        {
            cleaned += tolower(ch);
        }
    }

    return cleaned;
}

// Loading all dictionary words into a vector.
vector<string> loadDictionary(string dictionaryFile)
{
    vector<string> words;
    ifstream inputFile(dictionaryFile);
    string word;

    if (!inputFile)
    {
        cout << "Error: Could not open dictionary file." << endl;
        return words;
    }

    while (inputFile >> word)
    {
        words.push_back(cleanWord(word));
    }

    inputFile.close();
    return words;
}


//Cheaking if a word exists in the dictionary vector.
bool containsWord(const vector<string>& words, string word)
{
    for (string dictionaryWord : words)
    {
        if (dictionaryWord == word)
        {
            return true;
        }
    }

    return false;
}
//Cheaking the spelling of words in the input file.
void checkSpelling(string fileToCheck, const vector<string>& dictionary)
{
    ifstream inputFile(fileToCheck);
    string word;

    if (!inputFile)
    {
        cout << "Error: Could not open file to check." << endl;
        return;
    }

    cout << "Words not found in the dictionary:" << endl;

    while (inputFile >> word)
    {
        string cleanedWord = cleanWord(word);

        if (cleanedWord != "" && !containsWord(dictionary, cleanedWord))
        {
            cout << cleanedWord << endl;
        }
    }

    inputFile.close();
}

int main()
{
    string dictionaryFile;
    string fileToCheck;

    cout << "Enter the dictionary file name: ";
    cin >> dictionaryFile;

    cout << "Enter the file name to check: ";
    cin >> fileToCheck;

    vector<string> dictionary = loadDictionary(dictionaryFile);

    if (dictionary.size() == 0)
    {
        cout << "Dictionary is empty or could not be loaded." << endl;
        return 1;
    }

    checkSpelling(fileToCheck, dictionary);

    return 0;
}
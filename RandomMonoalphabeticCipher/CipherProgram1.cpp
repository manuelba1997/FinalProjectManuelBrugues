
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
//Change a normal letter to an encrypted letter using the coded alphabet
char encryptLetter(char letter, string codedAlphabet)
{
    string normalAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    bool isLower = islower(letter);

    char upperLetter = toupper(letter);

    int position = normalAlphabet.find(upperLetter);

    if (position == string::npos)
    {
        return letter;
    }

    char encryptedLetter = codedAlphabet[position];

    if (isLower)
    {
        encryptedLetter = tolower(encryptedLetter);
    }

    return encryptedLetter;
}

// change a coding letter to a normal letter using the coded alphabet
char decryptLetter(char letter, string codedAlphabet)
{
    string normalAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    bool isLower = islower(letter);

    char upperLetter = toupper(letter);

    int position = codedAlphabet.find(upperLetter);

    if (position == string::npos)
    {
        return letter;
    }

    char decryptedLetter = normalAlphabet[position];

    if (isLower)
    {
        decryptedLetter = tolower(decryptedLetter);
    }

    return decryptedLetter;
}

// Open the archive file and read it character by character, encrypting or decrypting each character and writing the result to the output file
void processFile(string inputFile, string outputFile, string codedAlphabet, bool decryptMode)
{
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile)
    {
        cout << "Error: Could not open input file." << endl;
        return;
    }

    if (!outFile)
    {
        cout << "Error: Could not open output file." << endl;
        return;
    }

    char ch;

    while (inFile.get(ch))
    {
        if (decryptMode)
        {
            outFile << decryptLetter(ch, codedAlphabet);
        }
        else
        {
            outFile << encryptLetter(ch, codedAlphabet);
        }
    }

    inFile.close();
    outFile.close();

    cout << "File processed successfully." << endl;
}
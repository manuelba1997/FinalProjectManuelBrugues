/*Program Name : CipherProgram.cpp
Assignment : P8.7 Random Monoalphabetic Cipher
Course : C++
Team Members : Matthew Holm, Jenni Helvik, Manuel Brugues

Description :
    This program encrypts and decrypts text files using a random monoalphabetic cipher.*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;


// Create a cipher alphabet based on the keyword and the normal alphabet

string createCipherAlphabet(string keyword)
{
    string normalAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string cipherAlphabet = "";

    // Paso 1: limpiar keyword (mayúsculas y sin duplicados)
    for (char ch : keyword)
    {
        char upper = toupper(ch);

        // Solo letras y que no se repitan
        if (isalpha(upper) && cipherAlphabet.find(upper) == string::npos)
        {
            cipherAlphabet += upper;
        }
    }

    // Paso 2: agregar letras restantes del alfabeto en orden inverso
    for (int i = normalAlphabet.length() - 1; i >= 0; i--)
    {
        char ch = normalAlphabet[i];

        if (cipherAlphabet.find(ch) == string::npos)
        {
            cipherAlphabet += ch;
        }
    }

    return cipherAlphabet;
}
 


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


int main()
{
    string keyword;
    string inputFile, outputFile;
    int choice;

    cout << "Enter keyword: ";
    cin >> keyword;

    string codedAlphabet = createCipherAlphabet(keyword);

    cout << "Enter input file name: ";
    cin >> inputFile;

    cout << "Enter output file name: ";
    cin >> outputFile;

    cout << "Enter 1 to encrypt, 2 to decrypt: ";
    cin >> choice;

    bool decryptMode = (choice == 2);

    processFile(inputFile, outputFile, codedAlphabet, decryptMode);

    return 0;
}
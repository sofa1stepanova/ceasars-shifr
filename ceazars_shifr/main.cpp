#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

void encryptWord(const char* original, char* encrypted, int key)
{
    const char* src = original;
    char* dst = encrypted;
    while (*src != '\0')
    {
        if (*src >= 'a' && *src <= 'z')
            *dst = (*src - 'a' + key) % 26 + 'a';
        else if (*src >= 'A' && *src <= 'Z')
            *dst = (*src - 'A' + key) % 26 + 'A';
        else
            *dst = *src;
        src++;
        dst++;
    }
    *dst = '\0';
}

void revealOneLetter(const char* original, char* encrypted)
{
    const char* o = original;
    char* e = encrypted;
    while (*o != '\0' && *e != '\0')
    {
        if (*o != *e)
        {
            *e = *o;
            return;
        }
        o++;
        e++;
    }
}

bool checkAnswer(const char* userGuess, const char* original, int& attempts)
{
    if (strcmp(userGuess, original) == 0)
        return true;
    attempts--;
    return false;
}

int main()
{
    srand((unsigned)time(0));
    int key = rand() % 5 + 1;

    char secret[] = "genius";
    char encrypted[32];
    encryptWord(secret, encrypted, key);

    cout << "encrypted word: " << encrypted << endl;
    cout << "key: " << key << endl;
    cout << "3 attempts. type 'hint' to open one letter" << endl;

    int attempts = 3;
    char guess[32];

    while (attempts > 0)
    {
        cout << "\nword: " << encrypted << endl;
        cout << "attempts left: " << attempts << endl;
        cout << "your guess: ";
        cin >> guess;

        if (strcmp(guess, "hint") == 0)
        {
            revealOneLetter(secret, encrypted);
            cout << "one letter opened" << endl;
            if (strcmp(secret, encrypted) == 0)
            {
                cout << "you win! word: " << secret << endl;
                return 0;
            }
            continue;
        }

        if (checkAnswer(guess, secret, attempts))
        {
            cout << "correct! you win!" << endl;
            return 0;
        }
        cout << "wrong" << endl;
    }

    cout << "\nno attempts left. word was: " << secret << endl;
    return 0;
}
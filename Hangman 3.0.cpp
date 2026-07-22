#include <iostream> // provides input/output functionality
#include <string>  //string used for handling text
#include <vector>  //stores similar datatype
#include <cstdlib> // random number generator and other utility functions 
#include <ctime>  //To seed random number generator with the current time

using namespace std;  //we can use name for objects and variable

void displayHangman(int attempts) //function for body of the hangman
{
    cout << "\nHangman Figure:" << endl;
    switch (attempts) 
    {
    case 6: cout << "  -----\n |     |\n |     \n |     \n |     \n |     \n |     \n-------\n"; break;  //single line
    case 5: cout << "  -----\n |     |\n |     O\n |     \n |     \n |     \n |     \n-------\n"; break; //face
    case 4: cout << "  -----\n |     |\n |     O\n |     |\n |     \n |     \n |     \n-------\n"; break; //again single line
    case 3: cout << "  -----\n |     |\n |     O\n |    /|\n |     \n |     \n |     \n-------\n"; break; //left hand
    case 2: cout << "  -----\n |     |\n |     O\n |    /|\\\n |     \n |     \n |     \n-------\n"; break; //right hand
    case 1: cout << "  -----\n |     |\n |     O\n |    /|\\\n |    / \n |     \n |     \n-------\n"; break; //left leg
    case 0: cout << "  -----\n |     |\n |     O\n |    /|\\\n |    / \\\n |     \n |     \n-------\n"; break; //right leg
    }
}

void displayWord(const string& word, const vector<bool>& guessed) //const string& word: This is the word player is trying to guess. It is a full word, with no hidden characters.
{                                                                 //const vector<bool>& guessed: This vector keeps the track of which letters in the word have been guessed correctly. If the word is guessed correctly it returns true if not so it returns false. 
    for (size_t i = 0; i < word.size(); i++) //It ensures that each character in the word is checked one by one.
    {
        if (guessed[i]) //if its true it means player has guessed the correct letter
        {
            cout << word[i] << " "; // and its print here
        }
        else 
        {
            cout << "_ "; //if its false so a underscore is printed to represent a hidden letter
        }
    }
    cout << endl;
}

bool checkWin(const vector<bool>& guessed) 
{
    for (bool b : guessed) //range based for loop: each element b in the loop represents whether the specific letter in the word has been correctly guessed
    {
        if (!b) // if the word is not correctly guessed it will return as false
        {
            return false;
        }
    }
    return true; // it will return true if the word is correctly guessed
}

int main() 
{
    const vector<string> wordList = { "nimbus", "crypto", "assassian", "quitar", "developer", "sapphire", "tundra" }; // wordlist hard coded in the program

    srand(time(0)); //This initializes the random no generator using current time. it ensures that each time the program runs it generate a different sequence of random numbers
    string word = wordList[rand() % wordList.size()]; // this will ensure to that the word will be selected from the wordlist only

    vector<bool> guessed(word.size(), false); //This line creates a vector guessed of type bool that tracks whether each letter in the word has been guessed correctly. It has the same size as the word (word.size()), and all values are initially set to false (indicating no letters have been guessed yet).
    int attempts = 6; // total attempts are 6
    char guess;
    vector<char> incorrectGuesses; //it will store incorrect guesses

    cout << "Welcome to Hangman!" << endl;

    while (attempts > 0) // it will run as long as the player has remaining guesses
    {
        displayHangman(attempts); // it will displays the representation of the hangman based on the attempts
        cout << "\nYou have " << attempts << " attempts left." << endl; //it will show how many atttempts are left
        displayWord(word, guessed); // it will display the current state of the word the player is trying to guess

        if (!incorrectGuesses.empty()) // this check if the incorrectguesses container is not empty. this is done to avoid printing "incorrect guesses, when there is no incorrect guess.
        {
            cout << "Incorrect guesses: "; //print this string
            for (char c : incorrectGuesses) //this loop iterates through eaxh character in the incorrectguesses collection and prints out each wrong letter.
            {
                cout << c << " "; //it will print the wrong guesses
            }
            cout << endl; //next line
        }

        cout << "Enter a letter: "; //string will be displayed on the console
        cin >> guess; //player will write the letter
        guess = tolower(guess);  //we don't want case-sensitivity in our program

        bool found = false; //if found remains false after the loop, it means the player's guess is correct
        for (size_t i = 0; i < word.size(); i++) //This line begins a for loop that will iterate through each letter of the string
        {
            if (word[i] == guess && !guessed[i]) //it gives to condition; the first condition checks whether the word matches the player's guess; the second condition checks whether the letter hasn't been guessed 
            {
                guessed[i] = true; //corrected letter will be printed
                found = true; //condition is true
            }
        }

        if (!found) //if found is false it means that player's guess is correct this line sets as false
        {
            cout << "Wrong guess!" << endl; //string will be printed
            incorrectGuesses.push_back(guess); //stores all the incorrect guesses that player has made 
            attempts--; //reduces attempts
        }

        if (checkWin(guessed)) 
        {
            cout << "\nCongratulations! You guessed the word: " << word << endl; //if the correct word is guessed
            break;
        }
    }

    if (attempts == 0) {
        cout << "\nGame over! The word was: " << word << endl; //if not the game is over
        displayHangman(attempts); //the hangman will be displayed 
    }

    return 0;
}
